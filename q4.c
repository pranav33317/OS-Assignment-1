#include <stdio.h>
#include <stdlib.h>
#include <climits>
typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int time_quantum;
    int time_first_burst;
    int time_completion;
} Process_Table;

int compare_by_arrival_time(const void *first, const void *second)
{
    const Process_Table *process1 = (const Process_Table *)first;
    const Process_Table *process2 = (const Process_Table *)second;

    if (process1->arrival_time > process2->arrival_time)
        return 1;
    if (process1->arrival_time < process2->arrival_time)
        return -1;
    return 0;
}

int compare_by_burst_time(const void *first, const void *second)
{
    const Process_Table *process1 = (const Process_Table *)first;
    const Process_Table *process2 = (const Process_Table *)second;

    if (process1->burst_time > process2->burst_time)
        return 1;
    if (process1->burst_time < process2->burst_time)
        return -1;
    return 0;
}

void get_fifo(Process_Table *table, int length)
{
    qsort(table, length, sizeof(Process_Table), compare_by_arrival_time);

    int time = table[0].arrival_time;
    int *execution_order = (int *)malloc(length * sizeof(int));
    float average_turnaround = 0;
    float average_response = 0;

    for (int i = 0; i < length; i++)
    {
        table[i].time_first_burst = time;
        execution_order[i] = table[i].pid;
        time += table[i].burst_time;
        table[i].time_completion = time;
    }

    printf("FIFO Execution order:\n");
    for (int i = 0; i < length; i++)
    {
        average_response += table[i].time_first_burst - table[i].arrival_time;
        average_turnaround += table[i].time_completion - table[i].arrival_time;
        printf("Process No.%d %d\n", i + 1, execution_order[i]);
        // printf("Time of completion : %d\n", table[i].time_completion);
        // printf("Time for first burst : %d\n", table[i].time_first_burst);
        // printf("Time for arrival : %d\n", table[i].arrival_time);
    }

    printf("Average turnaround time: %f\n", average_turnaround / (float)length);
    printf("Average response time: %f\n", average_response / (float)length);

    free(execution_order);
}

// void get_sjf(Process_Table *table, int length)
// {
//     qsort(table, length, sizeof(Process_Table), compare_by_arrival_time);
//     int arrival_time = table[0].arrival_time;
//     int burst_time = table[0].burst_time;
//     int *execution_order = (int *)malloc(length * sizeof(int));
//     float average_turnaround = 0;
//     float average_response = 0;
//     int time = 0;
//     time += arrival_time;
//     table[0].arrival_time = time;
//     time += burst_time;
//     table[0].time_completion = time;
//     execution_order[0] = table[0].pid;
//     qsort(table, length, sizeof(Process_Table), compare_by_burst_time);
//     // now we have first shortest process' arrival and burst time
//     // for n-1 processes
//     for (int i = 1; i < length; i++)
//     {
//         // now find next process that has shortest time and arrived <= time
//         for (int j = 0; j < length; j++)
//         {
//             if (table[j].arrival_time <= time && table[j].time_completion == -1)
//             {
//                 table[j].arrival_time = time;
//                 time += table[j].burst_time;
//                 table[j].time_completion = time;
//                 execution_order[i] = table[j].pid;
//                 break;
//             }
//         }
//     }

//     printf("SJF Execution order:\n");
//     for (int i = 0; i < length; i++)
//     {
//         average_response += table[i].time_first_burst - table[i].arrival_time;
//         average_turnaround += table[i].time_completion - table[i].arrival_time;
//         printf("Process No.%d %d\n", i + 1, execution_order[i]);
//         printf("Time of completion : %d\n", table[i].time_completion);
//         printf("Time for first burst : %d\n", table[i].time_first_burst);
//         printf("Time for arrival : %d\n", table[i].arrival_time);
//     }

//     printf("Average turnaround time: %f\n", average_turnaround / (float)length);
//     printf("Average response time: %f\n", average_response / (float)length);

