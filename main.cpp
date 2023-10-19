#include <iostream>
#include <conio.h>

using namespace std;

const int height = 10;
const int width = 10;
int x, y, pointx, pointy, score;
int tailx[100], taily[100];
int ntail;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
bool gameOver;

void Setup()
{
    bool clear = true;
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    ntail = 3;
    for (int i = 0; i < ntail; i++)
    {
        tailx[i] = x - i - 1;
        taily[i] = y;
    }
    do
    {
        pointx = rand() % width;
        pointy = rand() % height;
        if (pointx == x && pointy == y)
            clear = false;
        for (int i = 0; i < ntail; i++)
        {
            if (pointx == tailx[i] && pointy == taily[i])
                clear = false;
        }
    } while (!clear);
    score = 0;
}

void Draw()
{
    system("clear");
    cout << "Controls:" << endl
         << "W:UP\tS:DONW\nA:LEFT\tD:RIGHT\nX:EXIT" << endl
         << "Enter any key to pause" << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0 || j == width + 2 - 1)
                cout << "#";
            else if (i == y && j - 1 == x)
                cout << "0";
            else if (i == pointy && j - 1 == pointx)
                cout << "*";
            else
            {
                bool blank = true;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j - 1 && taily[k] == i)
                    {
                        if (k == 0 && tailx[k] == x)
                            cout << "|";
                        else if (tailx[k] == tailx[k - 1])
                            cout << "|";
                        else
                            cout << "-";
                        blank = false;
                    }
                }
                if (blank)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "SCORE : " << score << endl;
    cout << "no of tail: " << ntail << endl;
}

void Input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            dir = STOP;
            break;
        }
    }
}

void Logic()
{
    if (dir != STOP)
    {
        int prevX = tailx[0];
        int prevY = taily[0];
        int tempx, tempy;
        tailx[0] = x;
        taily[0] = y;
        for (int i = 1; i < ntail; i++)
        {
            tempx = tailx[i];
            tempy = taily[i];
            tailx[i] = prevX;
            taily[i] = prevY;
            prevX = tempx;
            prevY = tempy;
        }
    }
    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
    default:
        break;
    }

    for (int i = 0; i < ntail; i++)
    {
        if (x == tailx[i] && y == taily[i])
            gameOver = true;
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    if (x == pointx && y == pointy)
    {
        score += 10;

        bool clear = true;
        do
        {
            pointx = rand() % width;
            pointy = rand() % height;
            for (int i = 0; i < ntail; i++)
            {
                if (pointx == tailx[i] && pointy == taily[i])
                    clear = false;
            }
        } while (!clear);

        ntail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        sleep(1);
    }
    sleep(1);
    cout << "\nGAME OVER!!!" << endl;
    sleep(1);
    cout << "\nPress 'r' to continue playing or press any other key to exit" << endl;
    if (getch() == 'r')
        main();

    return 0;
}
