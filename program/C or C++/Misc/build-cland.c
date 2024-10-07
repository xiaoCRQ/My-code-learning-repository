#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILE "gcc_path.txt"
#define GCC "gcc.exe"
#define GPP "g++.exe"
#define CLANGD_TEMPLATE                                                        \
  "CompileFlags:\n\
  Add:\n\
    - \"-Wall\"         # 启用所有常见警告\n\
    - \"-fuse-ld=lld\" # 使用LLVM的lld连接器\n\
    - \"--target=x86_64-pc-windows-gnu\" # 使用 MinGW 目标\n\
    - \"-I%s/x86_64-w64-mingw32/include\" # MinGW 的头文件路径\n\
\n\
InlayHints:\n\
  BlockEnd: No\n\
  Designators: No\n\
  Enabled: No\n\
  ParameterNames: No\n\
  DeducedTypes: No\n\
  TypeNameLimit: 24\n"
#define CLANGD_STYLE                                                           \
  "--- \n\
# We'll use defaults from the LLVM style, but with 4 columns indentation.\n\
BasedOnStyle: LLVM\n\
IndentWidth: 2\n\
---\n\
Language: Cpp\n\
# Force pointers to the type for C++.\n\
# DerivePointerAlignment: false\n\
# PointerAlignment: Left\n\
# BinPackParameters: false\n\
# BraceWrapping:\n\
#   AfterFunction: false\n\
#   AfterControlStatement: true\n\
---\n\
"

void str_del(char *gcc_path) {
  char *mingw_bin = gcc_path;
  while (*mingw_bin) {
    if (*mingw_bin == '\\')
      *mingw_bin = '/';
    mingw_bin++;
  }
  mingw_bin = strrchr(gcc_path, '/'); // 找到最后一个反斜杠
  if (mingw_bin != NULL) {
    *mingw_bin = '\0';                  // 移除 bin 路径部分
    mingw_bin = strrchr(gcc_path, '/'); // 再找一次，得到 MinGW 根目录
    if (mingw_bin != NULL) {
      *mingw_bin = '\0'; // 移除 gcc 之前的路径，得到 MinGW 安装目录
    } else {
      fprintf(stderr, "Error: Unable to determine MinGW path.\n");
      exit(1);
    }
  } else {
    fprintf(stderr, "Error: Invalid gcc path format.\n");
    exit(1);
  }
}

int main() {
  char mingw_path[512];

  // 使用 where 命令查找 gcc
  if (system("where gcc > gcc_path.txt 2>&1"))
    return 1;

  FILE *file = fopen(TEMP_FILE, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: Unable to find gcc in PATH.\n");
    exit(1);
  }

  if (fgets(mingw_path, sizeof(mingw_path), file) == NULL) {
    fprintf(stderr, "Error: gcc or g++ not found in PATH.\n");
    fclose(file);
    // 删除临时文件
    remove(TEMP_FILE);
    exit(1);
  }
  fclose(file);

  // 删除临时文件
  remove(TEMP_FILE);

  str_del(mingw_path);
  puts(mingw_path);

  // 创建 .clangd 文件
  file = fopen(".clangd", "w");
  if (file == NULL) {
    fprintf(stderr, "Error: Unable to create .clangd file.\n");
    return 1;
  }
  fprintf(file, CLANGD_TEMPLATE, mingw_path);

  // 创建 .clangd 文件
  file = fopen(".clang-format", "w");
  if (file == NULL) {
    fprintf(stderr, "Error: Unable to create .clang-format file.\n");
    return 1;
  }
  fprintf(file, CLANGD_STYLE);

  fclose(file);
  return 0;
}
