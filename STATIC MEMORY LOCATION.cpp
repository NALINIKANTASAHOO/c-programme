#include<stdio.h>
#include<conio.h>
int main ()
{
	int size ;
	printf("enter limit of the text:\n");
	scanf("%d",&size);
	char str[size];
	printf("Enter some texts \n");
	scanf("%c");
	gets(str);
	printf("Inputtrd text is:%s \n ",str);
	return 0;
	
}
