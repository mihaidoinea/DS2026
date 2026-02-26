#include<stdio.h>

void main()
{
	static char a = 7;
	static char b = 9;
	static int c = 0;
	c = a + b;
}