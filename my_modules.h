
#ifndef MYSHELL_MY_MODULES_H
#define MYSHELL_MY_MODULES_H

#endif //MYSHELL_MY_MODULES_H
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
using namespace std;
int my_hello(vector<string> argv);
int mpwd(char *argv[]);
int mcd(char *argv[]);
int mexit(char *argv[]);