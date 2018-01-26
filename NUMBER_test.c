#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mulcal.h"

int main(){
	struct NUMBER a,b,c,d,e,f,g;
	int r,x,y,z,i;

	srandom(time(NULL));

	setInt(&a,123456);

	int_divide(&a,7,&c,&x);

	printf("a / b =");
	dispNumber(&c);
	putchar('\n');
	printf("a %% b = %d\n",x);

	diff(10e6);

	return 0;
}