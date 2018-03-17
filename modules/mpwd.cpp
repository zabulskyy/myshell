#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>


#include <string.h>
using namespace std;
void print_help();


int main(int argc, char *argv[]){

    if(argc > 1){
        if(string(argv[1]) == "-h" || string(argv[1]) == "--help"){
            print_help();
            return 0;
        }

        cerr << "Wrong arguments" << endl;
        exit(1);

    }
    char dir[1024];

    if (getcwd(dir, sizeof(dir)) == nullptr) {
        cerr << "getcwd() error" << endl;
        exit(1);
    }

    cout << dir << endl;

    return 1;
}

void print_help(){
    std::cout << "help: \n mpwd [-h|--help] \n Write current dir." << std::endl;
}

void err_exit(std::string error)
{
    cerr << error  << endl;
    exit(1);
}
