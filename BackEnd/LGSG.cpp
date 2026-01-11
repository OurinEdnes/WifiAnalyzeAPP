#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "ERROR1";
        return 1;
    }

    string mode = argv[1];
    string username = argv[2];
    string password = argv[3];

    string databasePath = "C:/xampp/htdocs/WifiAnalyze/BackEnd/User-DataBase.txt";
    ifstream file(databasePath);
    if (!file.is_open()) {
        cerr << "KRITIS: Gagal membuka file database di -> " << databasePath << std::endl;
        cout << "FAIL" << username;
        return 1;
    }
    cout << "MODE=" << mode << endl << flush;
    cout << "USERNAME=" << username << endl << flush;
    cout << "PASSWORD=" << password << endl << flush;

    string line;

    if (mode == "login" || mode == "Login") {
        string currentUser = "", currentPass = "";

            cout << "MODE=" << mode << "\n";
            cout << "USERNAME=" << username << "\n";
            cout << "PASSWORD=" << password << "\n";
        while (getline(file, line)) {
            if (line.empty()) continue;  // Lewati baris kosong

            if (line.find("username ##") != string::npos) {
                currentUser = line.substr(line.find("##") + 3);
            }
            else if (line.find("password ##") != string::npos) {
                currentPass = line.substr(line.find("##") + 3);
            }
            else if (line.find("====") != string::npos) {
                if (currentUser == username && currentPass == password) {
                    cout << "SUCCESS";
                    return 0;
                }
                currentUser = currentPass = "";
            }
        }

        cout << "FAIL" << username;
        return 0;
    }

    else if (mode == "signup") {
        // Cek apakah username sudah ada
        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line.find("username ##") != string::npos &&
                line.substr(line.find("##") + 3) == username) {
                cout << "EXIST";
                return 0;
            }
        }

        file.close();  // Tutup sebelum mode tulis

        // Tambahkan user baru ke file
        ofstream out(databasePath, ios::app);
        out << "\n============================\n";
        out << "username ## " << username << "\n";
        out << "password ## " << password << "\n";
        out.close();

        // Buat folder dan file user baru
        string baseDir = "C:/xampp/htdocs/WifiAnalyze/BackEnd/UserData(" + username + ")";
        fs::create_directory(baseDir);

        ofstream wifi(baseDir + "/Wifi-Ap-Speed.txt");
        wifi << "Wifi milik " << username << endl;
        wifi.close();

        ofstream kategori(baseDir + "/WifiConfigure.txt");
        kategori << "Kategori Wifi user " << username << endl;
        kategori.close();

        ofstream kegiatan(baseDir + "/Wifi-User.txt");
        kegiatan << "Kegiatan user " << username << endl;
        kegiatan.close();

        cout << "CREATED";
        return 0;
    }

    cout << "INVALID_MODE";
    return 1;
}
