#include <string.h>
void addPiece(char well[][13], char piece[][4], int y);
void rotatePiece(char piece[][4], int t);

int main(int argc, char *argv[])
{
        char well[13][13];
        char bP[4][4] = {{' ', ' ', '#', '#'}, {' ', '#', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
        char dP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}};
        char gP[4][4] = {{' ', ' ', '#', '#'}, {' ', ' ', '#', '#'}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
        char hP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {' ', '#', ' ', ' '}};
        char mP[4][4] = {{' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {'#', '#', ' ', ' '}, {' ', ' ', ' ', ' '}};
        char nP[4][4] = {{' ', ' ', '#', ' '}, {' ', '#', '#', '#'}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};


        int a, b;
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


        char line[1000];
        FILE *fp;
        fp = fopen(argv[1], "r");

        while(fgets(line, 1000, fp) != NULL) {

                /*
                 * R = amount of times to rotate
                 * S = starting position
                 */
                char P = line[0];
                int R = line[3] - '0';
                int S = line[5] - '0';
                char rp[4][4];

                if(P == 'B') {
                        if(R % 4 == 2 || R % 4 == 3)
                                S++;
                        char bP[4][4] = {{' ', ' ', '#', '#'}, {' ', '#', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
                        rotatePiece(bP, R % 4);
                        addPiece(well, bP, S);
                }
                else if(P == 'D') {
                        if(R % 4 == 1 || R % 4 == 3)
                                S++;
                        char dP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}};
                        rotatePiece(dP, R % 4);
                        addPiece(well, dP, S);
                }
                else if(P == 'G') {
                        if(R % 4 == 0)
                                S--;
                        else if(R % 4 == 2 || R % 4 == 3)
                                S++;
                        char gP[4][4] = {{' ', ' ', '#', '#'}, {' ', ' ', '#', '#'}, {' ', ' ', '#', ' '}, {' ', ' ', ' ', ' '}};
                        rotatePiece(gP, R % 4);
                        addPiece(well, gP, S);
                }
                else if(P == 'H') {
                        if(R % 4 == 1 || R % 4 == 3)
                                S++;
                        char hP[4][4] = {{' ', ' ', '#', ' '}, {' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {' ', '#', ' ', ' '}};
                        rotatePiece(hP, R % 4);
                        addPiece(well, hP, S);
                }
                else if(P == 'M') {
                        if(R % 4 == 0)
                                S++;
                        else if(R % 4 == 1 || R % 4 == 3)
                                S--;
                        char mP[4][4] = {{' ', ' ', '#', ' '}, {' ', '#', '#', ' '}, {'#', '#', ' ', ' '}, {' ', ' ', ' ', ' '}};
                        rotatePiece(mP, R % 4);
                        addPiece(well, mP, S);
                               }


                int start;
                int x, y;
                for(x=0; x<12; x++) {
                        for(y=1; y<11; y++) {
                                if(well[x][y] != '#')
                                        break;
                                if(y == 10 && well[x][y] == '#')
                                {
                                        start = x;
                                        int i, j;
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

        int a=0,b=0;
        int i, j;
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
