#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "winlix.h"

using namespace std;

// Game Variables
int WIDTH = 80;
int HEIGHT = 30;
char BORDER = '#';
const char FOOD = 'F';
char SNAKE_HEAD = 'O';
char SNAKE_TAIL = 'o';
const int WALL_SHRINK = 1;
const int SPEED_UP = 1;
const int SHRINK_POINT = 2;
int SPEED = 100;
int score = 0;
int maxscore = 0;
int snakeX, snakeY;
bool GameStatus = true;
vector<pair<int, int>> SnakeMap;
const vector<string> DIRECTION = {"LEFT", "RIGHT", "UP", "DOWN", "STOP"};

// All Function Declaration
char SetUp();
int MapSelection();
void SnakeSelection();
void Loading();
void KeyInput();
void GameLogic_Easy();
void GameLogic_Medium();
void GameLogic_Hard();
void Draw(int m);
void GameOver();
void PlayAgain();
// Snake Class
class Snake
{
private:
    int x;
    int y;
    string CurrDir = "STOP";

public:
    int getPosX()
    {
        return x;
    }

    int getPosY()
    {
        return y;
    }

    string getDir()
    {
        return CurrDir;
    }

    int setPosX(int x)
    {
        this->x = x;
        snakeX = x;
        return x;
    }

    int setPosY(int y)
    {
        this->y = y;
        snakeY = y;
        return y;
    }

    string setDir(string dir)
    {
        CurrDir = dir;
        return CurrDir;
    }
};

// Food Class
class Food
{
private:
    int x;
    int y;

public:
    int getPosX()
    {
        return x;
    }

    int getPosY()
    {
        return y;
    }
    vector<int> GenFood(bool bor = true)
    {
        if (bor)
        {
            srand(time(0));
            while (true)
            {
                this->x = rand() % (WIDTH - 3) + 1;
                this->y = rand() % (HEIGHT - 3) + 1;
                if ((this->x != snakeX) && (this->y != snakeY))
                    break;
            }

            vector<int> position;
            position.push_back(this->x);
            position.push_back(this->y);

            return position;
        }
        else
        {
            srand(time(0));
            while (true)
            {
                this->x = rand() % (WIDTH - 3 - WALL_SHRINK) + 1;
                this->y = rand() % (HEIGHT - 3 - WALL_SHRINK) + 1;
                if ((this->x != snakeX) && (this->y != snakeY))
                    break;
            }

            vector<int> position;
            position.push_back(this->x);
            position.push_back(this->y);

            return position;
        }
    }
};

// Objects in Game
Snake s;
Food f;

int main()
{
    if (SetUp() == 'x')
        return 0;
    int m = MapSelection();
    SnakeSelection();
    Loading();

    while (GameStatus)
    {
        if (m == 1)
        {
            KeyInput();
            GameLogic_Easy();
            Draw(1);
        }
        else if (m == 2)
        {
            KeyInput();
            GameLogic_Medium();
            Draw(2);
        }
        else
        {
            KeyInput();
            GameLogic_Hard();
            Draw(3);
        }
    }

    GameOver();
    return 0;
}

char SetUp()
{
    ClearScreen();
    // cout << "=======================================================================================================================================================================" << endl;
    // cout << "000000000000000   0000       000        000000        000    000  000000000000000      00000000000          000000       0000                 00000   000000000000000  " << endl;
    // cout << "000000000000000   00000      000       00000000       000   000   000000000000000     0000000000000        00000000      00000               000000   000000000000000  " << endl;
    // cout << "000               000000     000      000    000      000  000    000                0000        000      000    000     000000             000 000   000              " << endl;
    // cout << "000               000 000    000     000      000     000 000     000                000                 000      000    000  000         000   000   000              " << endl;
    // cout << "000000000000000   000  000   000    000        000    000000      000000000000       000                000        000   000   000       000    000   000000000000     " << endl;
    // cout << "000000000000000   000   000  000   0000000000000000   000000      000000000000       000               0000000000000000  000     000    000     000   000000000000     " << endl;
    // cout << "            000   000    000 000   0000000000000000   000 000     000                000      000000   0000000000000000  000       000 000      000   000              " << endl;
    // cout << "            000   000     000000   000          000   000  000    000                0000    0000000   000          000  000         000        000   000              " << endl;
    // cout << "000000000000000   000      00000   000          000   000   000   000000000000000     000000000 000    000          000  000                    000   000000000000000  " << endl;
    // cout << "000000000000000   000       0000   000          000   000    000  000000000000000      00000000  000   000          000  000                    000   000000000000000  " << endl;
    // cout << "=======================================================================================================================================================================" << endl;
    // cout << "                                                                                                                                                    -By Binary Minds.  " << endl;
    // cout << "=======================================================================================================================================================================" << endl;
    
    cout << "                                                                                                                                                                       " << endl;
    cout << "                                                                               $$$$$$$$$$                                                                              " << endl;
    cout << "                                                                              $   Play   $  -Press p To Play.                                                          " << endl;
    cout << "                                                                               $$$$$$$$$$                                                                              " << endl;
    cout << "                                                                                                                                                                       " << endl;
    cout << "                                                                               $$$$$$$$$$                                                                              " << endl;
    cout << "                                                                              $   Quit   $  -Press x To Quit.                                                          " << endl;
    cout << "                                                                               $$$$$$$$$$                                                                              " << endl;
    cout << "                                                                                                                                                                       " << endl;
    FILE *file = fopen("maxscore.txt", "r");
    if (file == NULL)
    {
        cout << "Something Went Wrong." << endl;
    }

    fscanf(file, "%d", &maxscore);

    fclose(file);

    while (true)
    {
        char c = _getch();

        if (c == 'p')
            return 'p';
        else if (c == 'x')
            return 'x';
    }
}

