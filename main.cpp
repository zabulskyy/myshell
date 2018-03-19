#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <algorithm>
#include <dirent.h>
//#include <my_modules.h>
#include "my_modules.h"

using namespace std;

void parse_command(string &cmd);

void split_str(const string &txt, vector<string> &strs, char ch);

void execute(string &command, char *const *options);

void print_error(int error_code);

void execute_my_command(string &command, vector<string> options);

string get_error_string(int error_code);

void merrno_(vector<string> argv);

char *prj_dir;  // myshell directory
char cur_dir[1024];  // current directory
vector<string> my_modules = {"myhello", "merrno", "mpwd", "mcd", "mexit"};
int merrno = 0;

int main() {
    string cmd;  // command
    int parse_result = 0;  // just in case

    // get current directory
    if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
        cerr << "getcwd() error" << endl;
        merrno = 4;
    }
    if (merrno)
        print_error(merrno);

    char *prj_dir = cur_dir;
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
        cout << endl << cur_dir << " $ ";


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
        execute_my_command(command, commands);
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
            if (ent->d_name == command) {
                execve((command).c_str(), options, environ);
            };
        }
        closedir(adir);
    } else {
        /* could not open directory */
        merrno = 2;
    }
}

void execute_my_command(string &command, vector<string> options) {
    // {"myhello", "merrno", "mpwd", "mcd", "mexit"}

    for(int i = 0; i < my_modules.size(); i++){
        if(command == my_modules[i]){
            if(i == 0){
                merrno = myhello(options);
                return;
            } else if (i == 1){
                merrno_(options);
                return;
            } else if (i == 2){
                merrno = mpwd(options);
                return;
            } else if (i == 3){
                merrno = mcd(options);
                return;
            } else if (i == 4){
                int k = mexit(options);

                if (k != -1024){
                    merrno = abs(k);
                } else
                    merrno = 0;
//                cout<<merrno<<endl;
                merrno = min(merrno, 8);
                if( k > -1){
                    exit(merrno);
                }
                return;
            }

        }
    }



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
              "wrong arguments",
              "too few parameters",
              "unknown error"};
    return errors[error_code];

}

void print_error(int error_code) {
    cout << "\tError: " << get_error_string(error_code) << endl;
}

void merrno_(vector<string> argv){
    merrno = merrno_f(argv);
    print_error(merrno);
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