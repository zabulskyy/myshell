#include <iostream>
#include <map>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <unistd.h>

#define print(x) std::cout<<(x)<<std::endl;
#define print_v(v) for (int i = 0; i < (v).size(); ++i) {print((v)[i])};

using std::string;
using std::map;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ostringstream;
using std::stringstream;


bool is_in(const string &str, vector<string> vec);

void split_str(const string &str, vector<string> &vec);

bool is_dir(const char *path);

bool is_spec(const char *path);

vector<string>
bubble_sort_vector(bool (*criteria)(string, vector<string>, string, vector<string>), map<string, vector<string>> params,
                   vector<string> args, bool r, bool D);


vector<string> single_folder_content(string dir_open);

void print_help();

void show_folder_content(string path, bool R, bool l, bool r, bool F, string sort_val);

void parse_options(const string &command, map<string, bool> &res, string &sort_value, vector<string> &folders,
                   vector<string> &files, string &path);

void get_ext_size_date(string name, map<string, vector<string>> &all_f, string path);

bool equal_words(string first, int i, string second, int j);

void apply_mask(string path, vector<string> &files, vector<string> &dirs, bool &err);

void print_separate_files(vector<string> vec, bool l, bool r, bool F, string sort_val, string path);

bool S_crit(string name1, vector<string> params1, string name2, vector<string> params2) {
    return atoi(params1[1].c_str()) > atoi(params2[1].c_str());
}

bool U_crit(string name1, vector<string> params1, string name2, vector<string> params2) {
    return 0;
}

bool cmp(string t_1, string t_2) {

    time_t t1, t2;
    struct tm tm1, tm2;
    const char *time1 = t_1.c_str();
    const char *time2 = t_2.c_str();

    strptime(time1, "%Y-%m-%d %H:%M", &tm1);
    strptime(time2, "%Y-%m-%d %H:%M", &tm2);

    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    return difftime(t1, t2) > 0.0;
}

bool t_crit(string name1, vector<string> params1, string name2, vector<string> params2) {


    return cmp(params1[2], params2[2]);

}

bool X_crit(string name1, vector<string> params1, string name2, vector<string> params2) {
    return params1[0] > params2[0];
}

bool N_crit(string name1, vector<string> params1, string name2, vector<string> params2) {
    return name1.compare(name2) > 0;
}

char compile_dir[1024];

int main(int argc, char *argv[]) {
    if (getcwd(compile_dir, sizeof(compile_dir)) == nullptr) {
        cerr << "getcwd() error";
        exit(1);

    }
    map<string, bool> res;
    string sort_val;

    ostringstream oss;
    for (int i = 1; i < argc; ++i) {
        oss << argv[i] << " ";
    }
    string arguments = oss.str(), command_path = ".";
    vector<string> folders, files;

    parse_options(arguments, res, sort_val, folders, files, command_path);

    bool l = false, h = false, help = false, r = false, R = false, F = false;
    l = res["-l"];
    h = res["-h"];
    help = res["--help"];
    r = res["-r"];
    R = res["-R"];
    F = res["-F"];

    if (h || help) {
        print_help();
        return 0;
    }
     print_separate_files(files, l, r, F, sort_val, command_path);

    for (const auto &folder: folders)
        show_folder_content(folder, R, l, r, F, sort_val);


}

