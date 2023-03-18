/*
	The purpose of this program is to calculate the average and max value
	of a data file and then save them on a new file. First, open a file named 
	"data.txt" containing integers with the first one being the total number of 
	integers the file contains, and the rest being the actual values.
	Then, the program computes the average and maximum value of the data 
	and outputs it on the screen and on a new file.
	~Ioannis Symeonidis
*/
#include <stdio.h>     
#include <stdlib.h> 

int * scan_data(char*, int*); //function used to scan the file, takes filename and a reference to the array size
void average_max(int*,int,double*,int*);//calculates the average and max values, which are being referenced at func. call
void display_and_write(int*data, int size, double average, int maximum);//displays the writes the values at a new file

int main(void)
{
	int arr_size;
	int * data =  scan_data("data.txt", &arr_size);//get the data from the file
	int i=0;
	double average;
	int maximum;
	
	average_max(data,arr_size,&average,&maximum);//calculate average and max, call by referance
	display_and_write(data,arr_size,average,maximum);//display and write
	
	free(data);//free the space occupied by the array
}

void display_and_write(int*data, int size, double average, int maximum)
{
	int i;
	printf("\nThe data values are:\n\n");
	for(i=0;i<size;i++)
		printf("%d ", data[i]);
	printf("\n\nThe average value is: %lf\n\nAnd the maximum is  : %d\n", average, maximum);
	
	FILE* fp = fopen("answer-hw3.txt","w"); //open a file, write the data and then close it.
	fprintf(fp,"%lf   %d", average,maximum);
	
	fclose(fp);//close the file
	
}
void average_max(int*data,int size, double*av, int*max)
{
	int i=0;
	(*av)=0;
	(*max)=0;
	//Now add all scanned data to the average
	//and then divide by the size to get the actual average value.
	//Calculate the max value at the sime time.
	for(i=0;i<size;i++)
	{
		(*av)+=(double)data[i];
		if(data[i]>(*max))
			(*max)=data[i]; 
	}
	(*av)/=size;
}
int* scan_data(char* filename, int* arr_size)
{
	FILE* fp = fopen(filename,"r"); //open the file as read mode 
	int size;
	fscanf(fp,"%d",&size); //get the size of the array
	int *data = malloc(sizeof(int)*size);//dynamically create the array
	int element;
	int i=0;
	for(;fscanf(fp,"%d",&element)!=EOF;i++)//initialise the array with the scanned data
		data[i] = element;
	*arr_size = size;
	
	fclose(fp);//close the file and return the array
	
	return data;
}
