#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int sqrt_newton(int);

int main(int argc,char **argv){
    int i, r,r1,r2,d;

    srandom(time(NULL));

    for(i=0;i<10;i++){
        r = random();
        r1=sqrt_newton(r);      //自家製ルーチンによる計算
        r2=(int)sqrt((double)r);
        d=r1-r2;
        printf("%6d - %6d = %d\n",r1,r2,d);
    }

    return 0;
}

//平方根(Newton_Raphson法)
//
//入力:N...平方根を求めた整数
//出力:なし
//戻り値:
//  -1:エラー(N<0のとき)
//  それ以外:√Nを越えない最大の整数の値
int sqrt_newton(int N){
    int x;  //現在の平方根の近似値
    int b;  //1つ前のx
    int c;  //2つ前のx

    x=N/2;
    if(x==0) return N;  //N=0 or 1 なら√N=N
    if(x<0) return -1;  //N<0 ならエラーで-1を返す
    b=x;
    c=x;

    while(1){
        c=b;    //2つ前のx
        b=x;    //1つ前のx
        x=(b+(N/b))/2;   //x_{i+1}=(x_{i}+(N/x_{i}))/2

        if(x==b)break;  //収束
        if(x==c){       //振動
            if(b<x)x=b; //小さいほうをとる
            break;
        }
    }

    return x;
}