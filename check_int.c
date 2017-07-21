#include<stdio.h>
#include<limits.h>

int main(){
	int int_maximum_value=2147483647;

	int_maximum_value++;

	printf("2147483647+1=%d\n",int_maximum_value);

	int int_minimum_value=-2147483648;

	int_minimum_value--;

	printf("-2147483648-1=%d\n",int_minimum_value);

	return 0;
}