void print_separate_files(vector<string> vec, bool l, bool r, bool F, string sort_val, string path) {
    bool D = false, s = false;
    string sort_crit = "";
    const string possible_sort_crit = {'D', 's', 'N', 'U', 'X', 't', 'S'};
    for (int i = 0; i < sort_val.size(); ++i) {
        if (sort_val[i] != 'D' && sort_val[i] != 's') {
            if (possible_sort_crit.find(sort_val[i]) > possible_sort_crit.length()) {
                cerr << "\tError: invalid --sort argument: " << sort_val[i] << endl;
                exit(1);
            }
            sort_crit = sort_val[i];
        }
    }


    for (int i = 0; i < sort_val.size(); ++i) {

        if (sort_val[i] == 'D') {
            D = true;
        }
        if (sort_val[i] == 's') {
            s = true;
        }
    }


    ostringstream oss;
    oss << compile_dir << "/" << path;
    string cur_dir = oss.str();
    map<string, vector<string>> ll;

    for (string el: vec) {
        get_ext_size_date(el, ll, cur_dir);
    }


    if (sort_crit == "N") {
        vec = bubble_sort_vector(N_crit, ll, vec, r, D);
    } else if (sort_crit == "S") {
        vec = bubble_sort_vector(S_crit, ll, vec, r, D);
    } else if (sort_crit == "t") {
        vec = bubble_sort_vector(t_crit, ll, vec, r, D);
    } else if (sort_crit == "X") {
        vec = bubble_sort_vector(X_crit, ll, vec, r, D);
    } else { // U or nothing
        vec = bubble_sort_vector(U_crit, ll, vec, r, D);
    }
    string glob_dir = path + '/';
    vector<string> spec_files;

    for (const auto &elem : vec) {
        if (elem[0] == '.') continue;
        if (s) {
            if (is_spec((glob_dir + elem).c_str())) {
                spec_files.emplace_back(elem);
                continue;
            }
        }
        if (F) {
            struct stat buf;
            stat((glob_dir + elem).c_str(), &buf);
            if (S_ISSOCK(buf.st_mode))
                cout << '=';
            else if (S_ISLNK(buf.st_mode))
                cout << '@';
            else if (S_ISFIFO(buf.st_mode))
                cout << '|';
            else if (buf.st_mode & S_IEXEC != 0)
                cout << '*';
            else if (!S_ISDIR(buf.st_mode) && !S_ISREG(buf.st_mode))
                cout << '?';

        }


        if (l) {
            auto info = ll[elem];
            string elem_ext = info[0];
            string elem_size = info[1];
            string elem_date = info[2];
            cout << elem << "\t\t" << elem_size << "\t\t" << elem_date << endl;
        } else
            cout << elem << "\t";
    }
    if (s) {
        cout << endl;
        for (const auto &elem : spec_files) {
            struct stat buf;
            stat((glob_dir + elem).c_str(), &buf);
            if (S_ISSOCK(buf.st_mode))
                cout << '=';
            else if (S_ISLNK(buf.st_mode))
                cout << '@';
            else if (S_ISFIFO(buf.st_mode))
                cout << '|';
            else if (buf.st_mode & S_IEXEC != 0)
                cout << '*';
            else if (!S_ISDIR(buf.st_mode) && !S_ISREG(buf.st_mode))
                cout << '?';

            if (l) {
                auto info = ll[elem];
                string elem_ext = info[0];
                string elem_size = info[1];
                string elem_date = info[2];
                cout << elem << "\t\t" << elem_size << "\t\t" << elem_date << endl;
            } else
                cout << elem << "\t";
        }

    }

    cout << endl;


}

void apply_mask(string str, vector<string> &files, vector<string> &dirs,  bool &err) {
    struct dirent **namelist;
    size_t found = str.find_last_of("/\\");
    string dir_open, mask;
    int len_files = (int)files.size(), len_dirs = (int)dirs.size();
    if (found != string::npos) {
        dir_open = str.substr(0, found + 1);
        mask = str.substr(found + 1);
    } else {
        dir_open = ".";
        if (str != ".")
            mask = str;
        else
            mask = "*";
    }
    int n;
    char *word_check;


    n = scandir((dir_open).c_str(), &namelist, nullptr, alphasort);
    if (n == -1) {

        return;
    }




    while (--n > 1) {
        word_check = namelist[n]->d_name;
        if (equal_words(mask, 0, word_check, 0)) {

            if (is_dir((dir_open + word_check).c_str())) {
                if(word_check[0] != '.')
                    dirs.emplace_back(dir_open + word_check);
            } else
                files.emplace_back(word_check);


        }
        free(namelist[n]);
    }
    free(namelist);

    if(!((int)dirs.size() - len_dirs) && !((int)files.size() - len_files)){
        err = !err;
        cerr << "\tno such folder: " << str << endl;

    }
}


