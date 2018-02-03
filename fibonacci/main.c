#include<stdio.h>
#include<sys/time.h>
#include"mulcal.h"
#include<stdlib.h>
#include<time.h>

int main(){
	struct NUMBER f1,f2,old_quo,quo,fbuf,buf,sum;
	int x,count=0;
	struct timeval tv;
	double tstart,tend;

	gettimeofday(&tv,NULL);
	tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	clearByZero(&f1);
	clearByZero(&f2);
	clearByZero(&old_quo);
	clearByZero(&quo);
	clearByZero(&buf);

	setInt(&f1,2);
	setInt(&f2,3);
	mulBy10n(&f2,(KETA-2)/2,&fbuf);
	divide(&fbuf,&f1,&old_quo,&buf);
	while(1){
		add(&f1,&f2,&sum);
		copyNumber(&f2,&f1);
		copyNumber(&sum,&f2);
		mulBy10n(&f2,(KETA-2)/2,&fbuf);
		divide(&fbuf,&f1,&quo,&buf);
		if(numComp(&quo,&old_quo)==0) break;
		copyNumber(&quo,&old_quo);
		count++;
	}

	printf("f1 = ");
	dispNumberZeroSuppress(&f1);
	putchar('\n');
	printf("f2 = ");
	dispNumberZeroSuppress(&f2);
	putchar('\n');
	printf("phi = ");ru
	dispNumberZeroSuppress(&quo);
	putchar('\n');
	printf("count = %d\n",count);

	gettimeofday(&tv,NULL);
	tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

	printf("time:%f[s]\n",tend-tstart);

	return 0;
}