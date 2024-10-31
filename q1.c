#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
int main()
{
    // Defining no of child processes
    int no_children = 7;
    // initliasing array to hold mean values of all children
    int mean_values_processes[no_children];
    for (int i = 1; i <= no_children; i++)
    {
        int fork_return_value = fork();
        // asserting if fork has been succesfull , else give assertion error
        assert(fork_return_value >= 0);
        // if it is a child
        if (fork_return_value == 0)
        {
            sleep(5);
            // initliasing random number generator using srand() or seed random
            // using pid here ensures diff value for each process
            srand(time(NULL) ^ (getpid() << 16));
            // srand is initialsed with time(NULL) or current time so that it gives different number each time  , since every time time(NULL)
            // gives diffrent value
            int sum = 0;
            for (int j = 1; j <= 4; j++)
            {
                // generating random number b/w 1 and 100
                int random_num = (rand() % 100) + 1;
                sum += random_num;
            }
            sum /= 4;
            mean_values_processes[i - 1] = sum;
            printf("The mean values for the process %d with Process ID  %d is %d\n", i, getpid(), sum);
            exit(0);
        }
    }
    for (int i = 1; i <= no_children; i++)
    {
        int wait_values = wait(NULL);
    }
    printf("Parent executed succesfully");
    return 0;
}