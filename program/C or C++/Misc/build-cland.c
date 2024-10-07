#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILE "gcc_path.txt"
#define GCC "gcc.exe"
#define GPP "g++.exe"
#define CLANGD_TEMPLATE                                                        \
  "CompileFlags:\n\
  Add:\n\
    - \"-Wall\"         # �������г�������\n\
    - \"-fuse-ld=lld\" # ʹ��LLVM��lld������\n\
    - \"--target=x86_64-pc-windows-gnu\" # ʹ�� MinGW Ŀ��\n\
    - \"-I%s/x86_64-w64-mingw32/include\" # MinGW ��ͷ�ļ�·��\n\
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
  mingw_bin = strrchr(gcc_path, '/'); // �ҵ����һ����б��
  if (mingw_bin != NULL) {
    *mingw_bin = '\0';                  // �Ƴ� bin ·������
    mingw_bin = strrchr(gcc_path, '/'); // ����һ�Σ��õ� MinGW ��Ŀ¼
    if (mingw_bin != NULL) {
      *mingw_bin = '\0'; // �Ƴ� gcc ֮ǰ��·�����õ� MinGW ��װĿ¼
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

  // ʹ�� where ������� gcc
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
    // ɾ����ʱ�ļ�
    remove(TEMP_FILE);
    exit(1);
  }
  fclose(file);

  // ɾ����ʱ�ļ�
  remove(TEMP_FILE);

  str_del(mingw_path);
  puts(mingw_path);

  // ���� .clangd �ļ�
  file = fopen(".clangd", "w");
  if (file == NULL) {
    fprintf(stderr, "Error: Unable to create .clangd file.\n");
    return 1;
  }
  fprintf(file, CLANGD_TEMPLATE, mingw_path);

  // ���� .clangd �ļ�
  file = fopen(".clang-format", "w");
  if (file == NULL) {
    fprintf(stderr, "Error: Unable to create .clang-format file.\n");
    return 1;
  }
  fprintf(file, CLANGD_STYLE);

  fclose(file);
  return 0;
}
