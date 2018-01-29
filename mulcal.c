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

void setRnd(struct NUMBER *a,int keta){
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

	clearByZero(a);

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

int getInt(const struct NUMBER *a,int *x){
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
	
	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				buf=a->n[i]+b->n[i]+carry;
				sum->n[i]=buf%10;
				carry=buf/10;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=sub(a,&Babs,sum);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=sub(b,&Aabs,sum);
		}
		if(getSign(b)==-1){
			getAbs(a,&Aabs);
			getAbs(b,&Babs);
			ret=add(&Aabs,&Babs,sum);
			setSign(sum,-1);
		}
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

	if(getSign(a)==1){
		if(getSign(b)==1){
			if(numComp(a,b)==0||numComp(a,b)==1){
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
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,diff);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=add(&Aabs,b,diff);
			setSign(diff,-1);
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,diff);
		}
	}

	if(borrow){
		ret=-1;
	}

	return ret;
}

int increment(const struct NUMBER *a,struct NUMBER *b){
	struct NUMBER one;
	int ret;
	
	setInt(&one,1);
	ret=add(a,&one,b);

	return ret;
}

int decrement(const struct NUMBER *a,struct NUMBER *b){
	struct NUMBER one;
	int ret;

	setInt(&one,1);
	ret = sub(a,&one,b);

	return ret;
}

int multiple(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *product){
	int ret = 0,r1,r2,r3 = 0;
	int i,j;
	int buf = 0;
	int carry = 0;
	struct NUMBER d,e;

	clearByZero(product);

	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				clearByZero(&d);
				clearByZero(&e);
				carry = 0;

				for(j=0;j<KETA;j++){
					buf = a->n[j]*b->n[i]+carry;
					d.n[j] = buf%10;
					carry = buf/10;
				}
				for(j=0;j<i;j++){
					r1 = mulBy10(&d,&e);
					swap(&d,&e);
				}

				r2 = add(product,&d,&e);
				copyNumber(&e,product);
			}
			if(carry){
				r3 = -1;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&d);
			ret = multiple(a,&d,product);
			setSign(product,-1);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&d);
			ret = multiple(&d,b,product);
			setSign(product,-1);
		}
		if(getSign(b)==-1){
			getAbs(a,&d);
			getAbs(b,&e);
			ret = multiple(&d,&e,product);
		}
	}

	if(r1||r2||r3) ret=-1;

	return ret;
}

int divide(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *quotient,struct NUMBER *remainder){
	struct NUMBER buffer,abuf,aabs,babs;

	clearByZero(quotient);
	clearByZero(remainder);

	if(!isZero(b)) return -1;

	if(getSign(a)==1){
		if(getSign(b)==1){
			copyNumber(a,&abuf);

			while(1){
				if(numComp(&abuf,b)==-1) break;
				increment(quotient,&buffer);
				copyNumber(&buffer,quotient);
				sub(&abuf,b,&buffer);
				copyNumber(&buffer,&abuf);
			}
			copyNumber(&abuf,remainder);
		}
		if(getSign(b)==-1){
			getAbs(b,&babs);
			divide(a,&babs,quotient,remainder);
			setSign(quotient,-1);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&aabs);
			divide(&aabs,b,quotient,remainder);
			setSign(quotient,-1);
			setSign(remainder,-1);
		}
		if(getSign(b)==-1){
			getAbs(a,&aabs);
			getAbs(b,&babs);
			divide(&aabs,&babs,quotient,remainder);
			setSign(remainder,-1);
		}
	}

    return 0;
}

int int_divide(const struct NUMBER *a,const int b,struct NUMBER *quotient,int *remainder){
	int rembuf=0,t,babs;
	int i;
	struct NUMBER aabs;

	if(b==0||b>9) return -1;

	clearByZero(quotient);
	clearByZero(&aabs);

	if(getSign(a)==1){
		if(b>0){
			for(i=KETA-1;i>=0;i--){
				t=10*rembuf+a->n[i];
				rembuf=t%b;
				quotient->n[i]=(t-rembuf)/b;
			}

			*remainder=rembuf;
		}
		if(b<0){
			babs=b*-1;
			int_divide(a,babs,quotient,remainder);
			setSign(quotient,-1);
		}
	}
	if(getSign(a)==-1){
		if(b>0){
			getAbs(a,&aabs);
			int_divide(&aabs,b,quotient,remainder);
			setSign(quotient,-1);
			*remainder*=-1;
		}
		if(b<0){
			getAbs(a,&aabs);
			babs=b*-1;
			int_divide(&aabs,babs,quotient,remainder);
			*remainder*=-1;
		}
	}

	return 0;
}

// int sqrt_newton(const struct NUMBER *a,struct NUMBER *b){
// 	struct NUMBER x;  //現在の平方根の近似値
// 	struct NUMBER c;  //1つ前のx
// 	struct NUMBER d;  //2つ前のx
// 	struct NUMBER e,f;

// 	setInt(&f,0);

// 	int_divide(a,2,&x,&e);
// 	if(isZero(&x)){
// 		copyNumber(a,b);  //a=0 or 1 なら√a=a
// 		return 0;
// 	}
// 	if(numComp(a,&f)==-1) return -1;  //N<0 ならエラーで-1を返す

// 	copyNumber(&x,&c);
// 	copyNumber(&x,&d);

// 	while(1){
// 		copyNumber(&c,&d);	//2つ前のx
// 		copyNumber(&x,&c);	//1つ前のx
// 		x=(b+(N/b))/2;   //x_{i+1}=(x_{i}+(N/x_{i}))/2

// 		if(x==b)break;  //収束
// 		if(x==c){       //振動
// 			if(b<x)x=b; //小さいほうをとる
// 			break;
// 		}
// 	}

//     return x;
// }


void diff(int count){
	int i;
	int x,y,z,w,r;
	struct NUMBER a,b,c,d;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);

	for(i=0;i<count;i++){
		x=(random()-RAND_MAX/2)%100000000;
		y=(random()-RAND_MAX/2)%100;
		if(y==0) y=1;
		setInt(&a,x);
		setInt(&b,y);
		divide(&a,&b,&c,&d);
		getInt(&c,&z);
		getInt(&d,&w);
		if(((x/y)!=z||(x%y)!=w)){
			printf("mismatched.%d\n",i);
			printf("x = %d,y = %d,x / y = %d,x %% y = %d\n",x,y,x/y,x%y);
			printf("a = ");
			dispNumber(&a);
			printf("\nb = ");
			dispNumber(&b);
			printf("\na / b =");
			dispNumber(&c);
			printf("\na %% b =");
			dispNumber(&d);
			printf("\nz = %d,w = %d\n",z,w);
		}
	}
}