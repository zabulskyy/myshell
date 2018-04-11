#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <errno.h>

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

bool equal_words(string first, int i, string second, int j);

string vector_str_str(vector<string> vec);

char prj_dir[1024];;  // myshell directory
const char *mod_dir;  // modules directory
char cur_dir[1024];   // current directory
vector<string> defauld_modules = {"merrno", "mpwd", "mcd", "mexit"}; //TODO make local for main()
vector<string> my_modules = {"myhello", "mycat"}; //TODO make local for main()
int merrno = 0;

int main() {
    string cmd;  // command
    int parse_result = 0;  // just in case
    // get current directory
    if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
        cerr << "getcwd() error";
        merrno = 4;
    }
    if (getcwd(prj_dir, sizeof(prj_dir)) == nullptr) {
        cerr << "getcwd() error";
        merrno = 4;
    }
    if (merrno)
        print_error(merrno);

    char *prj_dir = cur_dir;
//    wildcards("bin/*[jhgy]??[hjt]");
    while (true) {

        if (getcwd(cur_dir, sizeof(cur_dir)) == nullptr) {
            merrno = 4;
        }
        if (merrno) {
            print_error(merrno);
        }

        // merrno = 0;
        printf("\n%s $ ", cur_dir);
        if (getline(cin, cmd)) {
            parse_command(cmd);
        }
    }
    return 0;
}

void parse_command(const string &cmd) {

    if (cmd.empty() ||
        cmd.find_first_not_of(' ') == string::npos ||
        cmd.find_first_not_of('\t') == string::npos)
        return;


    vector<string> commands;
    split_str(cmd, commands, ' ');


    string command = commands[0];
    char *t_options[commands.size() + 1];

    for (int i = 0; i < commands.size(); ++i) {
//        cout<<vector_str_str(wildcards(commands[i]))<<endl;
        vector<string> wild_res = wildcards(commands[i]);
        cout << vector_str_str(wild_res) << endl;
        t_options[i] = const_cast<char *>(vector_str_str(wild_res).c_str());
        //const_cast<char *>(commands[i].c_str()); // func vector<string> char*
    }

    t_options[commands.size()] = {nullptr};

    char *const *options = t_options;


    if (find(defauld_modules.begin(), defauld_modules.end(), command) != defauld_modules.end()) {
        execute_default_command(command, commands);
        return;
    }


    if (find(my_modules.begin(), my_modules.end(), command) != my_modules.end()) {
        command = ((string) prj_dir + "/bin/") + command;
        execute_my_command(command, options);
        return;
    }

    vector<string> wild_commands = wildcards(command);

    if (wild_commands.size() == 0) {
        merrno = 2;
    }

    for (auto elem : wild_commands) {
        execute(elem, options);
    }
}


string vector_str_str(vector<string> vec) {
    string res;
    for (const string &elem: vec) {
        res += elem + ' ';
    }
    res.pop_back();
    return res;

}

void execute(const string &command, char *const *options) {
    pid_t parent = getpid();
    pid_t pid = fork();
    int state = 0;

    if (pid == 0) {
        /*child*/
        int e = execve((command).c_str(), options, environ);
        if (e == -1) {
            cerr << "exit with error ";
            print_error(e);
            merrno = 2;
            exit(2);
        }
        return;
    } else if (pid > 0) {
        /*parent*/
        waitpid(pid, &state, 0);
    } else {
        /*error*/
        merrno = 3;
    }


//    cout<<e<<endl;

}

void execute_my_command(const string &command, char *const *options) {

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

void execute_default_command(const string &command, const vector<string> &options) {
    // {"myhello", "merrno", "mpwd", "mcd", "mexit"}

    if (command == "myhello") {
        merrno = myhello(options);
        return;
    } else if (command == "merrno") {
//        cout << merrno<<endl;
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
            cout << endl;
            exit(merrno);
        }
        return;
    }
}


