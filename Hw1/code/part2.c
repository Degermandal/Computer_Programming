#include <stdio.h>

#define PI 3.14

float diameter(float circumference);
float ageOfTree(float diameter, float growth_factor);

int main(){
	float dia;
	float age;
	dia=diameter(60.5);
	
	age=ageOfTree(dia,4.5);
	printf("dia:%.2f\n",dia);
	printf("age:%.2f\n",age);
	
	return (0);
}

/* Calculate the age of a tree */

float diameter(float circumference){ /* Calculating the diameter using the circumference of the tree */
	
	float diameter; /* Declare variable */
	
	diameter=circumference/PI; /*The formula is circumference=2*PI*radius */ /* And storing in diameter */
	
	printf("%f\n",diameter); /* Display output */
	
	return (diameter);
}

float ageOfTree(float diameter, float growth_factor){ /* Calculating the age of tree using the diameter and growth factor */
	
	float Age_of_Tree; /* Declare variable */
	
	Age_of_Tree=diameter*growth_factor; /* The formula is age of tree = diameter * growth factor */ /* And storing in Age_of_Tree */
	
	printf("%f\n",Age_of_Tree); /* Display output */
	
	return (Age_of_Tree);
}











