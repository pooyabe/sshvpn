#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_the_process_id()
{
    // Run a command to list processes and filter for the SSH process
    FILE *psOutput = popen("ps aux | grep 'ssh -D 1080 -f -C -N -p' | grep -v grep | awk '{print $2}'", "r");

    if (psOutput == NULL)
    {
        perror("popen");
        return -1;
    }

    char pid_buffer[256];
    if (fgets(pid_buffer, sizeof(pid_buffer), psOutput) != NULL)
    {
        int pid;
        if (sscanf(pid_buffer, "%d", &pid) == 1)
        {
            printf("SSH process ID: %d\n", pid);
            return pid;
        }
        else
        {
            printf("Unable to parse the process ID.\n");
        }
    }
    else
    {
        printf("SSH process not found.\n");
    }

    pclose(psOutput);
    return -1;
}

void kill_the_process()
{
    char sshKillCommand[1024];

    int the_id = get_the_process_id();

    // Check if there is any process
    if (the_id == -1)
    {
        printf("There is no ssh vpn process running");
        return;
    }

    /**
     *
     * Kill the process
     *
     */
    // Run a command to list processes and filter for the SSH process
    sprintf(sshKillCommand, "kill %d", the_id);

    //
    int result = system(sshKillCommand);

    if (result == 0)
    {
        printf("******\n VPN proxy stopped\n******\n");
    }
    else
    {
        printf("Failed to kill the process. If you are sure there is SSH Vpn tunnel running, please kill it manually! \n");
    }

    return;
}

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
        printf("Number of arguments not correct! \n");

        return 0;
    }

    /**
     *
     * Get ssh proxy running process id
     *
     */
    if (strncmp(argv[1], "pid", 3) == 0)
    {
        get_the_process_id();
        return 0;
    }

    /**
     *
     * Kill ssh proxy running process
     *
     */
    if (strncmp(argv[1], "kill", 4) == 0)
    {
        kill_the_process();
        return 0;
    }

    /**
     *
     * Run the ssh vpn tunnel
     *
     */
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
    sprintf(sshCommand, "ssh -D 1080 -f -C -N -p %s %s@%s", port, username, host);

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

    // Print Ok
    printf("******\n VPN proxy running on localhost(127.0.0.1) port 1080\n******\n");
}
