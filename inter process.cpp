#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main()
{
    int pipefd[2];
    pid_t pid;
    char buffer[256];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        cerr << "Failed to create pipe." << endl;
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        cerr << "Failed to fork a child process." << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process (Writer)

        // Close the unused read end of the pipe
        close(pipefd[0]);

        // Get input from the user
        cout << "Enter a message: ";
        cin.getline(buffer, sizeof(buffer));

        // Write the message to the pipe
        write(pipefd[1], buffer, strlen(buffer) + 1);

        // Close the write end of the pipe
        close(pipefd[1]);

        // Terminate the child process
        return 0;
    } else {
        // Parent process (Reader)

        // Close the unused write end of the pipe
        close(pipefd[1]);

        // Read the message from the pipe
        read(pipefd[0], buffer, sizeof(buffer));

        // Print the received message
        cout << "Received message: " << buffer << endl;

        // Close the read end of the pipe
        close(pipefd[0]);

        // Wait for the child process to terminate
        wait(NULL);

        // Terminate the parent process
        return 0;
    }
}
