#include <stdio.h>
#include <termios.h>
#include <unistd.h> 
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>

bool inputAvailable()  
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return (FD_ISSET(0, &fds));
}

int main() {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = 'a';
    char* str = "Have not any characters";
    while(c != 'q')
    {
        if(inputAvailable()) {
            c = getchar();
            str = "Character written";
            if(c == 'b')
                str = "b written in char";
            else if (c == 'c')
                str = "c written in char";
        }
        printf("%s\n", str);
    }
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
