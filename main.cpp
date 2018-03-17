#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>

using namespace std;

int parse_command(string &cmd);

void split_str(const string &txt, vector<string> &strs, char ch);

char *prj_dir;
char mds_dir[1024];

int main() {
    string cmd;
    char dir[1024];
    int parse_result = 0;

    if (getcwd(dir, sizeof(dir)) == nullptr) {
        cerr << "getcwd() error" << endl;
        exit(1);
    }

    char *prj_dir = dir;
    char mds_dir[1024];
    strcpy(mds_dir, dir);
    strcat(mds_dir, "/modules");

    while (true) {
        if (errno) {
            perror("\tError: ");
            return 1;
        }
        if (getcwd(dir, sizeof(dir)) == nullptr) {
            cerr << "getcwd() error" << endl;
            return 1;
        }

        cout << dir << " $ ";

        if (getline(cin, cmd))
            parse_result = parse_command(cmd);

        if (parse_result != 0)
            return parse_result;


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
        /*TODO try to search in modules*/
        if (command[0] == 'm') {
            execve(("modules/" + command).c_str(), options, environ);
            exit(1);
        }
    }

        /*parent*/
    else {
        waitpid(pid, &state, 0);
    }

    return 0;
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
