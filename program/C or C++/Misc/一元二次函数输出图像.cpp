#include "stdio.h"
#include "math.h"
#include <stdlib.h>
#define N 235		//y��̶���������-MAX=835����������ʾ���䣺-999,999��
#define M 835		//x��̶���������-MAX=835����������ʾ���䣺-99 , 99��
#define X 1.0//x����С�̶�
#define Y 1.0//y����С�̶�
#define Z 1.0//������ʾ�̶�
#define D 1.0//����-����1/D����ȷС��λ����ע��D>=1,�ǵñ���һλС��-.0��
void out()
{int i;
 for(i=0;i<100;i++)
 putchar('\n');
}
void f();

int n,m;
int main()
{	puts("[��ȷ�ϴ���ȫ��]\n");
	system("pause");
	system("color F0");			//�������� 
	out(); 
	puts("��������� /һԪ���κ���/ ͼ�񡿡��Ƽ�ֵy=95,x=55��\n"); 
	printf("��������ʾy���������������MAX-%d����",N);
	scanf("%d",&n);
	printf("��������ʾx���������������MAX-%d����",M);
	scanf("%d",&m);
	while(1){	f();system("pause");
	system("color F0");		 
	out();}
}

void f()
{
	int i,j,t=1,data,date,xaos,yaos,x1,x2;
	char str[N][M];
	double a,b,c,d,s[M];			//s[]Ϊ����x�����ݵ�y������
	double x,y;			//aos�Գ���
	puts("\n\n������������ġ�һԪ���κ�������\n");
	puts("��ʽ��ax^2+bx+c=y\n");
	printf("a=��");
	scanf("%lf", &a);
	
	if(a>0)t=0,data=1;							
	else if(a<0) t=1,data=-1;
    else{puts("a<0!");return ;}
    
	printf("b=��");
	scanf("%lf", &b);
	printf("c=��");
	scanf("%lf", &c);
	puts("\n\n");
	printf("    ");	for(i=0;i<m;i++) printf("--+");	printf("--\n    ");//����
	puts("�뽫��Ļ��������ʾ��������\n");
	system("pause");

//----------------------------------------------------------------------

	x=-b/(2*a),y=(4*a*c-b*b)/4*a;		//x,y��ƫ��ֵ��-b/2a��4ac-b^2/4a��
	x/=Y,y/=X;											//���㶥������Ķ�Ӧֵ

	for(i=0,d=-(m/2*X);i<m;i++,d+=X)
	s[i]=data*a*d*d,s[i]=(int)(s[i]*D)/D,s[i]/=Y;

	if (t) xaos=-y;
	else xaos=n-1-y;
	yaos=m/2-x;						//x��=-y,y��=-x
	
	//printf("xaos=%.2lf,yaos=%.2lf\n",xaos,yaos);
//----------------------------------------------------------------------
	for(i=0;i<n;i++)							//�������� 
	for(j=0;j<m;j++)
	if(j==yaos&&i==xaos) str[i][j]='+';
	else if(j==yaos) str[i][j]='|';
	else if(i==xaos) str[i][j]='-';
	else str[i][j]=' ';

  if(t)	i=d=0,data=-1;					//��������,data=-1
	else	i=d=n-1,data=1;				//��������,data= 1

	if(a<1&&a>-1) date=fabs(1/a);
	else date=1; 

			for(x1=x2=m/2;i<n&&i>=0;i-=data)
			 {
		 	 if(abs(i-(int)d)==s[x1])		//�ж�������Ƿ�Ϊ����
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
	//for(i=0;i<M;i++)	printf("%.2lf ",s[i]);	putchar('\n'); //���s[]����ֵ
	
	for(i=0,d=xaos;i<n;i++,d--)		//���ͼ��
	{
	printf("%4d+",t=(int)d%1000);						//�޶����y��̶��������Ϊ��-999��999��
	for(j=0;j<m;j++)
	printf("  %c",str[i][j]);
	putchar('\n');
	}
	//-------------------------------------------------
	printf("     ");	for(i=0;i<m;i++) printf("--+");	printf("--\n     ");//����
	for(i=0,d=-yaos;i<m;i++,d++) //���X������
	printf("%3d",t=(int)d%100);						//�޶����x��̶��������Ϊ��-99��99��
	//-------------------------------------------------

	printf("\n\nx��=%.2f/ÿ����\ty��=%.2f/ÿ����\t����=%.4lf\n",X,Y,1/D);
	printf("\n����Ϊ��%.2fx^2+%.2fx+%.2f\n",a,b,c);
	printf("\n�������꣺��%.2f,%.2f��\n",-x*Y,-y*X);

}
