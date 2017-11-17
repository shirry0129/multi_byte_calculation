#include"mulcal.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void dispNumber(const struct NUMBER *a){
    int i;

	if(getSign(a)==1){
		printf(" +");
	}
	if(getSign(a)==-1){
		printf(" -");
	}

	for(i=KETA-1;i>=0;i--){
		printf("%2d",a->n[i]);
	}
}

void dispNumberZeroSuppress(struct NUMBER *a){
	int i=KETA-1;

	if(getSign(a)==1){
		printf(" +");
	}
	if(getSign(a)==-1){
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

	setSign(a,1);
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
		setSign(a,1);
	}else{
		setSign(a,-1);
	}
}

void copyNumber(struct NUMBER *a,struct NUMBER *b){
	int i;
	
	for(i=0;i<KETA;i++){
		b->n[i]=a->n[i];
	}

	setSign(b,getSign(a));
}

void getAbs(struct NUMBER *a,struct NUMBER *b){
	copyNumber(a,b);
	setSign(b,1);
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

	setSign(b,getSign(a));

	for(i=0;i<KETA-1;i++){
		b->n[i+1]=a->n[i];
	}
	b->n[0]=0;

	return ret;
}

int divBy10(struct NUMBER *a,struct NUMBER *b){
	int ret;
	int i;

	if(getSign(a)==1){
		ret=a->n[0];
	}
	if(getSign(a)==-1){
		ret=-a->n[0];
	}

	setSign(b,getSign(a));

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
		setSign(a,-1);
		for(i=0;i<KETA;i++){
			a->n[i]=(x%10)*-1;
			x-=x%10;
			x/=10;
		}
	}else{
		setSign(a,1);
		for(i=0;i<KETA;i++){
			a->n[i]=x%10;
			x-=x%10;
			x/=10;
		}
	}

	if(x){
		ret=-1;
	}

	return ret;
}

int getInt(struct NUMBER *a,int *x){
	int digits_decide=1;
	int i,ret=0;
	int limit=10;
	struct NUMBER int_max,int_min;

	setInt(&int_max,INT_MAX);
	setInt(&int_min,INT_MIN);

	if(numComp(a,&INT_MAX)==1||numComp(a,&INT_MIN)==-1){
		ret=-1;
	}

	if(KETA<10){
		limit=KETA;
	}

	*x=0;

	for(i=0;i<limit;i++){
		*x+=a->n[i]*digits_decide;
		digits_decide*=10;
	}

	return ret;
}

void setSign(struct NUMBER *a,int s){
	if(!isZero(a)){
		a->sign=1;
		return;
	}

	a->sign=s;
}

int getSign(const struct NUMBER *a){
	return a->sign;
}

int numComp(struct NUMBER *a,struct NUMBER *b){
	int i;

	if(getSign(a)>getSign(b)){
		return 1;
	}
	if(getSign(a)<getSign(b)){
		return -1;
	}

	if(getSign(a)==1&&getSign(b)==1){
		for(i=KETA-1;i>=0;i--){
			if(a->n[i]>b->n[i]){
				return 1;
			}
			if(a->n[i]<b->n[i]){
				return -1;
			}
		}

		return 0;
	}

	if(getSign(a)==-1&&getSign(b)==-1){
		for(i=KETA-1;i>=0;i--){
			if(a->n[i]>b->n[i]){
				return -1;
			}
			if(a->n[i]<b->n[i]){
				return 1;
			}
		}

		return 0;
	}
}

void setInt_diff(struct NUMBER *a,int x){
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

	if(getSign(a)==-1){
		if(!(x<0)){
			printf("mismatched sign.\n");
			printf("NUMBER = ");
			dispNumber(a);
			printf(", x = %20d\n",x);
			return;
		}
	}
	if(getSign(a)==1){
		if(x<0){
			printf("mismatched sign.\n");
			printf("NUMBER = ");
			dispNumber(a);
			printf(", x = %020d\n",x);
			return;
		}
	}
}

void numComp_diff(int sl,int x,int y){
	switch (sl){
	case 1:
		if(!(x>y)){
			printf("mismatched.\n");
			printf("x = %d, y = %d\n",x,y);
		}
		break;
	case 0:
		if(!(x==y)){
			printf("mismatched.\n");
			printf("x = %d, y = %d\n",x,y);
		}
		break;
	case -1:
		if(!(x<y)){
			printf("mismatched.\n");
			printf("x = %d, y = %d\n",x,y);
		}
		break;
	default:
		break;
	}
}