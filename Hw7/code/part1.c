#include <stdio.h>

#define MAX_WEIGHT 99999
#define SHORTEST_DAMAGE 4
#define COMFORTABLE_DAMAGE 2
#define SAFEST_DAMAGE 6
#define TOTAL_LIFE 30 /* can change for different tests  */


typedef enum _tileType {BORDER, WALL, EMPTY, USED, START} TILE_TYPE;
typedef enum _pathType {DISTANCE, COMFORT, DANGER} PATH_TYPE;
typedef enum _printType {P_DISTANCE, P_COMFORT, P_DANGER, P_TRAP} PRINT_TYPE;



typedef struct _tiles{
	TILE_TYPE type;
	int distance;
	int dangerLevel;
	int comfortLevel;
	int trapDamage;
}TILES;


typedef struct _coord{
	int x;
	int y;
}Coord;


typedef struct _path{
	Coord coords[200];
	int size;
	int totalDistance;
	int totalDanger;
	int totalComfort;
	int totalDamage;
}Path;


/*starter functions*/
int testMaze(char * fileName, Coord startTile, PATH_TYPE pType);
void readMaze(TILES maze[100][100], char * fileName, int *w, int *h);
void printMaze(TILES maze[100][100], int a, int b);
void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType);
void printAll(TILES maze[100][100], int a, int b);
void markPath(TILES maze[100][100], Path path);
void clearBoard(TILES maze[100][100]);

/*Required*/
int isStuck(TILES maze[100][100], Coord currentTile);
int isExit(TILES maze[100][100], Coord currentTile);
Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);
Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight);

/*Optional*/
void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);
void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType);


int testMaze(char * fileName, Coord startTile, PATH_TYPE pType){
	int w = 0, h = 0;
	Path path, resultPath;
	int result = 0;

	TILES maze[100][100];
	int minWeight = MAX_WEIGHT;
	
	printf("Board name: %s\n", fileName);

	readMaze(maze, fileName, &w, &h);

	addCoord(maze, &path, startTile, pType);
	resultPath = shortestExit(maze, startTile, path, &minWeight);
	removeLastCoord(maze, &path, startTile, pType);

	markPath(maze, resultPath);
	maze[startTile.x][startTile.y].type = START;

	switch(pType){
		case DISTANCE:
			printf("Shortest Path\n");
			result = resultPath.totalDistance;
			printMazeWithValues(maze, w, h, P_DISTANCE);
			break;
		case COMFORT:
			printf("Comfortable Path\n");
			result = resultPath.totalComfort;
			printMazeWithValues(maze, w, h, P_COMFORT);
			break;
		case DANGER:
			printf("Safest Path\n");
			result = resultPath.totalDanger;
			printMazeWithValues(maze, w, h, P_DANGER);
			break;
	}

	printMaze(maze, w, h);

	printf("Total weight: %d\n", result);
	
	printf("-------------------------------------\n");
	return result;
}

/*marks path tiles as USED for printing*/
void markPath(TILES maze[100][100], Path path){
	int i = 0;

	for (i = 0; i < path.size; ++i){
		maze[path.coords[i].x][path.coords[i].y].type = USED;
	}
}

void readMaze(TILES maze[100][100], char * fileName, int *w, int *h){
	int i = 0, j = 0, tile = 0, distance, comfort, danger, trap;
	FILE *fp = fopen (fileName, "r");

	clearBoard(maze);

	fscanf(fp, "%d", w);
	fscanf(fp, "%d", h);

	/* Tile type*/
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &tile);
			switch(tile){
				case 0:
					maze[i][j].type = EMPTY;
					break;
				case 1:
					maze[i][j].type = WALL;
					break;
				case 2:
					maze[i][j].type = USED;
					break;
				case 3:
					maze[i][j].type = BORDER;
					break;
			}
		}
	}

	fscanf(fp, "%d", &distance);/*useless seperator*/

	/* distance values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &distance);
			maze[i][j].distance = distance;
		}
	}
	
	fscanf(fp, "%d", &comfort);/*useless seperator*/

	/* comfort values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &comfort);
			maze[i][j].comfortLevel = comfort;
		}
	}
	fscanf(fp, "%d", &danger);/*useless seperator*/

	/* danger values */
	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &danger);
			maze[i][j].dangerLevel = danger;
		}
	}

	/* trap values */
	fscanf(fp, "%d", &trap);/*useless seperator*/

	for (i = 0; i < *w; ++i){
		for (j = 0; j < *h; ++j){
			fscanf(fp, "%d", &trap);
			maze[i][j].trapDamage = trap;
		}
	}
  
	fclose(fp);
}

