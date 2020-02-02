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
	FILE *fpt2; // File pointer for output interacting protein file (out1_prot.pdb)
	FILE *fpt3; // File pointer for output interacting rna file (out2_rna.pdb)
	FILE *fpt4; // File pointer for output interacting pairs (out3_interact.txt)
	FILE *fpt_pAll; // File pointer for all the proteins
	FILE *fpt_rAll; // File pointer for all the rna


	// File info [Magic Numbers]
	int num_cols_in_file = 80; // Maximum 80 columns are in the file
	int max_word_length = 5; // Max length of a word
	int atom_len = 4; // Max length of atom column
	int atom_serial_no_len = 5; // Max length of atom-serial-no column
	int atom_name_len = 4; // Max length of atom name
	int residue_no_len = 4; // Max length of residue number
	int coord_len = 8; // Max length of coordinates

	char line[num_cols_in_file]; // to read and store the lines in the file
	char word[max_word_length]; // to store the word in the line

	char r_array[20000][num_cols_in_file]; // array to store rna atoms
	char p_array[20000][num_cols_in_file]; // array to store prot atoms

	int r_counter = 0; // rna counter
	int p_counter = 0; // protein counter

	int i, j; // counter for loops

	fpt1 = fopen("1asy.pdb", "r");  // input file
	fpt2 = fopen("out1_prot.pdb", "w"); // output the proteins in the file
	fpt3 = fopen("out2_rna.pdb", "w"); // output the rna in the file
	fpt4 = fopen("out3_interact.txt", "w"); // output the interacting pairs


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

	/*	
	// -- FOR PRINTING ALL PROT AND RNA FILES -- 
	//---------- For Debugging Only -------------
	fpt_rAll = fopen("rnaAll.pdb", "w");
	fpt_pAll = fopen("protAll.pdb", "w");

	// A. Printing Protein file
	for (i = 0; i < p_counter; i++) // looping through the rows of protein array
	{
		fprintf(fpt_pAll, "%s\n", p_array[i]);	
	}
	// B. Printing RNA file
	for (i = 0; i < r_counter; i++) // looping through the rows of protein array
	{
		fprintf(fpt_rAll, "%s\n", r_array[i]);	
	}

	// closing the files
	fclose(fpt_pAll);
	fclose(fpt_rAll);
	//------------------- END ---------------------
	*/

	int temp; // counter for reading coordinates
	char coord[8]; // holder array for coordinate
	float cord_xo, cord_yo, cord_zo; // coordinate holder for outer loop
	float cord_xi, cord_yi, cord_zi; // coordinate holder for inner loop

	int count_interact = 0; // counter for interacting atoms
	double distance = 0; // To calculate distance

	// to store variables to put in out4_interact.txt
	char atom_number_p[5], atom_name_p[3], atom_number_r[5], atom_name_r[3];
	int int_atom_number_p, int_atom_number_r;
	char residue_name_p[3], residue_name_r[3];
	char residue_num_p[4], residue_num_r[4];
	int int_residue_num_p, int_residue_num_r;

	/* -- FOR INTERACTING ATOMS FILE -- */
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
				coord[temp] = p_array[j][temp+30]; // from the i-th line of p_array, read line
			}
		    coord[8]='\0';
		    cord_xi=atof(coord);
		    for ( temp = 0; temp < 8; temp++)
			{
				coord[temp] = p_array[j][temp+38];
			}
		    coord[8]='\0';
		    cord_yi=atof(coord);
		    for ( temp = 0; temp < 8; temp++)
			{
				coord[temp] = p_array[j][temp+46];
			}
		    coord[8]='\0';
		    cord_zi=atof(coord);

			// compare distances
		    distance = sqrt( 
		    	pow((cord_xo - cord_xi), 2) + 
		    	pow((cord_yo - cord_yi), 2) + 
		    	pow((cord_zo - cord_zi), 2) );

		    if (distance <= 4.5)
		    {
		    	// storing Protein Data
		    	for (temp = 0; temp < 5; temp++)
		    		atom_number_p[temp] = p_array[j][temp + 6];
		    	atom_number_p[5] = '\0';
		    	int_atom_number_p = atoi(atom_number_p);

		    	for (temp = 0; temp < 3; temp++)
		    		atom_name_p[temp] = p_array[j][temp + 13];
		    	atom_name_p[3] = '\0';
		    	
		    	for (temp = 0; temp < 3; temp++)
		    		residue_name_p[temp] = p_array[j][temp + 17];
		    	residue_name_p[3] = '\0';

		    	for (temp = 0; temp < 4; temp++)
		    		residue_num_p[temp] = p_array[j][temp + 23];
		    	residue_num_p[4] = '\0';
		    	int_residue_num_p = atoi(residue_num_p);

		    	// Storing RNA Data
		    	for (temp = 0; temp < 5; temp++)
		    		atom_number_r[temp] = r_array[i][temp + 6];
		    	atom_number_r[5] = '\0';
		    	int_atom_number_r = atoi(atom_number_r);

		    	for (temp = 0; temp < 3; temp++)
		    		atom_name_r[temp] = r_array[i][temp + 13];
		    	atom_name_r[3] = '\0';
		    	
		    	for (temp = 0; temp < 3; temp++)
		    		residue_name_r[temp] = r_array[i][temp + 17];
		    	residue_name_r[3] = '\0';

		    	for (temp = 0; temp < 4; temp++)
		    		residue_num_r[temp] = r_array[i][temp + 23];
		    	residue_num_r[4] = '\0';
		    	int_residue_num_r = atoi(residue_num_r);

		    	// Store in array_interacting
		    	fprintf(fpt4, "PROTEIN  %5d  %s %s %4d RNA  %5d  %s %s %4d \n", 
		    		int_atom_number_p, atom_name_p, residue_name_p, int_residue_num_p, 
		    		int_atom_number_r, atom_name_r, residue_name_r, int_residue_num_r);

		    	// Store in interacting Protein and RNA arrays
		    	fprintf(fpt2, "%s\n", p_array[j]);
		    	fprintf(fpt3, "%s\n", r_array[i]);
		    	count_interact++;
		    }
		}
	}

	printf("%d\n", count_interact);

	fclose(fpt1);
	fclose(fpt2);
	fclose(fpt3);

	return 0;
}
