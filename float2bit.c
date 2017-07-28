//float型変数の内容を16進/2進表示する

#include<stdio.h>

void printbit(unsigned char *_p){
	int i;
	int binary[8];

	unsigned char p=*_p;
	for(i=7;i>=0;i--){
		binary[i]=p%2;
		p=p/2;
	}
	for(i=0;i<8;i++){
		printf("%d",binary[i]);
	}

	putchar(' ');
}

int main(int argc,char **argv){
	float x=-3.14159;	// -3.14159 = 0xc0490fd0
	unsigned char *p;
	int i;

	p=(unsigned char *)&x;
	printf("%d\n",x);
	printf("%02x %02x %02x %02x\n",*p,*(p+1),*(p+2),*(p+3));
	for(i=0;i<4;i++){
		printbit(p+i);
	}
	putchar('\n');

	return 0;
}