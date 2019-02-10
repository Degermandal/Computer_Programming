#include <stdio.h>
#define gridSize 4

typedef enum {mined,empty,flaggedMined,flaggedEmpty,closedEmpty,closedMined} cell;

void printGrid (cell grid[][gridSize]);
int openCell(cell grid[][gridSize], int x, int y);
void flagCell(cell grid[][gridSize], int x, int y);
int isCellEmpty(cell grid[][gridSize], int x, int y);
int isLocationLegal(int x, int y);
void initGrid(cell grid[][gridSize]);
int asMain();






int main()
{

	asMain();

	return 0;

}

int asMain()
{
	int counter = 0;
	int win = 0;
	int lose = 0;
	char ch;
	int col, row;
	int error;
	int i, j;
	int noWin;

	cell grid[gridSize][gridSize];

	initGrid(grid);


	do{

		noWin = 0;
		printGrid(grid);

		printf("\nPlease choose what do you want to do?\n");
		printf("Press 'f' to flag and 'o' to open the cell.\n");
		scanf(" %c", &ch);

		printf("Please give the coordinates.\n");
		printf("x: ");
		scanf("%d", &col);
		printf("y: ");
		scanf(" %d", &row);

		if(ch == 'o')
		{
			error = openCell(grid, col, row); 
			if(error == -2)
			{
				counter--;   /*eger hatali bir durum girilirse counter'i arttirmamak icin */
			}
			if(error == 1)
			{
				lose = 1;
			}
		}
		else if(ch == 'f')
		{
			flagCell(grid, col, row);
		}

		for(i=0; i<gridSize; i++)
		{
			for(j=0; j<gridSize; j++)
			{
				if(grid[i][j] == mined || grid[i][j] == flaggedEmpty || grid[i][j] == closedEmpty)
				{
					noWin = 1; 			/*	game moves on  */ 
					printf("mhgmdg");
				}
			}
		}

		counter++;
		if(noWin == 0)
		{
			win = 1; 
		}
	}while(win == 0 && lose == 0);	/*  game condition  */


	printGrid(grid);

	if(win == 1)		/*  you win  */
	{
		printf("Congratulations! You win the game with %d moves\n", counter);
	}
	else
	{
		printf("You Lost!\n");
	}
	return 0;

}

void initGrid(cell grid[][gridSize])
{
	int i, j;
	cell gridGrid[][gridSize] = /* benim olusturdugum mayin tarlasi duzeni */
	{
	   	{closedEmpty , closedMined , closedMined , closedEmpty},

		{closedEmpty , closedEmpty , closedMined , closedMined},

		{closedEmpty , closedEmpty , closedEmpty , closedEmpty},

		{closedEmpty , closedEmpty , closedEmpty , closedEmpty}
	};


	for(i=0; i<gridSize; i++) 
	{
		for(j=0; j<gridSize; j++)
		{
			grid[i][j] = gridGrid[i][j];
		}
	}
}

void printGrid (cell grid[][gridSize])
{
	int i, j;
	
	for(i=0; i<gridSize; i++) /*dongulerle matrisimi olusturup type enumdaki verileri kullanark switch case yaptim */
	{							/* veriler girildikce noktalar harflere donecek */
		for(j=0; j<gridSize; j++)
		{
			switch(grid[i][j]){

			case closedEmpty: 
				printf(".  ");
				break;
			case closedMined:
				printf(".  ");
				break;
			case empty:
				printf("e  ");
				break;
			case mined:
				printf("m  ");
				break;
			case flaggedEmpty:
				printf("f  ");
				break;
			case flaggedMined:
				printf("f  ");
				break;
			default:
				printf(".  ");
				break;
			}
		}
		printf("\n");
	}
}

int isLocationLegal(int x, int y)
{
	int result = 0;

	if(x>=0 && x<gridSize && y>=0 && y<gridSize) /*koordinatlarimiz hem 0'dan buyuk olmali hem de gridsize'dan kucuk olmali cunku index 0'dan basliyor */
	{
		result = 1; /* dogru ise 1 yanlis ise 0 */
	}
	else
	{
		result = 0;
	}

	return result;
}

