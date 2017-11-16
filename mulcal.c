#include"mulcal.h"
#include<stdio.h>
#include<stdlib.h>

void dispNumber(struct NUMBER *a){
    int i;

	if(a->sign==1){
		printf(" +");
	}
	else if(a->sign==-1){
		printf(" -");
	}

	for(i=KETA-1;i>=0;i--){
		printf("%2d",a->n[i]);
	}
}

void dispNumberZeroSuppress(struct NUMBER *a){
	int i=KETA-1;

	if(a->sign==1){
		printf(" +");
	}
	else if(a->sign==-1){
		printf(" -");
	}

	while(!a->n[i]&&i>0){
		i--;
	}

	for(;i>=0;i--){
		printf("%2d",a->n[i]);
	}
}

void clearByZero(struct NUMBER *a){
	int i;

	for(i=0;i<KETA;i++){
		a->n[i]=0;
	}

	a->sign=1;
}

void setRnd(struct NUMBER *a,int k){
	int i;

	clearByZero(a);

	for(i=0;i<k;i++){
		a->n[i]=random()%10;
	}

	if(random()%2){
		a->sign=1;
	}else{
		a->sign=-1;
	}
}

void copyNumber(struct NUMBER *a,struct NUMBER *b){
	int i;
	
	for(i=0;i<KETA;i++){
		b->n[i]=a->n[i];
	}

	b->sign=a->sign;
}

void getAbs(struct NUMBER *a,struct NUMBER *b){
	copyNumber(a,b);
	b->sign=1;
}

int isZero(struct NUMBER *a){
	struct NUMBER buf;
	int i;

	getAbs(a,&buf);

	for(i=0;i<KETA;i++){
		if(buf.n[i]){
			return -1;
		}
	}

	return 0;
}

int mulBy10(struct NUMBER *a,struct NUMBER *b){
	int ret=0;
	int i;

	if(a->n[KETA-1]){
		ret=-1;
	}

	for(i=0;i<KETA-1;i++){
		b->n[i+1]=a->n[i];
	}
	b->n[0]=0;

	return ret;
}

int divBy10(struct NUMBER *a,struct NUMBER *b){
	int ret;
	int i;

	if(a->sign==1){
		ret=a->n[0];
	}
	else if(a->sign==-1){
		ret=-a->n[0];
	}

	for(i=1;i<KETA;i++){
		b->n[i-1]=a->n[i];
	}
	b->n[KETA-1]=0;

	return ret;
}

void swap(struct NUMBER *a,struct NUMBER *b){
	struct NUMBER c;
	copyNumber(c,a);
	copyNumber(a,b);
	copyNumber(b,c);
}

int setInt(struct NUMBER *a,int x){
	int ret=0;

	if(x<0){
		a->sign=-1;
		x*=-1;
	}else{
		a->sign=1;
	}

	if(KETA<10){
		ret=-1;
	}
}