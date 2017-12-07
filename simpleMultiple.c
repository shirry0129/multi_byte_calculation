#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

int simpleMultiple(const int a,const int b,int *c){
    int ret = 0;
    int i = 0,b_;
    *c = 0;

    if(b==0){
        return ret;
    }

    if(INT_MAX-a<=a){
        ret = -1;
    }

    if(b<0){
        b_=b*-1;
    }else{
        b_=b;
    }

    while(1){
        if(a<0){
            *c+=a*-1;
        }else{
            *c+=a;
        }

        i++;

        if(INT_MAX-*c<=a) ret = -1;

        if(i>=b_){
            break;
        }
    }

    if((a<0||b<0)&&!(a<0&&b<0)){
        *c*=-1;
    }

    return ret;
}

int main(){
    int a = (random()-RAND_MAX/2)%10000;
    int b = (random()-RAND_MAX/2)%10000;
    int c,r,i;

    srandom(time(NULL));

    r = simpleMultiple(a,b,&c);

    printf("%d * %d = %d\nr = %d\n",a,b,c,r);

    for(i=0;i<10e6;i++){
        a=(random()-RAND_MAX/2)%10000;
        b=(random()-RAND_MAX/2)%10000;

        r = simpleMultiple(a,b,&c);

        if(r==0&&c!=a*b){
            printf("mismatched.\n");
            printf("a = %d, b = %d, c = %d, a*b = %d\n",a,b,c,a*b);
        }
    }

    return 0;
}