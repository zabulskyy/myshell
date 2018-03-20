#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

#define BUFF_SIZE 16

void print_single_file(char *name, bool a);
void error_exit(string error, string inFile);
void print_help();
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cerr << "no arguments provided" << endl;
        exit(1);
    }

    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "-h" || string(argv[i]) == "--help")
        {
            print_help();
            return 0;
        }
    }

    bool a = false;
    for (int i = 1; i < argc; ++i)
    {
        if (!a && string(argv[i]) == "-A")
        {
            a = true;
            break;
        }
    }

    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) != "-A")
            print_single_file(argv[i], a);
    }

    return 0;
}

void print_single_file(char *name, bool a)
{
    int inputFD;
    inputFD = open(name, O_RDONLY);
    
    while (inputFD == -1 && errno == EINTR){
	inputFD = open(name, O_RDONLY);
    }
    if (inputFD == -1 && errno != EINTR)
    {
        error_exit("cannot open file", name);
    }
    char buf[BUFF_SIZE];
    int red;
    char hexed[2];
    char c;
    while ((red = read(inputFD, buf, BUFF_SIZE)) > 0)
    {
        if (!a)
            write(1, buf, red);
        else
        {
            for (int i = 0; i < red; ++i)
            {
                if (!isspace(buf[i]) && !isprint(buf[i]))
                {
                    c = buf[i];
                    sprintf(hexed,  "%02X", c & 0xFF);
                    write(1, "\\x", 2);
                    write(1, hexed, 2);
                }
                else
                {
		    
                    write(1, &buf[i], 1);
                }
            }
	    
        }
    }
}

void error_exit(string error, string inFile)
{
    cerr << error << " " << inFile << endl;
    exit(1);
}

void print_help()
{
    cerr << "help: \n mycat [-h|--help] [-A] <file1> <file2> ... <fileN>" << endl;
}
