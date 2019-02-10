#include <stdio.h>


int main(){
int i,j,z=1,a;

int startingPoint,width,height,printLastLine;
printf("enter satarting point");
scanf("%d",&startingPoint);
printf("enter width");
scanf("%d",&width);
printf("enter height");
scanf("%d",&height);
printf("enter print last line");
scanf("%d",&printLastLine);


	for(i=1; i<=width; i++){
		for(j=0;j<startingPoint;j++){
			printf(" ");
		}
		
		
		for(j=1; j<=height; j++){
			if(i==1 /*|| i==height */|| j==1 || j==height)
				printf("*");
			else 
				printf(" "); 
	}
	printf("\n");
	
	}
	
	//printf("\n");
		while(z<=startingPoint){
			printf(" ");
			z++; }
		

	
	//printf("*");

if(printLastLine==1){
	for(i=1; i<=height; i++){
		printf("*");
		
	}
}}








	
	
	
