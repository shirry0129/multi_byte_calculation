#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mulcal.h"

int main(){
	struct NUMBER a,b,c,d,e,f,g;
	int r,x,y,z,i;

	srandom(time(NULL));

	setInt(&a,123456);
	setInt(&b,2);

	divide(&a,&b,&c,&d);

	printf("a / b =");
	dispNumber(&c);
	putchar('\n');
	printf("a %% b =");
	dispNumber(&d);
	putchar('\n');

	//diff(10e6);

	return 0;
}