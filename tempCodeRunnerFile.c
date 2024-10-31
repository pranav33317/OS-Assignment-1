Check if exactly two arguments are passed(including the program name) if (argc == 2)
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