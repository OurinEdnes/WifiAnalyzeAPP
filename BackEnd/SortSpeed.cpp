#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MaxLantai = 10;
const int APMax = 10;

string CloneAPSpeed[MaxLantai][APMax][2];
int DataBaseUser[MaxLantai];
int Lantai = 0;

double convertToGbpsANDMbps(const string& val, char mode) {
    try {
        if (val.empty() || val == "-") return 0.0;
        double angka = stod(val);
        if (val.find("Gbps") != string::npos) return (mode == 'G') ? angka : angka * 1000;
        if (val.find("Mbps") != string::npos) return (mode == 'M') ? angka : angka / 1000;
        return angka;
    } catch (const invalid_argument& e) {
        cerr << "[Error] Konversi gagal untuk val: \"" << val << "\"\n";
        return 0.0;
    }
}

void LoadDataKecepatan(const string& username) {
    string path = "UserData(" + username + ")/Wifi-Ap-Speed.txt";
    ifstream file(path);
    string line;

    int lantai = -1, ap = 0;
    while (getline(file, line)) {
        if (line.find(">> Lantai") != string::npos) {
            lantai++;
            ap = 0;
        } else if (line.find("AccessPoint =") != string::npos) {
            size_t capPos = line.find("AccessPoint =") + 14;
            size_t sep = line.find("|| Kecepatan User =");
            string apSpeed = line.substr(capPos, sep - capPos - 1);
            string userSpeed = line.substr(sep + 22);

            // Bersihkan trailing space/newline
            apSpeed = apSpeed.substr(0, apSpeed.find_last_not_of(" \r\n") + 1);
            userSpeed = userSpeed.substr(0, userSpeed.find_last_not_of(" \r\n") + 1);

            CloneAPSpeed[lantai][ap][0] = apSpeed;
            CloneAPSpeed[lantai][ap][1] = userSpeed;
            ap++;
        }
    }

    Lantai = lantai + 1;
    for (int i = 0; i < Lantai; ++i) {
        DataBaseUser[i] = APMax;
    }

    file.close();
}

void TampilkanKecepatanSortPerAP(const char &c) {
    string TempSpeed[MaxLantai][APMax][2];
    int Ap[MaxLantai][APMax];

    // Salin data ke TempSpeed & inisialisasi AP-1, AP-2, dst
    for (int i = 0; i < Lantai; ++i) {
        for (int j = 0; j < DataBaseUser[i]; ++j) {
            TempSpeed[i][j][0] = CloneAPSpeed[i][j][0];
            TempSpeed[i][j][1] = CloneAPSpeed[i][j][1];
            Ap[i][j] = j + 1;
        }
    }

    // Sorting manual (Selection Sort)
    for (int i = 0; i < Lantai; ++i) {
        for (int j = 0; j < DataBaseUser[i] - 1; ++j) {
            int idxTerbaik = j;
            double selisihTerbaik = convertToGbpsANDMbps(TempSpeed[i][j][0], 'M') -
                                    convertToGbpsANDMbps(TempSpeed[i][j][1], 'M');

            for (int k = j + 1; k < DataBaseUser[i]; ++k) {
                double selisihSekarang = convertToGbpsANDMbps(TempSpeed[i][k][0], 'M') -
                                         convertToGbpsANDMbps(TempSpeed[i][k][1], 'M');

                bool ascending = (c == 'A');
                bool descending = (c == 'D');

                if ((selisihSekarang < selisihTerbaik && ascending) ||
                    (selisihSekarang > selisihTerbaik && descending)) {
                    idxTerbaik = k;
                    selisihTerbaik = selisihSekarang;
                }
            }

            // Tukar isi array tanpa swap()
            if (idxTerbaik != j) {
                string tempKap = TempSpeed[i][j][0];
                string tempPak = TempSpeed[i][j][1];
                TempSpeed[i][j][0] = TempSpeed[i][idxTerbaik][0];
                TempSpeed[i][j][1] = TempSpeed[i][idxTerbaik][1];
                TempSpeed[i][idxTerbaik][0] = tempKap;
                TempSpeed[i][idxTerbaik][1] = tempPak;

                int tempAP = Ap[i][j];
                Ap[i][j] = Ap[i][idxTerbaik];
                Ap[i][idxTerbaik] = tempAP;
            }
        }
    }

    // Tampilkan hasil
    for (int i = 0; i < Lantai; ++i) {
        cout << ">> Lantai " << i + 1 << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(10) << "AP"
             << setw(20) << "Kapasitas"
             << setw(20) << "Total User"
             << setw(15) << "Sisa (Mbps)" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int j = 0; j < DataBaseUser[i]; ++j) {
            string kapasitas = TempSpeed[i][j][0];
            string terpakai  = TempSpeed[i][j][1];
            if (kapasitas.empty() || kapasitas == "-") continue;

            double APS = convertToGbpsANDMbps(kapasitas, 'M');
            double SAU = convertToGbpsANDMbps(terpakai, 'M');
            double SISA = APS - SAU;

            cout << left << setw(10) << ("AP-" + to_string(Ap[i][j]))
                 << setw(20) << kapasitas
                 << setw(20) << terpakai
                 << setw(15) << fixed << setprecision(2) << SISA << endl;
        }
        cout << endl;
    }
}

int main() {
    string username = "Nom"; // Ganti sesuai nama folder user
    char mode = 'A';         // 'A' = Ascending, 'D' = Descending

    LoadDataKecepatan(username);
    TampilkanKecepatanSortPerAP(toupper(mode));

    return 0;
}
