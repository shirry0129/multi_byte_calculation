#include<stdio.h>

int simpleDivide(int,int,int*,int*);

int main(int argc,char **argv){
    int a,b,c,d;
    int r;

    a=1234567;
    b=3846;

    r=simpleDivide(a,b,&c,&d);

    if(r==-1){
        printf("divided by zero error.\n");
    }
    else{
        printf("%d / %d = %d ... %d\n",a,b,c,d);
    }

    return 0;
}

//加算と減算のみで除算を実現
//戻り値:0で正常,-1でdivby0
int simpleDivide(int x,int y,int *z,int *w){
    int k;

    if(y==0) return -1;

    k=0;
    while(1){
        if(x<y) break;
        x-=y;
        k++;
    }
    *z=k;
    *w=x;

    return 0;
}