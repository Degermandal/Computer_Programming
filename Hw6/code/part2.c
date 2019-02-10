#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define MAX_NUM_WORDS 500
#define WORD_LENGTH 50

int getAndFilterWord(char * w); /*returns 0 if the piece of input does not contain any 
								letter to add into the array; 1 if it does. */
void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count);
void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count);
void myTest();



int main()
{
	myTest();
	return 0;
}

void myTest()
{

/* ******  sort ve bazi kisimlar hocanin sinifta gosterdigi gibi yaptim yani bu odevdeki bazi kisimlari hoca derste tahtaya yazmisti ******* */
	int i=0,j,k;
	char* w;

	char text[25000];
	char words[MAX_NUM_WORDS][WORD_LENGTH];
    int occur[MAX_NUM_WORDS];
	int word_count=0; 

	for(i=0;i<500;i++) /*stringin butun elemanlarini sifirlar */
	{
		occur[i]=0;
		words[i][0]='\0';
	}

	printf("Your text => \n"); /* text'i aldim */
	scanf("%[^\n]s\n",text);

	for(i = 0; text[i]; i++) /* harflerin hepsini kucuk yapmak icin */
	{
  		text[i] = tolower(text[i]);
	}
	

	for(j = 0; text[j] != '\0'; ++j)   /*noktama isaretleri ve sayilari uzaklastirmak icin */
    {
        while (!( (text[j] >= 'a' && text[j] <= 'z') || text[j] == '\0' || text[j] == ' ') ) /*bunlara esit olmayanlari sil */
        {
            for(k = j; text[k] != '\0'; ++k)
            {
                text[k] = text[k+1]; /*o indextekini silip yerine yanindaki harfi koymak icin */
            }

            text[k] = '\0';
        }
    }
	
	    	w = strtok(text, " "); /* strtok'u kullanarak bosluga kadar kelimeyi aldim */
   
		   while( w != '\0') 
		   {
		      
			    if(strcmp(w,"end")==0) /* end kelimesini gordugu an almayi birakmali */
			    {
			    	w='\0';
			    }
			    else
			    {
			      	if(getAndFilterWord(w)==1) /*get and filter dogru ise addWord'u cagir */
			      	{
			      		addWord(w,words,occur, &word_count);
			      	}

			      	w = strtok(NULL, " ");
			    }
		   }
		   


		    for (i = 0; i < word_count; ++i) /* ekrana yazdirmak icin bu donguler */
		    {
		   		printf("words[%d] = %-15s 			occur = %d\n",i,words[i], occur[i] );
		    }

		    printf("\n****************************************************\n\n");

		    sortWords(words,occur, word_count);

	    	for (i = 0; i < word_count; ++i) /* sort olduktan sonraki hali icin */
		    {
		   		printf("words[%d] = %-15s 			occur = %d\n",i,words[i], occur[i] );
		    }

}

int getAndFilterWord(char * w)
{
	if(w[0] !='\0') /* null degilken 1 null iken 0 dondur */
	{
		return 1;
	}
	
	return 0;	
}

void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count)
{
	int i=0;
	int flag=0;
	
	for(i=0; i<(*word_count) && flag==0; i++)
	{
		if((strcmp(words[i],w))==0) /*o indexteki kelime bulursan occur'u arttir */
		{
			flag=1;
			occur[i]++;

			return;
		}			
	}
	
	if((*word_count)==i) /* bulamadim demek */
	{
		strcpy(words[i],w);	/* daha once o kelime gelmemis ilk defa o kelimeyi gordugu icin ekle dedim */

		occur[i]=1; /* ilk geldigi icin bir olur olur occur'u */
	}

	(*word_count)++; /*yeni bir kelime eklendiginde artmasi icin */
	
	return;
}

void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count)
{
	int i,j,temp;
	char tmp[200];

	for(i=0;i<word_count;i++) /* burdaki mantik yer degistirme mantigi daha buyk oldugunda yer degistir */
	{
		for(j=i+1;j<word_count;j++)
		{
			if(occur[i]<occur[j])
			{
				temp=occur[i];
				occur[i]=occur[j];
				occur[j]=temp;
			
			strcpy(tmp,words[i]); /*burda da kelimeleri strcpy ile degistiriyorum */
			strcpy(words[i],words[j]); /*yukaridaki degisiklik duzgun calissin diye */
			strcpy(words[j],tmp);

			}

		}
	}
}