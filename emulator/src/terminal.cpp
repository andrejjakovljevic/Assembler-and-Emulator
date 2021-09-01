#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

using namespace std;

struct termios backup;

void vrati()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &backup);
}

void handler(int id)
{
    vrati();
}

void Terminal::end()
{
    vrati();
}

void Terminal::start()
{
    tcgetattr(STDIN_FILENO,&backup);
    struct termios nes = backup;
    nes.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    nes.c_cflag &= ~(CSIZE | PARENB);
    nes.c_cflag |= CS8;
    nes.c_cc[VMIN] = 0;
    nes.c_cc[VTIME] = 0;
    atexit(vrati);
    signal(SIGINT,handler);
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&nes);
}

void Terminal::citaj()
{
    char c;
    if (read(STDIN_FILENO,&c,1)==1)
    {
        p->mem[0xFF02]=c;
        p->interrupts[3]=true;
    }
}
