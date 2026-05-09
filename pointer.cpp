#include<stdio.h>{
void swap (int *x,int*y)
{
int temp=*x;
*x=*y;
*y=temp;
}
	int main ()
{
int a=5,b=10;
printf("Before swap:ar%d,b=%d\n",a,b);
swap(&a,&b);
printf("after swap:a=%d,b=%d\n",a,b);
return 0;
}
