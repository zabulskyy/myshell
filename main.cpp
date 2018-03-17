#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <dirent.h>

using namespace std;

int parse_command(string &cmd);

void split_str(const string &txt, vector<string> &strs, char ch);

void execute(const string &command, char *const *options);

void my_exit(string error);

char *prj_dir;  // myshell directory
char mds_dir[1024];  // modules directory
int merrno = 0;
vector<string> errors;

int main() {
    errors = {" ", "getcwd() error", "\tError: "};
    string cmd;  // command
    char cur_dir[1024];  // current directory
    int parse_result = 0;  // just in case

    // get current directory
    if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
        cerr << "getcwd() error" << endl;
        /*TODO myexit*/
    }

    char *prj_dir = cur_dir;
    char mds_dir[1024];
    strcpy(mds_dir, cur_dir);
    strcat(mds_dir, "/modules");

    while (true) {

        if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
            merrno = 1;
        }
        if (errno) {
            perror("\tError: ");
        }
        if (merrno) {
            my_exit(errors[merrno]);
        }


        cout << cur_dir << " $ ";


        if (getline(cin, cmd))
            parse_result = parse_command(cmd);

        if (parse_result != 0) {
            /*TODO myexit*/
        }

    }
    return 0;
}

int parse_command(string &cmd) {
    if (cmd.empty() ||
        cmd.find_first_not_of(' ') == string::npos ||
        cmd.find_first_not_of('\t') == string::npos)
        return 0;


    vector<string> commands;
    split_str(cmd, commands, ' ');


    string command = commands[0];

    char *t_options[commands.size() + 1];

    for (int i = 0; i < commands.size(); ++i) {
        t_options[i] = const_cast<char *>(commands[i].c_str());
    }

    t_options[commands.size()] = {nullptr};

    char *const *options = t_options;

    pid_t parent = getpid();
    pid_t pid = fork();
    int state = 0;

    /*error*/
    if (pid == -1) {
        /*TODO error*/
    }

    /*child*/
    if (pid == 0) {
        /*TODO try to search in modules */
        if (command[0] == 'm') {
            execute("modules/" + command, options);
            exit(1);
        }
    }

        /*parent*/
    else {
        waitpid(pid, &state, 0);
    }

    return 0;
}

void execute(const string &command, char *const *options) {

    execve(command.c_str(), options, environ);
}

void split_str(const string &txt, vector<string> &strs, char ch) {
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

};

void my_exit(string error) {
    cout << error << endl;

}

void myls() {
    DIR *adir;
    struct dirent *ent;
    if ((adir = opendir("/home/zabulskyy/CLionProjects/myshell")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(adir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(adir);
    } else {
        /* could not open directory */
        perror("");
    }
}
