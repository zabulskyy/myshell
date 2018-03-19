
#ifndef MYSHELL_MY_MODULES_H
#define MYSHELL_MY_MODULES_H

#endif //MYSHELL_MY_MODULES_H
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
using namespace std;
int myhello(vector<string> argv);
int mpwd(vector<string> argv);
int mcd(vector<string> argv);
int mexit(vector<string> argv);
int merrno_f(vector<string> argv) ;