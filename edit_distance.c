//Utkarsh Verma 1001663173
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MaxLen:
Student answer:  Theta(T^D)

*/

/* You can write helper functions here */


int minimum(int a, int b, int c)
{
	int x;
	if(a<=b&&a<=c)
		x=a;
	else if(b<=a&&b<=c)
		x=b;
	else if(c<=a&&c<=b)
		x=c;
	
	return x;
}	
int mindistance(char *testword, char *dictword,int dec)
{
	char test[100],dict[100];
	int minimum;
	strcpy(test,testword);
	strcpy(dict,dictword);
	minimum=edit_distance(test,dict,dec);
	return minimum;
}	
int minarray(int num[],int size)
{
	int smallest,i;
	smallest=num[0];
	for(i=1;i<size;i++)
	{
		if(smallest>num[i])
		{
			smallest=num[i];
		}
	}
	return smallest;
}	
int word_finder(char *testword, char *dictword, int dec, int distance)
{
	int calc_distance;
	char test[100],dict[100];
	strcpy(test,testword);
	strcpy(dict,dictword);
	calc_distance=edit_distance(test,dict,dec);
	if(calc_distance==distance)
		return 1;
	else
		return 0;
}	
	
	

int edit_distance(char * first_string, char * second_string, int print_table){
	int arr[strlen(first_string)+1][strlen(second_string)+1];
	//printf("Length of first word%d\n",strlen(first_string)+1);
	//printf("Length of second word%d\n",strlen(second_string)+1);
	int i,j,k,x,y=0;
	arr[0][0]=0;
	for(i=1;i<strlen(first_string)+1;i++)
		arr[i][0]=i;
	for(j=1;j<strlen(second_string)+1;j++)
		arr[0][j]=j;
	
	for(i=1;i<strlen(first_string)+1;i++)
	{	for(j=1;j<strlen(second_string)+1;j++)
		{		
			if(first_string[(i-1)]==second_string[(j-1)])
				arr[i][j]=minimum(1+arr[i-1][j],1+arr[i][j-1],arr[i-1][j-1]);
			
			else
				arr[i][j]=minimum(1+arr[i-1][j],1+arr[i][j-1],1+arr[i-1][j-1]);
		 		
		}
		
	}	
	if(print_table==1) // if 1, then it will print
	{	
		for(i=0;i<strlen(first_string)+1;i++)
		{	/*
			if(i==1)
				printf("  |");
			else
				printf(" %c|",first_string[i]);*/
			for(j=0;j<strlen(second_string)+1;j++)
			{
				if(i==0&&j==0)
				{
					if(j==0)
						printf("  |   |");
					for(x=0;x<strlen(second_string);x++)
					{	printf("  %c|",second_string[x]);
					//	y=y+4;
					}
					printf("\n");
					for(k=0;k<4*strlen(second_string)+7;k++)
						printf("-");
					printf("\n  |");
				}
				
				else if(i!=0&&j==0)
					printf(" %c|",first_string[i-1]);
				if(arr[i][j]<10)
				{	
					printf("  %d|",arr[i][j]);
				}	
				else
				{	
					printf(" %d|",arr[i][j]);
				}
				
			}
			printf("\n");
			for(k=0;k<4*strlen(second_string)+7;k++)
				printf("-");
		printf("\n");
		}
	}
	//return -1;
	return arr[strlen(first_string)][strlen(second_string)];  // replace this line with your code
}
	  
	  
void spellcheck(char * dictname, char * testname){	
	// Write your code here
	int minimumdistance,i;
	int calculated_distance;
	char total_dict_words[100];
	int words,result;
	char dictfile[100];
	strcpy(dictfile,dictname);
	char testfile[100];
	strcpy(testfile,testname);
	char testword[100],dictword[100];
	//char EOF='\O';
	
	printf("\nLoading the dictionary file : %s\n",dictfile);
	printf("\nLoading the test file : %s\n",testfile);
	FILE *filedict;
	filedict=fopen(dictfile,"r");
	FILE *filetest;
	filetest=fopen(testfile,"r");
	
	if(filetest)
	{
		if(filedict)
		{	
			fgets(testword,100,filetest);
			fgets(total_dict_words,100,filedict);
			words=atoi(total_dict_words);
			//printf("Total dict words%d\n: ",words);
			int distance_array[words+1];
			while(fscanf(filetest,"%s",testword)==1)
			{	
				//scanf("%s",testword);
				printf("------Current test word: %s\n",testword);
				//puts(testword);
				i=0; 
				while(fscanf(filedict,"%s",dictword)==1)
				{	//printf("%s\n",dictword);
					calculated_distance=mindistance(testword,dictword,0);
					distance_array[i]=calculated_distance;
					i++;
				}	
				minimumdistance=minarray(distance_array,words);
				printf("Minimum distance: %d\n",minimumdistance);
				rewind(filedict);
				printf("Words that give minimum distance:\n");
				while(fscanf(filedict,"%s",dictword)==1)
				{	
					result=word_finder(testword,dictword,0,minimumdistance);
					if(result==1)
						printf("%s\n",dictword);
				}
				rewind(filedict);
				
			}
		}
		else
		{	printf("Error in opening the dict file.\n");	
			exit(0);
		}	
	}
	else
	{	
		printf("Error in opening the test file.\n");
		exit(0);
	}	
	fclose(filedict);
	fclose(filetest); 
	
}

