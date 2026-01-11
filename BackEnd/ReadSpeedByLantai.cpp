#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const int MaxLantai = 10;
const int MaxAP = 10;

string CloneAPSpeed[MaxLantai][MaxAP][2];
int DataBaseUser[MaxLantai]; // jumlah AP per lantai
int TotalLantai = 0;

// --- Konversi string angka ke double
double stringToDoubleManual(const string& s) {
    double result = 0.0, desimal = 0.0;
    bool adaTitik = false;
    double pembagi = 10.0;
    for (char c : s) {
        if (isdigit(c)) {
            if (!adaTitik)
                result = result * 10 + (c - '0');
            else {
                desimal += (c - '0') / pembagi;
                pembagi *= 10;
            }
        } else if ((c == '.' || c == ',') && !adaTitik) {
            adaTitik = true;
        }
    }
    return result + desimal;
}

double convertToGbpsANDMbps(const string& teks, char typeConvert) {
    double angka = stringToDoubleManual(teks);
    string satuan = teks;
    transform(satuan.begin(), satuan.end(), satuan.begin(), ::tolower);
    typeConvert = toupper(typeConvert);
    if (typeConvert == 'M') {
        if (satuan.find("gbps") != string::npos) return angka * 1000.0;
        if (satuan.find("mbps") != string::npos) return angka;
        if (satuan.find("kbps") != string::npos) return angka / 1000.0;
    } else if (typeConvert == 'G') {
        if (satuan.find("gbps") != string::npos) return angka;
        if (satuan.find("mbps") != string::npos) return angka / 1000.0;
        if (satuan.find("kbps") != string::npos) return angka / 1000000.0;
    }
    return angka;
}

// --- Baca file txt ke array
void LoadDataAP(const string& username) {
    string path = "C:/xampp/htdocs/WifiAnalyze/BackEnd/UserData(" + username + ")/Wifi-Ap-Speed.txt";
    ifstream file(path);
    string line;
    int lantai = -1, ap = 0;
    while (getline(file, line)) {
        if (line.find(">> Lantai") != string::npos) {
            lantai++;
            ap = 0;
            DataBaseUser[lantai] = 0;
        } else if (line.find("AccessPoint") != string::npos && line.find("||") != string::npos) {
            size_t eq = line.find('=');
            size_t pipe = line.find("||");
            string apSpeed = line.substr(eq + 2, pipe - (eq + 2));

            size_t userStart = line.find("Kecepatan User = ");
            string userSpeed = (userStart != string::npos) ? line.substr(userStart + 18) : "";

            CloneAPSpeed[lantai][ap][0] = apSpeed;
            CloneAPSpeed[lantai][ap][1] = userSpeed;

            ap++;
            DataBaseUser[lantai]++;
        }
    }
    TotalLantai = lantai + 1;
    file.close();
}

// --- Sorting dan tampilkan total per lantai
// --- Sorting dan tampilkan total per lantai berdasarkan SISA
void TampilkanKecepatanSortPerLantai(char c) {
    double sisaKecepatan[MaxLantai];
    string CloneLantai[MaxLantai];

    for (int i = 0; i < TotalLantai; i++) {
        double totalAP = 0, totalUser = 0;
        for (int j = 0; j < DataBaseUser[i]; j++) {
            totalAP += convertToGbpsANDMbps(CloneAPSpeed[i][j][0], 'M');
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[i][j][1], 'M');
        }
        sisaKecepatan[i] = totalAP - totalUser; //  diubah: sekarang pakai sisa!
        CloneLantai[i] = to_string(i);
    }

    // Bubble Sort
    for (int i = 0; i < TotalLantai - 1; i++) {
        for (int j = 0; j < TotalLantai - i - 1; j++) {
            bool tukar = false;
            if ((c == 'D' && sisaKecepatan[j] < sisaKecepatan[j + 1]) ||
                (c == 'A' && sisaKecepatan[j] > sisaKecepatan[j + 1])) {
                tukar = true;
            }

            if (tukar) {
                swap(sisaKecepatan[j], sisaKecepatan[j + 1]);
                swap(CloneLantai[j], CloneLantai[j + 1]);
            }
        }
    }

    cout << "===== KECEPATAN TOTAL PER LANTAI (URUT BERDASARKAN SISA) =====" << endl;
    for (int i = 0; i < TotalLantai; i++) {
        int id = stoi(CloneLantai[i]);
        double totalAP = 0, totalUser = 0;
        for (int j = 0; j < DataBaseUser[id]; j++) {
            totalAP += convertToGbpsANDMbps(CloneAPSpeed[id][j][0], 'M');
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[id][j][1], 'M');
        }

        double sisa = totalAP - totalUser;

        cout << "Lantai " << id + 1
             << " || Total Kecepatan AP: " << totalAP
             << " || Total Kecepatan User: " << totalUser
             << " || Sisa: " << sisa << endl;
    }
}


int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "ERROR: Argumen kurang. Format: ReadSpeed.exe <username> sort_lantai <A/D>\n";
        return 1;
    }

    string username = argv[1];
    string mode = argv[2];
    char sortMode = toupper(argv[3][0]); // 'A' atau 'D'

    LoadDataAP(username);

    if (mode == "sort_lantai") {
        TampilkanKecepatanSortPerLantai(sortMode);
    } else {
        cout << "INVALID_MODE\n";
    }

    return 0;
}