//     free(execution_order);
// }
void get_sjf(Process_Table *table, int length)
{
    // First, sort by arrival time
    qsort(table, length, sizeof(Process_Table), compare_by_arrival_time);

    // Array to keep track of whether a process has been scheduled
    int *scheduled = (int *)calloc(length, sizeof(int));

    int time = 0;
    int *execution_order = (int *)malloc(length * sizeof(int));
    float average_turnaround = 0;
    float average_response = 0;
    int completed = 0;

    for (; completed < length; completed++)
    {
        // Find the process with the shortest burst time that has arrived and not yet completed
        int min_burst_index = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < length; i++)
        {
            if (!scheduled[i] && table[i].arrival_time <= time && table[i].burst_time < min_burst_time)
            {
                min_burst_time = table[i].burst_time;
                min_burst_index = i;
            }
        }

        if (min_burst_index == -1)
        {
            // If no process is ready to run, skip to the next arrival time
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < length; i++)
            {
                if (!scheduled[i] && table[i].arrival_time < next_arrival_time)
                {
                    next_arrival_time = table[i].arrival_time;
                }
            }

            // Update time to the next arrival time if it is in the future
            if (next_arrival_time != INT_MAX)
            {
                time = next_arrival_time;
            }
            continue;
        }

        // Update time and completion for the selected process
        table[min_burst_index].time_first_burst = time;
        time += table[min_burst_index].burst_time;
        table[min_burst_index].time_completion = time;
        execution_order[completed] = table[min_burst_index].pid;
        scheduled[min_burst_index] = 1;
    }

    printf("SJF Execution order:\n");
    for (int i = 0; i < length; i++)
    {
        average_response += table[i].time_first_burst - table[i].arrival_time;
        average_turnaround += table[i].time_completion - table[i].arrival_time;
        printf("Process No.%d %d\n", i + 1, execution_order[i]);
        // printf("Time of completion : %d\n", table[i].time_completion);
        // printf("Time for first burst : %d\n", table[i].time_first_burst);
        // printf("Time for arrival : %d\n", table[i].arrival_time);
    }

    printf("Average turnaround time: %f\n", average_turnaround / (float)length);
    printf("Average response time: %f\n", average_response / (float)length);

    free(execution_order);
    free(scheduled);
}

