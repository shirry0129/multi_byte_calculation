#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mulcal.h"

int main(){
	struct NUMBER a,b,c,d,e,f,g;
	int r,x,y,i;

	srandom(time(NULL));

	clearByZero(&a);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');

	setRnd(&b,10);
	printf("b = ");
	dispNumber(&b);
	putchar('\n');

	copyNumber(&b,&c);
	printf("c = ");
	dispNumber(&c);
	putchar('\n');

	r = mulBy10(&b,&d);
	printf("b * 10 = ");
	dispNumber(&d);
	printf(", r = %d\n",r);

	r = divBy10(&c,&e);
	printf("c / 10 = ");
	dispNumber(&e);
	printf(", r = %d\n",r);

	printf("a == 0? --> %d\n",isZero(&a));
	printf("b == 0? --> %d\n",isZero(&b));
	printf("c == 0? --> %d\n",isZero(&c));
	printf("d == 0? --> %d\n",isZero(&d));
	printf("e == 0? --> %d\n",isZero(&e));

	swap(&a,&b);
	printf("a = ");
	dispNumber(&a);
	putchar('\n');
	printf("b = ");
	dispNumber(&b);

	putchar('\n');
	x=-1234567890;
	r = setInt(&f,x);
	printf("f = ");
	dispNumber(&f);
	printf(", r = %d\n",r);

	/*putchar('\n');
	for(i=0;i<10e6;i++){
		x=random()-RAND_MAX/2;
		setInt(&f,x);
		diff(&f,x);
	}*/

	putchar('\n');
	setRnd(&f,10);
	printf("f = ");
	dispNumber(&f);
	putchar('\n');
	setSign(&f,1);
	printf("f = ");
	dispNumber(&f);

	putchar('\n');
	setRnd(&g,10);
	printf("g = ");
	dispNumber(&g);
	printf(", sign = %d\n",getSign(&g));

	putchar('\n');
	r = getInt(&f,&y);
	printf("x = %d, y = %d, r = %d\n",x,y,r);

	return 0;
}