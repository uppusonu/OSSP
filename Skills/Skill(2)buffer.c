#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{
    struct termios oldt, newt;
    char buffer[100];
    int index = 0;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("praneeth@LAPTOP-SHK TDDI3 :~ $ ");
    fflush(stdout);

    while (1)
    {
        ch = getchar();

        if (ch == '\n')
        {
            buffer[index] = '\0';
            printf("\nYou entered: %s\n", buffer);
            break;
        }
        else if (ch == 127)
        {
            /* Backspace */
            if (index > 0)
            {
                index--;
                printf("\b \b");
                fflush(stdout);
            }
        }
        else
        {
            if (index < 99)
            {
                buffer[index] = ch;
                index++;

                printf("%c", ch);
                fflush(stdout);
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
