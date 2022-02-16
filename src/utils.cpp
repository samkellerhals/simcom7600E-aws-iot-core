#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
#include <filesystem>

void read_txt_file(const std::string root_dir, const std::string path) {
    std::ifstream file;
    std::string line;
    std::string fpath = root_dir + path;

    file.open(fpath);

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }

    file.close();
}

std::string get_exe_root_dir() {
    TCHAR buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string str = buffer;
    std::size_t pos = str.find("main.exe");
    std::string cwd = str.substr(0, pos);
    return cwd;
}
