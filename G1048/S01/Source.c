#include "stdio.h"

void switchValues(int*, int*);

void main()
{
	printf("Hello G1048!\n");

	int x = 8;
	int y = 9;

	int masiv[] = { 1,2,3,4,5 };

	printf("&x = %p, &y = %p\n", &x, &y);
	printf("x = %d, y = %d\n", x, y);
	
	printf("masiv = %p\n", masiv);
	printf("masiv = %p\n", &masiv);



	switchValues(&x, &y);

	printf("&x = %p, &y = %p\n", &x, &y);
	printf("x = %d, y = %d\n", x, y);

}

void switchValues(int* a, int* b)
{
	printf("\n------ENTER FUNCTION------\n");

	printf("&a = %p, &b = %p\n", &a, &b);
	printf("a = %d, b = %d\n", *a, *b);

	int z = *a;
	*a = *b;
	*b = z;

	printf("&a = %p, &b = %p\n", &a, &b);
	printf("a = %d, b = %d\n", *a, *b);
	
	printf("\n------EXIT FUNCTION-------\n");
}