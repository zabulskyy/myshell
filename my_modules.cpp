#include "my_modules.h"

using namespace std;
int myhello(vector<string> argv){
    long n = argv.size();
    for(int i = 0; i<n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n my_hello [-h|--help] \n Print \"Hello World \"" << endl;
            return 0;
        } else if (!argv[i].empty() && !isspace(argv[i][0]))
            return 6;
    }
    cout << "Hello, World!\n";
    return 0;
}

int mpwd(vector<string> argv){
    long n = argv.size();
    char dir[1024];
    for(int i = 0; i<n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n mpwd [-h|--help] \n Write current dir." << endl;
            return 0;

        }

    }


    if (getcwd(dir, sizeof(dir)) == nullptr) {
        return 4;
    }

    cout << dir << endl;

    return 0;
}

int mcd(vector<string> argv) {
    long n = argv.size();

    if (n == 0) {

        return 7;
    }
    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n mcd <path> [-h|--help] \n Change current dir." << endl;
            return 0;
        }
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if(!argv[i].empty() && !isspace(argv[i][0])){
            k = chdir( argv[i].c_str());

            if (k != 0) {
                return 6;
            }

            return k;
        }
    }


    return 6;
}

int mexit(vector<string> argv){
    long n = argv.size();

    // arg code of error if need to exit positive else negative, if err code 0 and don't need to exit then -1024
    int result = -1024;


    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n mexit <code of end> [-h|--help] \n Exit from myshell." << endl;
            result = -1024;
            return result;
        }
    }

    for (int i = 0; i < n; i++) {
        if(!argv[i].empty() && !isspace(argv[i][0]) && atoi(argv[i].c_str()) > -1){
            result = atoi(argv[i].c_str());
            return result;
        }
    }


    result = -6;
    return result;

}

int merrno_f(vector<string> argv) {
    long n = argv.size();

    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n merrno [-h|--help] \n Code of last error." << endl;
            return 0;
        }
        else if (!argv[i].empty() && !isspace(argv[i][0]))
            return 6;
    }

}
