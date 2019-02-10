#include <stdio.h>

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25, int
*krs10, int *krs5, int *krs1);

int main()
{
	double paid = 20, due = 3.76;
	int tl1,krs50,krs25,krs10,krs5,krs1;
	
	if(dispenseChange(paid,due,&tl1,&krs50, &krs25, &krs10, &krs5, &krs1)) /* returns 1 */
		printf("Change: 1TL:%d, Kurus-50:%d,25:%d,10:%d,5:%d,1:%d\n",tl1,krs50,krs25,krs10,krs5,krs1);
	else
		printf("Unable to dispense change.");

return 0;
}



int dispenseChange(double paid, double due, int *tl1, int *krs50,int *krs25, int
*krs10, int *krs5, int *krs1)
{
	
double money_owed;

money_owed=paid-due;	/* odenmesi gereken ucret */
money_owed*=100.0;  /* kuruslarla islem yapacagimiz icin 100 ile carpmaliyiz */

	if(due>paid)
	{
		return 0;
	}
	else
	{
		 *tl1=money_owed/100;    /* ilk 1 lira sayisini buldum bunuda money owed'i 100'e bolerek buldum cunku 1 lira 100 kurustur */
		 money_owed-=100*(*tl1); /* 1 lira sayisi kadar, 1 lira degerini carpip money owed'dan cikarttim */
		 
		 *krs50=money_owed/50;   /* yukarida anlattigim seyleri her para birimi icin tekrarladim */
		 money_owed-=50*(*krs50);
		 
		 *krs25=money_owed/25;
		 money_owed-=25*(*krs25);
		 
		 *krs10=money_owed/10;
		 money_owed-=10*(*krs10);
		 
		 *krs5=money_owed/5;
		 money_owed-=5*(*krs5);
		 
		 *krs1=money_owed/1;
		 money_owed-=1*(*krs1); /* en son kalan money owed ile islemine devam eder */
		 	
		}
			
	return 1;
}
