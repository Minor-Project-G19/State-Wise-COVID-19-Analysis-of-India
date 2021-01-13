typedef struct employment_data
{
	char State[40];
	char Labour_Participation_Rate_20[40];
	char Labour_Participation_Rate_19[40];
}ed;

typedef struct month_rate
{
    char State[40];
    char march_20[40];
    char april_20[40];
    char may_20[40];
    char june_20[40];
    char july_20[40];
    char august_20[40];
    char march_19[40];
    char april_19[40];
    char may_19[40];
    char june_19[40];
    char july_19[40];
    char august_19[40];

}mr;

int row_count;
float total_score1[34];
float unemployment_score[34];
float labour_rate_score[40];
float unemployment_avg_19[40];
float unemployment_avg_20[40];
float unemployment_diff[40];

void display_labour_participation_rate (ed values[ ], int row_count)
{
	int j;
	printf("\n State \t Labour-Particpation-Rate-2020 \t Labour-Particpation-Rate-2019 \n");
	for(j=1;j<35;j++)	
	{
		printf("%s   " ,values[j].State);
		printf("%s   " ,values[j].Labour_Participation_Rate_20);
		printf("%s  \n" ,values[j].Labour_Participation_Rate_19);
	}
}

void display_mr(mr values1[ ], int row_count)
{
	int i;
	for (i=0; i<row_count; i++)
	{
		printf("%s   " ,values1[i].State);
		printf("%s   " ,values1[i].march_19);
		printf("%s   " ,values1[i].april_19);
		printf("%s   " ,values1[i].may_19);
		printf("%s   " ,values1[i].june_19);
		printf("%s   " ,values1[i].july_19);
		printf("%s   " ,values1[i].august_19);
		printf("%s   " ,values1[i].march_20);
		printf("%s   " ,values1[i].april_20);
		printf("%s   " ,values1[i].may_20);
		printf("%s   " ,values1[i].june_20);
		printf("%s   " ,values1[i].july_20);
		printf("%s" ,values1[i].august_20);
		printf("\n");
	}
}

void calculate_month_avg(mr values1[ ],int row_count) //function to calculate the unemployment avg. rate
{
    int i,j;
	for(i=1,j=0;i<row_count,j<34;i++,j++)
	{
	
		unemployment_avg_19[j]=(atof(values1[i].april_19)+atof(values1[i].march_19)+atof(values1[i].may_19)+atof(values1[i].june_19)+atof(values1[i].july_19)+atof(values1[i].august_19))/6;
		unemployment_avg_20[j]=(atof(values1[i].april_20)+atof(values1[i].march_20)+atof(values1[i].may_20)+atof(values1[i].june_20)+atof(values1[i].july_20)+atof(values1[i].august_20))/6;
	}	
}

void display_month_avg(mr values1[], int row_count)
{
	int i,j;
	printf("\nState \tUnemployment-rate-2019 \t Unemployment-rate-2020 \n");
	for(i=0, j=1;i<34, j<35;i++, j++) //function to print unemploymeny avg. rate
	{
		printf("%s", values1[j].State);
	    printf("\t\t%f",unemployment_avg_19[i]);
	    printf( "\t\t\t%f",unemployment_avg_20[i]);
	    printf("\n");
	}
}

void unemployment_rate_score (mr values1[ ],int row_count)
{
	int i;
	calculate_month_avg(values1, row_count);
	for(i=0; i<row_count; i++)
	{
		unemployment_score[i]= 1.0*(unemployment_avg_20[i]-unemployment_avg_19[i]);
	}	
}

void display_unemployment_rate_score (mr values1[ ],int row_count)
{
	int i,j;
	for(i=0, j=1; i<34,j<35; i++,j++)
	{
		printf("\n%s \t", values1[j].State);
		printf("%f", unemployment_score[i]);
	}
}

void labour_particpation_score (ed values [ ], int row_count)
{
	int j,i;
	for(j=0, i=1;j<34,i<35;i++,j++)
	{
		labour_rate_score[j]= 0.5* (atof(values[i].Labour_Participation_Rate_20)-atof(values[i].Labour_Participation_Rate_19));
	}	
}

void display_labour_particpation_score (ed values [ ], int row_count)
{
	int j;
	for(j=0;j<34;j++)	
	{
		printf("%s " ,values[j+1].State);
		printf("%f\n" ,labour_rate_score[j]);
	}	
}

