#include <stdio.h>

void switchValues(int*, int*);
void changeValue(int*);

int main()
{
	printf("Hello G1055!\n");
	int x = 3;
	int y = 7;

	printf("x=%d, y=%d\n", x, y);
	printf("&x=%p, &y=%p\n", &x, &y);

	switchValues(&x, &y);

	printf("x=%d, y=%d\n", x, y);
	printf("&x=%p, &y=%p\n", &x, &y);

	int masiv[] = { 1, 2, 3, 4, 5 };

	printf("masiv=%p\n", masiv);
	printf("&masiv=%p\n", &masiv);

	printf("masiv+1=%p\n", masiv + 1);
	printf("&masiv+1=%p\n", &masiv + 1);

	changeValue(masiv);

	for (int i = 0; i < 5; i++)
	{
		printf("masiv[%d]=%d\n", i, masiv[i]);
	}

	return 0;
}

void changeValue(int* a)
{
	printf("\n--------ENTER FUNCTION--------\n");
	printf("a=%p\n", a);
	printf("&a=%p\n", &a);
	*a = 100;
	a[1] = 200;
	*(a + 2) = 300;
	(a + 3)[0] = 400;
	printf("a=%p\n", a);
	printf("&a=%p\n", &a);
	printf("--------EXIT FUNCTION---------\n\n");
}

void switchValues(int* a, int* b)
{
	printf("\n--------ENTER FUNCTION--------\n");

	printf("a=%p, b=%p\n", a, b);
	printf("&a=%p, &b=%p\n", &a, &b);

	int temp = *a;
	*a = *b;
	*b = temp;

	printf("a=%p, b=%p\n", a, b);
	printf("&a=%p, &b=%p\n", &a, &b);

	printf("--------EXIT FUNCTION---------\n\n");
}