#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    int shared_page_id = 10;
    int *address = open_sharedmem(shared_page_id);
    *address = 1;

    for (int i = 0; i < 3; i++)
    {
        if (fork() == 0)
        {
            int *new_address = open_sharedmem(shared_page_id);
            *new_address += 1;
            printf(1, "child %d %d\n", (*new_address), new_address);
            printf(1, "child %d %d\n", (*address), address);


            close_sharedmem(shared_page_id);
            exit();
        }
        sleep(100);
    }

    for (int i = 0; i < 3; i++)
    {
        wait();
    }

    printf(1, "Final counter value: %d\n", *address);

    close_sharedmem(shared_page_id);

    exit();
}
