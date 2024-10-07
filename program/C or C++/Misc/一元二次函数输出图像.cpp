#include "stdio.h"
#include "math.h"
#include <stdlib.h>
#define N 235		//y轴刻度数【奇数-MAX=835】【正常显示区间：-999,999】
#define M 835		//x轴刻度数【奇数-MAX=835】【正常显示区间：-99 , 99】
#define X 1.0//x轴最小刻度
#define Y 1.0//y轴最小刻度
#define Z 1.0//轴线显示刻度
#define D 1.0//精度-例：1/D【精确小数位】【注：D>=1,记得保留一位小数-.0】
void out()
{int i;
 for(i=0;i<100;i++)
 putchar('\n');
}
void f();

int n,m;
int main()
{	puts("[请确认窗口全屏]\n");
	system("pause");
	system("color F0");			//窗口亮白 
	out(); 
	puts("【输入输出 /一元二次函数/ 图像】【推荐值y=95,x=55】\n"); 
	printf("请输入显示y轴刻数【奇数】【MAX-%d】：",N);
	scanf("%d",&n);
	printf("请输入显示x轴刻数【奇数】【MAX-%d】：",M);
	scanf("%d",&m);
	while(1){	f();system("pause");
	system("color F0");		 
	out();}
}

void f()
{
	int i,j,t=1,data,date,xaos,yaos,x1,x2;
	char str[N][M];
	double a,b,c,d,s[M];			//s[]为各个x轴数据的y轴坐标
	double x,y;			//aos对称轴
	puts("\n\n请输入需输出的【一元二次函数】：\n");
	puts("格式：ax^2+bx+c=y\n");
	printf("a=：");
	scanf("%lf", &a);
	
	if(a>0)t=0,data=1;							
	else if(a<0) t=1,data=-1;
    else{puts("a<0!");return ;}
    
	printf("b=：");
	scanf("%lf", &b);
	printf("c=：");
	scanf("%lf", &c);
	puts("\n\n");
	printf("    ");	for(i=0;i<m;i++) printf("--+");	printf("--\n    ");//横线
	puts("请将屏幕缩放至显示完整横线\n");
	system("pause");

//----------------------------------------------------------------------

	x=-b/(2*a),y=(4*a*c-b*b)/4*a;		//x,y的偏移值（-b/2a，4ac-b^2/4a）
	x/=Y,y/=X;											//计算顶点坐标的对应值

	for(i=0,d=-(m/2*X);i<m;i++,d+=X)
	s[i]=data*a*d*d,s[i]=(int)(s[i]*D)/D,s[i]/=Y;

	if (t) xaos=-y;
	else xaos=n-1-y;
	yaos=m/2-x;						//x轴=-y,y轴=-x
	
	//printf("xaos=%.2lf,yaos=%.2lf\n",xaos,yaos);
//----------------------------------------------------------------------
	for(i=0;i<n;i++)							//开口向下 
	for(j=0;j<m;j++)
	if(j==yaos&&i==xaos) str[i][j]='+';
	else if(j==yaos) str[i][j]='|';
	else if(i==xaos) str[i][j]='-';
	else str[i][j]=' ';

  if(t)	i=d=0,data=-1;					//开口向下,data=-1
	else	i=d=n-1,data=1;				//开口向上,data= 1

	if(a<1&&a>-1) date=fabs(1/a);
	else date=1; 

			for(x1=x2=m/2;i<n&&i>=0;i-=data)
			 {
		 	 if(abs(i-(int)d)==s[x1])		//判断这个点是否为定点
				{
					str[i][x1]='*',str[i][x2]='*',x1-=data,x2+=data;
					for(;s[x1]==abs(i-(int)d);x1-=data,x2+=data)
					str[i][x1]='-',str[i][x2]='-';
					str[i][x1+data]='*',str[i][x2-data]='*';
				}
			 else str[i][x1]='I',str[i][x2]='I';
			 }
//----------------------------------------------------------------------


	//---------------------------------------------------------
	//for(i=0;i<M;i++)	printf("%.2lf ",s[i]);	putchar('\n'); //输出s[]的数值
	
	for(i=0,d=xaos;i<n;i++,d--)		//输出图像
	{
	printf("%4d+",t=(int)d%1000);						//限定输出y轴刻度最大区间为【-999，999】
	for(j=0;j<m;j++)
	printf("  %c",str[i][j]);
	putchar('\n');
	}
	//-------------------------------------------------
	printf("     ");	for(i=0;i<m;i++) printf("--+");	printf("--\n     ");//横线
	for(i=0,d=-yaos;i<m;i++,d++) //输出X轴坐标
	printf("%3d",t=(int)d%100);						//限定输出x轴刻度最大区间为【-99，99】
	//-------------------------------------------------

	printf("\n\nx轴=%.2f/每像素\ty轴=%.2f/每像素\t精度=%.4lf\n",X,Y,1/D);
	printf("\n方程为：%.2fx^2+%.2fx+%.2f\n",a,b,c);
	printf("\n顶点坐标：【%.2f,%.2f】\n",-x*Y,-y*X);

}
