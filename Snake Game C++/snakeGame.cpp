#include<iostream>
#include<conio.h>
#include<windows.h>
#include<dos.h>
#include<time.h>
#define MAXSNAKESIZE 100
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{
    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console, CursorPosition);
}



class Point
{

private:
    int x,y;
public:
    Point()
    {
        x=y=10;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void SetPoint(int x, int y)
    {
        this->x = x;
        this->y = y;

    }

    int GetX()
    {
        return x;
    }

    int GetY()
    {
        return y;
    }

    void MoveUp()
    {
        y--;
    }

    void MoveDown()
    {
        y++;
    }

    void MoveLeft()
    {
        x--;
    }

    void MoveRight()
    {
        x++;
    }

    void Draw()
    {
        gotoxy(x,y);
        cout<<"±";
    }


    void FruitDraw()
    {
        gotoxy(x,y);
        cout<<"$";

    }

    void Erase()
    {
        gotoxy(x,y);
        cout<<" ";
    }

    void CopyPos(Point * p)
    {
        p->x = x;
        p->y = y;
    }

    void Debug()
    {
        cout<<"("<<x<<","<<y<<")";
    }
};

class Snake
{
private:
    Point * cell[MAXSNAKESIZE];
    int size;
    char direction;
    Point fruit;

public:
    Snake()
    {
        size = 1;
        cell[0] = new Point(20,20);
        for(int i=1; i<MAXSNAKESIZE; i++)
        {
            cell[i] = NULL;
        }
        fruit.SetPoint(rand()%50, rand()%25);
    }

    void AddCell(int x, int y)
    {
        cell[size++] = new Point(x,y);
    }

    void Up()
    {
        direction = 'w';
    }
    void Down()
    {
        direction = 's';
    }
    void Left()
    {
        direction = 'a';
    }
    void Right()
    {
        direction = 'd';
    }

    void Move()
    {
        system("cls");
        for(int i=size-1; i>0; i--)
        {
            cell[i-1]->CopyPos(cell[i]);
        }


        switch(direction)
        {
            case 'w':
                cell[0]->MoveUp();
                break;
            case 's':
                cell[0]->MoveDown();
                break;
            case 'a':
                cell[0]->MoveLeft();
                break;
            case 'd':
                cell[0]->MoveRight();
                break;
        }

        if(fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY())
        {
            AddCell(0,0);
            fruit.SetPoint(rand()%50, rand()%25);
        }

        for(int i=0; i<size; i++){
            cell[i]->Draw();
        }
        fruit.FruitDraw();
        //Debug();

        Sleep(50);

    }

};

void instruction()
    {
        system("cls");
        cout<<"Instructions";
        cout<<"\n--------------------"<<endl;
        cout<<"Eat Food By Moving Up Down Left Right."<<endl<<endl;
        cout<<"Press 'W' to Move Up"<<endl;
        cout<<"Press 'S' to Move Down"<<endl;
        cout<<"Press 'A' to Move Left"<<endl;
        cout<<"Press 'D' to Move Right"<<endl;
        cout<<"Press 'ESC' to Exit"<<endl<<endl;
        cout<<"Press Any Key To Get Back to Menu"<<endl;
        getch();
    }

int main()
{
    srand((unsigned)time(NULL));
    Snake snake;
    char op = 'l';

    do
    {
        system("cls");
        gotoxy(10,5);
        cout<<"-------------------------";
        gotoxy(10,6);
        cout<<"| King-Cobra Snake Game |";
        gotoxy(10,7);
        cout<<"-------------------------";
        gotoxy(10,9);
        cout<<"1. Start The Game";
        gotoxy(10,10);
        cout<<"2. Instructions";
        gotoxy(10,11);
        cout<<"3. Exit";
        gotoxy(10,13);
        cout<<"Select Option : ";

        char opt = getche();

        if(opt=='1')
        {
            do
            {
                if(kbhit()){
                op = getch();
                }
                switch(op)
                {
                case 'w':
                case 'W':
                    snake.Up();
                    break;

                case 's':
                case 'S':
                    snake.Down();
                    break;

                case 'a':
                case 'A':
                    snake.Left();
                    break;

                case 'd':
                case 'D':
                    snake.Right();
                    break;
                }
        snake.Move();

            }while(op != 'e');
        }

        else if(opt=='2')
            instruction();
        else if(opt=='3')
            exit(0);
    }while(1);


    return 0;
}
