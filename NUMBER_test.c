#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mulcal.h"

int main(){
	struct NUMBER b,c,d;
	int buf,i;

	srandom(time(NULL));
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);

	printf("b = ");
	dispNumberZeroSuppress(&b);
	printf(",isZero==%d\n",isZero(&b));
	printf("c = ");
	dispNumber(&c);
	putchar('\n');
	printf("d = ");
	dispNumber(&d);
	putchar('\n');

	/*
	b.n[0]=9;
	b.n[1]=1;
	b.n[2]=0;
	b.n[3]=1;
	b.sign=1;

	c.n[0]=3;
	c.n[1]=0;
	c.n[2]=1;
	c.n[3]=5;
	c.sign=-1;

	d.n[0]=5;
	d.n[1]=9;
	d.n[2]=2;
	d.n[3]=5;
	d.n[4]=7;
	d.n[5]=2;
	d.n[6]=4;
	d.n[7]=7;
	d.n[8]=0;
	d.n[9]=0;
	d.n[10]=7;
	d.n[11]=8;
	d.n[12]=2;
	d.n[13]=3;
	d.n[14]=3;
	d.n[15]=4;
	d.sign=1;
	*/

	setRnd(&b,5);
	setRnd(&c,10);
	getAbs(&c,&d);

	printf("b = ");
	dispNumberZeroSuppress(&b);
	printf(",isZero==%d\n",isZero(&b));
	printf("c = ");
	dispNumber(&c);
	putchar('\n');
	while(1){
		buf=mulBy10(&c,&d);
		copyNumber(&d,&c);
		printf("c = ");
		dispNumber(&c);
		printf(",overflow==%d\n",buf);
		if(buf){
			break;
		}
	}
	printf("d = ");
	dispNumber(&d);
	putchar('\n');
	for(i=0;i<20;i++){
		buf=divBy10(&c,&d);
		copyNumber(&d,&c);
		printf("d = ");
		dispNumber(&c);
		printf(",division==%d\n",buf);
	}
	putchar('\n');

	return 0;
}