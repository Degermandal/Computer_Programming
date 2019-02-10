#include <stdio.h>

int isPrime(int num);
int goldbach(int num, int *p1, int *p2);

int main()
{
	int num=1998,p1,p2;
		if(goldbach(num,&p1,&p2))
			printf("%d=%d+%d\n",num,p1,p2);
		else
			printf("you should provide even number.\n");
			return 0;
}


int isPrime(int num)
{
int i;
int result=1;

	if(num<=0)  /* asal sayilar sadece 0 dan daha buyuk olabilir */
		return -1;
	
	for(i=2;i<num/2;i++) /*asal olup olmadigini kontrol ediyor */
	{
		if(num%i==0)
			result = 0;
	}	
	return result; /* asal ise result'i 1 esitleyip 1'i return eder */
}


int goldbach(int num, int *p1, int *p2)
{
	int i;
	
	int flag=0;  /* flag sayinin tek mi cift mi oldugunu kontrol ediyor */

		if(num%2==1)
		{
			flag=1; /* tek ise hic girmeyecek */
		}
		
			if(flag==0)
		 	{
				for(i=3;i<num;i+=2) /* ilk baslangic sayilarimiz 1 ve 2 olamaz cunku 2 olursa, cift olan sayi hep cift dondurur */
				{  /* +2 dememin nedeni, hep tek sayilara baksin, cift sayilara gerek yok */
					if(isPrime(i) && (isPrime(num-i))) /* buldugu iki sayininda asal olup olmadigina bakmasi icin */
					{
						*p1=i; /* sayi 1 */
						*p2=num-i; /* sayi 2 */

						return 1;
					}
			
				}
     		}
return 0;	

}










