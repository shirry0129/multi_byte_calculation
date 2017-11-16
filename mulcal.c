#include"mulcal.h"
#include<stdio.h>
#include<stdlib.h>

void dispNumber(const struct NUMBER *a){
    int i;

	if(a->sign==1){
		printf(" +");
	}
	if(a->sign==-1){
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
	int i,rimit;

	clearByZero(a);

	if(k>KETA){
		rimit=KETA;
	}else{
		rimit=k;
	}

	for(i=0;i<rimit;i++){
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

int isZero(const struct NUMBER *a){
	int i;

	for(i=0;i<KETA;i++){
		if(a->n[i]){
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

	b->sign=a->sign;

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

	b->sign=a->sign;

	for(i=1;i<KETA;i++){
		b->n[i-1]=a->n[i];
	}
	b->n[KETA-1]=0;

	return ret;
}

void swap(struct NUMBER *a,struct NUMBER *b){
	struct NUMBER c;
	copyNumber(a,&c);
	copyNumber(b,a);
	copyNumber(&c,b);
}

int setInt(struct NUMBER *a,int x){
	int ret=0;
	int i;

	if(x<0){
		a->sign=-1;
		x*=-1;
	}else{
		a->sign=1;
	}

	for(i=0;i<KETA;i++){
		a->n[i]=x%10;
		x-=x%10;
		x/=10;
	}

	if(x){
		ret=-1;
	}

	return ret;
}

int getInt(struct NUMBER *a,int *x){

}

void diff(struct NUMBER *a,int x){
	int i,_x;
	struct NUMBER buf;

	_x=x;
	getAbs(a,&buf);
	if(_x<0){
		_x*=-1;
	}

	for(i=0;i<KETA;i++){
		if(buf.n[i]!=_x%10){
			printf("mismatched number.\n");
			printf("NUMBER = ");
			dispNumber(a);
			printf(", x = %20d\n",x);
			return;
		}
		_x-=_x%10;
		_x/=10;
	}

	if(a->sign==-1){
		if(!(x<0)){
			printf("mismatched sign.\n");
			printf("NUMBER = ");
			dispNumber(a);
			printf(", x = %20d\n",x);
			return;
		}
	}
	if(a->sign==1){
		if(x<0){
			printf("mismatched sign.\n");
			printf("NUMBER = ");
			dispNumber(a);
			printf(", x = %020d\n",x);
			return;
		}
	}
}