void printMaze(TILES maze[100][100], int a, int b){
	int i = 0, j = 0;
	
	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			switch(maze[i][j].type){
				case EMPTY:
					printf("  ");
					break;
				case WALL:
					printf("W ");
					break;
				case USED:
					printf(". ");
					break;
				case BORDER:
					printf("B ");
					break;
				case START:
					printf("* ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printMazeWithValues(TILES maze[100][100], int a, int b, PRINT_TYPE pType){
	int i = 0, j = 0;
	
	printf("  ");
	for (j = 0; j < b; ++j){
		printf("%d ", j%10);
	}
	printf("\n");

	for (i = 0; i < a; ++i){
		printf("%d ", i%10);
		for (j = 0; j < b; ++j){
			if(maze[i][j].type == EMPTY || maze[i][j].type == USED || maze[i][j].type == START){
				if(pType == P_DISTANCE)
					printf("%d ", maze[i][j].distance);
				else if(pType == P_COMFORT)
					printf("%d ", maze[i][j].comfortLevel);
				else if(pType == P_DANGER)
					printf("%d ", maze[i][j].dangerLevel);
				else 
					printf("%d ", maze[i][j].trapDamage);
			}else if(maze[i][j].type == BORDER){
				printf("B ");
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printAll(TILES maze[100][100], int a, int b){
	printf("Distance Map:\n");
	printMazeWithValues(maze, a, b, P_DISTANCE);
	printf("Comfort Map:\n");
	printMazeWithValues(maze, a, b, P_COMFORT);
	printf("Danger Map:\n");
	printMazeWithValues(maze, a, b, P_DANGER);
	printf("Trap Map:\n");
	printMazeWithValues(maze, a, b, P_TRAP);
	printf("Path:\n");
	printMaze(maze, a, b);
}

void clearBoard(TILES maze[100][100]){
	int i = 0, j = 0;
	
	for (i = 0; i < 100; ++i){
		for (j = 0; j < 100; ++j){
			maze[i][j].type = BORDER;
		}
	}
}

/***********************************************************/

int isStuck(TILES maze[100][100], Coord currentTile)
{

/*bize verilen koordinatin 4 cevresine bakariz wall ise demekki bu adam sıkısmis o yuzden return degerimiz 1 olur */
	if(maze[currentTile.x+1][currentTile.y].type==WALL && maze[currentTile.x-1][currentTile.y].type==WALL && 
	   maze[currentTile.x][currentTile.y+1].type==WALL && maze[currentTile.x][currentTile.y-1].type==WALL )
	{
		return 1;
	}

/*ayrica kullanip kullanilmadigina da bakmamiz gerekiyor eger o tiledan gecmissek geri donemeyiz */
	if(maze[currentTile.x+1][currentTile.y].type==USED && maze[currentTile.x-1][currentTile.y].type==USED && 
	   maze[currentTile.x][currentTile.y+1].type==USED && maze[currentTile.x][currentTile.y-1].type==USED)
	{
		return 1;
	}
	else 
		return 0;
}

int isExit(TILES maze[100][100], Coord currentTile)
{

/* koordinat border ise hedefe ulasmissin demektir */
	if(maze[currentTile.x][currentTile.y].type==BORDER) 
		return 1;
	else
		return 0;
}

Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
	int Tlife = TOTAL_LIFE;
	int dmg = SHORTEST_DAMAGE; 
	int life=1;
	int tempWeight=0;
	int dis=0,dis1=0,dis2=0,dis3=0,dis4=0,smallest;
	*minWeight=0;

	if(!(isStuck(maze,currentTile)) && (!(isExit(maze,currentTile))) )  /*hem sıkısmamıs olacak hemde cikisa ulasmamis olacak diye dusundum */
	{   
		if(Tlife>0)      /* devam etmesi icin hala cani olmali */
		{		
				
				if(maze[currentTile.x][currentTile.y].type == EMPTY)
				{
					maze[currentTile.x][currentTile.y].type = USED;  /*verilen koordinat empty ise used yapki bir daha gidemesin gittigi yere */  
					dis= maze[currentTile.x][currentTile.y].distance; /*ilk tile'in uzunlugunu buldum */
					path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*tilelardaki trapleri total damage'e attim */

					/*asagidaki 4 if durumu x ve y koordinatlarinin cevresindeki 4 koordinatlardaki durumlara bakmak icin */
					if(maze[currentTile.x-1][currentTile.y].type == EMPTY) 
					{
						dis1+=dis; /*ilk acilan tile'in uzunlugunu koyuyorum, yukari cikmasi icin koydugum if durumunun distance birimine */
						maze[currentTile.x-1][currentTile.y].type = USED;  /*tekrar kullanilmasin diye used yaptim */
						dis1+= maze[currentTile.x-1][currentTile.y].distance; /*acilan tiledaki uzunluklari toplamak icin */
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*acilan tilelardaki trapleri total damage'e attim */
						(currentTile.x)--; /*hep azaltark yukari cikartmaya calistim */
						life++; /* burda arttiriyorum kac tile acildigini bulup damage katsayisiyla carpmak icin */
						return shortestExit(maze, currentTile, path, minWeight); /*bu tilelar icinde aynisi olsun diye recursive kullandim */
					}

					/*yukarida dusundugum ve yorumladigim seyleri aynisini asagi,saga ve sola dusunerek yaptim */

					if(maze[currentTile.x+1][currentTile.y].type == EMPTY)  
					{
						dis2+=dis;
						maze[currentTile.x+1][currentTile.y].type = USED; 
						dis2+= maze[currentTile.x+1][currentTile.y].distance;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.x)++;
						life++;
						return shortestExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y-1].type == EMPTY) 
					{
						dis3+=dis;
						maze[currentTile.x][currentTile.y-1].type = USED; 
						dis3 += maze[currentTile.x][currentTile.y-1].distance;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)--;
						life++;
						return shortestExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y+1].type == EMPTY)  
					{
						dis4+=dis;
						maze[currentTile.x][currentTile.y+1].type = USED; 
						dis4 += maze[currentTile.x][currentTile.y+1].distance;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)++;
						life++;
						return shortestExit(maze, currentTile, path, minWeight);
					}
	                
		                Tlife=Tlife-(life*dmg+path.totalDamage); /*kalan cani bulmak icin dusundugum denklem */

		                smallest = dis1; /* bu if durumlari en kucuk mesafeyi bulmak icin */

						if (dis2 < smallest) 
							{ 
								smallest = dis2;
							}
						if (dis3 < smallest) 
							{ 
								smallest = dis3;
							}
						if (dis4 < smallest) 
							{ 
								smallest = dis4;
							}

		                path.totalDistance=smallest;
		        
						tempWeight= path.totalDistance;
						if(tempWeight>*minWeight)
						{
							*minWeight=tempWeight; /* en son olarak da min weight'i bulmak icin ustten en kucuk dist gelecek, onu da total'e attim, 
													temp deger kullanarakta en son haliyle min weight'i bulmaya calistim */
						}   
						
				}

		}

	}
return shortestExit(maze, currentTile, path, minWeight);
	

}

Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
	int Tlife = TOTAL_LIFE;
	int dmg = COMFORTABLE_DAMAGE; 
	int life=1; /*ilk acarken bir life harcadigimiz icin */
	int tempWeight=0;
	int com=0,com1=0,com2=0,com3=0,com4=0,smallest;
	*minWeight=0;

	if(!(isStuck(maze,currentTile)) && (!(isExit(maze,currentTile))) )  /*hem sıkısmamıs olacak hemde cikisa ulasmamis olacak diye dusundum */
	{   
		if(Tlife>0)      /* devam etmesi icin hala cani olmali */
		{		
				
				if(maze[currentTile.x][currentTile.y].type == EMPTY)
				{
					maze[currentTile.x][currentTile.y].type = USED;  /*verilen koordinat empty ise used yapki bir daha gidemesin gittigi yere */  
					com= maze[currentTile.x][currentTile.y].comfortLevel; /*ilk tile'in comfort degerini buldum */
					path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*tilelardaki trapleri total damage'e attim */

					/*asagidaki 4 if durumu x ve y koordinatlarinin cevresindeki 4 koordinatlardaki durumlara bakmak icin */
					if(maze[currentTile.x-1][currentTile.y].type == EMPTY) 
					{
						com1+=com; /*ilk acilan tile'in comfort degerini koyuyorum, yukari cikmasi icin koydugum if durumunun comfort birimine */
						maze[currentTile.x-1][currentTile.y].type = USED;  /*tekrar kullanilmasin diye used yaptim */
						com1+= maze[currentTile.x-1][currentTile.y].comfortLevel; /*acilan tiledaki comfort degerlerini toplamak icin */
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*acilan tilelardaki trapleri total damage'e attim */
						(currentTile.x)--; /*hep azaltark yukari cikartmaya calistim */
						life++; /* burda arttiriyorum kac tile acildigini bulup damage katsayisiyla carpmak icin */
						return comfortableExit(maze, currentTile, path, minWeight); /*bu tilelar icinde aynisi olsun diye recursive kullandim */
					}

					/*yukarida dusundugum ve yorumladigim seyleri aynisini asagi,saga ve sola dusunerek yaptim */

					if(maze[currentTile.x+1][currentTile.y].type == EMPTY)  
					{
						com2+=com;
						maze[currentTile.x+1][currentTile.y].type = USED; 
						com2+= maze[currentTile.x+1][currentTile.y].comfortLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.x)++;
						life++;
						return comfortableExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y-1].type == EMPTY) 
					{
						com3+=com;
						maze[currentTile.x][currentTile.y-1].type = USED; 
						com3 += maze[currentTile.x][currentTile.y-1].comfortLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)--;
						life++;
						return comfortableExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y+1].type == EMPTY)  
					{
						com4+=com;
						maze[currentTile.x][currentTile.y+1].type = USED; 
						com4 += maze[currentTile.x][currentTile.y+1].comfortLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)++;
						life++;
						return comfortableExit(maze, currentTile, path, minWeight);
					}
	                
		                Tlife=Tlife-(life*dmg+path.totalDamage); /*kalan cani bulmak icin dusundugum denklem */

		                smallest = com1; /* bu if durumlari en kucuk comfort degerini bulmak icin */

						if (com2 < smallest) 
							{ 
								smallest = com2;
							}
						if (com3 < smallest) 
							{ 
								smallest = com3;
							}
						if (com4 < smallest) 
							{ 
								smallest = com4;
							}

		                path.totalComfort=smallest;
		        
						tempWeight= path.totalComfort;
						if(tempWeight>*minWeight)
						{
							*minWeight=tempWeight; /* en son olarak da min weight'i bulmak icin ustten en kucuk comfort degeri gelecek, onu da total'e attim, 
													temp deger kullanarakta en son haliyle min weight'i bulmaya calistim */
						}   
						
				}
		}

	}
