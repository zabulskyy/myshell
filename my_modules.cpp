#include "my_modules.h"

using namespace std;
int my_hello(vector<string> argv){
    long n = argv.size();
    for(int i = 0; i<n; i++)
        if (argv[i] == "-h" || argv[i] == "--help"){
            cout << "help: \n my_hello [-h|--help] \n Print \"Hello World \""<< endl;
            return 0;
        }
    cout << "Hello, World!\n";
    return 0;
}

int mpwd(vector<string> argv){
    long n = argv.size();
    for(int i = 0; i<n; i++)
        if (argv[i] == "-h" || argv[i] == "--help"){
            cout << "help: \n mpwd [-h|--help] \n Write current dir." << endl;
            return 0;
        }
    char dir[1024];

    if (getcwd(dir, sizeof(dir)) == nullptr) {
        return 4;
    }

    cout << dir << endl;

    return 0;
}

int mcd(vector<string> argv){
    long i = argv.size();

    if (i == 0){

        return 7;
    }

    if ((argv[0] == "-h" || argv[0] == "--help")||(i >1 &&( argv[1] == "-h" || argv[1] == "--help"))) {
        cout << "help: \n mcd <path> [-h|--help] \n Change current dir." << endl;
        //return 0;
    }
    int k = 0;
    if (!(argv[0] == "-h" || argv[0] == "--help")){
        //k = abs(chdir(argv[0]));
        //res.emplace_back(k);
        if (k != 0) {

            return 6;
        }

        return k;
        }
    //k = i>1 && !abs(chdir(argv[1]));
    if (k){

        return 0;
    }

    return 6;
}

int mexit(vector<string> argv){
    long i = argv.size();

    // arg code of error if need to exit positive else negative, if err code 0 and don't need to exit then -1024
    int result = -1024;


    if (i == 0){

        result=0;
        return result;
    }

    if ((argv[0] == "-h" || argv[0] == "--help")||(i >1 &&( argv[1] == "-h" || argv[1] == "--help"))) {
        cout << "help: \n mexit <code of end> [-h|--help] \n Exit from myshell." << endl;
        result = -1024;
        return result;
    }

//    if (atoi(argv[0]) > -1){
//        result = atoi(argv[0]);
//        return result;
//    }
    result = -6;
    return result;

}