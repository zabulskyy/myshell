
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <wait.h>
#include <sstream>
#include <algorithm>
#include <dirent.h>


using namespace std;
char cur_dir[1024] = "/home/iryna/CLionProjects/myshell/src";

int merrno = 0;
vector<string> wildcards(string str);
vector<string> wildcards(string str){
    // *.txt, ab??.dat, xy[klm].sh
    DIR *dir;
    vector<string> res;
    struct dirent *ent;
    size_t found = str.find_last_of("/\\");
    string dir_open ;
    if (found != string::npos){
        dir_open = str.substr(found+1);
    } else
        dir_open = cur_dir;
    if (   (dir = reinterpret_cast<DIR *>(opendir ((dir_open).c_str()) != NULL))) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        merrno = 2;
    }
    res.emplace_back("hi");
    return res;
}

bool equal_words(char* first_let, char* second_let){
    bool t = false;
    if(*first_let == '/0' && *second_let == '/0')
        return true;
    if(*first_let == "*" && *first_let != '/0' && *second_let == '/0')
        return false;
    if(*first_let == "["){
        *first_let++;
        while(*first_let != "]" && *first_let != '/0') {
            t = equal_words(*first_let,  *second_let) || t;
            *first_let++;
        }
        if(*first_let == '/0')
            return t && equal_words(*first_let, *second_let+1);
        else
            return t && equal_words(*first_let+1, *second_let);
    }
    if(*first_let == "?" || *first_let == *second_let)
        return equal_words(first_let+1, second_let+1);
    if(*first_let == "*")
        return equal_words(*first_let + 1, *second_let) || equal_words(*first_let, *second_let + 1);
}


int main(){
    wildcards("jrjrjr");
    return 0;
}