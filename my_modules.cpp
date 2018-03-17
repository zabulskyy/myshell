#include "my_modules.h"

using namespace std;
int my_hello(char *argv[]){
    int i = 0;
    while(argv[i][0] != '/0'){
        i++;
    }
    if(i > 1){
        return 5;
    }
    if (i == 1 && (argv[0] == "-h" || argv[0] == "--help")){
        cout << "Print \"Hello World \"";
    }
    cout << "Hello, World!\n";
    return 0;
}