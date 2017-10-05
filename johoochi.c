//情報落ちのプログラム

#include<stdio.h>

int main(int argc,char **argv){
	float a=1.23456e10;	//12345600000.0
	float b=7.89012e-3;	//					0.00789012
	float c=7.89012e2;	//				789.012
	float d,e;

	d=a+b;
	e=a+c;

	printf("a = %25.10f\n", a);
	printf("b = %25.10f\n", b);
	printf("c = %25.10f\n", c);
	printf("a + b = %25.10f\n", d);
	printf("a + c = %25.10f\n", e);

	return 0;
}