#include <stdio.h>
#include <sys/sysctl.h>
#include <time.h>
#include <errno.h>

// Function to print the system's uptime in hours, minutes, and seconds
void print_uptime_human_readable(time_t total_seconds_up)
{
    // Calculate the number of hours from total uptime seconds
    long total_hours_uptime = total_seconds_up / 3600;

    // Calculate the remaining minutes after hours
    long total_minutes_uptime = (total_seconds_up % 3600) / 60;

    // Calculate the remaining seconds after minutes
    long total_seconds_uptime = total_seconds_up % 60;

    // Print the result in "hours, minutes, and seconds" format
    printf("Uptime: %ld hours, %ld minutes, %ld seconds\n", total_hours_uptime, total_hours_uptime, total_seconds_uptime);
}

int main()
{
    // Structure to hold the boot time retrieved by sysctl
    struct timeval boot_time;

    // Define the size of the boot_time structure
    size_t boot_time_size = sizeof(boot_time);

    // Define the MIB (Management Information Base) array with KERN_BOOTTIME
    // This is used to specify the sysctl query
    int mib[2] = {CTL_KERN, KERN_BOOTTIME};

    // Use sysctl to retrieve the boot time of the system since this is MacOS
    // If sysctl fails, it returns -1, and we print an error message
    if (sysctl(mib, 2, &boot_time, &boot_time_size, NULL, 0) == -1)
    {
        // Print an error message if sysctl fails
        perror("Error retrieving boot time");
        return 1; // Exit with error code
    }

    // Variable to store the current time (in seconds since the Epoch)
    time_t current_time;

    // Retrieve the current time and store it in current_time
    time(&current_time);

    // Calculate the uptime in seconds by subtracting the boot time from the current time
    // `boot_time.tv_sec` holds the boot time in seconds since the Epoch
    time_t total_seconds_uptime = current_time - boot_time.tv_sec;

    // Error check: If the uptime calculation gives a negative value, print an error
    if (total_seconds_uptime < 0)
    {
        fprintf(stderr, "Error: negative uptime value\n");
        return 1; // Exit with error code
    }

    // Call the function to print the uptime in hours, minutes, and seconds
    print_uptime_human_readable(total_seconds_uptime);

    return 0; // Exit with success code
}
