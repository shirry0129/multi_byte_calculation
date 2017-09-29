//機械イプシロンの計算

#include <stdio.h>
#include <float.h>

int main(){
	//float e=1.0;
	double e=1.0;

	while(1.+e != 1.0){
		e*=1./2.;
	}

	printf("calculation:%.25f\n",e);

	//printf("definition:%.25f\n",FLT_EPSILON);
	printf("definition:%.25f\n",DBL_EPSILON);

	return 0;
}
