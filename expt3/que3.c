#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int main (void)
{
	FILE *fpt1; // File pointer for file to be opened (1ASY.pdb)
	FILE *fpt2; // File pointer for output file (out.pdb)

	// File info [Magic Numbers]
	int num_cols_in_file = 80; // Maximum 80 columns are in the file
	int max_word_length = 5; // Max length of a word
	int atom_len = 4; // Max length of atom column
	int atom_serial_no_len = 5; // Max length of atom-serial-no column
	int atom_name_len = 4; // Max length of atom name
	int residue_no_len = 4; // Max length of residue number
	int coord_len = 8; // Max length of coordinates

	fpt1 = fopen("1asy.pdb", "r");
	fpt2 = fopen("out.pdb", "w");

	char line[num_cols_in_file]; // to read and store the lines in the file
	char word[max_word_length]; // to store the word in the line

	int i; // for loops

	char r_array[20000][num_cols_in_file]; // array to store rna atoms
	char p_array[20000][num_cols_in_file]; // array to store prot atoms

	int r_counter = 0;
	int p_counter = 0;

	/* -- ID ALL RNA AND PROT ATOMS -- */
	while( fgets(line, num_cols_in_file, fpt1) != NULL )
	{
		// Identify if it is an ATOM or not
		for (i = 0; i < (atom_len); i++)
		{
			word[i] = line[i]; // store the word (i.e. "ATOM")
		}
		word[atom_len] = '\0'; // end the line with '\0'

		// check if all stored words are 'ATOM' and then execute further
		if ( strcmp(word, "ATOM") == 0 )
		{
			// Id if PROT or RNA
			if ((line[21] == 'R') || (line[21] == 'S')) // i.e. if chain id is RNA
			{
				strcpy(r_array[r_counter], line);
				r_counter++;
			}
			else if ((line[21] == 'A') || (line[21] == 'B')) // i.e. if chain id is prot
			{
				strcpy(p_array[p_counter], line);
				p_counter++;
			}
		}
	}

	printf("p_counter = %d\n", p_counter);

	char res_name[3]; // temp store residue name
	int j; // for looping through the residue name

	// Counters
	int pos_charged_counter = 0;
	int neg_charged_counter = 0;
	int aromatic_counter = 0;
	int neutral_polar_counter = 0;
	int hydphobic_counter = 0;

	/* -- INSIDE PROT ARRAY -- */
	for (i = 0; i < p_counter; i++)
	{
		for (j = 0; j < 3; j++)
		{
			res_name[j] = p_array[i][j+17];
		}
		res_name[3] = '\0';

		if (strcmp(res_name, "ARG") == 0)
		{
			pos_charged_counter++;
		}
		else if (strcmp(res_name, "LYS") == 0)
		{
			pos_charged_counter++;
		}
		else if (strcmp(res_name, "ASP") == 0)
		{
			neg_charged_counter++;
		}
		else if (strcmp(res_name, "GLU") == 0)
		{
			neg_charged_counter++;
		}
		else if (strcmp(res_name, "PHE") == 0)
		{
			aromatic_counter++;
		}
		else if (strcmp(res_name, "TRP") == 0)
		{
			aromatic_counter++;
		}
		else if (strcmp(res_name, "TYR") == 0)
		{
			aromatic_counter++;
		}
		else if (strcmp(res_name, "SER") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "THR") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "HIS") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "ASN") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "GLN") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "CYS") == 0)
		{
			neutral_polar_counter++;
		}
		else if (strcmp(res_name, "GLY") == 0)
		{
			hydphobic_counter++;
		}
		else if (strcmp(res_name, "ALA") == 0)
		{
			hydphobic_counter++;
		}
		else if (strcmp(res_name, "VAL") == 0)
		{
			hydphobic_counter++;
		}
		else if (strcmp(res_name, "ILE") == 0)
		{
			hydphobic_counter++;
		}
		else if (strcmp(res_name, "PRO") == 0)
		{
			hydphobic_counter++;
		}
		else if (strcmp(res_name, "MET") == 0)
		{
			hydphobic_counter++;
		}
	}

	printf("+ve Charged: %d\n", pos_charged_counter);
	printf("-ve Charged: %d\n", neg_charged_counter);
	printf("Aromatic: %d\n", aromatic_counter);
	printf("Neutral Polar: %d\n", neutral_polar_counter);
	printf("Hydrophobic: %d\n", hydphobic_counter);

	int total = pos_charged_counter + neg_charged_counter+ aromatic_counter+ neutral_polar_counter + hydphobic_counter;
	printf("%d\n", total);

	return 0;
}