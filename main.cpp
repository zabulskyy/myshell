#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <climits>
//#include <defauld_modules.h>
//#include "defauld_modules.h"

using namespace std;

int myhello(vector<string> argv);

int mpwd(vector<string> argv);

int mcd(vector<string> argv);

int mexit(vector<string> argv);

int merrno_f(vector<string> argv);

void parse_command(const string &cmd);

void split_str(const string &txt, vector<string> &strs, char ch);

void execute(const string &command, char *const *options);

void print_error(int error_code);

void execute_default_command(const string &command, const vector<string> &options);

void execute_my_command(const string &command, char *const *options);

string get_error_string(int error_code);

void merrno_(vector<string> argv);

vector<string> wildcards(string str);

char prj_dir[1024];;  // myshell directory
const char *mod_dir;  // modules directory
char cur_dir[1024];   // current directory
vector<string> defauld_modules = {"merrno", "mpwd", "mcd", "mexit"};
vector<string> my_modules = {"myhello", "mycat"};
int merrno = 0;

int main() {
    string cmd;  // command
    int parse_result = 0;  // just in case
    // get current directory
    if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
        cerr << "getcwd() error";
        merrno = 4;
    }    if (getcwd(prj_dir, sizeof(prj_dir)) == nullptr) {
        cerr << "getcwd() error";
        merrno = 4;
    }
    if (merrno)
        print_error(merrno);

    char *prj_dir = cur_dir;
    wildcards("dkdk");
    while (true) {

        if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
            merrno = 4;
        }
        if (merrno) {
            print_error(merrno);
        }

        merrno = 0;
        printf("\n%s $ ", cur_dir);
        if (getline(cin, cmd)) {
            cout << cmd << endl;
            parse_command(cmd);
        }
    }
    return 0;
}

void parse_command(string cmd) {

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


    if (find(defauld_modules.begin(), defauld_modules.end(), command) != defauld_modules.end()) {
        execute_default_command(command, commands);
        return;
    }


    if (find(my_modules.begin(), my_modules.end(), command) != my_modules.end()) {
        execute_my_command(command, commands);
        return;
    }


    pid_t parent = getpid();
    pid_t pid = fork();
    int state = 0;

    if (pid == 0) {
        /*child*/
        execute(command, options);
        return;
    } else if (pid > 0) {
        /*parent*/
        waitpid(pid, &state, 0);
    } else {
        /*error*/
        merrno = 3;
    }

}

void execute(const string &command, char *const *options) {
    int e = execve((command).c_str(), options, environ);
    if (e){
        merrno = 2;
    }
}

void execute_my_command(string command, char *const *options) {

    pid_t parent = getpid();
    pid_t pid = fork();
    int state = 0;

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

void execute_default_command(string command, vector<string> options) {
    // {"myhello", "merrno", "mpwd", "mcd", "mexit"}

    if (command == "myhello") {
        merrno = myhello(options);
        return;
    } else if (command == "merrno") {
        merrno_(options);
        return;
    } else if (command == "mpwd") {
        merrno = mpwd(options);
        return;
    } else if (command == "mcd") {
        merrno = mcd(options);
        return;
    } else if (command == "mexit") {
        int k = mexit(options);

        if (k != -1024) {
            merrno = abs(k);
        } else
            merrno = 0;
        merrno = min(merrno, 8);
        if (k > -1) {
            if (merrno != 0)
                print_error(merrno);
            exit(merrno);
        }
        return;
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
    cout << "\tError: " << get_error_string(error_code);
}

void merrno_(vector<string> argv) {
    merrno = merrno_f(argv);
    cout << merrno << ": ";
    //print_error(merrno);
}

int myhello(vector<string> argv) {
    long n = argv.size();
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n my_hello [-h|--help] \n Print \"Hello World \"";
            return 0;
        } else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;
    }
    cout << "Hello, World!";
    return 0;
//
//    Hello, World!
//
//                /home/iryna/CLionProjects/myshell $ Hello, World!

}

int mpwd(vector<string> argv) {
    long n = argv.size();
    char dir[1024];
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n mpwd [-h|--help] \n Write current dir";
            return 0;

        } else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;

    }


    if (getcwd(dir, sizeof(dir)) == nullptr) {
        return 4;
    }

    cout << dir;

    return 0;
}

int mcd(vector<string> argv) {
    long n = argv.size();

    if (n == 0) {

        return 7;
    }
    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n mcd <path> [-h|--help] \n Change current dir.";
            return 0;
        }
    }
    int k = 0;
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if (!argv[i].empty() && !isspace(argv[i][0])) {

            if (vova) {
                if (argv[i] == ".") {
                    return 0;
                }

                k = chdir(argv[i].c_str());

                if (k != 0) {
                    return 6;
                }

                return k;
            } else
                vova++;


        }
    }


    return 6;
}

int mexit(vector<string> argv) {
    long n = argv.size();

    // arg code of error if need to exit positive else negative, if err code 0 and don't need to exit then -1024
    int result = -1024;
    int vova = 0;

    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n mexit <code of end> [-h|--help] \n Exit from myshell.";
            result = -1024;
            return result;
        }
    }

    for (int i = 0; i < n; i++) {
        char *pEnd;
        if (!argv[i].empty() && !isspace(argv[i][0])) {
            if (vova) {
                stringstream ss;
                // string stream
                ss << argv[i];
                ss >> result;
                if (!ss.fail())
                    return result;
                else {

                    ss.clear();
                    return -6;

                }
            } else
                vova++;

        }
    }


    result = 0;
    return result;

}


int merrno_f(vector<string> argv) {
    long n = argv.size();
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n merrno [-h|--help] \n Code of last error.";
            return 0;
        } else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;
    }

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