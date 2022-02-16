#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
#include <sstream>

using std::ifstream; using std::ostringstream;

std::string readFileIntoString(const std::string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

std::string get_exe_root_dir() {
    TCHAR buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string str = buffer;
    std::size_t pos = str.find("main.exe");
    std::string cwd = str.substr(0, pos);
    return cwd;
}
