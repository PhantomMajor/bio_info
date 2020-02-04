#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


int main (void)
{
	FILE *fpt1; // File pointer for file to be opened
	FILE *fpt2; // File pointer for output file

	// introduce magic numbers later

	// 1. Opening the Files
	fpt1 = fopen("1oj6.pdb", "r");
	fpt2 = fopen("bfactor.txt", "w");

	int i, j; // counter for for-loops

	float b_factor; // to store current b-factor
	char b_factor_string[6];
	float b_factor_max = 0;
	float b_factor_min = 0;

	char line[80]; // read and store lines in the file
	char word[4]; // store the word in the line
	char atom_lines[20000][80]; // array to store all lines containing ATOM
	int atom_line_counter = 0; // number of lines containing ATOM

	char atom_name[4]; // to store N, C, CA or O

	float b_avg; // to calculate the average b-factor

	// -- Read the entire file -- //
	while ( fgets(line, 80, fpt1) != NULL )
	{
		// -- Identify ATOM -- //
		for (i = 0; i < 4; i++)
		{
			word[i] = line[i];
		}
		word[4] = '\0';

		// -- Proceed further if it is ATOM --//
		if ( strcmp(word, "ATOM") == 0 )
		{
			// -- Store all such lines seperately -- //
			strcpy(atom_lines[atom_line_counter], line);
			atom_line_counter++;
		}

		// 2. Reading the chains (A, B, C or D)
		for (i = 0; i < atom_line_counter; i++)
		{
			// Identify chain
			if (atom_lines[i][21] == 'A')
			{
				// this is chain A
				for (j = 0; j < 3; j++)
				{
					atom_name[j] = atom_lines[i][j+13];
				}
				atom_name[3] = '\0';

				b_avg = 0;

				for (j = 0; j < 6; j++)
				{
					b_factor_string[j] = line[j + 60];
				}
				b_factor_string[6] = '\0';
				b_factor = atof(b_factor_string);

				if ( 
					(strcmp(atom_name, "N  ") == NULL) || 
					strcmp(atom_name, "C  ") == NULL ||
					strcmp(atom_name, "CA ") == NULL ||
					strcmp(atom_name, "O  ") == NULL)
				{
					b_avg += b_factor;
				}

				// compare b-factors
				if (b_factor > b_factor_max)
				{
					b_factor_max = b_factor;
					// -->>> note the index also
				}
				if (b_factor < b_factor_min)
				{
					b_factor_min = b_factor;
				}
				// printf("B-factor_max A: %f\n", b_factor_max); // DEBUGGER
			}
			else if (atom_lines[i][21] == 'B')
			{
				continue;
				// this is chain B
			}
			else if (atom_lines[i][21] == 'C')
			{
				continue;
				// this is chain C
			}
			else if (atom_lines[i][21] == 'D')
			{
				continue;
				// this is chain D
			}
		}	
	}

	printf("B-factor_max A: %f\n", b_factor_max); // DEBUGGER
	printf("B-factor_min A: %f\n", b_factor_min); // DEBUGGER

	return 0;
}