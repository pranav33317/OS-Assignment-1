#include <stdio.h>
// Default time : Sun Sep 15 23:33:35 IST 2024
// UTC Format : Sun Sep 15 18:02:53 UTC 2024 (-u)
// RFC 2822 format : (-r)
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>

// Function to print date in UTC format
void print_utc()
{
    time_t time_variable;
    struct tm *utc_time_format;
    char full_date_in_utc[80];

    time(&time_variable);                     // Get current time
    utc_time_format = gmtime(&time_variable); // Convert to UTC

    // Format time in UTC format (default Linux format)
    strftime(full_date_in_utc, sizeof(full_date_in_utc), "%a %b %d %H:%M:%S UTC %Y", utc_time_format);
    printf("UTC: %s\n", full_date_in_utc);
}

// Function to print date in RFC 2822 format
void print_rfc2822()
{
    time_t time_variable;
    struct tm *local_time;
    char full_date_in_rfc2822[80];

    time(&time_variable);                   // Get current time
    local_time = localtime(&time_variable); // Convert to local time

    // Format time according to RFC 2822: Day, DD Mon YYYY HH:MM:SS ±TZ
    strftime(full_date_in_rfc2822, sizeof(full_date_in_rfc2822), "%a, %d %b %Y %H:%M:%S %z", local_time);
    printf("RFC 2822: %s\n", full_date_in_rfc2822);
}

// Function to print date in the default Linux 'date' format
void print_default()
{
    time_t time_variable;
    struct tm *local_time;
    char default_time[80];

    time(&time_variable);                   // Get current time
    local_time = localtime(&time_variable); // Convert to local time

    // Format time in default Linux 'date' format
    strftime(default_time, sizeof(default_time), "%a %b %d %H:%M:%S %Z %Y", local_time);
    printf("Default: %s\n", default_time);
}

int main(int argc, char *argv[])
{
    // Check if exactly two arguments are passed(including the program name)
    if (argc == 2)
    {
        // Get the flag at argv[1]
        if (strcmp(argv[1], "-u") == 0)
        {
            print_utc();
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            print_rfc2822();
        }
        else
        {
            printf("Not recognised , use only -u and -r flag\n");
        }
    }
    else if (argc == 1)
    {
        // Default presesentation of date
        print_default();
    }
    else
    {
        printf("No more flags than 1 , use only -u and -r flag\n");
    }
    return 0;
}
