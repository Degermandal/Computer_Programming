#include <stdio.h>

int main(){
	
	int i,j,k;
	int xAxis,yAxis;
	int bosluk=(xAxis/2)-1;

printf("enter your xAxis,yAxis");
scanf("%d%d",&xAxis,&yAxis);
	
	for(i=yAxis;i>=0;i--){
		
		/*for(i=yAxis;i>=0;i--){*/
			printf("|");
		//}
		
		
	for(j=xAxis;j>=0;j--){
			
			for(k=(xAxis/2)-1;k>0;k-=2){
				printf(" ");
				
					if(j==xAxis/2){
					printf("*");
					j-=2;   }
			}
			
		if(j==xAxis/2){
					printf("*");
					j-=2;   }
				else	
					printf(" ");
				}
				
					
					
			}
			//xAxis=xAxis-2;
			printf("\n");
			
			for(k=0;k<xAxis;k++){
						printf("-");
					}
	}




















