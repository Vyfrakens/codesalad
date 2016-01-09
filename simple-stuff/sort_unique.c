//Program to remove duplicates from an array of strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b)
{
	return strcmp((char*)a , (char*)b);
}

int main(int argc, char const *argv[])
{
	char names[10][10] = {"Francis", "Abel", "Ann", "Francois", "Zebra", "Zebra", "Abel", "Abel"};
	int count = sizeof(names)/sizeof(names[0]);
	int i, j;
	//Before sorting
	for (int i = 0; i < count; ++i)
	{
		printf("%s ", names[i]);
	}
	printf("\n");
	//After sorting
	qsort(names, count, sizeof(names[0]), cmp);
	for (int i = 0; i < count; ++i)
	{
		printf("%s ", names[i]);
	}
	printf("\n");
	//Removing duplicates from sorted array
	for (i = j = 0; i < count; ++i)
	{
		if(strcmp(names[i], names[j]) != 0)
			strcpy(names[++j], names[i]);
	}
	//Fianl array of unique names
	for (i = 0; i < j+1; ++i)
	{
		printf("%s ", names[i]);
	}
	printf("\n");
	return 0;
}