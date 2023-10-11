#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Define port and host pointers
    char *port = NULL;
    char *host = NULL;
    char *username = NULL;

    /**
     *
     * Lopp through the arguments
     *
     */
    for (int i = 0; i < argc; i++)
    {

        /**
         *
         * Set the port
         *
         */

        // if the port is on -p
        if (strncmp(argv[i], "-p", 2) == 0)
        {
            if (i < argc - 1)
            {
                // Set the port to argument
                port = argv[i + 1];

                // Go to next argument
                i++;
            }
        }
        /**
         *
         * Set the host
         *
         */
        else if (strncmp(argv[i], "-h", 2) == 0)
        {
            if (i < argc - 1)
            {
                // set the host pointer to the argument
                host = argv[i + 1];

                // go to the next arg
                i++;
            }
        }

        /**
         *
         * Set the username
         *
         */
        else if (strncmp(argv[i], "-u", 2) == 0)
        {
            if (i < argc - 1)
            {
                // set the host pointer to the argument
                username = argv[i + 1];

                // go to the next arg
                i++;
            }
        }
    }

    /**
     *
     * Check if the host is not entered, return error
     *
     */
    if (!host)
    {
        printf("The host was not entered");

        return 0;
    }

    /**
     *
     * Check if the username is not entered, return error
     *
     */
    if (!username)
    {
        printf("The username was not entered");

        return 0;
    }

    printf("Port: %s\n", port);
    printf("Host: %s\n", host);
    printf("UserName: %s\n", username);
}