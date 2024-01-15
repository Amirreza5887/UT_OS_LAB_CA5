#include "types.h"
#include "stat.h"
#include "user.h"
#include "spinlock.h"


int main()
{
    struct spinlock global_lock;
    char *phys_address = open_sharedmem(0);
    *phys_address = 0;
    // // char *shared_memory = (char *)phys_address;
    // // int *counter = (int *)(shared_memory);
    // // (*counter) ++;
    // (*counter) = 10;
    for (int i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {

            acquire(&global_lock);
            (*phys_address) += 1;
            printf(1, "child %d\n", (*phys_address));
            release(&global_lock);

            close_sharedmem(0);
            exit();
        }
    }

    for (int i = 0; i < 3; i++)
    {
        wait();
    }

    printf(1, "Final counter value: %d\n", *phys_address);

    close_sharedmem(0);

    exit();
}
