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

void drawVerticalLine(int x, int y1, int y2)
{
    int y;

    for(y = y1; y <= y2; y++)
    {
        canvas[y][x] = '*';
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    drawHorizontalLine(x, x + width - 1, y);
    drawHorizontalLine(x, x + width - 1, y + height - 1);

    drawVerticalLine(x, y, y + height - 1);
    drawVerticalLine(x + width - 1, y, y + height - 1);
}


int main()
{
    initializeCanvas();

    drawPoint(10, 5);
    drawHorizontalLine(2, 20, 12);
    drawVerticalLine(25, 2, 15);
    drawRectangle(5, 2, 12, 6);

    displayCanvas();

    return 0;
}