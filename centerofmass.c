#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
	FILE *fpt1, *fpt2, *fpt3; // File pointers
	int i, c1, c2, store_atm_no[20000], store_res_no[20000];
	
	c1 = c2 = 0;
	
	// Character arrays
	char line[200], word[5], test1[6], x[9], slno[6], atm_nm[4];
	char res_no[4], store_res_nm[20000][4], chain_id[20000];
	char res_nm[5], store_atm_nm[20000][4];
	
	// Float arrays
	float store_x[20000], store_y[20000], store_z[20000];
	float tot_x, tot_y, tot_z, cm_x, cm_y, cm_z; // floating point variables
	
	// Open the file
	fpt1 = fopen("3snp.pdb", "r"); // open the file in read mode
	
	// Output file
	fpt2 = fopen("out.pdb", "w"); // opening a new output file in write mode
	
	// loop through the file
	while( fgets(line, 200, fpt1) != NULL )
	{
		// looping throught the first 4 letters of the [ATOM  ]
		for (i = 0; i < 4; i++)
		{
			word[i] = line[i]; // store the word (i.e. atom)
		}
		
		word[4] = '\0'; // end the line with '\0'
		
		// check if all stored words are 'ATOM' and then execute
		if ( strcmp(word, "ATOM") == 0 )
		{
			for ( i = 0; i < 5; i++ )
			{
				slno[i] = line[i+6];
			}
			slno[5] = '\0';
			
			// convert char to integer
			store_atm_no[c1] = atoi(slno);
			
			for ( i = 0; i < 3; i++ )
			{
				atm_nm[i] = line[i];
			}
			atm_nm[3] = '\0';
			
			for ( i = 0; i < 3; i++ )
			{
			res_nm[i] = line[i+17];
			}
			res_nm[3] = '\0';
			
			strcpy( store_res_nm[c1], res_nm );
			
			
			for ( i = 0; i < 3; i++ )
			{
				res_nm[i] = line[i+17];
			}
			res_nm[3] = '\0';
			
			strcpy( store_res_nm[c1], res_nm );
			
			chain_id[c1] = line[21];
			
			for ( i = 0; i < 4; i++ )
			{
				res_no[i] = line[i+22];
			}
			res_no[4] = '\0';
			
			store_res_no[c1] = atoi(res_no);
			
			
			// x is temporary array
			
			for ( i = 0; i < 8; i++ )
			{
				x[i] = line[i+30];
			}
			x[8] = '\0';
			
			// convert char to float
			store_x[c1] = atof(x);
			
			for ( i = 0; i < 8; i++ )
			{
				x[i] = line[i+38];
			}
			x[8] = '\0';
			store_y[c1] = atof(x);
			
			for (  i = 0; i < 8; i++ )
			{
				x[i] = line[i+46];
			}
			x[8] = '\0';
			store_z[c1] = atof(x);
			
			c1++;
		}
	}
	
	for ( i = 0; i < c1; i++ )
	{
		fprintf( fpt2, "ATOM  %5d  %s %s %c%4d    %8.3f%8.3f%8.3f\n", store_atm_no[i], store_atm_nm[i], store_res_nm[i], chain_id[i], store_res_no[i], store_x[i], store_y[i], store_z[i] );
	}
	
	
// --- Calculate COM--- //
	
	tot_x = tot_y = tot_z = 0.0;
	for ( i = 0; i < c1; i++ )
	{
		tot_x = tot_x + store_x[i];
		tot_y = tot_y + store_y[i];
		tot_z = tot_z + store_z[i];
	}
	
	cm_x = tot_x / c1;
	cm_y = tot_y / c1;
	cm_z = tot_z / c1;
	
	// COM will be treated as an ATOM
	// 99999, Zn and Z999 are arbit. number
	fprintf(fpt2, "ATOM  99999  Zn  Zn  Z9999    %8.3f%8.3f%8.3f\n", cm_x, cm_y, cm_z);
	
	// Close the files
	fclose(fpt1);
	fclose(fpt2);
}