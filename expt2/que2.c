/* CODE TO FIND THE DISTANCE BETWEEN TWO ATOMS */

/* 
	INPUT -- pdb file
	OUTPUT -- new pdb file (cm.pdb) with the center of mass
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int main(void)
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

	double distance = 0; // To calculate distance

	char line[num_cols_in_file]; // to read and store the lines in the file
	char word[max_word_length]; // to store the word in the line

	char r_array[20000][num_cols_in_file]; // array to store rna atoms
	char p_array[20000][num_cols_in_file]; // array to store prot atoms

	int r_counter = 0;
	int p_counter = 0;

	int i, j; // counter for loops

	fpt1 = fopen("1asy.pdb", "r");
	fpt2 = fopen("out.pdb", "w");


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
			if ((line[21] == 'A') || (line[21] == 'B')) // i.e. if chain id is prot
			{
				strcpy(p_array[p_counter], line);
				p_counter++;
			}
		}
	}

	int temp; // counter for reading coordinates
	char coord[8]; // holder array for coordinate
	int cord_xo, cord_yo, cord_zo; // coordinate holder for outer loop
	int cord_xi, cord_yi, cord_zi; // coordinate holder for inner loop

	for (i = 0; i < r_counter; i++) // outer loop on RNA array
	{
		// RNA atom coordinates
		for ( temp = 0; temp < 8; temp++)
		{
			coord[temp] = r_array[i][temp+30]; // from the i-th line of r_array, read line
		}
	    coord[8]='\0';
	    cord_xo=atof(coord);
	    for ( temp = 0; temp < 8; temp++)
		{
			coord[temp] = r_array[i][temp+38];
		}
	    coord[8]='\0';
	    cord_yo=atof(coord);
	    for ( temp = 0; temp < 8; temp++)
		{
			coord[temp] = r_array[i][temp+46];
		}
	    coord[8]='\0';
	    cord_zo=atof(coord);

		for (j = 0; j < p_counter; j++) // inner loop on Prot array
		{
			// PROT atom coordinates
			for ( temp = 0; temp < 8; temp++)
			{
				coord[temp] = p_array[i][temp+30]; // from the i-th line of p_array, read line
			}
		    coord[8]='\0';
		    cord_xi=atof(coord);
		    for ( temp = 0; temp < 8; temp++)
			{
				coord[temp] = p_array[i][temp+38];
			}
		    coord[8]='\0';
		    cord_yi=atof(coord);
		    for ( temp = 0; temp < 8; temp++)
			{
				coord[temp] = p_array[i][temp+46];
			}
		    coord[8]='\0';
		    cord_zi=atof(coord);

			// compare distances

		}
	}

	printf("p_counter: %d\n", p_counter); //  DEBUGGER


	return 0;
}