return comfortableExit(maze, currentTile, path, minWeight);
}

Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight)
{
	int Tlife = TOTAL_LIFE;
	int dmg = SAFEST_DAMAGE; 
	int life=1;
	int tempWeight=0;
	int safe=0,safe1=0,safe2=0,safe3=0,safe4=0,smallest;
	*minWeight=0;

	if(!(isStuck(maze,currentTile)) && (!(isExit(maze,currentTile))) )  /*hem sıkısmamıs olacak hemde cikisa ulasmamis olacak diye dusundum */
	{   
		if(Tlife>0)      /* devam etmesi icin hala cani olmali */
		{		
				
				if(maze[currentTile.x][currentTile.y].type == EMPTY)
				{
					maze[currentTile.x][currentTile.y].type = USED;  /*verilen koordinat empty ise used yapki bir daha gidemesin gittigi yere */  
					safe= maze[currentTile.x][currentTile.y].dangerLevel; /*ilk tile'in danger degerini buldum */
					path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*tilelardaki trapleri total damage'e attim */

					/*asagidaki 4 if durumu x ve y koordinatlarinin cevresindeki 4 koordinatlardaki durumlara bakmak icin */
					if(maze[currentTile.x-1][currentTile.y].type == EMPTY) 
					{
						safe1+=safe; /*ilk acilan tile'in danger degerini koyuyorum, yukari cikmasi icin koydugum if durumunun danger birimine */
						maze[currentTile.x-1][currentTile.y].type = USED;  /*tekrar kullanilmasin diye used yaptim */
						safe1+= maze[currentTile.x-1][currentTile.y].dangerLevel; /*acilan tiledaki danger degerlerini toplamak icin */
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage; /*acilan tilelardaki trapleri total damage'e attim */
						(currentTile.x)--; /*hep azaltark yukari cikartmaya calistim */
						life++; /* burda arttiriyorum kac tile acildigini bulup damage katsayisiyla carpmak icin */
						return safestExit(maze, currentTile, path, minWeight); /*bu tilelar icinde aynisi olsun diye recursive kullandim */
					}

					/*yukarida dusundugum ve yorumladigim seyleri aynisini asagi,saga ve sola dusunerek yaptim */

					if(maze[currentTile.x+1][currentTile.y].type == EMPTY)  
					{
						safe2+=safe;
						maze[currentTile.x+1][currentTile.y].type = USED; 
						safe2 += maze[currentTile.x+1][currentTile.y].dangerLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.x)++;
						life++;
						return safestExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y-1].type == EMPTY) 
					{
						safe3+=safe;
						maze[currentTile.x][currentTile.y-1].type = USED; 
						safe3 += maze[currentTile.x][currentTile.y-1].dangerLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)--;
						life++;
						return safestExit(maze, currentTile, path, minWeight);
					}

					if(maze[currentTile.x][currentTile.y+1].type == EMPTY)  
					{
						safe4+=safe;
						maze[currentTile.x][currentTile.y+1].type = USED; 
						safe4 += maze[currentTile.x][currentTile.y+1].dangerLevel;
						path.totalDamage +=maze[currentTile.x][currentTile.y].trapDamage;
						(currentTile.y)++;
						life++;
						return safestExit(maze, currentTile, path, minWeight);
					}
	                
		                Tlife=Tlife-(life*dmg+path.totalDamage); /*kalan cani bulmak icin dusundugum denklem */

		                smallest = safe1; /* bu if durumlari en kucuk danger degerini bulmak icin */

						if (safe2 < smallest) 
							{ 
								smallest = safe2;
							}
						if (safe3 < smallest) 
							{ 
								smallest = safe3;
							}
						if (safe4 < smallest) 
							{ 
								smallest = safe4;
							}

		                path.totalDanger=smallest;
		        
						tempWeight= path.totalDanger;
						if(tempWeight>*minWeight)
						{
							*minWeight=tempWeight; /* en son olarak da min weight'i bulmak icin ustten en kucuk danger deger gelecek, onu da total'e attim, 
													temp deger kullanarakta en son haliyle min weight'i bulmaya calistim */
						}   
						
				}
		}

	}
