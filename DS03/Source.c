#include <stdio.h>
typedef struct BitLetter
{
	short : 5;
	short sign : 1;
	short : 2;
}BitLetter;
void main()
{
	char letter = 'A';
	BitLetter* pLetter = (BitLetter*) &letter;
	printf("value before = %c\n", letter);

	pLetter->sign = !pLetter->sign;

	printf("value after = %c\n", letter);
}