void total_emp_score(mr values1[ ], int row_count)
{
	int i,k,l;
	for (i=0; i<34; i++)
	{
		total_score1[i]= -(unemployment_score[i]) + (labour_rate_score[i]);
	}
	
	FILE *fp10 = fopen ("total_employment_score.txt","w");
	if ( fp10 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	for(k=1,l=0;k<35,l<row_count-1;k++,l++)
	{
		fprintf (fp10, "%s ", values1[k].State);
		fprintf (fp10, "%f\n", total_score1[l]);
	}
	fclose(fp10);
}

void display_total_emp_score(mr values1[ ], int row_count)
{
	int i,j;
	for (i=0,j=1; i<34,j<35; i++,j++)
	{
		printf("%s", values1[j].State);
		printf("\t%f \n", total_score1[i]);
	}
}
void call2(mr values1[ ],ed values[ ],int row_count )
{
	
	
	    unemployment_rate_score(values1, 34);
			labour_particpation_score(values, 34);
			total_emp_score(values1, 34);
}

void employment_sector( int pl)
{
    FILE *file = fopen ("unemployment_data.csv","r");

	if ( file == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	char line[200];
	int row_count = 0;
	int field_count = 0;
	ed values [35];
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
				strcpy(values[i].State, token);
			}

			if(field_count == 1)
			{
				strcpy(values[i].Labour_Participation_Rate_20, token);
			}

			if(field_count == 2)
			{
				strcpy(values[i].Labour_Participation_Rate_19, token);
			}
			token = strtok(NULL, ",");
			field_count++;
		}
		i++;
		printf("\n");
	}
	fclose(file);

	FILE *file1 = fopen ("unemployment_Month_wise.csv","r");

	if ( file1 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	char line1[200];
	row_count = 0;
	field_count = 0;
	mr values1 [40];
	i = 0;

	while ( fgets (line1, sizeof (line1), file1) )
	{
		field_count = 0;
		row_count++;

		char *token;
		token = strtok (line1, ",");

		while (token != NULL)
		{
			if(field_count == 0)
			{
				strcpy(values1[i].State, token);
			}
			if(field_count == 1)
			{
				strcpy(values1[i].march_19, token);
			}
			if(field_count == 2)
			{
				strcpy(values1[i].april_19, token);
			}
			if(field_count == 3)
			{
				strcpy(values1[i].may_19, token);
			}
			if(field_count == 4)
			{
				strcpy(values1[i].june_19, token);
			}
			if(field_count == 5)
			{
				strcpy(values1[i].july_19, token);
			}
			if(field_count == 6)
			{
				strcpy(values1[i].august_19, token);
			}
			if(field_count == 7)
			{
				strcpy(values1[i].march_20, token);
			}
			if(field_count == 8)
			{
				strcpy(values1[i].april_20, token);
			}
			if(field_count == 9)
			{
				strcpy(values1[i].may_20, token);
			}
			if(field_count == 10)
			{
				strcpy(values1[i].june_20, token);
			}
			if(field_count == 11)
			{
				strcpy(values1[i].july_20, token);
			}
			if(field_count == 12)
			{
				strcpy(values1[i].august_20, token);
			}
			token = strtok(NULL, ",");
			field_count++;
		}
		i++;
		printf("\n");
	}
	fclose(file1);
	printf("%d",row_count);
	if(pl ==0)
	{
	
	int choice;
	do
	{
		printf("\n\n **EMPLOYMENT SECTOR** \n\n");
		printf("To View the Following, Enter the Number: \n");
		printf("1. Labour Particpation Rate \n");
		printf("2. Month-wise Data for Unemployment Rate in each state \n");
		printf("3. Average Unemployment Rate for the year 2019 and 2020 \n");
		printf("4. Unemployment Rate Score \n");
		printf("5. Labour Participation Score \n");
		printf("6. Total Score for Employment Score\n");
		printf("7. Exit from the Main Menu\n");
		
		scanf("%d", &choice);
		
		if (choice == 1)
		{
			display_labour_participation_rate (values, row_count);
		}
		else if (choice == 2)
		{
			display_mr(values1, row_count);	
		}
		else if (choice == 3)
		{
			calculate_month_avg(values1,row_count);
			display_month_avg(values1, row_count);
		}
		else if (choice == 4)
		{
			unemployment_rate_score(values1, row_count);
			display_unemployment_rate_score (values1, row_count);
		}
		else if (choice == 5)
		{
			labour_particpation_score(values, row_count);
			display_labour_particpation_score(values,row_count);
		}
		else if (choice == 6)
		{
			unemployment_rate_score(values1, row_count);
			labour_particpation_score(values, row_count);
			total_emp_score(values1, row_count);
			/*
			display_unemployment_rate_score (values1, row_count);
			printf("\n\n\n");
			display_labour_particpation_score(values,row_count);
			printf("\n\n\n");
			*/
			display_total_emp_score(values1,row_count);
		}
	}while(choice !=7);
}
else
{

	call2(values1,values,row_count);
}
}
