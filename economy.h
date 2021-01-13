#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct economy_data
{
	char States[40];
	char Growth_March[40];
	char Growth_June[40];
	char Growth_July[40];  
	char Growth_August[40];
	char Gdp_19[40];
	char Gdp_20[40];
	char Inflation_rate[40];
}ecd;

float avg_growth[40];
float gdp_score[40];
float inflation_rate1[40];
float total_score2[34];

void display_ecd (ecd values2[],int row_count)
{
	int i;
	for (i=0; i<row_count; i++)
	{
		printf("%s \t",values2[i].States);
		printf("%s \t" ,values2[i].Growth_March); 
		printf("%s \t" ,values2[i].Growth_June);
		printf("%s \t" ,values2[i].Growth_July);
		printf("%s \t" ,values2[i].Growth_August);
		printf("%s \t" ,values2[i].Gdp_19);
		printf("%s \t" ,values2[i].Gdp_20);
		printf("%s \t" ,values2[i].Inflation_rate);
		printf("\n");
	}
}

void avg_growth_calculate(ecd values2[ ],int row_count)
{
	int i,j,k,l;
	for(i=1,j=0;i<row_count,j<34;i++,j++)
	{
		avg_growth[j] = 0.5 * (atof(values2[i].Growth_March)+atof(values2[i].Growth_June)
                      +atof(values2[i].Growth_July)+atof(values2[i].Growth_August));
	}
	
	FILE *fp1101 = fopen ("growth_score.txt","w");
	if ( fp1101 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp1101, "%s ", values2[k].States);
		fprintf (fp1101, "%f\n",avg_growth[l]);
	}
	fclose(fp1101);
}
void avg_growth_print(ecd values2[ ],int row_count)
{
    int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++) 
	{
		printf("%s ", values2[j].States);
	    printf("%f",avg_growth[i]);
	    printf("\n");
	}
}

void gdp_score_calculate(ecd values2[ ],int row_count)
{
    int i,j;
	for(i=1,j=0;i<35,j<34;i++,j++)
	{
		float x = atof(values2[i].Gdp_20);
		float y = atof(values2[i].Gdp_19);
		//printf("%f \t %f \n", atof(values2[i].Gdp_20), atof(values2[i].Gdp_19));
		gdp_score[j] = 1.0 * (x - y)*10;
	}
}
void gdp_score_print(ecd values2[],int row_count)
{
	int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++)
	{
		printf("%s ", values2[j].States);
		printf("%f",gdp_score[i]);
		printf("\n");
	}
}

void inflation_score(ecd values2[], int row_count)
{
	int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++)
	{
		inflation_rate1[i] = 0.5 *(atof(values2[j].Inflation_rate));
	}
}
void inflation_score_print(ecd values2[],int row_count)
{
	int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++)
	{
		printf("%s ",values2[j].States);
		printf("%f",inflation_rate1[i]);
		printf("\n");
	}
}

void total_economy_score(ecd values2[], int row_count)
{
	int i,k,l;
	for(i=0;i<row_count;i++)
	{
		total_score2[i] =  - (inflation_rate1[i]) + (gdp_score[i]);
	}
	
	FILE *fp100 = fopen ("total_economy_score.txt","w");
	if ( fp100 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	for(k=1,l=0;k<35,l<row_count-1;k++,l++)
	{
		fprintf (fp100, "%s ", values2[k].States);
		fprintf (fp100, "%f\n", total_score2[l]);
	}
	fclose(fp100);
}
void total_economy_score_print(ecd values2[], int row_count)
{
	int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++)
	{
		printf("%s",values2[j].States);
		printf("\t\t%f",total_score2[i]);
		printf("\n");
	}
}

void call3( ecd values2[ ],int row_count)
{
	avg_growth_calculate( values2, row_count);
		gdp_score_calculate( values2, row_count);
		inflation_score(values2, row_count);
		total_economy_score( values2, row_count);
}


	
void economy_main(int pl )
{	
	
	FILE *file = fopen ("economy.csv","r");
	if ( file == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	
	char line[200];
	
	int row_count = 0;
	int field_count = 0;
	
	ecd values2 [40];
	int i = 0;
	
	while ( fgets (line, sizeof (line), file) )
	{
		field_count = 0;
		row_count++;
		
		
		char *token;
		token = strtok (line, ",");
		
		while (token != NULL)
		{
			if(field_count == 0)
			{
				strcpy(values2[i].States, token);
			}
			if(field_count == 1)
			{
				strcpy(values2[i].Growth_March, token);
			}
			
			if(field_count == 2)
			{
				strcpy(values2[i].Growth_June, token);
			}
			
			if(field_count == 3)
			{
				strcpy(values2[i].Growth_July, token);
			}
			
			if(field_count == 4)
			{
				strcpy(values2[i].Growth_August, token);
			}
			
			if(field_count == 5)
			{
				strcpy(values2[i].Gdp_19, token);
			}
			
			if(field_count == 6)
			{
				strcpy(values2[i].Gdp_20, token);
			}
			
			if(field_count == 7)
			{
				strcpy(values2[i].Inflation_rate, token);
			}
			
			token = strtok(NULL, ",");
			field_count++;
		}
		i++;
		printf("\n");
	}

	fclose(file);
	int choice;
	if(pl==0)
	{
	
		do
		{
			printf("\n\n Economy Sector \n\n");
			printf("To View the Following, Enter the Number: \n");
			printf("1. To view economy csv file \n");
	        printf("2. To view average score of growth\n");
			printf("3. To view GDP score\n");
			printf("4. To view Inflation score\n");
			printf("5. To view Total Economy Score\n");
		
			scanf("%d", &choice);
			
			if (choice == 1)
			{
				printf("####CSV file\n####");
				display_ecd(values2, row_count);
		 	}
	        else if (choice == 2)
	        {
				printf("####Average Growth Score\n####");
	            avg_growth_calculate(values2, row_count);
	            avg_growth_print(values2, row_count);
	        }
			else if (choice == 3)
			{
				printf("####GDP Score\n####");
				gdp_score_calculate(values2, row_count);
				gdp_score_print(values2, row_count);
			}
			else if (choice == 4)
			{
				printf("####Inflation Score\n####");
				inflation_score(values2, row_count);
				inflation_score_print(values2, row_count);
			}
			else if (choice == 5)
			{
				printf("####Total Score\n####");
				avg_growth_calculate(values2, row_count);
				gdp_score_calculate(values2, row_count);
				inflation_score(values2, row_count);
				total_economy_score(values2, row_count);
				total_economy_score_print(values2, row_count);
			}
		}while(choice !=7);
	}
	else
	{
		call3(values2,row_count);
	}
}

