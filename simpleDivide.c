#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int simpleDivide(int,int,int*,int*);

int main(int argc,char **argv){
    int a,b,c,d;
    int r,i;

    srandom(time(NULL));

    a=(random()-RAND_MAX/2)%1000000;
    b=(random()-RAND_MAX/2)%1000;

    r=simpleDivide(a,b,&c,&d);

    if(r==-1){
        printf("divided by zero error.\n");
    }
    else{
        printf("%d / %d = %d ... %d\n",a,b,c,d);
    }

    for(i=0;i<10e4;i++){
        a=(random()-RAND_MAX/2)%1000000;
        b=(random()-RAND_MAX/2)%1000;
        r=simpleDivide(a,b,&c,&d);
        if(!r){
            if(c!=a/b){
                printf("c mismatched.\n");
                printf("a = %d,b = %d\n",a,b);
                printf("c = %d,a/b = %d\n",c,a/b);
            }
            if(d!=a%b){
                printf(" mismatched.\n");
                printf("a = %d,b = %d\n",a,b);
                printf("d = %d,a%%b = %d\n",d,a%b);
            }
        }
    }

    return 0;
}

//加算と減算のみで除算を実現
//戻り値:0で正常,-1でdivby0
int simpleDivide(int x,int y,int *z,int *w){
    int k;
    int _x,_y;

    if(y==0) return -1;

    k=0;
    if(x>=0){
        if(y>0){
            while(1){
                if(x<y) break;
                x-=y;
                k++;
            }
            *z=k;
            *w=x;
        }
        if(y<0){
            _y=y*-1;
            simpleDivide(x,_y,z,w);
            *z*=-1;
        }
    }
    if(x<0){
        if(y>0){
            _x=x*-1;
            simpleDivide(_x,y,z,w);
            *z*=-1;
            *w*=-1;
        }
        if(y<0){
            _x=x*-1;
            _y=y*-1;
            simpleDivide(_x,_y,z,w);
            *w*=-1;
        }
    }

    return 0;
}