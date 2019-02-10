#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

int theAge(int day,int month,int year,int today,int this_month, int this_year);

int daysLeft(int day,int month,int today,int this_month);


int main(){
	int age;
	int days;
age=theAge(25,2,1984,25,2,2017);

days=daysLeft(4,7,22,2);

printf("age:%d\n",age);
printf("days:%d\n",days);
 return (0); }

/* Compute the age */

int theAge(int day,int month,int year,int today,int this_month, int this_year){ /* Our variables in the function */

	int age; /* Declare variable */
	
	age=((today-day)+((this_month-month)*30)+((this_year-year)*360))/360; /* Compute age and store in age */
    
    printf("%d\n",age); /* Display output */
    
	return (age);  /* Return the age value */
}

/* Calculating how many days left to his/her birthday */

int daysLeft(int day,int month,int today,int this_month){ /* Our variables in the function */
	
	int days;  /* Declare variable */
	
	days=(((12-this_month)+(1-month))*30)+(30+day-today);  /* I write the formula to calculate how many days left and storing in days*/
	
	printf("%d\n", days); /* Display output */
	
	return (days); /*Return the days value */
}