int isCellEmpty(cell grid[][gridSize], int x, int y)
{
	int result;

	if(grid[x][y] == closedEmpty || grid[x][y] == closedMined) /* kapali bosluk yada kapali mayin olmali dogru durumda */
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	return result;
}

int openCell(cell grid[][gridSize], int x, int y)
{
	if(isLocationLegal(x, y) == 0) /* illegal durum */
	{ 
		printf("The cell is illegal. Please try again.\n");
		return -2; 
	}

	if(isCellEmpty(grid, x, y) == 0) /* bos olmama durumu */
	{
		printf("The cell is already opened. Please try again.\n");
		return -2; 
	}

	if(grid[x][y] == flaggedEmpty || grid[x][y] == flaggedMined) /* bayrak olma durumu */
	{
		printf("The cell is flagged. Please try again.\n");
		return -2;
	}

	if(grid[x][y] == closedEmpty || grid[x][y] == closedMined)
	{
		if(grid[x][y] == closedEmpty)
		{
			grid[x][y] = empty;
			 /*grid[x][y] = unflagged;kapali bos ise bunu bosa cevir yani ac */
		}
		else if(grid[x][y] == closedMined)
		{
			grid[x][y] = mined; 
			return 1; /* game over */
		}

		if(isLocationLegal(x-1, y-1)) /* bu asagida yaptiklarim cevresindeki 8 kutucugunda bos olup olmama durumunu kontrol etmek icin */
		{								/* bunuda ilk legal ve bos olup olmamasina bakarak kontrol ettim */
			if(isCellEmpty(grid, x-1, y-1)){
				if(grid[x-1][y-1] == closedEmpty)
				{
					grid[x-1][y-1] = empty;
				}
			}
		} 

		if(isLocationLegal(x, y-1))
		{
			if(isCellEmpty(grid, x, y-1)){
				if(grid[x][y-1] == closedEmpty)
				{
					grid[x][y-1] = empty;
				}
			}
		} 

		if(isLocationLegal(x+1, y-1))
		{
			if(isCellEmpty(grid, x+1, y-1)){
				if(grid[x+1][y-1] == closedEmpty)
				{
					grid[x+1][y-1] = empty;
				}
			}
		} 

		if(isLocationLegal(x-1, y))
		{
			if(isCellEmpty(grid, x-1, y)){
				if(grid[x-1][y] == closedEmpty)
				{
					grid[x-1][y] = empty;
				}
			}
		} 

		if(isLocationLegal(x+1, y))
		{
			if(isCellEmpty(grid, x+1, y)){
				if(grid[x+1][y] == closedEmpty)
				{
					grid[x+1][y] = empty;
				}
			}
		} 

		if(isLocationLegal(x-1, y+1))
		{
			if(isCellEmpty(grid, x-1, y+1)){
				if(grid[x-1][y+1] == closedEmpty)
				{
					grid[x-1][y+1] = empty;
				}
			}
		} 

		if(isLocationLegal(x, y+1))
		{
			if(isCellEmpty(grid, x, y+1)){
				if(grid[x][y+1] == closedEmpty)
				{
					grid[x][y+1] = empty;
				}
			}
		} 

		if(isLocationLegal(x+1, y+1))
		{
			if(isCellEmpty(grid, x+1, y+1)){
				if(grid[x+1][y+1] == closedEmpty)
				{
					grid[x+1][y+1] = empty;
				}
			}
		} 

	}
	return 0;
}

void flagCell(cell grid[][gridSize], int x, int y)
{

	if(isLocationLegal(x, y) == 1 /*&& isCellEmpty(grid, x, y) == 1*/) /* dogru degerleri donduruyorlar ise */
	{
		if(grid[x][y] == closedEmpty)
		{
			grid[x][y] = flaggedEmpty;
		}
		else if(grid[x][y] == closedMined)
		{
			grid[x][y] = flaggedMined;
		}
		
		
			else if(grid[x][y] == flaggedEmpty )
			{
			  	grid[x][y] == closedEmpty;
			}
	
			else if(grid[x][y] == flaggedMined )
			{
			  	grid[x][y] == closedMined;
			}
		

	}	
}

