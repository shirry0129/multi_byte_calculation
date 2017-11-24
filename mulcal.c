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
	int i;
	int limit=10;
	struct NUMBER int_max,int_min;

	setInt(&int_max,INT_MAX);
	setInt(&int_min,INT_MIN);

	if(numComp(a,&int_max)==1||numComp(a,&int_min)==-1){
		*x=0;
		return -1;
	}

	if(KETA<10){
		limit=KETA;
	}

	*x=0;

	for(i=0;i<limit;i++){
		*x+=a->n[i]*digits_decide;
		digits_decide*=10;
	}

	if(a->sign==-1){
		(*x)*=-1;
	}

	return 0;
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

int numComp(const struct NUMBER *a,const struct NUMBER *b){
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

int add(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int i;
	int e=0,buf;
	int ret=0;

	clearByZero(c);
	
	for(i=0;i<KETA;i++){
		buf=a->n[i]+b->n[i]+e;
		c->n[i]=buf%10;
		e=buf/10;
	}

	if(e){
		ret=-1;
	}

	return ret;
}

int sub(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int i;
	int h=0,buf;
	int ret=0;

	clearByZero(c);

	if(numComp(a,b)==(0||1)){
		for(i=0;i<KETA;i++){
			if(a->n[i]-h<b->n[i]){
				buf=10+a->n[i]-h-b->n[i];
				h=1;
			}else{
				buf=a->n[i]-h-b->n[i];
				h=0;
			}
			c->n[i]=buf;
		}
	}else{
		sub(b,a,c);
		setSign(c,-1);
	}

	if(h){
		ret=-1;
	}

	return ret;
}

void diff(int count){
	int i;
	int x,y,z;
	struct NUMBER a,b,c;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);

	for(i=0;i<count;i++){
		x=random()/10;
		y=random()/10;
		setInt(&a,x);
		setInt(&b,y);
		sub(&a,&b,&c);
		getInt(&c,&z);
		if(x-y!=z){
			printf("mismatched.\n");
			printf("x = %d,y = %d,x - y = %d\n",x,y,x+y);
			printf("a = ");
			dispNumber(&a);
			printf("\nb = ");
			dispNumber(&b);
			printf("\na - b =");
			dispNumber(&c);
			putchar('\n');
		}
	}
}