void show_folder_content(string path, bool R, bool l, bool r, bool F, string sort_val) {
    vector<string> vec = single_folder_content(path);

    bool D = false, s = false;

    string sort_crit = "";
    const string possible_sort_crit = {'D', 's', 'N', 'U', 'X', 't', 'S'};
    for (int i = 0; i < sort_val.size(); ++i) {
        if (sort_val[i] != 'D' && sort_val[i] != 's') {
            if (possible_sort_crit.find(sort_val[i]) > possible_sort_crit.length()) {
                cerr << "\tError: invalid --sort argument: " << sort_val[i] << endl;
                exit(1);
            }
            sort_crit = sort_val[i];
        }
    }


    for (int i = 0; i < sort_val.size(); ++i) {

        if (sort_val[i] == 'D') {
            D = true;
        }
        if (sort_val[i] == 's') {
            s = true;
        }
    }

    ostringstream oss;
    //oss << compile_dir << "/" << path;
    //string cur_dir = oss.str();
    string cur_dir = path;
    string glob_dir = path + '/';
    map<string, vector<string>> ll;

    for (string el: vec) {
        get_ext_size_date(el, ll, cur_dir);
    }

    // U|S|t|X
    if (sort_crit == "N") {
        vec = bubble_sort_vector(N_crit, ll, vec, r, D);
    } else if (sort_crit == "S") {
        vec = bubble_sort_vector(S_crit, ll, vec, r, D);
    } else if (sort_crit == "t") {
        vec = bubble_sort_vector(t_crit, ll, vec, r, D);
    } else if (sort_crit == "X") {
        vec = bubble_sort_vector(X_crit, ll, vec, r, D);
    } else { // U or nothing
        vec = bubble_sort_vector(U_crit, ll, vec, r, D);
    }

    if (R)
        cout << path << ":" << endl;

    vector<string> spec_files;


    bool isdir;
    for (const auto &elem : vec) {
        if (elem[0] == '.') continue;
        if (s) {
            if (is_spec((glob_dir + elem).c_str())) {
                spec_files.emplace_back(elem);
                continue;
            }
        }
        isdir = is_dir((glob_dir + elem).c_str());
        cout << (isdir ? "/" : "");

        if (F) {
            struct stat buf;
            stat((glob_dir + elem).c_str(), &buf);
            if (S_ISSOCK(buf.st_mode))
                cout << '=';
            else if (S_ISLNK(buf.st_mode))
                cout << '@';
            else if (S_ISFIFO(buf.st_mode))
                cout << '|';
            else if (buf.st_mode & S_IEXEC != 0)
                cout << '*';
            else if (!S_ISDIR(buf.st_mode) && !S_ISREG(buf.st_mode))
                cout << '?';

        }


        if (l) {
            auto info = ll[elem];
            string elem_ext = info[0];
            string elem_size = info[1];
            string elem_date = info[2];
            cout << elem << "\t\t" << elem_size << "\t\t" << elem_date << endl;
        } else
            cout << elem << "\t";
    }
    if (s) {
        cout << endl;
        for (const auto &elem : spec_files) {
            struct stat buf;
            stat((glob_dir + elem).c_str(), &buf);
            if (S_ISSOCK(buf.st_mode))
                cout << '=';
            else if (S_ISLNK(buf.st_mode))
                cout << '@';
            else if (S_ISFIFO(buf.st_mode))
                cout << '|';
            else if (buf.st_mode & S_IEXEC != 0)
                cout << '*';
            else if (!S_ISDIR(buf.st_mode) && !S_ISREG(buf.st_mode))
                cout << '?';

            if (l) {
                auto info = ll[elem];
                string elem_ext = info[0];
                string elem_size = info[1];
                string elem_date = info[2];
                cout << elem << "\t\t" << elem_size << "\t\t" << elem_date << endl;
            } else
                cout << elem << "\t";
        }

    }

    cout << endl;

    if (R) {
        for (const auto &elem : vec) {
            if (elem[0] == '.') continue;
            ostringstream oss;
            oss << cur_dir << "/" << elem;
            string dir = oss.str();

            if (is_dir(dir.c_str())) {
                show_folder_content(glob_dir + elem, R, l, r, F, sort_val);
            }
        }
    }
}


vector<string>
bubble_sort_vector(bool (*criteria)(string, vector<string>, string, vector<string>), map<string, vector<string>> params,
                   vector<string> args, bool r, bool D) {
    auto n = (int) (args.size());
    string reserve;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            string first = args[j];
            string second = args[j + 1];
            bool swap = criteria(first, params[first], second, params[second]);
            if (D) {
                ostringstream foss;
                foss << compile_dir << "/" << first;
                string fdir = foss.str();
                ostringstream soss;
                soss << compile_dir << "/" << second;
                string sdir = soss.str();
                bool fd = is_dir(fdir.c_str()), sd = is_dir(sdir.c_str());

                if (fd && !sd) {
                    swap = false;
                } else if (!fd && sd) {
                    swap = true;
                }
            }
            if (r) swap = !swap;

            if (swap) {
                reserve = first;
                args[j] = second;
                args[j + 1] = reserve;
            }

        }
    }
    return args;

}