int MapSelection()
{
    ClearScreen();
    cout << "-----> Choose Your Favourite Map:" << endl;
    cout << "       ####################            $$$$$$$$$$$$$$$$$$$$           &&&&&&&&&&&&&&&&&&&&       " << endl;
    cout << "       #                  #            $                  $           &                **&       " << endl;
    cout << "       #                  #            $                  $           &       =====    **&       " << endl;
    cout << "       #~~~      F   @~~~~#            $      ----O  F    $           &  F  0==   =    **&       " << endl;
    cout << "       #                  #            $      -           $           &           ==== **&       " << endl;
    cout << "       #                  #            $   ----           $           &                **&       " << endl;
    cout << "       #                  #            $ ---              $           &******************&       " << endl;
    cout << "       ####################            $$$$$$$$$$$$$$$$$$$$           &&&&&&&&&&&&&&&&&&&&       " << endl;
    cout << "      --Through The Walls--O             ..|Rock Walls|..             --|Shrinking Walls|--      " << endl;
    cout << "               (1)                              (2)                            (3)               " << endl;
    while (true)
    {
        char c = _getch();
        if (c == '1')
            return 1;
        else if (c == '2')
        {
            BORDER = '$';
            return 2;
        }
        else if (c == '3')
        {
            SPEED = 90;
            BORDER = '&';
            return 3;
        }
    }
}

void SnakeSelection()
{
    ClearScreen();
    cout << "-----> Choose Your Snake:" << endl;
    cout << "       ####################            $$$$$$$$$$$$$$$$$$$$           &&&&&&&&&&&&&&&&&&&&       " << endl;
    cout << "       #         ~~@      #            #         --O      #           #         ==0      #       " << endl;
    cout << "       #         ~        #            #         -        #           #         =        #       " << endl;
    cout << "       #       ~~~        #            #       ---        #           #       ===        #       " << endl;
    cout << "       ####################            $$$$$$$$$$$$$$$$$$$$           &&&&&&&&&&&&&&&&&&&&       " << endl;
    cout << "               (1)                              (2)                            (3)               " << endl;
    while (true)
    {
        char c = _getch();
        if (c == '1')
        {
            SNAKE_HEAD = '@';
            SNAKE_TAIL = '~';
            break;
        }
        else if (c == '2')
        {
            SNAKE_HEAD = 'O';
            SNAKE_TAIL = '-';
            break;
        }
        else if (c == '3')
        {
            SNAKE_HEAD = '0';
            SNAKE_TAIL = '=';
            break;
        }
    }
}

void Loading()
{
    ClearScreen();

    SleepFunction(450);
    cout << "Preparing Environment for Game..." << endl;
    s.setPosX(WIDTH / 2);
    s.setPosY(HEIGHT / 2);
    SnakeMap.insert(SnakeMap.begin(), {WIDTH / 2, HEIGHT / 2});
    SleepFunction(450);

    cout << "Snake Is Coming..." << endl;
    f.GenFood();
    SleepFunction(400);

    cout << "Setting Up Controlls..." << endl;
    SleepFunction(400);

    cout << "Enjoy..." << endl;
    SleepFunction(900);
}

void KeyInput()
{
    if (_kbhit())
    {
        int c = _getch();
        switch (c)
        {
        case 'w':
            if (!(s.getDir() == "DOWN"))
                s.setDir("UP");
            break;
        case 'a':
            if (!(s.getDir() == "RIGHT"))
                s.setDir("LEFT");
            break;
        case 's':
            if (!(s.getDir() == "UP"))
                s.setDir("DOWN");
            break;
        case 'd':
            if (!(s.getDir() == "LEFT"))
                s.setDir("RIGHT");
            break;
        case 'x':
            s.setDir("STOP");
            GameStatus = false;
            break;
        }
    }
}

