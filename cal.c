#include <stdio.h>
#include <string.h>

// Zeller's Congruence Function
int zellers_congruence(int day_month, int month, int year_of_century, int zero_based_century)
{
    int h = (day_month + (13 * (month + 1) / 5) + year_of_century + (year_of_century / 4) + (zero_based_century / 4) - 2 * zero_based_century) % 7;
    if (h < 0)
    {
        h += 7; // Adjust for negative result
    }
    return h;
}

// Function to determine if a year is a leap year
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to return the number of days in a given month
int get_days_in_month(int month, int year)
{
    switch (month)
    {
    case 1:
        return 31; // January
    case 2:
        return is_leap_year(year) ? 29 : 28; // February
    case 3:
        return 31; // March
    case 4:
        return 30; // April
    case 5:
        return 31; // May
    case 6:
        return 30; // June
    case 7:
        return 31; // July
    case 8:
        return 31; // August
    case 9:
        return 30; // September
    case 10:
        return 31; // October
    case 11:
        return 30; // November
    case 12:
        return 31; // December
    default:
        return 0; // Invalid month
    }
}

void print_day_and_month(int month, int year)
{
    int flag_year_changed = 0;
    if (month <= 2)
    {
        flag_year_changed = 1;
        month += 12;
        year--;
    }

    int year_of_century = year % 100;
    int zero_based_century = year / 100;

    int day_number = zellers_congruence(1, month, year_of_century, zero_based_century);

    // Days of the week
    const char *day_of_week[] = {
        "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    printf("The first day of the month is : %s\n", day_of_week[day_number]);

    int no_days_month = get_days_in_month(month % 12, year + flag_year_changed);

    printf("Number of days in the month: %d\n", no_days_month);
    for (int i = 1; i <= no_days_month; i++)
    {
        printf("%d %s\n", i, day_of_week[day_number % 7]);
        day_number++;
    }
}

int main()
{
    int month;
    int year;

    printf("Enter month: ");
    scanf("%d", &month);

    printf("Enter year: ");
    scanf("%d", &year);

    if (year >= 0 && month >= 1 && month <= 12)
    {
        print_day_and_month(month, year);
    }
    else
    {
        printf("Please ensure month is between 1 and 12 and year is non-zero.\n");
    }

    return 0;
}
