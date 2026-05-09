#include<stdio.h>
int main(){
	int arr[10],i;
	printf("Enter the elements of array: ");
	int even=0,odd=0;
	for(i=0;i<10;i++){
		scanf("%d",&arr[i]);
		if(arr[i]%2==0)
		even++;
		else
		odd++;
	}
	printf("The total no of even numbers: %d\n",even);
	printf("The total no of odd numbers: %d\n ",odd);
 return 0;	
}
