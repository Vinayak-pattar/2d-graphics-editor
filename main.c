#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 50
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

typedef struct
{
    int id;
    int type;   // 1=line, 2=rectangle, 3=triangle, 4=circle
    int x1, y1, x2, y2;
    int width, height;
    int size;
    int radius;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;
int nextId = 1;

void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

void displayCanvas()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);

        printf("\n");
    }
}

void drawPoint(int x, int y)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
        canvas[y][x] = '*';
}

void drawLine(int x1, int y1, int x2, int y2)
{
    if(y1 == y2)
    {
        if(x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for(int x = x1; x <= x2; x++)
            drawPoint(x, y1);
    }
    else if(x1 == x2)
    {
        if(y1 > y2)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for(int y = y1; y <= y2; y++)
            drawPoint(x1, y);
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width - 1, y);
    drawLine(x, y + height - 1, x + width - 1, y + height - 1);
    drawLine(x, y, x, y + height - 1);
    drawLine(x + width - 1, y, x + width - 1, y + height - 1);
}

void drawTriangle(int x, int y, int size)
{
    for(int i = 0; i < size; i++)
    {
        drawPoint(x - i, y + i);
        drawPoint(x + i, y + i);
    }

    for(int i = x - size + 1; i <= x + size - 1; i++)
        drawPoint(i, y + size - 1);
}

void drawCircle(int cx, int cy, int radius)
{
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            int distance = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            int rSquare = radius * radius;

            if(abs(distance - rSquare) <= radius)
                drawPoint(x, y);
        }
    }
}

void redrawAllShapes()
{
    initializeCanvas();

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].type == 1)
            drawLine(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2);

        else if(shapes[i].type == 2)
            drawRectangle(shapes[i].x1, shapes[i].y1, shapes[i].width, shapes[i].height);

        else if(shapes[i].type == 3)
            drawTriangle(shapes[i].x1, shapes[i].y1, shapes[i].size);

        else if(shapes[i].type == 4)
            drawCircle(shapes[i].x1, shapes[i].y1, shapes[i].radius);
    }
}

void addLine()
{
    Shape s;
    s.id = nextId++;
    s.type = 1;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d", &s.x1, &s.y1, &s.x2, &s.y2);

    shapes[shapeCount++] = s;
    redrawAllShapes();

    printf("Line added with ID %d\n", s.id);
}

void addRectangle()
{
    Shape s;
    s.id = nextId++;
    s.type = 2;

    printf("Enter x y width height: ");
    scanf("%d %d %d %d", &s.x1, &s.y1, &s.width, &s.height);

    shapes[shapeCount++] = s;
    redrawAllShapes();

    printf("Rectangle added with ID %d\n", s.id);
}

void addTriangle()
{
    Shape s;
    s.id = nextId++;
    s.type = 3;

    printf("Enter x y size: ");
    scanf("%d %d %d", &s.x1, &s.y1, &s.size);

    shapes[shapeCount++] = s;
    redrawAllShapes();

    printf("Triangle added with ID %d\n", s.id);
}

void addCircle()
{
    Shape s;
    s.id = nextId++;
    s.type = 4;

    printf("Enter center x center y radius: ");
    scanf("%d %d %d", &s.x1, &s.y1, &s.radius);

    shapes[shapeCount++] = s;
    redrawAllShapes();

    printf("Circle added with ID %d\n", s.id);
}

void deleteShape()
{
    int id;
    printf("Enter shape ID to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].id == id)
        {
            shapes[i].type = 0;
            redrawAllShapes();
            printf("Shape deleted successfully.\n");
            return;
        }
    }

    printf("Shape ID not found.\n");
}

void modifyShape()
{
    int id;
    printf("Enter shape ID to modify: ");
    scanf("%d", &id);

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].id == id)
        {
            if(shapes[i].type == 1)
            {
                printf("Enter new x1 y1 x2 y2: ");
                scanf("%d %d %d %d", &shapes[i].x1, &shapes[i].y1, &shapes[i].x2, &shapes[i].y2);
            }
            else if(shapes[i].type == 2)
            {
                printf("Enter new x y width height: ");
                scanf("%d %d %d %d", &shapes[i].x1, &shapes[i].y1, &shapes[i].width, &shapes[i].height);
            }
            else if(shapes[i].type == 3)
            {
                printf("Enter new x y size: ");
                scanf("%d %d %d", &shapes[i].x1, &shapes[i].y1, &shapes[i].size);
            }
            else if(shapes[i].type == 4)
            {
                printf("Enter new center x center y radius: ");
                scanf("%d %d %d", &shapes[i].x1, &shapes[i].y1, &shapes[i].radius);
            }

            redrawAllShapes();
            printf("Shape modified successfully.\n");
            return;
        }
    }

    printf("Shape ID not found.\n");
}

void showMenu()
{
    printf("\n===== 2D Graphics Editor =====\n");
    printf("1. Add Line\n");
    printf("2. Add Rectangle\n");
    printf("3. Add Triangle\n");
    printf("4. Add Circle\n");
    printf("5. Delete Object\n");
    printf("6. Modify Object\n");
    printf("7. Display Picture\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        showMenu();
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addLine();
                break;

            case 2:
                addRectangle();
                break;

            case 3:
                addTriangle();
                break;

            case 4:
                addCircle();
                break;

            case 5:
                deleteShape();
                break;

            case 6:
                modifyShape();
                break;

            case 7:
                displayCanvas();
                break;

            case 8:
                printf("Exiting Graphics Editor...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while(choice != 8);

    return 0;
}