void get_srtf(Process_Table *table, int length)
{
    // First, sort by arrival time
    qsort(table, length, sizeof(Process_Table), compare_by_arrival_time);

    // Array to keep track of remaining burst times
    int *remaining_burst_times = (int *)malloc(length * sizeof(int));
    int *execution_order = (int *)malloc(length * sizeof(int));
    float average_turnaround = 0;
    float average_response = 0;
    int completed = 0;
    int time = 0;

    // Initialize remaining burst times
    for (int i = 0; i < length; i++)
    {
        remaining_burst_times[i] = table[i].burst_time;
    }

    // Process information
    int *scheduled = (int *)calloc(length, sizeof(int));
    int *time_first_burst = (int *)calloc(length, sizeof(int));
    int last_process_index = -1;

    while (completed < length)
    {
        // Find the process with the shortest remaining time that has arrived and not yet completed
        int min_burst_index = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < length; i++)
        {
            if (!scheduled[i] && table[i].arrival_time <= time && remaining_burst_times[i] < min_burst_time)
            {
                min_burst_time = remaining_burst_times[i];
                min_burst_index = i;
            }
        }

        if (min_burst_index == -1)
        {
            // If no process is ready to run, skip to the next arrival time
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < length; i++)
            {
                if (!scheduled[i] && table[i].arrival_time < next_arrival_time)
                {
                    next_arrival_time = table[i].arrival_time;
                }
            }

            // Update time to the next arrival time if it is in the future
            if (next_arrival_time != INT_MAX)
            {
                time = next_arrival_time;
            }
            continue;
        }

        // Update times for the selected process
        if (last_process_index != min_burst_index)
        {
            if (last_process_index != -1 && remaining_burst_times[last_process_index] > 0)
            {
                remaining_burst_times[last_process_index] -= (time - time_first_burst[last_process_index]);
                time_first_burst[last_process_index] = time;
            }

            time_first_burst[min_burst_index] = time;
        }

        // Execute the process
        remaining_burst_times[min_burst_index]--;
        time++;

        if (remaining_burst_times[min_burst_index] == 0)
        {
            table[min_burst_index].time_completion = time;
            execution_order[completed] = table[min_burst_index].pid;
            scheduled[min_burst_index] = 1;
            completed++;
        }

        last_process_index = min_burst_index;
    }

    // Calculate average turnaround and response times
    for (int i = 0; i < length; i++)
    {
        average_response += time_first_burst[i] - table[i].arrival_time;
        average_turnaround += table[i].time_completion - table[i].arrival_time;
    }

    printf("SRTF Execution order:\n");
    for (int i = 0; i < length; i++)
    {
        printf("Process No.%d %d\n", i + 1, execution_order[i]);
    }

    printf("Average turnaround time: %f\n", average_turnaround / (float)length);
    printf("Average response time: %f\n", average_response / (float)length);

    free(remaining_burst_times);
    free(execution_order);
    free(scheduled);
    free(time_first_burst);
}
void get_rr(Process_Table *table, int length)
{
    int time_quantum = table[0].time_quantum;
    int *execution_order = (int *)malloc(length * sizeof(int));
    int *remaining_burst_times = (int *)malloc(length * sizeof(int));
    int *time_first_burst = (int *)malloc(length * sizeof(int));
    float average_turnaround = 0;
    float average_response = 0;
    int completed = 0;
    int current_time = 0;
    int front = 0;
    int rear = 0;

    // Initialize remaining burst times
    for (int i = 0; i < length; i++)
    {
        remaining_burst_times[i] = table[i].burst_time;
        time_first_burst[i] = -1; // Not started
    }

    for (; completed < length;)
    {
        int process_found = 0;

        for (int i = 0; i < length; i++)
        {
            if (table[i].arrival_time <= current_time && remaining_burst_times[i] > 0)
            {
                if (time_first_burst[i] == -1)
                {
                    time_first_burst[i] = current_time;
                }

                // Determine the time slice for the current process
                int time_slice = remaining_burst_times[i] < time_quantum ? remaining_burst_times[i] : time_quantum;

                // Update the current time and remaining burst time
                current_time += time_slice;
                remaining_burst_times[i] -= time_slice;

                // Mark the process as completed if its remaining burst time is zero
                if (remaining_burst_times[i] == 0)
                {
                    table[i].time_completion = current_time;
                    execution_order[completed] = table[i].pid;
                    completed++;
                }

                process_found = 1;
            }
        }

        if (!process_found)
        {
            current_time++;
        }
    }

    // Calculate average turnaround and response times
    for (int i = 0; i < length; i++)
    {
        average_response += time_first_burst[i] - table[i].arrival_time;
        average_turnaround += table[i].time_completion - table[i].arrival_time;
    }

    printf("RR Execution order:\n");
    for (int i = 0; i < length; i++)
    {
        printf("Process No.%d %d\n", i + 1, execution_order[i]);
    }

    printf("Average turnaround time: %f\n", average_turnaround / (float)length);
    printf("Average response time: %f\n", average_response / (float)length);

    free(execution_order);
    free(remaining_burst_times);
    free(time_first_burst);
}

int main()
{
    printf("Enter the number of processes you want to enter (don't enter more than 900):\n");
    int process_number;
    Process_Table table[1000];
    scanf("%d", &process_number);

    if (process_number > 1000 || process_number <= 0)
    {
        printf("Invalid number of processes. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < process_number; i++)
    {
        printf("Enter Process ID: ");
        scanf("%d", &table[i].pid);
        printf("Enter Arrival time: ");
        scanf("%d", &table[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &table[i].burst_time);
        printf("Enter Time quantum: (all processes should have same value of time quantum)\n ");
        scanf("%d", &table[i].time_quantum);

        table[i].time_completion = -1;  // Not completed
        table[i].time_first_burst = -1; // Not started
    }

    // Now that we have input, let's run FIFO and SJF
    get_fifo(table, process_number);
    get_sjf(table, process_number);
    get_srtf(table, process_number);
    get_rr(table, process_number);

    return 0;
}
