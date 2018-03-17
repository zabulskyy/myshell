#include "my_modules.h"

using namespace std;
int my_hello(char *argv[]){
    int i = 0;
    while(argv[i][0] != '/0'){
        i++;
    }
    if(i > 1){
        return 6;
    }
    if (i == 1 && (argv[0] == "-h" || argv[0] == "--help")){
        cout << "help: \n my_hello [-h|--help] \n Print \"Hello World \""<< endl;
        return 0;
    }
    cout << "Hello, World!\n";
    return 0;
}

int mpwd(char *argv[]){
    int i = 0;
    while(argv[i][0] != '/0'){
        i++;
    }
    if(i > 1){
        return 6;
    }
    if (i == 1 && (argv[0] == "-h" || argv[0] == "--help")){
        cout << "help: \n mpwd [-h|--help] \n Write current dir." << endl;
        return 0;
    }
    char dir[1024];

    if (getcwd(dir, sizeof(dir)) == nullptr) {
        cerr << "getcwd() error" << endl;
        exit(1);
    }

    cout << dir << endl;

    return 1;
}