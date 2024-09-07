//
// Created by zomoroda on 9/8/2024.
//


#include <iostream>
#include <filesystem>
#include <map>
#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;
using namespace std;

void organize_files(const fs::path& dir_path) {
    map<string, string> categories = {
        {".jpg", "Imgs"}, {".jpeg", "Imgs"}, {".png", "Imgs"}, {".gif", "Imgs"},
        {".pdf", "Docs"}, {".docx", "Docs"}, {".pptx", "Docs"}, {".xlsx", "Docs"},
        {".md", "Ideas"}, {".txt", "Ideas"}, {".dat", "Data"}, {".json", "Data"}, {".csv", "Data"},
        {".mp3", "Multimedia"}, {".mp4", "Multimedia"}, {".avi", "Multimedia"}
    };

    for (const auto& entry : fs::directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();
            string folder = categories.count(ext) ? categories[ext] : "Others";
            fs::create_directory(dir_path / folder);
            try {
                fs::rename(entry.path(), dir_path / folder / entry.path().filename());
            } catch (...) {
                cerr << "Error moving file: " << entry.path() << endl;
            }
        }
    }

    cout << "Files organized successfully!" << endl;

#ifdef _WIN32
    ShellExecute(NULL, "open", dir_path.string().c_str(), NULL, NULL, SW_SHOWDEFAULT);
#elif __linux__
    system(("xdg-open " + dir_path.string()).c_str());
#else
    cout << "Opening folder is not supported on this operating system." << endl;
#endif
}

int main() {
    string directory;
    cout << "Enter directory path: ";
    cin >> directory;
    organize_files(directory);
    return 0;
}