#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <algorithm>
#include <dirent.h>

using namespace std;

void parse_command(string &cmd);

void split_str(const string &txt, vector<string> &strs, char ch);

void execute(string &command, char *const *options);

void print_error(int error_code);

void execute_my_command(string &command, char *const *options);

string get_error_string(int error_code);

char *prj_dir;  // myshell directory
char mds_dir[1024];  // modules directory
vector<string> my_modules;
int merrno = 0;

int main() {
    string cmd;  // command
    char cur_dir[1024];  // current directory
    int parse_result = 0;  // just in case
    my_modules = {"myhello", "merrno", "mpwd", "mcd", "mexit"};

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
            merrno = 4;
        }
        if (errno) {
            perror("\tError: ");
        }
        if (merrno) {
            print_error(merrno);
        }

        merrno = 0;
        cout << cur_dir << " $ ";


        if (getline(cin, cmd))
            parse_command(cmd);

    }
    return 0;
}

void parse_command(string &cmd) {
    if (cmd.empty() ||
        cmd.find_first_not_of(' ') == string::npos ||
        cmd.find_first_not_of('\t') == string::npos)
        return;


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


    if (find(my_modules.begin(), my_modules.end(), command) != my_modules.end()) {
        execute_my_command(command, options);
        return;
    }


    /*error*/
    if (pid == -1) {
        merrno = 3;
        return;
    }

    /*child*/
    if (pid == 0) {
        execute(command, options);
        return;
    }

    /*parent*/
    waitpid(pid, &state, 0);
}

void execute(string &command, char *const *options) {

    DIR *adir;
    struct dirent *ent;
    if ((adir = opendir(prj_dir)) != nullptr) {
        while ((ent = readdir(adir)) != nullptr) {
            if (ent->d_name[0] == '.') continue;
            if(ent->d_name == command){
                execve((command).c_str(), options, environ);
            };
        }
        closedir(adir);
    } else {
        /* could not open directory */
        merrno = 2;
    }
}

void execute_my_command(string &command, char *const *options) {
    // {"myhello", "merrno", "mpwd", "mcd", "mexit"}

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

string get_error_string(int error_code) {
    vector<string> errors;
    errors = {"",
              "permission denied",
              "file/folder not found",
              "no such process",
              "getcwd() error",
              "no such command",
              "unknown error"};
    return errors[error_code];

}

void print_error(int error_code) {
    cout << "\tError: " << get_error_string(error_code) << endl;
}




/*
void myls() {
    DIR *adir;
    struct dirent *ent;
    if ((adir = opendir("/home/zabulskyy/CLionProjects/myshell")) != NULL) {
        //print all the files and directories within directory
        while ((ent = readdir(adir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        closedir(adir);
    } else {
        // could not open directory
        perror("");
    }
}
*/