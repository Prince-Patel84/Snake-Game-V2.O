#ifndef CONIO_H
#define CONIO_H

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
void ClearScreen(bool full)
    {
        if(full)
        system("cls");
        else{
            HANDLE hOut;
            COORD Position = {0, 0};
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(hOut, Position);
        }
    }

    void SleepFunction(int milliseconds) {
        Sleep(milliseconds);
    }
#else
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

inline char _getch()
{
    struct termios oldt, newt;
    char ch;

    // Save current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar(); // Read single character

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

    void ClearScreen(bool full)
    {
        system("clear");
    }

    void SleepFunction(int milliseconds) {
        usleep(milliseconds * 1000); // Convert to microseconds
    }


#endif

#endif // CONIO_H
