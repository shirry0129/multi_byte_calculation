#include<stdio.h>

int main(){
	unsigned int uint_maximum_value=4294967295;

	printf("4294967295+1=%d\n",++uint_maximum_value);

	unsigned int uint_minimum_value=0;

	printf("0-1=%u\n",--uint_minimum_value);

	return 0;
}