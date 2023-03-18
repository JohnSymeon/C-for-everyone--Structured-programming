/*
This script uses a type date containing a month and the day of the month,
and prints the next day.
*/
#include <stdio.h>           //standard library
#include <stdlib.h>          //library used for malloc

//enum for the convenient representation of months
typedef enum month{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec} month;
typedef struct date{   //struct date contains the month and the day of the month
	month m; 
	int d;
	} date;
//Functions
month next_month(month); //this function returns the next month of the input
date next_day(date);    //returns the next date from the input
void printdate(date);	//prints the date that is fed
//Main
int main(void)
{
	//Create an instance of a type date
	//and then print it
	//and then print the next date.
    date d0; 
    d0.d = 1;
    d0.m = jan;
    printdate(d0);
    printdate(next_day(d0));
    
    date d1;
    d1.d = 28;
    d1.m = feb;
    printdate(d1);
    printdate(next_day(d1));
    
    date d2;
    d2.d = 14;
    d2.m = mar;
    printdate(d2);
    printdate(next_day(d2));
    
    date d3;
    d3.d = 31;
    d3.m = oct;
    printdate(d3);
    printdate(next_day(d3));
    
    date d4;
    d4.d = 31;
    d4.m = dec;
    printdate(d4);
    printdate(next_day(d4));
}
//Functions
month next_month(month m)
    {								//the use of the operator % makes sure the next month is always correct
        return((m + 1) % 12); 		// if the month is before December the next one is returned
    }								//but if it is December, the first month is returned which is January
date next_day(date current_date)
{
	date *new_day = malloc(sizeof(date));    //dynamically creates a date at the heap so that it can be returned 
											//at the return of the function and not get lost
											
	if(current_date.d<28 )						//if the curent day is less than 28 
	{											//just add a day to the integer value d;
		new_day->d = current_date.d+1;			//and keep the month the same
		new_day->m = current_date.m;
	}
	else if(current_date.d==30 && current_date.m%2==0 )//every second month for example jan,mar,may...
	{													//has 31 days so if the current day is 30 
														//the next day will be 31 and month stays the same
		new_day->d = 31;
		new_day->m = current_date.m;	
	}
	else if( current_date.d==30 && current_date.m%2!=0 )//same case as before but the month is in between
	{													//so the next date gets to be the 1st of the next month
		new_day->d=1;
		new_day->m = next_month(current_date.m);
	}
	else if( current_date.d<30 && current_date.m!=feb) //if the day is less than 30 and it is not February
	{													//just add a day and keep the month the same
		new_day->d= current_date.d+1;
		new_day->m = current_date.m;
	}
	else if( current_date.d==28 && current_date.m==feb) //if the day is 28 and it is not February
	{												//the next date becomes the 1st of March
		new_day->d= 1;
		new_day->m = mar;
	}
	else if(current_date.d == 31)					//if the day is 31,
	{												//the next day will be always the 1st of the next month
		new_day->d= 1;
		new_day->m =next_month(current_date.m);
	}
	return *new_day; //returns the next date
}
void printdate(date Date)
{
	char *month;
	switch(Date.m)			//first, it uses switch-case to convert the month to a string value
	{						//so that it can be properly printed
		case jan: month = "January";break;
		case feb: month = "February";break;
		case mar: month = "March";break;
		case apr: month = "April";break;
		case may: month = "May";break;
		case jun: month = "June";break;
		case jul: month = "July";break;
		case aug: month = "August";break;
		case sep: month = "September";break;
		case oct: month = "October";break;
		case nov: month = "November";break;
		case dec: month = "December";break;
		default:break;
	}
	printf("The date is %d of %s\n\n", Date.d, month);//mow it is ready to print the date
}

