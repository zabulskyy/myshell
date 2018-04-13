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
using boost::system::error_code;
using boost::system::errc::success;
using boost::system::errc::no_such_file_or_directory;
using boost::system::errc::permission_denied;
using boost::system::errc::read_only_file_system;
using namespace boost::filesystem;

void print_help() {
    cout << "myrm [-h|--help] [-f] [-R] <file1> <file2> <file3>" << endl;
    cout << "removes file(s) and directory(ies)" << endl;
}

void parse(int argc, char *argv[], bool &h, bool &f, bool &R, vector<string> &files, string &e) {
    e = "";
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg[0] == '-') {
            if (arg == "--help" || arg == "-h") {
                h = true;
            } else if (arg == "-f") {
                f = true;
            } else if (arg == "-R") {
                R = true;
            } else {
                e = "\t Error: unknown argument: ";
                e += arg;
                return;
            }
        } else {
            files.emplace_back(argv[i]);
        }
    }

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

    bool h = false, f = false, R = false;
    vector<string> expressions;
    string e;
    parse(argc, argv, h, f, R, expressions, e);

    if (!e.empty()) {
        cerr << e << endl;
        exit(1);
    }

    if (h) {
        print_help();
        return 0;
    }

    vector<string> vs;
    vector<string> parsed_expressions;
    for (const auto &elem : expressions) {
        parsed_expressions.emplace_back(elem);
    }

    if (parsed_expressions.empty()) {
        cerr << "No files or directories match with provided arguments" << endl;
        exit(1);
    }

    string if_remove;
    boost::system::error_code ec;

    for (auto &filename: parsed_expressions) {
        string abs_filename = working_directory;
        abs_filename += '/';
        abs_filename += filename;

        if (!boost::filesystem::exists(abs_filename.c_str())) {
            cerr << "No such file or directory: " << filename << endl;
            continue;
        }

        if (boost::filesystem::is_directory(abs_filename.c_str())) {
            if (!R) {
                cout << "Trying to delete directory: " << filename << " skipping." << endl;
                continue;
            }
            filename = '/' + filename;
        }
        if (!f) {
            cout << "remove " << filename << "? Y/N/A/C: ";
            cin >> if_remove;
            transform(if_remove.begin(), if_remove.end(), if_remove.begin(), ::tolower);
            if (if_remove == "y" || if_remove == "yes") {
                boost::filesystem::remove_all(abs_filename.c_str(), ec);
//                if (remove(abs_filename.c_str()) != 0) { cerr << "Error deleting file: " << filename << endl; }
            } else if (if_remove == "n" || if_remove == "no") {
                cout << "Skipping deleting file: " << filename << endl;
            } else if (if_remove == "a" || if_remove == "all") {
                f = true;
                boost::filesystem::remove_all(abs_filename.c_str(), ec);
//                if (remove(abs_filename.c_str()) != 0) { cerr << "Error deleting file: " << filename << endl; }
            } else if (if_remove == "c" || if_remove == "cancel") {
                cout << "Aborting" << endl;
                return 0;
            } else {
                cout << "Unknown answer " << if_remove << ", abort" << endl;
                exit(1);
            }

        } else {
            boost::filesystem::remove_all(abs_filename.c_str(), ec);
//            if (remove(abs_filename.c_str()) != 0) {cerr << "Error deleting file: " + filename;}
        }
        if (ec.value() != 0) {
            cerr << ec.message() << endl;
            exit(ec.value());
        }


    }

    return 0;
}
