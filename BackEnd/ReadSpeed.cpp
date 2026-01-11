#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "ERROR: Username tidak diberikan";
        return 1;
    }

    string username = argv[1];
    string path = "C:/xampp/htdocs/WifiAnalyze/BackEnd/UserData(" + username + ")/Wifi-Ap-Speed.txt";

    ifstream file(path);
    if (!file.is_open()) {
        cout << "ERROR: Gagal membuka file";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    cout << "UserName Ditemukan!";
    return 0;
}
