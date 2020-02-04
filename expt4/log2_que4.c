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
	int atom_no_counter = 0;

	char slno[6], atm_name[4];
	char res_no[4], store_res_name[20000][4], chain_id[20000];
	char res_name[5], store_atm_name[20000][4], b_factor_string[6];
	int store_atm_no[20000], store_res_no[20000], b_factor[20000];

	char line[80]; // read and store lines in the file
	char word[4]; // store the word in the line

	int visited = 0;
	int b_factor_avg = 0;
	int b_avg_store_A[20000], b_avg_store_B[20000], b_avg_store_C[20000], b_avg_store_D[20000];

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
			// atom serial number
			for ( i = 0; i < 5; i++ )
			{
				slno[i] = line[i+6];
			}
			slno[5] = '\0';
			store_atm_no[atom_no_counter] = atoi(slno);

			// chain id
			chain_id[atom_no_counter] = line[21];

			// residue number
			for ( i = 0; i < residue_no_len; i++ )
			{
				res_no[i] = line[i+22];
			}
			res_no[residue_no_len] = '\0';
			store_res_no[atom_no_counter] = atoi(res_no);

			// residue name
			for ( i = 0; i < 3; i++ )
			{
				res_nm[i] = line[i+17];
			}
			res_nm[3] = '\0';
			strcpy( store_res_nm[atom_no_counter], res_nm );

			// atom name
			for ( i = 0; i < 3; i++ )
			{
				atm_nm[i] = line[i + 13];
			}
			atm_nm[3] = '\0';
			strcpy( store_atm_nm[atom_no_counter], atm_nm );

			// b_factor
			for ( i = 0; i < 6; i++)
			{
				b_factor_string[i] = line[i + 60];
			}
			b_factor_string[6] = '\0';
			b_factor = atof(b_factor_string);

			// -------- FOR CHAIN A --------- //
			if (chain_id == 'A')
			{
				if (
					store_atm_name[atom_no_counter] == "N  " ||
					store_atm_name[atom_no_counter] == "C  " ||
					store_atm_name[atom_no_counter] == "CA " ||
					store_atm_name[atom_no_counter] == "O  " ||)
				{
					if (visited != store_res_no[atom_no_counter])
					{
						b_factor_avg += b_factor;
						b_avg_store_A[atom_no_counter] = b_factor_avg;
						atom_no_counter++;
					}
					else
					{
						visited = store_res_no[atom_no_counter];
						atom_no_counter++;
					}
				}
			}
			else if (chain_id == 'B')
			{
				if (
					store_atm_name[atom_no_counter] == "N  " ||
					store_atm_name[atom_no_counter] == "C  " ||
					store_atm_name[atom_no_counter] == "CA " ||
					store_atm_name[atom_no_counter] == "O  " ||)
				{
					if (visited != store_res_no[atom_no_counter])
					{
						b_factor_avg += b_factor;
						b_avg_store_B[atom_no_counter] = b_factor_avg;
						atom_no_counter++;
					}
					else
					{
						visited = store_res_no[atom_no_counter];
						atom_no_counter++;
					}
				}
			}
			else if (chain_id == 'C')
			{
				if (
					store_atm_name[atom_no_counter] == "N  " ||
					store_atm_name[atom_no_counter] == "C  " ||
					store_atm_name[atom_no_counter] == "CA " ||
					store_atm_name[atom_no_counter] == "O  " ||)
				{
					if (visited != store_res_no[atom_no_counter])
					{
						b_factor_avg += b_factor;
						b_avg_store_C[atom_no_counter] = b_factor_avg;
						atom_no_counter++;
					}
					else
					{
						visited = store_res_no[atom_no_counter];
						atom_no_counter++;
					}
				}
			}
			else if (chain_id == 'D')
			{
				if (
					store_atm_name[atom_no_counter] == "N  " ||
					store_atm_name[atom_no_counter] == "C  " ||
					store_atm_name[atom_no_counter] == "CA " ||
					store_atm_name[atom_no_counter] == "O  " ||)
				{
					if (visited != store_res_no[atom_no_counter])
					{
						b_factor_avg += b_factor;
						b_avg_store_D[atom_no_counter] = b_factor_avg;
						atom_no_counter++;
					}
					else
					{
						visited = store_res_no[atom_no_counter];
						atom_no_counter++;
					}
				}
			}
		}

		for (i = 0; i < atom_no_counter; i++)
		{
			b_avg_store_A[i] = (b_avg_store_A[i] / 4);
			b_avg_store_B[i] = (b_avg_store_B[i] / 4);
			b_avg_store_C[i] = (b_avg_store_C[i] / 4);
			b_avg_store_D[i] = (b_avg_store_D[i] / 4);
		}

	}

	return 0;
}