void split_str(const string &txt, vector<string> &strs, char ch) {
    long spacepos = -1;
    bool quote = false;
    string ss;

    for (unsigned long i = 0; i < txt.size(); ++i) {
        if (txt[i] == '\"') {
            if (i == 0 || txt[i - 1] != '\\') {
                quote = !quote;
            } else {

            }
        }
        if (quote)
            continue;
        if (txt[i] == ' ') {
            if (i - spacepos - 1) {
                ss = txt.substr((unsigned long) spacepos + 1, i - spacepos - 1);
                if (ss[0] == '\"') {
                    ss.erase(0, 1);
                    ss.erase(ss.size() - 1, 1);
                } else if (ss[0] == '\'') {
                    ss.erase(0, 1);
                    ss.erase(ss.size() - 1, 1);
                    for (int j = 0; j < ss.length(); ++j) {
                        if (ss[j] == '\\') {
                            ss.replace((unsigned long) j, 1, "\\\\");
                        }
                    }
                }
                strs.push_back(ss);
            }
            spacepos = i;
        }
    }
    ss = txt.substr((unsigned long) spacepos + 1, txt.size() - spacepos - 1);
    if (ss[0] == '\"') {
        ss.erase(0, 1);
        ss.erase(ss.size() - 1, 1);
    } else if (ss[0] == '\'') {
        ss.erase(0, 1);
        ss.erase(ss.size() - 1, 1);
        int j = 0;
        while (j++ < ss.length()) {
            if (ss[j] == '\\') {
                ss.replace((unsigned long) j, 1, "\\\\");
                ++j;
            }
        }
    }
    strs.push_back(ss);
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
              "unknown error",
              "scandir error"};
    return errors[error_code];

}

void print_error(int error_code) {
    cout << "\tError " << merrno << ": " << get_error_string(error_code);
}

void merrno_(vector<string> argv) {
    //cout << argv[0]<<endl;
    if (argv.size() > 1)
        merrno = merrno_f(argv);
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
                    return 2;
                }

                return k;
            } else
                vova++;


        }
    }


    return 2;
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


    return 0;

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

vector<string> wildcards(string str) {
    // *.txt, ab??.dat, xy[klm].sh
//    cout<<str<<endl;
    vector<string> res;
    struct dirent **namelist;
    size_t found = str.find_last_of("/\\");
    vector<int> n = {-1, -1};

    vector<string> mask = {str.substr(found + 1), ""};
    string bla;
    if (str.size() > 0 && str[0] != '/')
        bla = '/' + str.substr(0, found + 1);
    else
        bla = str.substr(0, found + 1);
    vector<string> dir_open = {cur_dir + bla, ""};

    n[0] = scandir((dir_open[0]).c_str(), &namelist, nullptr, alphasort);
    if (found != string::npos) {


        dir_open[1] = str.substr(0, found + 1);
        mask[1] = str.substr(found + 1);

        n[1] = scandir((dir_open[1]).c_str(), &namelist, nullptr, alphasort);


    }
    //DIR *dirp = opendir(dir_open);

    char *word_check;
    string y;
//    cout<<y<<endl;
    if (n[0] == -1 && n[1] == -1) {
        merrno = 9;
        return res;
    }
    for (int i = 0; i < n.size(); ++i) {
        while (--n[i] > 1) {
            word_check = namelist[n[i]]->d_name;

            cout << word_check << endl;
            if (equal_words(mask[i], 0, word_check, 0)) {
                y = dir_open[i] + word_check;
                //            y = word_check;
                res.emplace_back(y);

            }
            cout << (int) n[i] << endl;
            free(namelist[n[i]]);
            cout << n[i] << endl;


        }
        free(namelist);

    }

    //if(res.size()>0 res[res.size() - 1] == ".")

    return res;
}

bool equal_words(string first, int i, string second, int j) {
    bool t = false;
    if (first.size() == i && second.size() == j)
        return true;
    if (first[i] == '*' && first.size() != i + 1 && second.size() == j)
        return false;
    if (first[i] == '[') {
        i++;
        while (first.size() != i && first[i] != ']') {
            t = t || (first[i] == second[j]);
            i++;
        }
        if (first.size() == i)
            return t && equal_words(first, i, second, j + 1);
        else
            return t && equal_words(first, i + 1, second, j + 1);

    }

    if (first[i] == '?' || first[i] == second[j])
        return equal_words(first, i + 1, second, j + 1);
    if (first[i] == '*')
        return equal_words(first, i + 1, second, j) || equal_words(first, i, second, j + 1);
    return false;
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