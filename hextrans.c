//int型変数の内容を16進表示する

#include<stdio.h>

int main(int argc,char **argv){
	int x=-123456;	// -123456 = 0xfffe1dc0
	unsigned char *p;

	p=(unsigned char *)&x;
	printf("%02x %02x %02x %02x\n",*p,*(p+1),*(p+2),*(p+3));

	return 0;
}