void GameLogic_Easy()
{
    auto head = SnakeMap.front();
    for (auto p : SnakeMap)
    {
        if (s.getPosX() == p.first && s.getPosY() == p.second && score > 3)
        {
            GameStatus = false;
            return;
        }
    }

    if (s.getPosX() >= WIDTH - 1)
    {
        s.setPosX(1);
        SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});
    }
    else if (s.getPosX() <= 0)
    {
        s.setPosX(WIDTH - 2);
        SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});
    }
    else if (s.getPosY() >= HEIGHT - 1)
    {
        s.setPosY(1);
        SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});
    }
    else if (s.getPosY() <= 0)
    {
        s.setPosY(HEIGHT - 2);
        SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});
    }
    else
        SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});

    if (s.getDir() == "UP")
        s.setPosY(s.getPosY() - 1);
    else if (s.getDir() == "DOWN")
        s.setPosY(s.getPosY() + 1);
    else if (s.getDir() == "LEFT")
        s.setPosX(s.getPosX() - 1);
    else if (s.getDir() == "RIGHT")
        s.setPosX(s.getPosX() + 1);

    if (f.getPosX() == s.getPosX() && f.getPosY() == s.getPosY())
    {
        score++;
        SPEED -= SPEED_UP;
        f.GenFood();
    }
    else
    {
        SnakeMap.pop_back();
    }
}

void GameLogic_Medium()
{
    auto head = SnakeMap.front();
    for (auto p : SnakeMap)
    {
        if (s.getPosX() == p.first && s.getPosY() == p.second && score > 3)
        {
            GameStatus = false;
            return;
        }
    }

    SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});

    if (s.getDir() == "UP")
        s.setPosY(s.getPosY() - 1);
    else if (s.getDir() == "DOWN")
        s.setPosY(s.getPosY() + 1);
    else if (s.getDir() == "LEFT")
        s.setPosX(s.getPosX() - 1);
    else if (s.getDir() == "RIGHT")
        s.setPosX(s.getPosX() + 1);

    if (f.getPosX() == s.getPosX() && f.getPosY() == s.getPosY())
    {
        score++;
        SPEED -= SPEED_UP;
        f.GenFood();
    }
    else
    {
        SnakeMap.pop_back();
    }

    if (s.getPosX() >= WIDTH - 1 || s.getPosX() <= 0 || s.getPosY() >= HEIGHT - 1 || s.getPosY() <= 0)
        GameStatus = false;
}

void GameLogic_Hard()
{
    auto head = SnakeMap.front();
    for (auto p : SnakeMap)
    {
        if (s.getPosX() == p.first && s.getPosY() == p.second && score > 3)
        {
            GameStatus = false;
            return;
        }
    }

    SnakeMap.insert(SnakeMap.begin(), {s.getPosX(), s.getPosY()});

    if (s.getDir() == "UP")
        s.setPosY(s.getPosY() - 1);
    else if (s.getDir() == "DOWN")
        s.setPosY(s.getPosY() + 1);
    else if (s.getDir() == "LEFT")
        s.setPosX(s.getPosX() - 1);
    else if (s.getDir() == "RIGHT")
        s.setPosX(s.getPosX() + 1);

    if (f.getPosX() == s.getPosX() && f.getPosY() == s.getPosY())
    {
        score++;
        SPEED -= SPEED_UP;
        if (score % SHRINK_POINT == 0 && score != 0)
            f.GenFood(false);
        else
            f.GenFood();

        if (score % SHRINK_POINT == 1 && score != 1)
        {
            WIDTH -= WALL_SHRINK;
            HEIGHT -= WALL_SHRINK;
        }
    }
    else
    {
        SnakeMap.pop_back();
    }

    if (s.getPosX() >= WIDTH - 1 || s.getPosX() <= 0 || s.getPosY() >= HEIGHT - 1 || s.getPosY() <= 0)
        GameStatus = false;
}

void Draw(int m)
{
    ClearScreen();

    if (m == 1)
        cout << "Map: --Through The Walls--O" << endl;
    else if (m == 2)
        cout << "Map: ..|Rock Walls|.." << endl;
    else
        cout << "Map: --|Shrinking Walls|--" << endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            bool eSnake = false;
            for (auto p : SnakeMap)
            {
                if (SnakeMap.front() == p && p.first == j && p.second == i)
                {
                    cout << SNAKE_HEAD;
                    eSnake = true;
                    break;
                }
                else if (p.first == j && p.second == i)
                {
                    cout << SNAKE_TAIL;
                    eSnake = true;
                    break;
                }
            }
            if (!eSnake)
            {
                if (i == 0)
                    cout << BORDER;
                else if (j == f.getPosX() && i == f.getPosY())
                    cout << FOOD;
                else if (j == 0 || j == WIDTH - 1)
                    cout << BORDER;
                else if (i == HEIGHT - 1)
                    cout << BORDER;
                else
                    cout << ' ';
            }
        }
        cout << endl;
    }
    if (maxscore < score)
        maxscore = score;
    cout << "\nScore:" << score << ' ' << "Max Score:" << maxscore << endl;
    cout << "\nPress x To Quit the Game..." << endl;

    if (_kbhit())
        if (_getch() == 'x')
            GameStatus = false;

    SleepFunction(SPEED);
}

