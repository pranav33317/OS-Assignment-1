// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// void run_program(const char *program)
// {
//     printf("Running program: %s\n", program);
//     // This function will execute the given program using exec
//     execlp(program, program, (char *)NULL);
//     // If execlp fails
//     perror("exec failed");
//     exit(EXIT_FAILURE);
// }

// int main()
// {
//     int pid1, pid2, pid3;
//     int status;

//     // Create the first child process to run 'date'
//     pid1 = fork();
//     if (pid1 == 0)
//     {
//         // Inside the first child
//         printf("Child 1 (date) executing...\n");
//         run_program("./date"); // run date program
//     }
//     else if (pid1 > 0)
//     {
//         // In the parent process, create the second child process to run 'cal'
//         pid2 = fork();
//         if (pid2 == 0)
//         {
//             // Inside the second child
//             printf("Child 2 (cal) executing...\n");
//             run_program("./cal"); // run cal program
//         }
//         else if (pid2 > 0)
//         {
//             // In the parent process, create the third child process to run 'uptime'
//             pid3 = fork();
//             if (pid3 == 0)
//             {
//                 // Inside the third child
//                 printf("Child 3 (uptime) executing...\n");
//                 run_program("./uptime"); // run uptime program
//             }
//             else if (pid3 > 0)
//             {
//                 // Parent process: Wait for all child processes to finish
//                 waitpid(pid1, &status, 0);
//                 printf("Child 1 (date) finished with status: %d\n", WEXITSTATUS(status));
//                 waitpid(pid2, &status, 0);
//                 printf("Child 2 (cal) finished with status: %d\n", WEXITSTATUS(status));
//                 waitpid(pid3, &status, 0);
//                 printf("Child 3 (uptime) finished with status: %d\n", WEXITSTATUS(status));
//             }
//             else
//             {
//                 perror("fork failed for third child");
//             }
//         }
//         else
//         {
//             perror("fork failed for second child");
//         }
//     }
//     else
//     {
//         perror("fork failed for first child");
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int process_ID;

    // Fork three child processes
    for (int i = 0; i < 3; i++)
    {
        process_ID = fork();

        if (process_ID < 0)
        {
            perror("Fork failed");
            exit(1);
        }

        if (process_ID == 0)
        { // Child process
            if (i == 0)
            {
                execl("./date", "date", (char *)NULL); // Call ./date
            }
            else if (i == 1)
            {
                execl("./cal", "cal", (char *)NULL); // Call ./cal
            }
            else if (i == 2)
            {
                execl("./uptime", "uptime", (char *)NULL); // Call ./uptime
            }
            perror("execl failed");
            exit(1);
        }
    }

    // Wait for all children to finish
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    return 0;
}
