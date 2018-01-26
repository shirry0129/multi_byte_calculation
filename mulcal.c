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

void copyNumber(const struct NUMBER *a,struct NUMBER *b){
	int i;
	
	for(i=0;i<KETA;i++){
		b->n[i]=a->n[i];
	}

	setSign(b,getSign(a));
}

void getAbs(const struct NUMBER *a,struct NUMBER *b){
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
	struct NUMBER c;
	copyNumber(a,&c);
	copyNumber(b,a);
	copyNumber(&c,b);
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

void setSign(struct NUMBER *a,const int s){
	if(isZero(a)==0){
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
	struct NUMBER Aabs,Babs;

	clearByZero(c);
	
	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				buf=a->n[i]+b->n[i]+e;
				c->n[i]=buf%10;
				e=buf/10;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=sub(a,&Babs,c);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=sub(b,&Aabs,c);
		}
		if(getSign(b)==-1){
			getAbs(a,&Aabs);
			getAbs(b,&Babs);
			ret=add(&Aabs,&Babs,c);
			setSign(c,-1);
		}
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
	struct NUMBER Aabs,Babs;

	clearByZero(c);

	if(getSign(a)==1){
		if(getSign(b)==1){
			if(numComp(a,b)==0||numComp(a,b)==1){
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
				ret=sub(b,a,c);
				setSign(c,-1);
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,c);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=add(&Aabs,b,c);
			setSign(c,-1);
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,c);
		}
	}

	if(h){
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

int multiple(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int ret = 0,r1,r2,r3 = 0;
	int i,j;
	int buf = 0;
	int h = 0;
	struct NUMBER d,e;

	clearByZero(c);

	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				clearByZero(&d);
				clearByZero(&e);
				h = 0;

				for(j=0;j<KETA;j++){
					buf = a->n[j]*b->n[i]+h;
					d.n[j] = buf%10;
					h = buf/10;
				}
				for(j=0;j<i;j++){
					r1 = mulBy10(&d,&e);
					swap(&d,&e);
				}

				r2 = add(c,&d,&e);
				copyNumber(&e,c);
			}
			if(h){
				r3 = -1;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&d);
			ret = multiple(a,&d,c);
			setSign(c,-1);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&d);
			ret = multiple(&d,b,c);
			setSign(c,-1);
		}
		if(getSign(b)==-1){
			getAbs(a,&d);
			getAbs(b,&e);
			ret = multiple(&d,&e,c);
		}
	}

	if(r1||r2||r3) ret=-1;

	return ret;
}

int divide(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c,struct NUMBER *d){
	struct NUMBER m,n,p,q;

	clearByZero(c);
	clearByZero(d);

    if(!isZero(b)) return -1;


	if(getSign(a)==1){
		if(getSign(b)==1){
			copyNumber(a,&n);

			while(1){
				if(numComp(&n,b)==-1) break;
				increment(c,&m);
				copyNumber(&m,c);
				sub(&n,b,&m);
				copyNumber(&m,&n);
			}
			copyNumber(&n,d);
		}
		if(getSign(b)==-1){
			getAbs(b,&p);
			divide(a,&p,c,d);
			setSign(c,-1);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&p);
			divide(&p,b,c,d);
			setSign(c,-1);
			setSign(d,-1);
		}
		if(getSign(b)==-1){
			getAbs(a,&p);
			getAbs(b,&q);
			divide(&p,&q,c,d);
			setSign(d,-1);
		}
	}

    return 0;
}

int int_divide(const struct NUMBER *a,const int b,struct NUMBER *c,int *d){
	int h=0,t,p,q;
	int i;
	struct NUMBER buf;

	if(b==0||b>9) return -1;

	clearByZero(c);
	clearByZero(&buf);

	if(getSign(a)==1){
		if(b>0){
			for(i=KETA-1;i>=0;i--){
				t=10*h+a->n[i];
				h=t%b;
				c->n[i]=(t-h)/b;
			}

			*d=h;
		}
		if(b<0){
			p=b*-1;
			int_divide(a,p,c,d);
			setSign(c,-1);
		}
	}
	if(getSign(a)==-1){
		if(b>0){
			getAbs(a,&buf);
			int_divide(&buf,b,c,d);
			setSign(c,-1);
			*d*=-1;
		}
		if(b<0){
			getAbs(a,&buf);
			p=b*-1;
			int_divide(&buf,p,c,d);
			*d*=-1;
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
		y=random()%9+1;
		if(random()%2) y*=-1;
		setInt(&a,x);
		r = int_divide(&a,y,&c,&w);
		getInt(&c,&z);
		if(((x/y)!=z||(x%y)!=w)){
			printf("mismatched.%d\n",i);
			printf("x = %d,y = %d,x / y = %d,x %% y = %d\n",x,y,x/y,x%y);
			printf("a = ");
			dispNumber(&a);
			printf("\na / b =");
			dispNumber(&c);
			printf("\na %% b = %d\n",w);
		}
	}
}