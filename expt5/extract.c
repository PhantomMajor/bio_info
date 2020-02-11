#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


int main(void)
{
	FILE *fpt1; // *fpt2

	fpt1 = fopen("1asy.pdb", "r");
	// fpt2 = fopen("Outpot.txt", "w");

	// Variables to read lnes and words
	char line[80], word[6], r_value[7], r_value_val[5];
	char free_r[14];

	int l_string;
	float r_value_float;

	int i; // counter for loops

	int chain_count = 0;

	while( fgets(line, 80, fpt1) != NULL )
	{
		// -- Identify ATOM -- //
		for (i = 0; i < 6; i++)
		{
			word[i] = line[i];
		}
		word[6] = '\0';

		l_string = (line[9]);
		// printf("%c\n", l_string);

		if ( strcmp(word, "TITLE ") == 0 )
		{
			// printf("HELLO\n"); //DB
			// print 11 -80
			for (i = 0; i < (80-11); i++)
			{
				printf("%c", line[i + 10]);
			}
			printf("\n");
		}

		if ( strcmp(word, "EXPDTA") == 0 )
		{
			// Store in string
			for (i = 0; i < (80-11); i++)
			{
				printf("%c", line[i + 10]);
			}
			printf("\n");
		}

		// INSIDE REMARK 3
		if ( (strcmp(word, "REMARK") == 0) && (l_string == '3') )
		{
			// 14 to  20
			for (i = 0; i < 7; i++)
			{
				r_value[i] = line[i + 13];
			}
			r_value[7] = '\0';

			if ( strcmp(r_value, "R VALUE") == 0 )
			{
				for (i = 0; i < 5; i++)
				{
					r_value_val[i] = line[i + 48]; 
				}
				r_value_val[5] = '\0';
				r_value_float = atof(r_value_val);

				printf("%f\n", r_value_float);
			}

			for (i = 0; i < 14; i++)
			{
				free_r[i] = line[i + 13];
			}
			free_r[14] = '\0';

			if ( strcmp(free_r, "FREE R VALUE  ") == 0 )
			{
				for (i = 0; i < 5; i++)
				{
					r_value_val[i] = line[i + 48]; 
				}
				r_value_val[5] = '\0';
				r_value_float = atof(r_value_val);

				printf("%f\n", r_value_float);
			}
		}

		if ( (strcmp(word, "DBREF ") == 0))
		{
			chain_count++;
		}
	}

	printf("%d\n", chain_count);


	return 0;
}