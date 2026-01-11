#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MaxLantai = 10;
const int MaxAP = 10;
const int MaxUser = 20;

string Pengguna[MaxLantai][MaxAP][MaxUser][2];
int Lantai = 0;

void PenggunaIN(const string& user_folder_path) {
    string path = user_folder_path + "/Wifi-User.txt";
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "[ERROR] Tidak bisa membuka file: " << path << endl;
        cout << "Pengguna dengan nama tidak ditemukan (file tidak ada).\n";
        Lantai = 0;
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

void CariNama(const string& target) {
    bool ditemukan = false;
    for (int i = 0; i < Lantai; ++i) {
        for (int j = 0; j < MaxAP; ++j) {
            for (int k = 0; k < MaxUser; ++k) {
                string nama = Pengguna[i][j][k][0];
                string kegiatan = Pengguna[i][j][k][1];

                if (nama == target) {
                    if (!ditemukan) {
                        cout << "=== HASIL PENCARIAN ===\n";
                        ditemukan = true;
                    }
                    cout << "Lantai " << i + 1
                         << " || AP Ke-" << j + 1
                         << " || Nama = " << nama
                         << " || Kegiatan = " << kegiatan << "\n";
                }
            }
        }
    }

    if (!ditemukan) {
        cout << "Pengguna dengan nama \"" << target << "\" tidak ditemukan.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "[ERROR] Format: <exe> <user_folder_path> <target_nama>\n";
        return 1;
    }

    string user_folder_path = argv[1];
    string target = argv[2];

    PenggunaIN(user_folder_path);
    CariNama(target);

    return 0;
}
