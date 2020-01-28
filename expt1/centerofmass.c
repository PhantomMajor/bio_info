/* CODE TO FIND THE CENTER OF MASS OF A GIVEN PROTEIN */

/* 
	INPUT -- pdb file
	OUTPUT -- new pdb file (com.pdb) with the center of mass
	ASSUMPTION -- Same weight of all atoms
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>


int main(void)
{
	FILE *fpt1; // File pointer for file to be opened (3snp.pdb)
	FILE *fpt2; // File pointer for output file (created after running the program)

	// File info [Magic Numbers]
	int num_cols_in_file = 80; // Maximum 80 columns are in the file
	int max_word_length = 5; // Max length of a word
	int atom_len = 4; // Max length of atom column
	int atom_serial_no_len = 5; // Max length of atom-serial-no column
	int atom_name_len = 4; // Max length of atom name
	int residue_no_len = 4; // Max length of residue number
	int coord_len = 8; // Max length of coordinates


	// Counter variables
	// i -- temp variable for counting in loops
	// temp_row_indicator -- variable for indicating the index of the current row.
	int i, temp_row_indicator;

	// Arrays to store atom number and residue number
	int store_atm_no[20000], store_res_no[20000];
	
	temp_row_indicator  = 0; // init to 0 to point to the first row
	
	// Character arrays to store
	/* 
		line -- array to read columns from the input file and store the 
				information in the "read line". Helps in looping through
				the columns.
		word -- temporary variable to store the word read from the line
		temp_array -- temporary array used for holding the values of coordinates in char form
		slno -- to store the atom serial number in string format
		atm_nm -- store atom number of current row
		res_no -- residue number
		store_res_nm -- 2-D array of all the residue names in order.
		chain_id -- variable to store the chain id of the atom from the input file.
		res_nm -- temporary variable to store residue name
		store_atm_nm -- 2-D Array to store the name of the atoms.
	 */
	char line[num_cols_in_file], word[max_word_length], test1[6], temp_array[9], slno[6], atm_nm[4];
	char res_no[4], store_res_nm[20000][4], chain_id[20000];
	char res_nm[5], store_atm_nm[20000][4];
	
	// Float arrays
	/* 
		store_x -- to store the x coordinates of all the atoms
		store_y -- to store the y coordinates of all the atoms
		store_z -- to store the z coordinates of all the atoms
	*/
	float store_x[20000], store_y[20000], store_z[20000];

	// Float variables
	/*
		tot_x -- to store the (non-weighted) sum of x coordinates
		tot_y -- to store the (non-weighted) sum of y coordinates
		tot_z -- to store the (non-weighted) sum of z coordinates

		cm_x -- to store the x coordinate of the com
		cm_y -- to store the y coordinate of the com
		cm_z -- to store the z coordinate of the com
	*/
	float tot_x, tot_y, tot_z, cm_x, cm_y, cm_z;
	
	// Open the file 3snp.pdb in read mode
	fpt1 = fopen("3snp.pdb", "r");
	
	// Output file named "out.pdb"
	fpt2 = fopen("out.pdb", "w"); // opening a new output file in write mode
	
	// Read the line (row) and store it in the 'line' variable
	/*
		while there is a line in input file <scan from T to B>, or
		while the characters are less than "num_cols_in_file" <scan from L to R>, or
		while newline character is not read.
	*/
	while( fgets(line, num_cols_in_file, fpt1) != NULL )
	{
		// looping throught the first 4 letters of the ['ATOM']
		// one less than max number, because last element will be NULL CHARACTER
		for (i = 0; i < (atom_len); i++)
		{
			word[i] = line[i]; // store the word (i.e. "ATOM")
		}
		word[atom_len] = '\0'; // end the line with '\0'
		
		/* 
			---- EXTRACTING THE DATA FROM THE FILE ----

			Since we are calculating the COM only for the protein
			therefore we have to consider the weights of only the atoms

			Therefore, scan through all the "ATOM" parts of the table
		*/
		// check if all stored words are 'ATOM' and then execute further
		if ( strcmp(word, "ATOM") == 0 )
		{
			/* For a particular row (i.e. one line) */

			// atom serial number
			// Loop through the atom serial number [col 7 to 11], i.e. index 6 to 10
			for ( i = 0; i < atom_serial_no_len; i++ )
			{
				slno[i] = line[i+6];
			}
			slno[5] = '\0'; // NULL CHARACTER at the end of the string
			store_atm_no[temp_row_indicator] = atoi(slno); // convert string to integer
			
			// atom name
			// Loop through the atom name [col 13 to 16], i.e. index 12 to 15
			for ( i = 0; i < 3; i++ )
			{
				atm_nm[i] = line[i + 13];
			}
			atm_nm[3] = '\0'; // NULL CHARACTER at the end of the string
			// storing all the atom names in order
			strcpy( store_atm_nm[temp_row_indicator], atm_nm );
			
			// residue name
			// Loop through the residue name [col 18 to 20], i.e. index 17 to 19
			for ( i = 0; i < 3; i++ )
			{
				res_nm[i] = line[i+17];
			}
			res_nm[3] = '\0'; // NULL CHARACTER at the end of the string			
			// storing all the residue names in order
			strcpy( store_res_nm[temp_row_indicator], res_nm );
			

			// chain id
			chain_id[temp_row_indicator] = line[21]; // according to the format
			

			// residue number
			for ( i = 0; i < residue_no_len; i++ )
			{
				res_no[i] = line[i+22];
			}
			res_no[residue_no_len] = '\0';
			// storing the residue number as int in an array
			store_res_no[temp_row_indicator] = atoi(res_no);
			
			
			/* Reading the coordinates */
			
			for ( i = 0; i < coord_len; i++ )
			{
				// for reading x coordinate, index goes from 30 to 37
				temp_array[i] = line[i+30];
			}
			temp_array[coord_len] = '\0';
			// convert string to float and store the float in the array for storing x
			store_x[temp_row_indicator] = atof(temp_array);
			
			for ( i = 0; i < coord_len; i++ )
			{
				// for reading y coordinate, index goes from 38 to 45
				temp_array[i] = line[i+38];
			}
			temp_array[coord_len] = '\0';
			// convert string to float and store the float in the array for storing y
			store_y[temp_row_indicator] = atof(temp_array);
			
			for (  i = 0; i < coord_len; i++ )
			{
				// for reading y coordinate, index goes from 46 to 455
				temp_array[i] = line[i+46];
			}
			temp_array[coord_len] = '\0';
			// convert string to float and store the float in the array for storing z
			store_z[temp_row_indicator] = atof(temp_array);
			
			/* All the data required from the "current row" has been extracted */
			// to move to next row, increment the row indicator/ counter by one
			temp_row_indicator++;
		}
	}
	
	// currently, the temp_row_indicator is set to the last row number
	// (after final iteration of the while loop)

	// Writing the scrapped data to the output file (for visualization)
	for ( i = 0; i < temp_row_indicator; i++ )
	{
		fprintf(
			fpt2,
			"ATOM  %5d  %s %s %c%4d    %8.3f%8.3f%8.3f\n",
			store_atm_no[i],
			store_atm_nm[i],
			store_res_nm[i],
			chain_id[i],
			store_res_no[i],
			store_x[i],
			store_y[i],
			store_z[i]);
	}
	
	
	// --- Calculate COM --- //
	tot_x = tot_y = tot_z = 0.0;
	for ( i = 0; i < temp_row_indicator; i++ )
	{
		tot_x = tot_x + store_x[i];
		tot_y = tot_y + store_y[i];
		tot_z = tot_z + store_z[i];
	}
	// Sum of the individual coordinates

	// calculation of center of mass
	cm_x = tot_x / temp_row_indicator;
	cm_y = tot_y / temp_row_indicator;
	cm_z = tot_z / temp_row_indicator;
	
	// COM will be treated as an ATOM
	// 99999, Zn and Z999 are arbit. number
	fprintf(
		fpt2, "ATOM  99999 ZZZ   Z Z  99    %8.3f%8.3f%8.3f\n",
		cm_x,
		cm_y,
		cm_z);
	
	// Close the files
	fclose(fpt1);
	fclose(fpt2);

	return 0;
}