#include <stdio.h>
#include <string.h>
void addPiece(char well[][13], char piece[][4], int y);
void rotatePiece(char piece[][4], int t);

int main(int argc, char *argv[])
{
	char well[13][13];
	char line[1000];
	FILE *fp;
	int a, b;

	if(argc > 1)
		fp = fopen(argv[1], "r");
		
	for(a=0; a<13; a++) {
		for(b=0; b<13; b++) {
			if(b == 0 || b == 11) 
				well[a][b] = '!';	
			else if(b == 12) 
				well[a][b] = '\n';
			else if(a == 12) 
				well[a][b] = '=';
			else 
				well[a][b] = ' ';
		}
	}

		
	while(fgets(line, 1000, fp) != NULL) {

		/*
		 * R = amount of times to rotate
		 * S = y axis starting position
		 */

		char P = line[0];
		int R = line[3] - '0';
		int S = line[5] - '0';
		int i, j, x, y, start;

		if(P == 'B') {
			char bP[4][4] = {{' ', ' ', '#', '#'}, {' ', '#', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
			if(R % 4 == 2 || R % 4 == 3)
				S++;
			rotatePiece(bP, R % 4);
			addPiece(well, bP, S);
		}
		else if(P == 'D') {
			char dP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}};
			if(R % 4 == 1 || R % 4 == 3)
				S++;
			rotatePiece(dP, R % 4);
			addPiece(well, dP, S);
		}	
		else if(P == 'G') {
			char gP[4][4] = {{' ', ' ', '#', '#'}, {' ', ' ', '#', '#'}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
			if(R % 4 == 0)
				S--;
			else if(R % 4 == 2 || R % 4 == 3)
				S++;
			rotatePiece(gP, R % 4);
			addPiece(well, gP, S);
		}
		else if(P == 'H') {
			char hP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {' ', '#', ' ', ' '}};
			if(R % 4 == 1 || R % 4 == 3)
				S++;
			rotatePiece(hP, R % 4);
			addPiece(well, hP, S);
		}
		else if(P == 'M') {
			char mP[4][4] = {{' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {'#', '#', ' ', ' '}, {' ', ' ', ' ', ' '}};
			if(R % 4 == 0)
				S++;
			else if(R % 4 == 1 || R % 4 == 3)
				S--;
			rotatePiece(mP, R % 4);
			addPiece(well, mP, S);
		}
		else if(P == 'N') {
			char nP[4][4] = {{' ', ' ', '#', ' '}, {' ', '#', '#', '#'}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
			addPiece(well, nP, S);
		}

		for(x=0; x<12; x++) {
			for(y=1; y<11; y++) {
				if(well[x][y] != '#')
					break;
				if(y == 10 && well[x][y] == '#')
				{
					start = x;
					
					for(i=1; i<11; i++)
						well[x][i] = ' ';
					
					for(i=start-1; i>=0; i--) {
						for(j=1; j<11; j++) {
							well[i+1][j] = well[i][j];
						}
					}	
				}
			}
		}
	}
	printf("\033[2J\033[1;1H");
		for(a=0; a<13; a++)
			for(b=0; b<13; b++)
				putchar(well[a][b]);

	fclose(fp);

	return 0;
}

void addPiece(char well[][13], char piece[][4], int y)
{
	int start = 0;
	int collision = 0;
	int end = 10;
	int a=0, b=0;
	int i, j;

	if(piece[3][0] == '#' || piece[3][1] == '#' || piece[3][2] == '#' || piece[3][3] == '#')
	       end = 9;

	while(start < end && collision == 0) {
		int a=0, b=0;
		int i, j;
		for(i=start; i<start+4; i++) {
			for(j=y; j<y+4; j++) {
				if(well[i][j] == '#' && piece[a][b] == '#')
					collision = 1;
				b++;
			}
			a++;
			b=0;
		}
		if(collision == 0)
			start++;
	}
	
	start--;

	for(i=start; i<start+4; i++) {
		for(j=y; j<y+4; j++) {
			if(piece[a][b] == '#')
				well[i][j] = piece[a][b];
			b++;
		}
		a++;
		b=0;
	}
}

void rotatePiece(char piece[][4], int t)
{
	int i=0;
	int x, y;

	while(i < t)
	{
		for(x=0; x<2; x++) {
			for(y=x; y<4-x-1; y++) {
				char temp = piece[x][y];
				piece[x][y] = piece[4-1-y][x];
				piece[4-1-y][x] = piece[4-1-x][4-1-y];
				piece[4-1-x][4-1-y] = piece[y][4-1-x];
				piece[y][4-1-x] = temp;
			}
		}
		i++;
	}
}
