#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }

        printf("\n");
    }
}


void drawPoint(int x, int y)
{
    canvas[y][x] = '*';
}

void drawHorizontalLine(int x1, int x2, int y)
{
    int x;

    for(x = x1; x <= x2; x++)
    {
        canvas[y][x] = '*';
    }
}



int main()
{
    initializeCanvas();

    drawPoint(10, 5);
    drawHorizontalLine(5, 20, 8);

    displayCanvas();

    return 0;
}