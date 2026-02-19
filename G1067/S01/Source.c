#include "stdio.h"
void switchValues(int*, int*);
void main()
{
	printf("Hello G1067!\n");

	int x = 7;
	int y = 8;
	printf("x = %d, y = %d\n", x,y);
	printf("&x = %p, &y = %p\n", &x,&y);
	switchValues(&x, &y);
	printf("x = %d, y = %d\n", x, y);
	printf("&x = %p, &y = %p\n", &x, &y);
}

void switchValues(int* a, int* b)
{
	printf("\n------Inside the function------\n");
	printf("a = %d, b = %d\n", *a, *b);
	printf("&a = %p, &b = %p\n", &a, &b);
	
	int x = *a;
	*a = *b;
	*b = x;

	printf("a = %d, b = %d\n", *a, *b);
	printf("&a = %p, &b = %p\n", &a, &b);

	printf("\n------Exit the function------\n");


}