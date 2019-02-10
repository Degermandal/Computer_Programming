#include <stdio.h>
#include <string.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct person_s {
	int id;
	char name[NAMELEN];
} Person;

typedef struct record_s {
	int id;
	char number[NAMELEN];
} Record;

typedef struct Records_s {
	Record data[MAXRECORD];
	int size;
} Records;

typedef struct people_s {
	Person data[MAXRECORD];
	int size;
} People;

/* ========== IMPLEMENT THE FUNCTIONS BELOW ========== */
/*
	Write Records.data array to the filename.
	Note that file should be binary.
*/
void writeRecords(Records records, char* filename) 
{
	FILE *fp;
	int i; 

	fp=fopen(filename, "wb"); /*dosyami binary dosya olarak yazma modunda actim */

		if(fp==NULL) /*eger dosya olusturulamazsa null deger dondurur bunu kontrol ediyorum */
		{
			printf("Dosya olusturulamadi...\n"); 
			return;
		}

		else
		{
			for(i=0;i<records.size;i++) /*kac tane kayit varsa onlari yazmasi icin */
	 		{
				fwrite(&records.data[i],sizeof(Record),1,fp); /* fwrite'in parametre duzeni bu sekilde binary dosyada yazma islemini gerceklestiriyoruz */
			}
		}

		fclose(fp); /* mutlaka dosyamizi kapatmaliyiz */
}

/*
	Reads Record structs from the binary file and places them to Records.data array.
	Note that the number of Record structs in the file is unkown.
*/
void readRecords(Records *records, char* filename)
{

	FILE *fp;
	int i;
	records->size=0;

	if((fp=fopen(filename, "rb"))==NULL) /*read binary modunda acip null dondurup dondurmedigini kontrol ettim */
	{
		printf("Dosya acilamadi...\n");
		return;
	} 

	else
	{
		for(i=0;fread(&records->data[i],sizeof(Record),1,fp)==1;i++) /* binary dosyalar icin read modu olan fread'i kullandim 
																	 fread 1'e esit oluncaya kadar records size'i arttiracak */
	 		{				
				records->size++;
			}
	}

	fclose(fp); /* mutlaka dosyamizi kapatmaliyiz */

}

/*
	Write People.data array to the filename.
	Note that file should be binary.
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
	Reads Person structs from the binary file and places them to People.data array.
	Note that the number of Person structs in the file is unkown.
*/
void readPeople(People *people, char* filename) 
{
	FILE * fp;
	int i;

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

/**
  * Reads the input file and constructs People and Records structs.
  	Note that each Record in Records is unique (should not present multiple times).
  */
void read(char* filename, People *people, Records *records) 
{
	FILE * fp;
	int i=0;
	int num;
	char name[NAMELEN];
	char name1[NAMELEN];
 
/* asil fonksiyonumuza gelirsek */
	
	fp=fopen(filename,"r");/* dosyami read modunda actim */

			while(!feof(fp)) /* dosyanin sonu degilken text dosyanin ozelligi olarak, text dosyasinda fscanf kullandim */
							/* bu verileri okumami sagladi text dosyasindan */
			{

				fscanf(fp,"%d %s %s",&people->data[people->size].id,name,name1); /* ID isim(name) ve soyisimi(name1) okudum */
				fscanf(fp,"%d",&num); /* sonraki gelen sayida kac tane telefon numarasina sahip oldugunu gosteren sayi */
				
				strcat(name," "); /* isim + bosluk */
				strcat(name,name1); /* + soyisim */
				strcpy(people->data[people->size].name,name); /* toplaminida struct'a isim olarak kopyaladim */

				for(i=0;i<num;i++) /* for dongusunun amaci tel sayisi kadar donsun sirasiyla numberlari okusun */
				{
					fscanf(fp,"%s",records->data[records->size].number);

					records->data[records->size].id = people->data[people->size].id; /* IDlerin ayni olmasi gerekiyor bunun icin gerekli bu atama */
					records->size++; /* records size'i arttirmaliyiz data arrayi icin yani sirayla alabilmek icin */
				}

				people->size++;
	
			}

		fclose(fp); /* mutlaka dosyamizi kapatmaliyiz */

}




/* ========== IMPLEMENT THE FUNCTIONS ABOVE ========== */

void print(People people, Records records) {
	int i,j,found = 0;
	/* header */
	printf("%-5s %-30s %-20s\n", "ID","NAME","NUMBER(s)");
	/* line */
	for (i = 0; i < 57; ++i)
		printf("-");
	printf("\n");

	for (i = 0; i < people.size; ++i) {
		found = 0;
		printf("%-5d %-30s", people.data[i].id, people.data[i].name);
		for (j = 0; j < records.size; ++j) {
			if(records.data[j].id == people.data[i].id) {
				if(found)
					printf("%36s", "");
				printf("%-20s\n", records.data[j].number);
				found = 1;
			}
		}
		printf("\n");
	}
}

int isPeopleEq(People ppl1, People ppl2) {
	int i;
	if(ppl1.size != ppl2.size)
		return 0;
	for (i = 0; i < ppl1.size; ++i)
		if(strcmp(ppl1.data[i].name,ppl2.data[i].name) ||
			ppl1.data[i].id != ppl2.data[i].id)
			return 0;
	return 1;
}

int isRecordsEq(Records rec1, Records rec2) {
	int i;
	if(rec1.size != rec2.size)
		return 0;
	for (i = 0; i < rec1.size; ++i)
		if(strcmp(rec1.data[i].number,rec2.data[i].number) ||
			rec1.data[i].id != rec2.data[i].id)
			return 0;
	return 1;
}

int main(int argc, char** argv) 
{
	People people1,people2;
	Records records1,records2;
	people1.size = 0;
	records1.size = 0;
	read(argv[1],&people1, &records1);
	print(people1, records1);
	writePeople(people1,"people.bin");
	writeRecords(records1,"records.bin");
	readRecords(&records2,"records.bin");
	readPeople(&people2,"people.bin");
	print(people2, records2);
	printf("%s\n", isRecordsEq(records1,records2) ? "RECORDS ARE SAME" : "RECORDS ARE DIFFERENT!");
	printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
	return 0;
}
