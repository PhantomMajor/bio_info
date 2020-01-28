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

	// Counters
	int pos_charged_counter = 0;
	int neg_charged_counter = 0;
	int aromatic_counter = 0;
	int neutral_polar_counter = 0;
	int hydphobic_counter = 0;
	int purine_counter = 0;
	int pyrimidine_counter = 0;

	char residue_number[4];
	char res_name[3]; // temp store residue name
	int j; // for looping through the residue name
	int residue_number_int;

	int visited = 0;

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
			for (j = 0; j < 4; j++)
			{
				residue_number[j] = line[j + 22];
			}
			residue_number[4] = '\0';
			residue_number_int = atoi(residue_number);

			for (j = 0; j < 3; j++)
			{
				res_name[j] = line[j+17];
			}
			res_name[3] = '\0';

			if (residue_number_int != visited)
			{

				/* -- PROTEIN PART -- */
				if (strcmp(res_name, "ARG") == 0 || strcmp(res_name, "LYS") == 0)
				{
					pos_charged_counter++;
				}
				else if (strcmp(res_name, "ASP") == 0 || strcmp(res_name, "GLU") == 0)
				{
					neg_charged_counter++;
				}
				else if (strcmp(res_name, "PHE") == 0 || strcmp(res_name, "TRP") == 0 || strcmp(res_name, "TYR") == 0)
				{
					aromatic_counter++;
				}
				else if (strcmp(res_name, "SER") == 0 || strcmp(res_name, "THR") == 0 || strcmp(res_name, "HIS") == 0 ||
					strcmp(res_name, "ASN") == 0 || strcmp(res_name, "GLN") == 0 || strcmp(res_name, "CYS") == 0)
				{
					neutral_polar_counter++;
				}
				else if (strcmp(res_name, "GLY") == 0 || strcmp(res_name, "ALA") == 0 || strcmp(res_name, "VAL") == 0 ||
					strcmp(res_name, "ILE") == 0 || strcmp(res_name, "PRO") == 0 || strcmp(res_name, "MET") == 0 ||
					strcmp(res_name, "LEU") == 0)
				{
					hydphobic_counter++;
				}

				/* -- RNA PART -- */
				else if (strcmp(res_name, "  A") == 0 || strcmp(res_name, "  G") == 0)
				{
					purine_counter++;
				}
				else if (strcmp(res_name, "  C") == 0 || strcmp(res_name, "  U") == 0)
				{
					pyrimidine_counter++;
				}
				visited = residue_number_int; // so that the same residue is not counted again
			}
		}
	}


	/* -- INSIDE PROT ARRAY -- */
	/*printf("+ve Charged: %d\n", pos_charged_counter);
	printf("-ve Charged: %d\n", neg_charged_counter);
	printf("Aromatic: %d\n", aromatic_counter);
	printf("Neutral Polar: %d\n", neutral_polar_counter);
	printf("Hydrophobic: %d\n", hydphobic_counter);*/

	int total = pos_charged_counter + neg_charged_counter+ aromatic_counter+ neutral_polar_counter + hydphobic_counter;
	printf("total amino acids in protein chain is %d\n", total);

	printf("\n");
	float percent_pc = (float)pos_charged_counter * 100 / total;
	float percent_nc = (float)neg_charged_counter * 100 / total;
	float percent_arom = (float)aromatic_counter * 100 / total;
	float percent_neut = (float)neutral_polar_counter * 100 / total;
	float percent_hydr = (float)hydphobic_counter * 100 / total;

	printf("Percantage of positively charged amino acid residues is %.2f\n", percent_pc);
	printf("Percantage of negatively charged amino acid residues is %.2f\n", percent_nc);
	printf("Percantage of aromatic amino acid residues is %.2f\n", percent_arom);
	printf("Percantage of neutral amino acid residues is %.2f\n", percent_neut);
	printf("Percantage of hydrophobic amino acid residues is %.2f\n", percent_hydr);

	int total_nuc = purine_counter + pyrimidine_counter;

	float percent_pur = (float)purine_counter * 100 / total_nuc;
	float percent_pyr = (float)pyrimidine_counter * 100 / total_nuc;

	printf("\n\n");
	printf("total nucleotides in rna chain is %d\n", total_nuc);
	printf("\n");
	printf("Percentage of purine bases is %.2f\n", percent_pur);
	printf("Percentage of pyrimidine bases is %.2f\n", percent_pyr);

	return 0;
}