void parse_options(const string &command, map<string, bool> &res, string &sort_value, vector<string> &folders,
                   vector<string> &files, string &com_path) {
    vector<string> possible_opt = {"-h", "--help", "-r", "-l", "-R", "-F", "--"};
    vector<string> options;
    split_str(command, options);
    sort_value = "";

    bool mm_found = false, error_no_dir = false;

    if (options[0][0] != '-') {
        apply_mask(options[0], files, folders, error_no_dir);
        size_t found = options[0].find_last_of("/\\");
        if (found != string::npos) {
            com_path = options[0].substr(0, found + 1);

        } else {
            com_path = ".";
        }
    }
    //folders.emplace_back(options[0]);

    for (const auto &option: options) {
        if (option == "")
            continue;
        if (option == "--") {
            mm_found = true;
            continue;
        }

        if (mm_found) {
            apply_mask(option, files, folders, error_no_dir);
            size_t found = option.find_last_of("/\\");
            if (found != string::npos) {
                com_path = option.substr(0, found + 1);

            } else {
                com_path = ".";
            }
        }
//        folders.emplace_back(option);
    }

    if (folders.empty() && files.empty() && !error_no_dir)
        folders.emplace_back(".");


    for (int i = 0; i < folders.size(); ++i) {
        ostringstream oss;
        oss << compile_dir << "/" << folders[i];

        folders[i] = oss.str();
    }


    for (const auto &opt : possible_opt) {
        res[opt] = false;
    }

    for (const auto &opt : options) {
        if (opt.find('-') == 0 && opt.find("--sort") != 0) {
            if (!is_in(opt, possible_opt)) {
                cerr << "Error: no such option: " << opt << endl;
                exit(1);

            }
            res[opt] = true;
        }
        if (opt == "--sort") {
            sort_value = "";
        } else if (opt.find("--sort") == 0) {
            sort_value = opt.substr(7, opt.size() - 6);
        }
    }
}


void split_str(const string &str, vector<string> &vec) {
    auto start = 0;
    char sep = ' ';
    auto end = str.find(sep);
    while (end != std
    ::string::npos) {
        vec.emplace_back(str.substr((unsigned long) (start), end - start));
        start = (int) end + 1;
        end = str.find(sep, (unsigned long) start);
    }
    vec.emplace_back(str.substr((unsigned long) (start), end - start));

}

bool is_in(const string &str, vector<string> vec) {
    for (const auto &i : vec)
        if (str == i)
            return true;
    return false;
}


void print_help() {
    cout << "Usage: myls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X|D|s] [-r]\n"
            "List information about the FILEs (the current directory by default).\n"
            "Sort entries alphabetically if none of -cftuvSUX nor --sort is specified." << endl;
}

bool is_dir(const char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

bool is_spec(const char *path) {
    struct stat buf;
    stat(path, &buf);
    if (S_ISSOCK(buf.st_mode))
        return true;
    else if (S_ISLNK(buf.st_mode))
        return true;
    else if (S_ISFIFO(buf.st_mode))
        return true;
    else if (buf.st_mode & S_IEXEC != 0)
        return true;
    return false;
}

vector<string> single_folder_content(string dir_open) {
    vector<string> res;
    struct dirent **namelist;
    int n;
    char *file;
    string path_with_file;
    size_t pos = dir_open.find("..");
//    if(pos == 0)
//        dir_open = compile_dir +(string)"/"+dir_open+(string)"/";
    n = scandir((dir_open).c_str(), &namelist, nullptr, alphasort);
    if (n == -1) {
        return res;
    }
    while (--n > 1) {
        file = namelist[n]->d_name;
        path_with_file = dir_open + (string) "/" + file;
        res.emplace_back(file);
        free(namelist[n]);
    }
    free(namelist);
    return res;
}

void get_ext_size_date(string name, map<string, vector<string>> &all_f, string path) {
    struct stat fileInfo{};
    vector<string> dat;
    if(path[path.size()-1] == '.'){
        path.pop_back();
    }
    if (stat((path + (string) "/" + name).c_str(), &fileInfo) != 0) {  // Use stat( ) to get the info
//        cerr << name << ": " << "Error: " << strerror(errno) << '\n';
    }

    // ext
    size_t found = name.find_last_of(".");
    if (found != std::string::npos)
        dat.emplace_back(name.substr(found + 1));
    else
        dat.emplace_back("'folder'");

    // size
    string size;
    std::stringstream strstream;
    strstream << (unsigned long long) fileInfo.st_size; //<<" "<< &fileInfo.st_mtime;;
    strstream >> size;
    dat.emplace_back(size);

    // time last modified
    struct tm tm;
    char buf[200];
    localtime_r(&fileInfo.st_mtime, &tm);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);

    //printf("%s\n", buf);
    dat.emplace_back(buf);
    all_f[name] = dat;

}

bool equal_words(string first, int i, string second, int j) {
    bool t = false;
    if (first.size() == i && second.size() == j)
        return true;
    if (first[i] == '*' && first.size() != i + 1 && second.size() == j)
        return false;
    if (first[i] == '[') {
        i++;
        while (first.size() != i && first[i] != ']') {
            t = t || (first[i] == second[j]);
            i++;
        }
        if (first.size() == i)
            return t && equal_words(first, i, second, j + 1);
        else
            return t && equal_words(first, i + 1, second, j + 1);

    }

    if (first[i] == '?' || first[i] == second[j])
        return equal_words(first, i + 1, second, j + 1);
    if (first[i] == '*')
        return equal_words(first, i + 1, second, j) || equal_words(first, i, second, j + 1);
    return false;
}

