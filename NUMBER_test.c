#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define KETA 30

struct NUMBER{
	int n[KETA];	//各桁の値
	int sign;			//符号変数
};

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

int main(){
	struct NUMBER b,c,d;

	srandom(time(NULL));
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);

	printf("b = ");
	dispNumberZeroSuppress(&b);
	putchar('\n');
	printf("c = ");
	dispNumber(&c);
	putchar('\n');
	printf("d = ");
	dispNumber(&d);
	putchar('\n');

	/*
	b.n[0]=9;
	b.n[1]=1;
	b.n[2]=0;
	b.n[3]=1;
	b.sign=1;

	c.n[0]=3;
	c.n[1]=0;
	c.n[2]=1;
	c.n[3]=5;
	c.sign=-1;

	d.n[0]=5;
	d.n[1]=9;
	d.n[2]=2;
	d.n[3]=5;
	d.n[4]=7;
	d.n[5]=2;
	d.n[6]=4;
	d.n[7]=7;
	d.n[8]=0;
	d.n[9]=0;
	d.n[10]=7;
	d.n[11]=8;
	d.n[12]=2;
	d.n[13]=3;
	d.n[14]=3;
	d.n[15]=4;
	d.sign=1;
	*/

	setRnd(&b,5);
	setRnd(&c,10);
	setRnd(&d,15);

	printf("b = ");
	dispNumberZeroSuppress(&b);
	putchar('\n');
	printf("c = ");
	dispNumberZeroSuppress(&c);
	putchar('\n');
	printf("d = ");
	dispNumberZeroSuppress(&d);
	putchar('\n');

	return 0;
}