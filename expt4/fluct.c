#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    FILE *fpt1, *fpt2, *fpt3;

    int Acount = 0, Rcount = 0;
    int i,c1,c2,j,store_atm_no[20000],store_res_no[20000],interactc=0,minia,minib,minic,minid,maxia,maxib,maxic,maxid;
    
    double bMaxA=0.0,bMinA=200.0,bMaxB=0.0,bMinB=200.0,bMaxC=0.0,bMinC=200.0,bMaxD=0.0,bMinD=200.0;
    c1=c2=0;
    char line[200], word[5], test1[6], x[9],slno[6],atm_nm[4],res_nm[4],store_res_nm[20000][4],ch_id[20000],res_no[5],store_atm_nm[20000][4];
    double  bVal[20000],bTemp[20000];
    fpt1=fopen("1oj6.pdb","r");


    while(fgets(line,200,fpt1)!=NULL){
            for(i=0;i<4;i++) word[i]=line[i];
            word[4]='\0';

            if(strcmp(word,"ATOM")==0){
                    for(i=0;i<5;i++)  slno[i]=line[i+6];
                    slno[5]='\0';
                    store_atm_no[c1]=atoi(slno);

                    for(i=0;i<3;i++) atm_nm[i]=line[i+13];
                    atm_nm[3]='\0';
                    strcpy(store_atm_nm[c1],atm_nm);

                    for(i=0;i<3;i++) res_nm[i]=line[i+17];
                    res_nm[3]='\0';
                    strcpy(store_res_nm[c1],res_nm);

                    ch_id[c1]=line[21];

            	for(i=0;i<4;i++) res_no[i]=line[i+22];
                    res_no[4]='\0';
                    store_res_no[c1]=atoi(res_no);      

                    for(i=0;i<6;i++) x[i]=line[i+60];
                    x[6]='\0';
                    bVal[c1]=atof(x);


                    c1++;


           }

    }

	for(i=0;i<c1;i++){
		
;
		if(strcmp(store_atm_nm[i],"N  ")==0 && strcmp(store_atm_nm[i+1],"CA ")==0 && strcmp(store_atm_nm[i+2],"C  ")==0 && strcmp(store_atm_nm[i+3],"O  ")==0 ){
			bTemp[i]=(bVal[i]+bVal[i+1]+bVal[i+2]+bVal[i+3])/4.000000;
			
			if (ch_id[i]=='A'){

				if(bTemp[i] < bMinA){ bMinA = bTemp[i];minia=i;} 
                        	if(bTemp[i] > bMaxA){ bMaxA = bTemp[i];maxia=i;}
		
			}

                        if(ch_id[i]=='B'){

                                if(bTemp[i] < bMinB){ bMinB = bTemp[i];minib=i;}
                                if(bTemp[i] > bMaxB){ bMaxB = bTemp[i];maxib=i;}
                        }


                        if(ch_id[i]=='C'){

                                if(bTemp[i] < bMinC){ bMinC = bTemp[i];minic=i;}
                                if(bTemp[i] > bMaxC){ bMaxC = bTemp[i];maxic=i;}

                        }


                        if(ch_id[i]=='D'){

                                if(bTemp[i] < bMinD){ bMinD = bTemp[i];minid=i;}
                                if(bTemp[i] > bMaxD){ bMaxD = bTemp[i];maxid=i;}

                        }


		}
	


	}

	printf("chain=%c %d %s %3.2f %d %s %3.2f\n",ch_id[minia],store_res_no[minia],store_res_nm[minia],bTemp[minia],store_res_no[maxia],store_res_nm[maxia],bTemp[maxia]);

        
	printf("chain=%c %d %s %3.2f %d %s %3.2f\n",ch_id[minib],store_res_no[minib],store_res_nm[minib],bTemp[minib],store_res_no[maxib],store_res_nm[maxib],bTemp[maxib]);
	printf("chain=%c %d %s %3.2f %d %s %3.2f\n",ch_id[minic],store_res_no[minic],store_res_nm[minic],bTemp[minic],store_res_no[maxic],store_res_nm[maxic],bTemp[maxic]);
	printf("chain=%c %d %s %3.2f %d %s %3.2f\n",ch_id[minid],store_res_no[minid],store_res_nm[minid],bTemp[minia],store_res_no[maxid],store_res_nm[maxid],bTemp[maxid]);

	fclose(fpt1);
        

}




























