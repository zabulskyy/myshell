#include <sstream>
#include "my_modules.h"

using namespace std;
int myhello(vector<string> argv){
    long n = argv.size();
    int vova = 0;
    for(int i = 0; i<n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n my_hello [-h|--help] \n Print \"Hello World \"" << endl;
            return 0;
        } else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;
    }
    cout << "Hello, World! \n";
    return 0;
//
//    Hello, World!
//
//                /home/iryna/CLionProjects/myshell $ Hello, World!

}

int mpwd(vector<string> argv){
    long n = argv.size();
    char dir[1024];
    int vova =0 ;
    for(int i = 0; i<n; i++) {
        if (argv[i] == "-h" || argv[i] == "--help") {
            cout << "help: \n mpwd [-h|--help] \n Write current dir." << endl;
            return 0;

        }else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;

    }


    if (getcwd(dir, sizeof(dir)) == nullptr) {
        return 4;
    }

    cout << dir << endl;

    return 0;
//    /home/iryna/CLionProjects/myshell/cmake-build-debug
//
//                                                  /home/iryna/CLionProjects/myshell/cmake-build-debug $ /home/iryna/CLionProjects/myshell/cmake-build-debug

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
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if(!argv[i].empty() && !isspace(argv[i][0])){

            if (vova){
                //cout << argv[i] << endl;
                if (argv[i] == "."){
                    return 0;
                }

                k = chdir( argv[i].c_str());

                if (k != 0) {
                    return 6;
                }

                return k;
            }

            else
                vova++;


        }
    }


    return 6;
}

int mexit(vector<string> argv){
    long n = argv.size();

    // arg code of error if need to exit positive else negative, if err code 0 and don't need to exit then -1024
    int result = -1024;
    int vova = 0;

    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n mexit <code of end> [-h|--help] \n Exit from myshell." << endl;
            result = -1024;
            return result;
        }
    }

    for (int i = 0; i < n; i++) {
        char * pEnd;
        if(!argv[i].empty() && !isspace(argv[i][0]) ){
            if (vova){
                stringstream ss;
                // string stream
                ss << argv[i];
                ss >> result;
                if (!ss.fail())
                    return result;
                else{

                    ss.clear();
                    return 6;

                }
            }
            else
                vova++;

        }
    }


    result = -6;
    return result;

}



int merrno_f(vector<string> argv) {
    long n = argv.size();
    int vova = 0;
    for (int i = 0; i < n; i++) {
        if ((argv[i] == "-h" || argv[i] == "--help")) {
            cout << "help: \n merrno [-h|--help] \n Code of last error." << endl;
            return 0;
        }
        else if (!argv[i].empty() && !isspace(argv[i][0]))
            if (vova)
                return 6;
            else
                vova++;
    }

}
