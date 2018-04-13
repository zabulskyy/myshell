#include <iostream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <vector>
#include <sys/stat.h>
#include <algorithm>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/iterator_range.hpp>

using namespace std;


void parse(int argc, char *argv[], bool &h, bool &p, vector<string> &files, string &e) {
    e = "";
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg[0] == '-') {
            if (arg == "--help" || arg == "-h") {
                h = true;
            } else if (arg == "-p") {
                p = true;
            } else {
                e = "Error: unknown argument: ";
                e += arg;
                return;
            }
        } else {
            files.emplace_back(argv[i]);
        }
    }

}

void print_help() {
    cout << "mymkdir [-h|--help] [-p]  <dirname>" << endl;
    cout << "make a directory(ies)" << endl;
}


int main(int argc, char *argv[]) {


    if (argc < 2) {
        cerr << "No arguments were provided" << endl;
        exit(1);
    }

    char working_directory[1024];

    if (getcwd(working_directory, sizeof(working_directory)) == nullptr) {
        cerr << "getcwd() error";
        exit(1);
    }

    bool h = false, p = false;
    vector<string> expressions;
    string e;
    parse(argc, argv, h, p, expressions, e);

    if (!e.empty()) {
        cerr << e << endl;
        exit(1);
    }

    if (h) {
        print_help();
        return 0;
    }

    for (auto const &elem : expressions) {
        string abs_filename = working_directory;
        abs_filename += '/';
        abs_filename += elem;
        if (!p && boost::filesystem::is_directory(abs_filename.c_str()) && boost::filesystem::exists(abs_filename.c_str())) {
            cerr << "folder " << elem << " already exists, exit" << endl;
            exit(1);
        }
        boost::system::error_code ec;
        if (!boost::filesystem::create_directory(abs_filename, ec) && ec.message() != "Success"){
            cerr << "Error: " << ec.message() << endl;
        }
    }

    return 0;
}