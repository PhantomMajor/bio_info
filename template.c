#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


int int main(void)
{
	// Opening the files
	FILE *fpt1;
	FILE *fpt2;

	char line[80]; // var to store the lines from the file
	char word[5]; // var to store the word from the line

	// Opening the files
	fpt1 = fopen("", "r"); // input file
	fpt2 = fopen("", "w"); // output file

	// Closing the files
	fclose(fpt1);
	fclose(fpt2);

	return 0;
}