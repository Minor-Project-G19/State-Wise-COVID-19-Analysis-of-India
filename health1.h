typedef struct health_data    //Structure of health data
{
	char State[40];
	char State_sort[40];
	char Confirmed_Cases[40];
	char Active_Cases[40];
	char Recovered_Cases[40];
	char Deaths[40];
	char Tested[40];
	char Population[40];
}hd;
// Global variables
float death_score[34];   //Array for death score
float Tested_score[34];  //Array for Test case score
float recover_rate[34];  //Array for recovery score
float covid_effect[34];  //Arrray for covid effected score
float total_state_score[34]; //Array for total state score

//Global variables

void display (hd values[],int row_count)
{
	int i;
	for (i=0; i<row_count; i++)
	{
		printf("%s   " ,values[i].State);
		printf("%s   " ,values[i].Confirmed_Cases);
		printf("%s   " ,values[i].Active_Cases);
        printf("%s   " ,values[i].Recovered_Cases);
        printf("%s   " ,values[i].Deaths);
        printf("%s   " ,values[i].Tested);
        printf("%s   \n" ,values[i].Population);
	}
}

void total_score( hd values[ ])                                   //function to evaluate the total_score of the state
{
	int i=0,k,l;
	for(i=0;i<34;i++)
	{
		total_state_score[i]= -(death_score[i]) + Tested_score[i] - (covid_effect[i]);
	}

	FILE *fp6 = fopen ("total_health_score.txt","w");
	if ( fp6 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp6, "%s ", values[k].State_sort);
		fprintf (fp6, "%f\n", total_state_score[l]);
	}
	fclose(fp6);
	
}

void total_score_print(hd values[ ],float total_state_score[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)        //loop to display state with their score
	{
  		printf("%s  ",values[k].State_sort);
  		printf("%f",total_state_score[l]);
  		printf("\n");
	}
}

void value_set_Death(hd values[ ],int row_count) //function to evaluate the Death score
{
	int use,use1;
	int k=0,l,i;
	for(l=1;k<34,l<35;k++,l++)
	{
  		use=atoi(values[l].Deaths);
        use1=atoi(values[l].Population);
  		death_score[k] = 1.0*((float)use/use1)*100000 ;
  	}

	FILE *fp = fopen ("deaths.txt","w");
	if ( fp == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp, "%s ", values[k].State);
		fprintf (fp, "%f\n", death_score[l]);
	}

	fclose(fp);
}

void death_score_print( hd values[ ],float death_score[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)
  	{
  		printf("%s\t\t\t\t",values[k].State);
  		printf("%f",death_score[l]);
  		printf("\n");
	}
}

void value_set_Tested(hd values[ ],int row_count)     //function to evaluate the test score
{
	int use,use1;
	int k=0,l;
  	for(l=1;k<34,l<35;k++,l++)
  	{
  		use=atoi(values[l].Tested);
    	use1=atoi(values[l].Population);
  		Tested_score[k]= ((float)use/use1) * 0.10 *1000 ;
  	}

  	FILE *fp3 = fopen ("tested.txt","w");
	if ( fp3 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp3, "%s ", values[k].State);
		fprintf (fp3, "%f\n", Tested_score[l]);
	}
	fclose(fp3);
}
void Tested_score_print( hd values[ ],float Tested_score[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)
  	{
  		printf("%s  ",values[k].State);
  		printf("%f\n",Tested_score[l]);
  	}
}

void recovery_rate(hd values[ ],int row_count)           // function to calculate recovery rate
{
	int i,use,use1,k=0,l;
	for(l=1;k<34,l<35;k++,l++)
	{
  		use=atoi(values[l].Recovered_Cases);
  		use1=atoi(values[l].Confirmed_Cases);
		recover_rate[k]= ((float) use/ use1)*100;
  	}

  	FILE *fp4 = fopen ("recovery.txt","w");
	if ( fp4 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp4, "%s ", values[k].State);
		fprintf (fp4, "%f\n", recover_rate[l]);
	}

	fclose(fp4);
}

void recovery_rate_print( hd values[ ],float recover_rate[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)
  	{
  		printf("%s  ",values[k].State);
  		printf("%f\n",recover_rate[l]);
  	}
}

void covid_effected(hd values[ ],int row_count)              //function to evaluate covid_effected scores
{

	int i,use,use1,k=0,l;
	for(l=1;k<34,l<35;k++,l++)
	{
  		use=atoi(values[l].Confirmed_Cases);
  		use1=atoi(values[l].Population);
  		covid_effect[k]= ((float) use/ use1)*0.75*1000 ;
	}

	FILE *fp1 = fopen ("covid_effected.txt","w");
	if ( fp1 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	for(k=1,l=0;k<35,l<34;k++,l++)
  	{
  		fprintf (fp1, "%s ", values[k].State);
		fprintf (fp1, "%f\n", covid_effect[l]);
	}

	fclose(fp1);
}

void covid_effected_print(hd values[ ],float covid_effect[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)
  	{
  		printf("%s  ",values[k].State);
  		printf("%f\n",covid_effect[l]);
	}
}
void call1(hd values[ ],int row_count )
{
	  value_set_Death(values,row_count);
	    value_set_Tested(values,row_count);
	    covid_effected(values,row_count);
	     recovery_rate(values,row_count);
	     total_score(values);
}


void health_sector(int pl )
{
	//clrscr( );
	FILE *file = fopen ("health_2.csv","r");

	if ( file == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	char line[200];
	int row_count = 0;
	int field_count = 0;
	hd values [40];
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

			if(field_count == 0)
			{
				strcpy(values[i].State_sort, token);
			}

			if(field_count == 1)
			{
				strcpy(values[i].Confirmed_Cases, token);
			}

			if(field_count == 2)
			{
				strcpy(values[i].Active_Cases, token);
			}

			if(field_count == 3)
			{
				strcpy(values[i].Recovered_Cases, token);
			}

			if(field_count == 4)
			{
				strcpy(values[i].Deaths, token);
			}

			if(field_count == 5)
			{
				strcpy(values[i].Tested, token);
			}

			if(field_count == 6)
			{
				strcpy(values[i].Population, token);
			}

			token = strtok(NULL, ",");
			field_count++;

		}
		i++;
		printf("\n");
	}


	fclose(file);
	value_set_Death(values,row_count);
	value_set_Tested(values,row_count);
	covid_effected(values,row_count);
	recovery_rate(values,row_count);
	total_score(values);
	if(pl==0)
	{
	
    int choice;

	do
	{
		printf("**HEALTH SECTOR**\n");
		printf("To View the Following, Enter the Number: \n1 Health File \n2 Death Score \n3 Tested Score\n");
		printf("4 Covid Effected Score\n5 Final Health State Score\n");
		printf("6 Recovery Rate For Each State\n 7 Exit from the Main Menu\n");
    	scanf("%d",&choice);

		if(choice == 1)
    	{
        	display(values, row_count);
		}
    	else if(choice == 2)
    	{

			death_score_print(values,death_score);

		}
    	else if(choice == 3)
    	{
     	   Tested_score_print(values,Tested_score);

		}
    	else if(choice == 4)
    	{
     	   covid_effected_print(values,covid_effect);

		}
    	else if(choice == 5)
    	{
     	   total_score_print(values,total_state_score);

		}
		else if(choice ==6)
		{
		   recovery_rate_print(values,recover_rate);
		}
	
   	} while(choice != 7);  //atoi function is used to convert string value to integer value
   }
   else
   {
   
   	call1( values,row_count);
   }
}

