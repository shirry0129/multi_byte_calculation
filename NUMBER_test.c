#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<sys/time.h>
#include"mulcal.h"

int main(){
	struct NUMBER a,b,c,d,e,f,g,one,sum;
	int r,x,y,z,i;
	struct timeval tv;
	double tstart,tend;

	srandom(time(NULL));

	gettimeofday(&tv,NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);
	clearByZero(&one);

	setRnd(&a,KETA);

	printf("phi = ");
	dispNumberZeroSuppress(&a);
	putchar('\n');

	gettimeofday(&tv,NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	printf("time:%f[s]\n",tend-tstart);

	return 0;
}