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
        return 4;
    }

    cout << dir << endl;

    return 0;
}

int mcd(char *argv[]) {
    int i = 0;

    while (argv[i][0] != '/0') {
        i++;
    }
    if (i == 0){

        return 7;
    }
    if (i > 2) {

        return 6;
    }
    if ((argv[0] == "-h" || argv[0] == "--help")||(i >1 &&( argv[1] == "-h" || argv[1] == "--help"))) {
        cout << "help: \n mcd <path> [-h|--help] \n Change current dir." << endl;
        //return 0;
    }
    int k;
    if (!(argv[0] == "-h" || argv[0] == "--help")){
        k = abs(chdir(argv[0]));
        //res.emplace_back(k);
        if (k != 0) {

            return 6;
        }

        return k;
        }
    k = i>1 && !abs(chdir(argv[1]));
    if (k){

        return 0;
    }

    return 6;
}