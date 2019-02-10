#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s {
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s {
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers; /* head her kisinin numarasini linked list olarak ordan devam ettirecen sonuna null */

} Person;

typedef struct people_s {
    Person data[MAXRECORD];
    int size;
} People;


/*
 Write People.data array to the filename.   
*/
void writePeople(People people, char* filename) 
{
	FILE * fp;
	int i;
	
	fp=fopen(filename,"wb");/*dosyami binary dosya olarak yazma modunda actim */

	if(fp == NULL) /*eger dosya olusturulamazsa null deger dondurur bunu kontrol ediyorum */
	{
		printf("Dosya olusturulamadi...\n");
		return;
	}

	else 
 	{
 		for(i = 0 ; i < people.size ; i++) /*kac tane kayit varsa onlari yazmasi icin */
 		{
			fwrite(&people.data[i],sizeof(Person),1,fp); /* fwrite'in parametre duzeni bu sekilde binary dosyada yazma islemini gerceklestiriyoruz */
		}
 	}

	fclose(fp); /* mutlaka dosyamizi kapatmaliyiz */
}



/*
 Reads Person structs from file and places them to People.data array.
 Note that the number of Person structs in the file is unkown. 
*/
void readPeople(People *people, char* filename)
{
	FILE * fp;
	int i;
	people->size=0;

		fp=fopen(filename,"rb"); /*read binary modunda acip null dondurup dondurmedigini kontrol ettim */

		if(fp==NULL)
		{
			printf("Dosya acilamadi...\n");
			return;
		}

		else
		{
			
			for(i = 0 ;fread(&people->data[i],sizeof(Person),1,fp)==1 ; i++)/* binary dosyalar icin read modu olan fread'i kullandim 
																	 		fread 1'e esit oluncaya kadar records size'i arttiracak */
 			{
				people->size++;
			}
		}

		fclose(fp); /* mutlaka dosyamizi kapatmaliyiz */
}




/*
 Calculates the expected expenditure for the person with unknown expenditure.
 Persons' expenditure is -1 if their expenditure is unknown.
 You should calculate average bill amount for a phone number and multiply it by
 the phone number count for the person.

*/
void imputation(People *people) 
{
	int i;
	double total=0;
	int Ncount=0, Kcount=0;

	for(i=0;people->size;i++) /* kac kisi varsa o kadar tekrarlansin */
	{
		if(people->data[i].expenditure != -1) /* expenditure degerini bilmiyorken yani diger kisiler icin */
		{
			total+=people->data[i].expenditure; /* total expenditure buldum */

			while(people->data[i].numbers->next != NULL) /*son elemana kadar */
			{
				Ncount++; /* kac tane numara var say */
			}
		}

		if(people->data[i].expenditure == -1) /* belli olmayan kisiden bahsediyorsak */
		{ 
			while(people->data[i].numbers->next != NULL) /*son elemana kadar */
			{
				Kcount++; /* bilinmeyen kisinin kac tane tel numarasi var onu say */
			}
		}

		people->data[i].expenditure=(total/Ncount)*Kcount; /* en son buldugun, formule gore expendituredir */

	}

}




/*
 Reads the input file and constructs People struct.
 Note that the number of phone numbers in file is unknown unlike your
 previous homework. You should keep phone numbers in the linked list
 (numbers field)

*/
void read(char* filename, People *people) 
{

	FILE * fp;
	people->size=0;
	
	char name[NAMELEN];
	char surname[NAMELEN];
	char num1[NAMELEN];
	char ch;
 
/* asil fonksiyonumuza gelirsek */
	
	fp=fopen(filename,"r");/* dosyami read modunda actim */

			while(!feof(fp)) /* dosyanin sonu degilken text dosyanin ozelligi olarak, text dosyasinda fscanf kullandim */
							/* bu verileri okumami sagladi text dosyasindan */
			{


				fscanf(fp,"%d %s %s",&people->data[people->size].id,name,surname); /* ID, isim ve soyisimi fscanf ile aldim */
				fscanf(fp,"%lf",&people->data[people->size].expenditure);  /* daha sonra gelen sayiyi yani expenditure alip structuruna attim */
				
				strcat(name," "); /* isim + bosluk */
				strcat(name,surname); /* + soyisim */
				strcpy(people->data[people->size].name,name); /* toplaminida struct'a isim olarak kopyaladim */

				fscanf(fp,"%c",ch); /* bu biraz yanlis oldu da soyle dusundum newline karakterinde satir sonlanacak bende ilk onu alip dongu kurmaya calistim */

				while(ch != '\n') /* o mantikla newline degilken dedim */
				{	
					fscanf(fp,"%s",num1); /*ilk gelen numarayi aldim */
				
				    people->data[people->size].numbers=malloc(sizeof(Record)); /* numaralari koyabilmek icin yer ayirdim */
	
				    while(people->data[people->size].numbers != NULL) /*head null degilken diye de dusunebiliriz */
				    {
				    	people->data[people->size].numbers->id = people->data[people->size].id; /* ID leri birbirine atiyorum */
	
				    	people->data[people->size].numbers->next=NULL; /*sonrakini null yapiyorum bitis icin */
				    	strcpy(people->data[people->size].numbers->number,num1); /* aldigim numarayi structdaki yerine yazdim */
				    }
				}

				people->size++; /* data arrayi icin bir arttirim array mantigiyla ilerlesin diye */
	
			}


		fclose(fp); /* dosyamizi mutlaka kapatmaliyiz */
}


/******************************************************************/

void print(People people) {
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2) {
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
    {
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    People people1,people2;
    people1.size = 0;
    read(argv[1],&people1);
    print(people1);
    writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    return 0;
}
