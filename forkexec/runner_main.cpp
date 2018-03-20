#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
extern char **environ;

int main() {
    char *args[] = {0}; //Empty array of pointers
    string victim_name("victim_main");

    pid_t parent = getpid();
    pid_t pid = fork();


    if (pid == -1)
    {
        std::cerr << "Failed to fork()" << std::endl;
        return 1;
        //exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // We are parent process
        cout << "Parent: Hello from parent" << endl;
        cout << "Parent: Parent PID: " << parent << ", child PID: " << pid << endl;
        int status;
        waitpid(pid, &status, 0);
        cout << "Parent: child stopped, exit code: " << status << endl;
    }
    else
    {
        // We are the child
        execve(victim_name.c_str(), args, environ);
        cerr << "Parent: Failed to execute " << victim_name << " \n\tCode: " << errno << endl;
        return 1;
        //exit(EXIT_FAILURE);   // exec never returns
    }
    return 0;
}