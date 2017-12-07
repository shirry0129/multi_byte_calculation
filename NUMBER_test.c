#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mulcal.h"

int main(){
	struct NUMBER a,b,c,d,e,f,g;
	int r,x,y,z,i;

	srandom(time(NULL));

	// clearByZero(&a);
	// printf("a = ");
	// dispNumber(&a);
	// putchar('\n');

	// setRnd(&b,10);
	// printf("b = ");
	// dispNumber(&b);
	// putchar('\n');

	// copyNumber(&b,&c);
	// printf("c = ");
	// dispNumber(&c);
	// putchar('\n');

	// r = mulBy10(&b,&d);
	// printf("b * 10 = ");
	// dispNumber(&d);
	// printf(", r = %d\n",r);

	// r = divBy10(&c,&e);
	// printf("c / 10 = ");
	// dispNumber(&e);
	// printf(", r = %d\n",r);

	// printf("a == 0? --> %d\n",isZero(&a));
	// printf("b == 0? --> %d\n",isZero(&b));
	// printf("c == 0? --> %d\n",isZero(&c));
	// printf("d == 0? --> %d\n",isZero(&d));
	// printf("e == 0? --> %d\n",isZero(&e));

	// swap(&a,&b);
	// printf("a = ");
	// dispNumber(&a);
	// putchar('\n');
	// printf("b = ");
	// dispNumber(&b);
	// putchar('\n');

	// setInt(&a,-12345);
	// printf("a = ");
	// dispNumber(&a);
	// putchar('\n');

	// copyNumber(&a,&b);
	// setSign(&b,1);
	// printf("b = ");
	// dispNumber(&b);
	// putchar('\n');

	// r=getSign(&b);
	// printf("getSign() = %d\n",r);

	// r=numComp(&a,&b);
	// printf("numComp() = %d\n",r);

	//putchar('\n');
	setInt(&a,-100);
	setInt(&b,-500);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');
	printf("b = ");
	dispNumber(&b);
	putchar('\n');
	r=add(&a,&b,&c);
	printf("a + b = ");
	dispNumber(&c);
	printf(", r = %d\n",r);

	//diff(10e6);

	putchar('\n');
	setInt(&a,-100);
	setInt(&b,-50);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');
	printf("b = ");
	dispNumber(&b);
	putchar('\n');
	r=sub(&a,&b,&c);
	printf("a - b = ");
	dispNumber(&c);
	printf(", r = %d\n",r);

	putchar('\n');
	setInt(&a,10e10);
	r=0;
	while(!r){
		r=increment(&a,&b);
		swap(&a,&b);
	}

	//diff(10e6);
	
	return 0;
}