void GameOver()
{
    FILE *file = fopen("maxscore.txt", "w");
    if (file == NULL)
    {
        cout << "Something Went Wrong." << endl;
    }
    fprintf(file, "%d", maxscore);
    fclose(file);

    ClearScreen();

    cout << "=====================================================================================================================================================================" << endl;
    cout << "         00000000000          000000       0000     0000  000000000000000            000000000     000                   000  000000000000000   000000000000         " << endl;
    cout << "        0000000000000        00000000      00000   00000  000000000000000          000       000    000                 000   000000000000000   000       000        " << endl;
    cout << "       0000        000      000    000     000000 000000  000                     000         000    000               000    000               000        000       " << endl;
    cout << "       000                 000      000    000 00000 000  000                     000         000     000             000     000               000       000        " << endl;
    cout << "       000                000        000   000  000  000  000000000000            000         000      000           000      000000000000      000     000          " << endl;
    cout << "       000               0000000000000000  000   0   000  000000000000            000         000       000         000       000000000000      000000000            " << endl;
    cout << "       000      000000   0000000000000000  000       000  000                     000         000        000       000        000               000     000          " << endl;
    cout << "       0000    0000000   000          000  000       000  000                     000         000         000     000         000               000      000         " << endl;
    cout << "        000000000 000    000          000  000       000  000000000000000          000       000           000   000          000000000000000   000       000        " << endl;
    cout << "         00000000  000   000          000  000       000  000000000000000            000000000              0000000           000000000000000   000         000      " << endl;
    cout << "=====================================================================================================================================================================" << endl;

    cout << "\n                                       ";

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            bool eSnake = false;
            for (auto p : SnakeMap)
            {
                if (SnakeMap.front() == p && p.first == j && p.second == i)
                {
                    cout << SNAKE_HEAD;
                    eSnake = true;
                    break;
                }
                else if (p.first == j && p.second == i)
                {
                    cout << SNAKE_TAIL;
                    eSnake = true;
                    break;
                }
            }
            if (!eSnake)
            {
                if (i == 0)
                    cout << BORDER;
                else if (j == f.getPosX() && i == f.getPosY())
                    cout << FOOD;
                else if (j == 0 || j == WIDTH - 1)
                    cout << BORDER;
                else if (i == HEIGHT - 1)
                    cout << BORDER;
                else
                    cout << ' ';
            }
        }
        cout << "\n                                       ";
    }

    cout << "\n                                                               Score:" << score << ' ' << "                   Max Score:" << maxscore << endl;

    cout << endl;
    cout << "=====================================================================================================================================================================" << endl;
    cout << "                                                                                                                                                                   " << endl;
    cout << "                                                                     $$$$$$$$$$$$$$$$$$$$                                                                          " << endl;
    cout << "                                                                    $     Play Again     $  -Press p To Play Again.                                                " << endl;
    cout << "                                                                     $$$$$$$$$$$$$$$$$$$$                                                                          " << endl;
    cout << "                                                                                                                                                                   " << endl;
    cout << "                                                                          $$$$$$$$$$                                                                               " << endl;
    cout << "                                                                         $   Quit   $  -Press x To Quit.                                                           " << endl;
    cout << "                                                                          $$$$$$$$$$                                                                               " << endl;
    cout << "                                                                                                                                                                   " << endl;
    cout << "=====================================================================================================================================================================" << endl;
    while (true)
    {
        char c = _getch();
        if (c == 'p')
        {
            PlayAgain();
            break;
        }
        else if (c == 'x')
            break;
    }
}

void PlayAgain()
{
    ClearScreen();
    GameStatus = true;
    SnakeMap = {};
    s.setDir("STOP");
    score = 0;
    SPEED = 100;

    int m = MapSelection();
    SnakeSelection();
    Loading();

    while (GameStatus)
    {
        if (m == 1)
        {
            KeyInput();
            GameLogic_Easy();
            Draw(1);
        }
        else if (m == 2)
        {
            KeyInput();
            GameLogic_Medium();
            Draw(2);
        }
        else
        {
            KeyInput();
            GameLogic_Hard();
            Draw(3);
        }
    }

    GameOver();
}