#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "emp1 .h"
#include "health1.h"
#include "economy.h"
typedef struct state  
{
	char State[40];
	char State_Sort[40];
}st;

char  state_Grade[34];       //Array for storing state grade
int no_grades[5]={0,0,0,0,0};  //Array for storing total no of states in each grade
char grades[5]={'O','A','B','C','D'}; // Different grades used
float final_score[34];

void calculate_final_score(st values[], float total_score2[ ],float total_state_score[ ],float total_score1[ ] )
{  
    int i,k,l;
	for(i=0;i<34;i++)
	{
		final_score[i]=total_score2[i]+total_score1[i]+total_state_score[i];
	}	
	
	FILE *fp101 = fopen ("final_score.txt","w");
	if ( fp101 == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}
	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		fprintf (fp101, "%s ", values[k].State);
		fprintf (fp101, "%f\n",final_score[l]);
	}
	fclose(fp101);
}

void find_min_max(float final_score[ ],float *max,float *min) //function to find the minimum and maximum score of a state
{
 	*max = final_score[0];
 	*min = final_score[0];
	//printf("%f   %f  \n",max,min);
	int i;
	for( i = 1; i < 34; i++) 
	{
	
		if ( final_score[i] < *min)
        {
       		*min = final_score[i];
       	}

		if(final_score[i] > *max)
		{
			*max = final_score[i];
		}
	}
}
void swap(float *xp, float *yp)  //swap function for sorting state marks
{
	float temp = *xp;
    *xp = *yp;
   	*yp = temp;
}
void score_sort( float final_score[ ],st values[ ]) //sorting function for state score and state values
{
	
	int i, j;
	char temp[40];   
	
    for (i = 0; i < 33; i++)
   	{
	    for (j = 0; j < 34-i-1; j++)
		{
        	if (final_score[j] > final_score[j+1])
       		{
        		swap(&final_score[j],&final_score[j+1]);
        		
				strcpy(temp,values[j+1].State_Sort);
			    strcpy(values[j+1].State_Sort,values[j+2].State_Sort);
			    strcpy(values[j+2].State_Sort,temp);
			    
        	}
        }
    }
    
}

void view_grade(st values[ ],char state_Grade[ ])
{
	int k,l;
	for(k=1,l=0;k<35,l<34;k++,l++)
	{
		printf ("%s ", values[k].State_Sort);
		printf ("%c\n", state_Grade[l]);
	}
}    
	
void grade_decider(float final_score[ ],st values[ ]) //function for deciding the grade according to the score
{
	float max_marks,min_marks;
	int i,k,l;
	find_min_max(final_score,& max_marks,&  min_marks);
	//printf("Max marks = %f\n",max_marks);
	//printf("Min marks =%f\n",min_marks);
	score_sort( final_score,values);
	float second_highest=final_score[32];
	float second_lowest=final_score[1];
	float range=second_highest-second_lowest;   //Range for deciding the grades A,B and C
	//printf("%f\n",range);
	float plus= (range)/3 ;                     //Incremental value for the entire range
	//printf("%f\n",plus);
	float val1=final_score[1]+plus;
	//printf("%f\n",val1);
	float val2=val1+plus;
	//printf("%f\n\n\n\n",val2);

	for(i=0;i<34;i++)
    {
		if(final_score[i]== min_marks)
		{
			state_Grade[i] ='D' ; //Minimum grade is given to the state with least score
			no_grades[4]++ ;
		}

		else if(final_score[i]== max_marks)
		{
			state_Grade[i]='O';   //Maximum garde is given to the state with highest score
			no_grades[0]++ ;
		}

		else if(final_score[i]>=second_lowest && final_score[i] < val1)
		{
			state_Grade[i]='C';
			no_grades[3]++ ;
		}

		else if(final_score[i] >=val1 && final_score[i] < val2)
		{
			state_Grade[i]='B';
			no_grades[2]++ ;
		}

		else if(final_score[i] >= val2 && final_score[i] <=second_highest)
		{
			state_Grade[i]='A' ;
			no_grades[1]++ ;
		}
		else
		{
			state_Grade[i]='N';
		}
	}
	view_grade(values,state_Grade); 
	
}

void display_final_score( st values[ ],float final_score[ ])
{
	int i,j;
	for(i=0,j=1;i<34,j<35;i++,j++)
	{
		printf("%s   %f\n",values[j].State,final_score[i]);
	}
	printf("\n\n\n");
	
}

int main ( )
{ 
FILE *file = fopen ("States_name.csv","r");

	if ( file == NULL)
	{
		perror ("UNABLE TO OPEN THE FILE! \n");
		exit(1);
	}

	char line[200];
	int row_count = 0;
	int field_count = 0;
	st values [40];
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
				strcpy(values[i].State_Sort, token);
			}

			token = strtok(NULL, ",");
			field_count++;

		}
		i++;
		printf("\n");
	}
    fclose(file);
    int pl;
	char sec_choice;
	printf("SECTORS: \nA) Health \nB) Employment \nC) Economy \n D) For Total Score ");
	printf("Which sector do you wish to view?\n");
	scanf("%c", &sec_choice);
	if(sec_choice == 'A')
	{
	   pl=0;
		health_sector(pl);
	}
	
	if(sec_choice == 'B')
	{
		pl=0;
		employment_sector ( pl);
	}
	
	if(sec_choice == 'C')
	{
		pl=0;
		economy_main( pl);
	}
	if(sec_choice == 'D')
	{
		pl=1;
		health_sector( pl);
   		employment_sector(pl );
   		economy_main( pl);
		calculate_final_score(values, total_score2,total_state_score,total_score1 );
    	display_final_score( values,final_score);
    	grade_decider(final_score,values);
    }
    
return 0;
}

