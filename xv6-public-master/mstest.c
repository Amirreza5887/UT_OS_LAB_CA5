#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    char *address = open_sharedmem(0);
    *address = 0;
    
    for (int i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            (*address) += 1;
            printf(1, "child %d\n", (*address));

            close_sharedmem(0);
            exit();
        }
        sleep(100);
    }

    for (int i = 0; i < 3; i++)
    {
        wait();
    }

    printf(1, "Final counter value: %d\n", *address);

    close_sharedmem(0);

    exit();
}
