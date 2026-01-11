#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

const int MaxLantai = 10;
const int MaxAP = 10;
const int MaxUser = 20;

string Pengguna[MaxLantai][MaxAP][MaxUser][2];
int Lantai = 0;

void PenggunaIN(const string& username) {
    //Gunakan path absolut
    string basePath = "C:/xampp/htdocs/WifiAnalyze/BackEnd/UserData(" + username + ")/Wifi-User.txt";
    ifstream file(basePath);

    if (!file.is_open()) {
        cout << "[ERROR] Gagal membuka file: " << basePath << endl;
        return;
    }

    string line;
    int indexLantai = -1, indexAP = 0, indexUser = 0;

    while (getline(file, line)) {
        if (line.find(">> Lantai") != string::npos) {
            indexLantai++;
            indexAP = 0;
        } else if (line.find("AccessPoint") != string::npos) {
            indexUser = 0;
            indexAP++;
        } else if (line.find("Nama =") != string::npos && line.find("Kegiatan =") != string::npos) {
            size_t namaPos = line.find("Nama =") + 7;
            size_t kegiatanPos = line.find("Kegiatan =");
            string nama = line.substr(namaPos, kegiatanPos - namaPos - 4);
            string kegiatan = line.substr(kegiatanPos + 11);

            Pengguna[indexLantai][indexAP - 1][indexUser][0] = nama;
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = kegiatan;
            indexUser++;
        } else if (line.find("[None]") != string::npos) {
            Pengguna[indexLantai][indexAP - 1][indexUser][0] = "-";
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = "-";
            indexUser++;
        }
    }

    Lantai = indexLantai + 1;
    file.close();
}

void CetakPengguna() {
    for (int i = 0; i < Lantai; ++i) {
        cout << ">> Lantai " << i + 1 << "\n";
        for (int j = 0; j < MaxAP; ++j) {
            bool adaData = false;

            for (int k = 0; k < MaxUser; ++k) {
                string nama = Pengguna[i][j][k][0];
                string kegiatan = Pengguna[i][j][k][1];

                if (nama.empty()) break;

                if (nama != "-") {
                    if (!adaData) {
                        cout << "  AccessPoint = " << j + 1 << "\n";
                        adaData = true;
                    }
                    cout << "       Nama = " << nama << " || Kegiatan = " << kegiatan << "\n";
                }
            }

            if (!adaData) {
                cout << "  AccessPoint = " << j + 1 << "\n";
                cout << "       [None]\n";
            }
        }
        cout << "\n";
    }

    cout << "=================================\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "[ERROR] Butuh username!\n";
        return 1;
    }

    string username = argv[1];
    cout << "[DEBUG] Username: " << username << endl;

    PenggunaIN(username);
    CetakPengguna();

    return 0;
}
