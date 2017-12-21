#include<stdio.h>
#include<math.h>

double newton(double);
double f(double);
double fdash(double);

int main(int argc,char **argv){
	double x;
	double x0;
	double i;

	for(i=0.9;i<=1.1;i+=0.1){
		x0=(double)i;
		x=newton(x0);
		printf("x0=%10.6lf, x=%10.6lf\n",x0,x); //初期値と解
	}

	return 0;
}

//Newton-Raphson法で f(x)=0 を解く(x0=初期値)
double newton(double x0){
	double x;   //現在の近似値
	double b;   //1つ前のx
	double e;   //収束判定

	e = 1.e-7;
	x = x0;
	b = x0;

	while(1){
		b = x;  //1つ前のx
		x = b - (f(b)/fdash(b));
		
		if(fabs(x - b) < e) break;   //収束
	}

	return x;
}

// f(x)
double f(double x){
	return log(x);
}

// f'(x)
double fdash(double x){
	return 1/x;
}