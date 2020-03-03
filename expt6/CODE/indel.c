#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

int main (void)
{
	FILE *fpt1;

	int i, j, count_D, count_I, count_both;
	char line[500], chopped_line[31];

	fpt1 = fopen("Mapped.sam", "r");

	count_both = count_D = count_I = 0;

	printf("HI\n");
	while( fgets(line, 500, fpt1) != NULL )
	{
		for(i = 0; i < 30; i++)
		{
			chopped_line[i] = line[i+61];
		}
		chopped_line[30] = '\0';

		for(i = 0; i < 30; i++)
		{
			if(chopped_line[i] == 'D')
			{
				count_D++;
				
				for(j = 0; j < 30; j++)
				{
					if(chopped_line[j] == 'I')
					{
						count_both++;
					}
				}
			}
			else if(chopped_line[i] == 'I')
			{
				count_I++;
			}
		}
	}

	fclose(fpt1);

	return 0;
}