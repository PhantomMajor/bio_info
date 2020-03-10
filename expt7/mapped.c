/*-
- To check the number of mapped reads per gene
- */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
	FILE *fpt1, *fpt2;

	int i, j=0, gene_counter=0, temp_count, red_count, k;
	char line[1000], gene_name[8], store_gene_name[100000][8], temp_g[8], read_gene[50000][8];

	fpt1 = fopen("Out1.sam", "r");
	fpt2 = fopen("counter_table.txt", "w");

	while( fgets(line, 1000, fpt1) != NULL )
	{
		i = 0;
		while(line[i] != 'Y')
		{
			i++;
		}

		for(j = 0; j < 7; j++)
		{
			gene_name[j] = line[i];
			i++;
		}
		gene_name[8] = '\0';

		if (gene_name[2] != ':')
		{
			// exclude from gene name list
			// eg. YT:Z:UU
			strcpy(store_gene_name[gene_counter], gene_name);
			gene_counter++;
		}

		/*
		for (j = 0; j < gene_counter; j++)
		{
			printf("%s\n", store_gene_name[j]);
		}*/
		// printf("%i\n", gene_counter);
	}

	// COUNTING THE NUMBER OF OCCURANCES
	red_count = 0;

	fprintf(fpt2, "GENE    -- COUNT\n");
	for(i = 0; i < gene_counter; i++)
	{
		strcpy(temp_g, store_gene_name[i]);

		for(k = 0; k < red_count + 1; k++)
		{
			if (strcmp(temp_g, read_gene[k]) != 0)
			{
				temp_count = 0;
				// not identical strings
				for(j = 0; j < gene_counter; j++)
				{
					if( strcmp(temp_g, store_gene_name[j]) == 0)
					{
						temp_count++;
					}
				}
			}
		}

		strcpy(read_gene[red_count], temp_g);
		red_count++;

		fprintf(fpt2, "%s -- %i\n", temp_g, temp_count);
	}

	fclose(fpt1);
	fclose(fpt2);

	return 0;
}