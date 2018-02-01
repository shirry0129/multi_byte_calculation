#include<stdio.h>
#include<sys/time.h>
#include"mulcal.h"
#include<stdlib.h>
#include<time.h>

int main(){
	struct NUMBER a,b,c,d,e,one,sum;
	int x,y,z,r,i;
	struct timeval tv;
	double tstart,tend;

	gettimeofday(&tv,NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	clearByZero(&e);
	clearByZero(&one);

	srandom(time(NULL));

	// setInt(&a,6499525);
	// setInt(&b,3269407);
	// divide(&a,&b,&c,&d);

	// printf("%d\n",6499525/3269407);
	// dispNumberZeroSuppress(&c);

	// for(i=0;i<10e3;i++){
	// 	clearByZero(&c);
	// 	clearByZero(&d);

	// 	x=random()%10000000;
	// 	y=random()%10000000+1;
	// 	setInt(&a,x);
	// 	setInt(&b,y);
	// 	r=divide(&a,&b,&c,&d);
	// 	getInt(&c,&z);

	// 	if(!r){
	// 		if(x/y!=z){
	// 			printf("mismatched. %d\n",i);
	// 			printf("x = %d,y = %d,x / y =%d\n",x,y,x/y);
	// 			printf("a = ");
	// 			dispNumberZeroSuppress(&a);
	// 			printf("\nb = ");
	// 			dispNumberZeroSuppress(&b);
	// 			printf("\na / b =");
	// 			dispNumberZeroSuppress(&c);
	// 		}
	// 	}
	// }

	setInt(&a,5);
	setInt(&e,1);
	mulBy10n(&a,KETA-2,&b);
	mulBy10n(&e,(KETA-2)/2,&one);
	sqrt_newton(&b,&c);
	add(&one,&c,&sum);
	int_divide(&sum,2,&d,&x);

	printf("phi = ");
	dispNumberZeroSuppress(&d);
	putchar('\n');

	gettimeofday(&tv,NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	printf("time:%f[s]\n",tend-tstart);

	return 0;
}