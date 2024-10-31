#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int binary_search(int arr[], int target_element, int low, int high)
{
    if (low > high)
    {
        return -1; // Element not found
    }
    // middle element in sorted range
    int mid = low + (high - low) / 2;

    if (arr[mid] == target_element)
    {
        return mid; // Element found
    }

    // Create a pipe for communication between parent and child
    // 0th index stores the reading bit of the child process
    // 1st index stores the writing bit of the child process
    int pipe_communication[2];
    if (pipe(pipe_communication) == -1)
    {
        printf("Pipe failed\n");
        return -1;
    }

    int fork_child = fork();

    if (fork_child == 0) // Child process
    {
        close(pipe_communication[0]); // Close the read end in the child process

        // Search in the left half
        if (arr[mid] > target_element)
        {
            int left_child = binary_search(arr, target_element, low, mid - 1);
            write(pipe_communication[1], &left_child, sizeof(left_child)); // Write result to pipe
        }
        // Search in the right half
        else
        {
            int right_child = binary_search(arr, target_element, mid + 1, high);
            write(pipe_communication[1], &right_child, sizeof(right_child)); // Write result to pipe
        }

        close(pipe_communication[1]); // Close the write end after writing
        exit(0);                      // Exit the child process
    }
    else if (fork_child > 0) // Parent process
    {
        close(pipe_communication[1]); // Close the write end in the parent process

        int child_process_result;
        read(pipe_communication[0], &child_process_result, sizeof(child_process_result)); // Read result from pipe
        close(pipe_communication[0]);                                                     // Close the read end after reading

        wait(NULL); // Wait for the child process to finish

        return child_process_result; // Return the result from the child process
    }
    else
    {
        printf("Fork failed");
        return -1;
    }
}

int main()
{
    int len = 16;
    // Dynamic re-allocation of memory
    int *arr = (int *)malloc(len * sizeof(int));
    printf("The sorted array of 16 elements :\n");
    for (int i = 0; i < len; i++)
    {
        arr[i] = i + 1;
        printf("%d ", arr[i]);
    }

    printf("\nEnter target element to be searched: ");
    int target_element;
    scanf("%d", &target_element);

    int index = binary_search(arr, target_element, 0, len - 1);

    if (index != -1)
    {
        printf("Element found at index: %d\n", index);
    }
    else
    {
        printf("Element not found %d\n", -1);
    }

    free(arr); // Freeing the allocated memory
    return 0;
}
