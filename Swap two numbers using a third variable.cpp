#include<stdio.h>
int main (){
	int a,b,c;
	printf("Enter two integers: ",a,b);
	scanf("%d  %d",&a,&b);
	printf("\n before swapping a=%d,b=%d",a,b);
	c=a;
	a=b;
	b=c;
	printf("\n After swapping a=%d b=%d",a,b);
	return 0;
}
