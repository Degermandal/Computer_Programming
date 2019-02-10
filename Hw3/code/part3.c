#include <stdio.h>

int charge(int cardType, int* monthlyUse, double* balance);

int main()
{
	int monthlyUse = 120;
	double balance = 20.0;
	
		if(!(charge(2,&monthlyUse, &balance) < 0))
			printf("Remaining monthly use: %d\nRemaining Balance: %.2f\n",monthlyUse,balance);
		else
			printf("Insufficient balance.");
		return 0;
}

int charge(int cardType, int* monthlyUse, double* balance)
{
	 
	 
		if(*monthlyUse>=1) /* montly use'i kullanabilmek icin 1'den buyuk olmali */
		{
			*monthlyUse -= 1; /* her basim icin 1 azaltacak */
		}
		
				if(*balance>0) /* balance 0 dan buyuk durum icin islem yapmali simdi de */
				{
					switch(cardType) /* kart tipi secimi */
					{
					case 1:  /* normal icin bakiye en az 2.30 olmali, bakiye yeterliyse o kadar azaltmali */
						
						if(*balance>=2.30)
							*balance-=2.30;
						else             /* yetersiz bakiye durumunda return -1 yapmali */
							return -1;
							break;
					case 2:
						
						if(*balance>=1.15) 
							*balance-=1.15;
						else
							return -1;
							break;
					case 3:
						
						if(*balance>=1.65)
							*balance-=1.65;
						else
							return -1;
							break;
							
					default:   /* Invalid card type */
							return -2;
					}	
				}

				else
					return -1;
		
return 0;
					
}					
	



	



