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
     * The command for the ssh
     *
     */
    char sshCommand[1024];

    /**
     *
     * Split the arg and fill the vars
     *
     */
    // check if there is arg
    if (argc != 2)
    {
        printf("Please enter the args correctly! \n");

        return 0;
    }

    char *token = strtok(argv[1], "@");
    if (token)
    {
        // the string before @ is the username
        username = token;

        // split remaining part and fill the host
        token = strtok(NULL, ":");
        if (token)
        {
            host = token;

            // split remaining part and fill the port
            token = strtok(NULL, ":");
            if (token)
            {
                port = token;
            }
            else
            {
                // if port was not declared, set it to 22
                port = "22";
            }
        }
    }

    // Check if data entered is correct
    if (username && host && port >= 0)
    {
        printf("User: %s\n", username);
        printf("Host: %s\n", host);
        printf("Port: %s\n", port);
    }
    else
    {
        printf("Invalid input string format.\n");
    }

    /**
     *
     * Execute the interactive ssh command
     *
     */
    // Use sprintf to create the ssh Command string with the values
    sprintf(sshCommand, "ssh -D 1080 -f -C -q -N -p %s %s@%s", port, username, host);

    // Open a pipe to execute the SSH command and capture its output
    FILE *pipe = popen(sshCommand, "r");

    if (pipe == NULL)
    {
        perror("popen");
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        printf("%s", buffer); // Print each line of output
    }

    pclose(pipe); // Close the first pipe
}