return safestExit(maze, currentTile, path, minWeight);
} 


/***********************************************************/


void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType)
{
	path->coords[path->size].x=coord.x;
	path->coords[path->size].y=coord.y;
	path->size +=1;

	if(pType==DANGER)
	{
		path->totalDanger+=maze[coord.x][coord.y].dangerLevel;
	}
	if(pType==COMFORT)
	{
		path->totalComfort+=maze[coord.x][coord.y].comfortLevel;
	}
	if(pType==DISTANCE)
	{
		path->totalDistance+=maze[coord.x][coord.y].distance;
	}
}

void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType)
{
	path->coords[path->size].x=coord.x=0;
	path->coords[path->size].x=coord.y=0;
	path->size +=1;

	if(pType==DANGER)
	{
		path->totalDanger-=maze[coord.x][coord.y].dangerLevel;
	}
	if(pType==COMFORT)
	{
		path->totalComfort-=maze[coord.x][coord.y].comfortLevel;
	}
	if(pType==DISTANCE)
	{
		path->totalDistance-=maze[coord.x][coord.y].distance;
	}
}



int main(){

	Coord startTile1;
	startTile1.x = 5;
	startTile1.y = 2;


	testMaze("maze1.txt", startTile1, DISTANCE);
	testMaze("maze1.txt", startTile1, COMFORT);
	testMaze("maze1.txt", startTile1, DANGER);
	
	return 0;
}

