#include"mulcal.h"
#include<stdio.h>
#include<limits.h>

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
		printf("%d",a->n[i]);
		if(i%5==0) putchar(' ');
		if(i%50==0) putchar('\n');
	}
}

void clearByZero(struct NUMBER *a){
	int i;

	for(i=0;i<KETA;i++){
		a->n[i]=0;
	}

	setSign(a,1);
}

void copyNumber(const struct NUMBER *source,struct NUMBER *target){
	int i;
	
	for(i=0;i<KETA;i++){
		target->n[i]=source->n[i];
	}

	setSign(target,getSign(source));
}

void getAbs(const struct NUMBER *source,struct NUMBER *target){
	copyNumber(source,target);
	setSign(target,1);
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

int mulBy10(const struct NUMBER *a,struct NUMBER *b){
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

int divBy10(const struct NUMBER *a,struct NUMBER *b){
	int ret;
	int i;
    //int getSign(a)=getSign(a);

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
	struct NUMBER buf;
	copyNumber(a,&buf);
	copyNumber(b,a);
	copyNumber(&buf,b);
}

int setInt(struct NUMBER *a,int x){
	int ret=0;
	int i;

	if(x<0){
		for(i=0;i<KETA;i++){
			a->n[i]=(x%10)*-1;
			x-=x%10;
			x/=10;
		}
		setSign(a,-1);
	}else{
		for(i=0;i<KETA;i++){
			a->n[i]=x%10;
			x-=x%10;
			x/=10;
		}
		setSign(a,1);
	}

	if(x){
		ret=-1;
	}

	return ret;
}

void setSign(struct NUMBER *a,const int sign){
	if(isZero(a)==0){
		a->sign=1;
		return;
	}

	a->sign=sign;
}

int getSign(const struct NUMBER *a){
	return a->sign;
}

int numComp(const struct NUMBER *a,const struct NUMBER *b){
	int i;
    // int getSign(a)=getSign(a);
    // int getSign(b)=getSign(b);

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

int add(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *sum){
	int i;
	int carry=0,buf;
	int ret=0;
	struct NUMBER Aabs,Babs;
	
	clearByZero(sum);

    for(i=0;i<KETA;i++){
		buf=a->n[i]+b->n[i]+carry;
		sum->n[i]=buf%10;
		carry=buf/10;
	}

	if(carry){
		ret=-1;
	}

	return ret;
}

int sub(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *diff){
	int i;
	int borrow=0,buf;
	int ret=0;
	struct NUMBER Aabs,Babs;

	clearByZero(diff);

    if(numComp(a,b)>=0){
		for(i=0;i<KETA;i++){
			if(a->n[i]-borrow<b->n[i]){
				buf=10+a->n[i]-borrow-b->n[i];
				borrow=1;
			}else{
				buf=a->n[i]-borrow-b->n[i];
				borrow=0;
			}
			diff->n[i]=buf;
		}
	}else{
		ret=sub(b,a,diff);
		setSign(diff,-1);
	}

	if(borrow){
		ret=-1;
	}

	return ret;
}

int divide(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *quotient,struct NUMBER *remainder){
	struct NUMBER buf,abuf,bbuf,aabs,babs,e;

	clearByZero(quotient);
	clearByZero(remainder);

	if(!isZero(b)) return -1;

    copyNumber(a,&abuf);

    while(1){
		if(numComp(&abuf,b)==-1) break;
	    copyNumber(b,&bbuf);
		clearByZero(&e);
		setInt(&e,1);
		while(1){
			if(numComp(&abuf,&bbuf)!=1) break;
			mulBy10(&bbuf,&buf);
			copyNumber(&buf,&bbuf);
			mulBy10(&e,&buf);
			copyNumber(&buf,&e);
		}

		if(numComp(b,&bbuf)==-1){
			clearByZero(&buf);
			divBy10(&bbuf,&buf);
			copyNumber(&buf,&bbuf);
			clearByZero(&buf);
			divBy10(&e,&buf);
			copyNumber(&buf,&e);
		}

		sub(&abuf,&bbuf,&buf);
		copyNumber(&buf,&abuf);

		add(quotient,&e,&buf);
		copyNumber(&buf,quotient);
	}
	copyNumber(&abuf,remainder);

    return 0;
}

int int_divide(const struct NUMBER *a,const int b,struct NUMBER *quotient,int *remainder){
	int rembuf=0,t,babs;
	int i;
	struct NUMBER aabs;

	if(b==0||b>9) return -1;

	clearByZero(&aabs);

    for(i=KETA-1;i>=0;i--){
		t=10*rembuf+a->n[i];
		rembuf=t%b;
		quotient->n[i]=(t-rembuf)/b;
	}

	*remainder=rembuf;

	return 0;
}

int sqrt_newton(const struct NUMBER *a,struct NUMBER *b){
	struct NUMBER c;  //1つ前のx
	struct NUMBER d;  //2つ前のx
	struct NUMBER Nbuf,garbage,x2;
	int ibuf;

	clearByZero(b);

	int_divide(a,2,b,&ibuf);
	if(isZero(b)==0){
		copyNumber(a,b);  //a=0 or 1 なら√a=a
		return 0;
	}
	if(getSign(a)==-1) return -1;  //a<0 ならエラーで-1を返す

	copyNumber(b,&c);
	copyNumber(b,&d);

	while(1){
		copyNumber(&c,&d);	//2つ前のx
		copyNumber(b,&c);	//1つ前のx

		divide(a,&c,&Nbuf,&garbage);
		add(&Nbuf,&c,&x2);
		int_divide(&x2,2,b,&ibuf);
		//x=(b+(N/b))/2;   //x_{i+1}=(x_{i}+(N/x_{i}))/2

		ibuf = numComp(b,&c);
		if(ibuf == 0)break;  //収束
		if(numComp(b,&d)==0){       //振動
			if(ibuf == 1) copyNumber(&c,b); //小さいほうをとる
			break;
		}
	}

    return 0;
}

int mulBy10n(const struct NUMBER *a,int index,struct NUMBER *b){
	int ret=0;
	int i;

	if(index>=KETA) {
		return -1;
	}
	if(index==0){
		copyNumber(a,b);
		return 0;
	}

	for(i=1;i<=index;i++){
		if(a->n[KETA-i]){
			ret=-1;
			break;
		}
	}

	for(i=0;i<KETA-index;i++){
		b->n[i+index]=a->n[i];
	}
	for(i=0;i<index;i++){
		b->n[i]=0;
	}

	setSign(b,getSign(a));

	return ret;
}