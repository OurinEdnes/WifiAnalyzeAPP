#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "ERROR: Username tidak diberikan.\n";
        return 1;
    }

    string username = argv[1];
    string path = "C:/xampp/htdocs/WifiAnalyze/BackEnd/UserData(" + username + ")/WifiConfigure.txt";

    ifstream file(path);
    if (!file.is_open()) {
        cout << "ERROR: Gagal membuka file konfigurasi WiFi.\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n")); // trim leading
        if (line.empty() || line.find("====") != string::npos || line.find("####") != string::npos) continue;

        cout << line << endl;
    }

    file.close();
    return 0;
}
