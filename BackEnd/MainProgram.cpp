#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <direct.h>
#include <string>
using namespace std;

//=================Untuk Mudahin Loop===============
#define fori(a, b) for(int i = (a); i < (b); i++)
#define forj(a, b) for(int j = (a); j < (b); j++)
#define forz(a, b) for(int z = (a); z < (b); z++)

#define forLantai(a, b) for(int i = (a); i < (b); i++)
#define forAP(a, b) for(int j = (a); j < (b); j++)
#define forUserPerAP(a, b) for(int k = (a); k < (b); k++)
#define forUserPerKegiatan(a, b) for(int l = (a); l < (b); l++)


//======Penginnisialisasi Warna MEnggunakan Define Untuk Teks======
#define WARNA_HITAM   0
#define WARNA_BIRU    1
#define WARNA_HIJAU   2
#define WARNA_CYAN    3
#define WARNA_MERAH   4
#define WARNA_UNGU    5
#define WARNA_KUNING  6
#define WARNA_PUTIH   7
#define WARNA_ORANGE   14

#define WARNA_HEADER  WARNA_CYAN
#define WARNA_ERROR   WARNA_MERAH
#define WARNA_INPUT   WARNA_KUNING
#define WARNA_LOADING WARNA_HIJAU
#define WARNA_LABEL   WARNA_UNGU
#define WARNA_NORMAL  WARNA_PUTIH

#define hijau(TEXT) setWarna(2); cout << (TEXT); setWarna(7)

//======UserandPass=====
string UserName;
string Password;
bool Pass = false;

bool Attemp = true;
int maxTry = 4;

string path;
bool PunyaDatabase = true;
//======================
//====Variabel-Global===
    const int MaxUser = 100;
    const int MaxLantai = 15;
    const int MaxAp_Per_lantai = 10;
    int Lantai, APMax = 0, MaxKat = 0;
    string pathFile1User, pathFile2User, pathFile3User;
//=======================

//======Function da prosedur=====
size_t findManual(const string& text, const string& pattern) {
    if (pattern.empty() || text.empty() || pattern.length() > text.length()) {
        return string::npos;
    }

    for (size_t i = 0; i <= text.length() - pattern.length(); i++) {
        bool found = true;
        for (size_t j = 0; j < pattern.length(); j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return string::npos;
}

bool findManualExists(const string& text, const string& pattern) {
    return findManual(text, pattern) != string::npos;
}


void Navbar();
void InterfaceAwal();
void Login();
void SignUp();
bool LoginProtection();
bool SignProtect();
void DirectP();

void SimpanDataWifiUser();
void SimpanDataKecepatanAP();
void SimpaDataUserPerAP();

void pauseScreen();


int stringToIntManual(const string& s);
double convertToGbpsANDMbps(const string& teks);

///====Untuk Cloning Data Jadi Yang Diotakatik Buat Sort dan Search dari Sini====
void CloningData();

//=======Page========
void PageAwal();
void PageLoading();
void PageUtama();
void NewPenggunna();
void NewInputUnntukPenggunnaBaru();
void cetakKategori();

void cetakKonfigurasWifiUser();
void ManuPagefirst(char &c, char &v);
void CetakKecepatan(const char& type, const char &typeSort); void cetakKatalog();

void TampilkanKecepatanNormal();
void TampilkanKecepatanSortPerAP(const char &c);
void TampilkanKecepatanSortPerLantai(const char &c);

void TampilkanNama(); void tampilNormal(); void TampilUrut(); void UrutSesuaiKatalog(int Katlog[]);

void gantiAtauTambah(); void ChangeConnfigure(); void AddUser(); void RemoveUser(); void RemoveUserperLantai();
void Searching(); void CariNama(); void cariBerdasarkanKegiatan();
void konfigurasiKecepatanDenganUser();
//===================

//======Folder-PerUser=====
void dataUser();
void cekbase();
void CekDatabaseUser();
void WifikonfigurasiList();
void KegiatanData();
void CekSSemuaDataUser();


///=====DataBase Ke Array=====
void WifiConnfigureIN();
void PenggunaIN();
void APSpeedIN();
void DataBaseUserIN();
void KegiatanIN();

//====Array-Save-Data-Buat-User====
int DataBaseUser[MaxLantai];
string Pengguna[MaxLantai][MaxAp_Per_lantai][MaxUser][2]; //2 Buat Nama Pengguna dan Kegiatan yang dilakukan
string APSpeed[MaxLantai][MaxAp_Per_lantai][2];
string WifiConnfigur[MaxLantai][5]; //4 buat deklarasi Nama wifi, kecepatann wwifi, sama total penngguna
string Kegiatan[20][2];
string WifiCategoryList[10][5];

// === Clone Arrays ===
string ClonePengguna[MaxLantai][MaxAp_Per_lantai][MaxUser][2];
string CloneAPSpeed[MaxLantai][MaxAp_Per_lantai][2];
string CloneWifiConnfigur[MaxLantai][5];
string CloneKegiatan[20][2];

//=========Array-Searching======
string findAP[MaxLantai][MaxAp_Per_lantai];

///====================================================================================
void WifiConnfigureIN() {
    string pathfile = path + "/WifiConfigure.txt";
    fstream file(pathfile, ios::in);
    string line;

    int indexLantai = 0;
    int currentLantai = 0;
    int jumlahAP = 0;
    while (getline(file, line)) {
        //=== PARSING JUMLAH LANTAI ===
        if (findManualExists(line, "Jumlah Lantai =")) {
            int result = 0;
            bool out = true;
            string s = line.substr(findManual(line, "=") + 2);

            fori(0, s.length()) {
                switch (s[i]) {
                    case '0': result = result * 10 + 0; break;
                    case '1': result = result * 10 + 1; break;
                    case '2': result = result * 10 + 2; break;
                    case '3': result = result * 10 + 3; break;
                    case '4': result = result * 10 + 4; break;
                    case '5': result = result * 10 + 5; break;
                    case '6': result = result * 10 + 6; break;
                    case '7': result = result * 10 + 7; break;
                    case '8': result = result * 10 + 8; break;
                    case '9': result = result * 10 + 9; break;
                    default: out = false; break;
                }
                if (!out) break;
            }
            if (out) {
                Lantai = result;
            }
        }

        //=== PARSING JUMLAH AP PER LANTAI ===
        else if (findManualExists(line, "> Lantai")) {
            bool out = true;
            string s = line.substr(findManual(line, "=") + 2);
            jumlahAP = 0;
            fori(0, s.length()) {
                switch (s[i]) {
                    case '0': jumlahAP = jumlahAP * 10 + 0; break;
                    case '1': jumlahAP = jumlahAP * 10 + 1; break;
                    case '2': jumlahAP = jumlahAP * 10 + 2; break;
                    case '3': jumlahAP = jumlahAP * 10 + 3; break;
                    case '4': jumlahAP = jumlahAP * 10 + 4; break;
                    case '5': jumlahAP = jumlahAP * 10 + 5; break;
                    case '6': jumlahAP = jumlahAP * 10 + 6; break;
                    case '7': jumlahAP = jumlahAP * 10 + 7; break;
                    case '8': jumlahAP = jumlahAP * 10 + 8; break;
                    case '9': jumlahAP = jumlahAP * 10 + 9; break;
                    default: out = false; break;
                }
                if (!out) break;
            }
            out = true;
            if (out) {
                DataBaseUser[indexLantai] = jumlahAP;
                if (APMax < jumlahAP) APMax = jumlahAP;
                indexLantai++;
            }
        }

        //=== PARSING ISI WIFI SETIAP LANTAI ===
        else if (findManualExists(line, "MerekWiFi") && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][0] = line.substr(findManual(line, ":") + 2);
        }
        else if (findManualExists(line, "AccessPoint") && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][1] = line.substr(findManual(line, ":") + 2);
        }
        else if (findManualExists(line, "KecepatanWiFi") && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][2] = line.substr(findManual(line, ":") + 2);
        }
        else if (findManualExists(line, "KecepatanAP") && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][3] = line.substr(findManual(line, ":") + 2);
        }
        else if (findManualExists(line, "MaxUser      :") && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][4] = line.substr(findManual(line, ":") + 2);
            currentLantai++;
        }

        if (currentLantai >= MaxLantai) break;
    }
    file.close();
}

void APSpeedIN() {
    fstream file(pathFile3User, ios::in);
    string line;

    int indexLantai = -1, indexAP = 0;
    while (getline(file, line)) {
        if (findManualExists(line, ">> Lantai")) {
            indexLantai++;
            indexAP = 0;
        }
        else if (findManualExists(line, "AccessPoint") && findManualExists(line, "=")) {
            size_t eqPos = findManual(line, "=");
            size_t delimiterPos = findManual(line, "||");

            string apSpeed = line.substr(eqPos + 2, delimiterPos - (eqPos + 2));
            APSpeed[indexLantai][indexAP][0] = apSpeed;

            size_t userSpeedPos = findManual(line, "Kecepatan User =");
            if (userSpeedPos != string::npos) {
                string userSpeed = line.substr(userSpeedPos + 17);
                APSpeed[indexLantai][indexAP][1] = userSpeed;
            }

            indexAP++;
        }
    }
    file.close();
}

void PenggunaIN() {
    fstream file(pathFile2User, ios::in);
    string line;

    int indexLantai = -1;
    int indexAP = 0;
    int indexUser = 0;

    while (getline(file, line)) {
        // Cek Lantai
        if (findManualExists(line, ">> Lantai")) {
            indexLantai++;
            indexAP = 0;
            continue;
        }

        // Cek Access Point
        else if (findManualExists(line, "AccessPoint")) {
            indexUser = 0;
            indexAP++; // <-- Ini cukup di sini aja
            continue;
        }

        // Cek jika baris ada Nama dan Kegiatan
        else if (findManualExists(line, "Nama =") && findManualExists(line, "Kegiatan =")) {
            size_t namaPos = findManual(line, "Nama =") + 7;
            size_t kegiatanPos = findManual(line, "Kegiatan =");

            string nama = line.substr(namaPos, kegiatanPos - namaPos - 4); // ' || '
            string kegiatan = line.substr(kegiatanPos + 11);

            Pengguna[indexLantai][indexAP - 1][indexUser][0] = nama;
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = kegiatan;

            indexUser++;
        }


        else if (findManualExists(line, "[None]")) {
            Pengguna[indexLantai][indexAP - 1][indexUser][0] = "-";
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = "-";
            indexUser++;
        }
    }
    file.close();
}


void KegiatanIN(){
    fstream file("DaftarKegiatan.txt", ios::in);
    string line;

    int indexX = 0;
    while(getline(file, line)){
        if(findManualExists(line, "Nama       =")){
            Kegiatan[indexX][0] = line.substr(findManual(line, "=") + 2);
            CloneKegiatan[indexX][0] = line.substr(findManual(line, "=") + 2);
            MaxKat++;
        } else if(findManualExists(line, "Kecepatan  =")){
            Kegiatan[indexX][1] = line.substr(findManual(line, "=") + 2);
            CloneKegiatan[indexX][1] = line.substr(findManual(line, "=") + 2);
        } else if(findManualExists(line, "================================")){
            indexX++;
        }
    }
    file.close();
}
///=======================================================================================

//====Set-Warnna====
void setWarna(int kodeWarna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kodeWarna);
}

void warnaText(const string& text, int i) {
    setWarna(i);
    cout << text;
    setWarna(WARNA_PUTIH);
}

string getHiddenInput() {
    string input = "";
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' = Enter
        if (ch == '\b') { // Backspace
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; // Hapus char terakhir dari layar
            }
        } else if (isprint(ch)) { // Cek apakah bisa dicetak
            input += ch;
            cout << '*'; // Tampilkan * tiap ketik
        }
    }
    cout << endl;
    return input;
}

///========Cover dari strig ke int atau double======
double stringToDoubleManual(const string& s) {
    double result = 0.0;
    double desimal = 0.0;
    bool adaTitik = false;
    double pembagiDesimal = 10.0;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            if (!adaTitik) {
                result = result * 10 + (c - '0');
            } else {
                desimal += (c - '0') / pembagiDesimal;
                pembagiDesimal *= 10;
            }
        } else if ((c == '.' || c == ',') && !adaTitik) {
            adaTitik = true;
        }
    }

    return result + desimal;
}

int stringToIntManual(const string& s) {
    int result = 0;
    bool negatif = false;
    int i = 0;

    if (s[0] == '-') {
        negatif = true;
        i = 1;
    }

    for (; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        } else {
            break;
        }
    }

    return negatif ? -result : result;
}


double convertToGbpsANDMbps(const string& teks, char typeConvert) {
    double angka = stringToDoubleManual(teks);

    string satuan = teks;
    transform(satuan.begin(), satuan.end(), satuan.begin(), ::tolower);

    typeConvert = toupper(typeConvert);

    if (typeConvert == 'M') {  // Ke Mbps
        if (findManualExists(satuan, "gbps")) {
            return angka * 1000.0;
        } else if (findManualExists(satuan, "mbps")) {
            return angka;
        } else if (findManualExists(satuan, "kbps")) {
            return angka / 1000.0;
        }
    }
    else if (typeConvert == 'G') {  // Ke Gbps
        if (findManualExists(satuan, "gbps")) {
            return angka;
        } else if (findManualExists(satuan, "mbps")) {
            return angka / 1000.0;
        } else if (findManualExists(satuan, "kbps")) {
            return angka / 1000000.0;
        }
    }

    // Kalau satuan tidak dikenali
    return angka;
}

///========Konfiguruasi Koneksi Anntara SpeedAP ke USER======
void konfigurasiKecepatanDenganUser(){
    int maxKatalog = sizeof(Kegiatan) / sizeof(Kegiatan[0]);
    forLantai(0, Lantai){
        forAP(0, DataBaseUser[i]){
            int maxUser = stringToIntManual(WifiConnfigur[i][4]);
            double apspeedTemp = 0;
            forUserPerAP(0, maxUser){
                if(Pengguna[i][j][k][0] == "-"){
                    continue;
                }else{
                forz(0, maxKatalog){
                    if (Kegiatan[z][0] == Pengguna[i][j][k][1]) {
                        string s = Kegiatan[z][1];
                        double connverter = convertToGbpsANDMbps(s, 'G');
                        apspeedTemp += connverter;
                    }
                }
                }
            }
            if(apspeedTemp == 0){
            APSpeed[i][j][1] = "[None]";
            }else{

            APSpeed[i][j][1] = to_string(apspeedTemp) + "Gbps";
            }

        }
    }
}

//====Cek-Database-User====
void reconDatabase(){
    fstream DataBase("User-DataBase.txt", ios::in);
    if(!DataBase){
        ofstream make("User-DataBase.txt");
        make.close();
    }
    DataBase.close();
}
//=========================

void Navbar(){
    system("cls");
    cout << "============================\n";
    cout << "|---"; setWarna(WARNA_HEADER); cout << "Wifi Analyze Company"; setWarna(WARNA_NORMAL); cout<< "---|\n";
    cout << "============================\n\n";
}
///===============================================================================
//====Page Awal====
void PageAwal(){
    system("cls");
    Navbar();
    InterfaceAwal();
}

void InterfaceAwal(){
    cout << "Selamat Datang... \n"; setWarna(WARNA_ORANGE); cout <<"Harap Masuk terlebih Dahulu!\n\n";
    setWarna(WARNA_NORMAL);
    cout << "Menu Pilihan: \n";
    cout << "1. Login. \n";
    cout << "2. SignUp. \n";
    cout << "Pilih Menu: ";
    setWarna(WARNA_KUNING);
    int req; cin >> req;
    setWarna(WARNA_NORMAL);

    if (req == 1){
        Login();
    } else if (req == 2){
        SignUp();
    } else {
        setWarna(WARNA_ERROR);
        cout << "Menu Belum Tersedia Harap Pilih Lagi! \n";
        setWarna(WARNA_NORMAL);
        Sleep(1000);
        PageAwal();
    }
}

void Login(){
    do{
    system("cls");
    Navbar();
    cout << "Login-Section\n\n";

    if(!Attemp){
        setWarna(4);
        cout << "Username / Password salah harap ulangi! (" << maxTry <<" Kali percobaan Lagi) \n\n";
        setWarna(7);
    }
    cout << "Username: ";
    setWarna(WARNA_HIJAU);
    cin >> UserName;
    setWarna(WARNA_NORMAL);
    cout << "Password: ";
    setWarna(WARNA_HIJAU);
    Password = getHiddenInput();
    setWarna(WARNA_NORMAL);
    if(LoginProtection()){
        CekSSemuaDataUser();
        Attemp = true;
        maxTry = 4;
        PageLoading();
        PageUtama();
    }
    else{maxTry--; Attemp = false;}
    } while(!Attemp && maxTry > 0);

    if(!Attemp){
        Attemp = true; maxTry = 4;
        setWarna(4);
        cout << "Anda Sudah Mencoba lebih dari 3 kali!\n";
        setWarna(7);
        Sleep(1000);
        PageAwal();
    }
}

bool LoginProtection(){
    fstream data("User-DataBase.txt", ios::in);
    string base;

    int sameboth = 0;
    bool same = false;
    while(getline(data, base)){

        if(findManualExists(base, "username ##")){
            string usernameBase = base.substr(findManual(base, "##") + 3);
            if(UserName == usernameBase){
                sameboth++;
            }
        } else if(findManualExists(base, "password ##")){
            string PasswordBase = base.substr(findManual(base, "##") + 3);
            if(PasswordBase == Password){
                sameboth++;
            }
        } else if(findManualExists(base, "==============")){
            sameboth = 0;
        }

        if(sameboth == 2){
            same = true;
            break;
        }
    }
    data.close();

    return (same == false ? false : true);
}

void SignUp(){
    system("cls");
    Navbar();
    cout << "SignUp-Section\n\n";
    cout << "username: ";
    cin >> UserName;
    cout << "Password: ";
    setWarna(WARNA_HIJAU);
    Password = getHiddenInput();
    setWarna(WARNA_NORMAL);
    if(SignProtect()){
        setWarna(3);
        cout <<"\nAkun Berhasil Dibuat!\n";
        setWarna(7);
        cout <<"Harap Login Lagi Terlebih Dahulu";
        Sleep(1000);
        Login();
    } else{
        setWarna(4);
        cout << "UserName sudah Terpakai, Harap Buat Ulang!\n";
        setWarna(7);
        Sleep(1000);
        SignUp();
    }
}

bool SignProtect(){
    fstream data("User-DataBase.txt", ios::app|ios::in);
    string base;

    while(getline(data, base)){
        if(findManualExists(base, "username ##")){
            string usernameBase = base.substr(findManual(base, "##") + 3);
            if(UserName == usernameBase){
                return false;
            }
        }
    }

    data.close();

    fstream Input("User-DataBase.txt", ios::app);
    Input << endl << endl;
    Input << "============================" << endl;
    Input << "username ## " << UserName << endl;
    Input << "password ## " << Password << endl;

    Input.close();
    return true;
}

//==========Katagero=========
void cetakKatalog(){
    cout << endl;
    int maxKatalog = sizeof(Kegiatan) / sizeof(Kegiatan[0]);
    fori(0, maxKatalog){
        int range = Kegiatan[i][0].length();
        if(Kegiatan[i][0] == "" || Kegiatan[i][0] == " " || Kegiatan[i][0] == "-") continue;
        cout << "Kegiatan " << i+1 << ": " << endl;
        cout << left << setw(5) << "Jenis: "; warnaText(Kegiatan[i][0], WARNA_BIRU);
        cout << left << setw(17-range) <<" "<< " || ";
        cout << left << setw(5) << "Kecepatan yang dipakai: "; warnaText(Kegiatan[i][1], WARNA_KUNING); cout << endl;
    }
    cout << endl;
}

//=======Page Loadig=======
void PageLoading() {
    system("cls");
    cout << "\nMemuat sistem WifiAnalyze...\n\n";
    setWarna(WARNA_LOADING);

    string loadingBar = "===================="; // 20 karakter total
    cout << "[                    ]"; // Bar kosong
    cout.flush();

    cout << "\r["; // Balik kursor ke depan
    fori(0, 20) {
        cout << loadingBar[i];
        cout.flush();
        Sleep(100); // Kecepatan pengisian bar
    }

    cout << "] Selesai!\n";
    setWarna(WARNA_NORMAL);
    Sleep(500); // jeda sedikit sebelum lanjut
}

void PageLoading2() {
    system("cls");
    cout << "\nMemuat Data WifiAnalyze...\n\n";
    setWarna(WARNA_LOADING);

    string spinner = "|/-\\";
    for (int i = 0; i < 20; i++) {
        cout << "\rLoading ";
        setWarna(WARNA_BIRU); cout << spinner[i % 4] << " ";
        cout.flush();
        Sleep(150);
    }

    setWarna(WARNA_NORMAL);
    cout << "\nSelesai!\n";
    Sleep(800);
}

//========CekDataUser=========
// => Nama Folder ("UserData(#username)")
void dataUser(){
    path = "UserData("+UserName+")";
    const char * folder = (path).c_str();
    mkdir(folder);
}

//========CekFile===========
void cekbase(){
    fori(0, 3){
        string construct;
        switch(i){
        case 0:
            construct = "/WifiConfigure.txt";
            break;
        case 1:
            construct = "/Wifi-User.txt";
            break;
        case 2:
            construct = "/Wifi-Ap-Speed.txt";
            break;
        default:
            construct = "/Eror.txt";
            break;
        }

        string pathFile = path + construct;
        fstream FileData(pathFile, ios::in);
        if(!FileData){
            ofstream create(pathFile);
            if(i == 0){
                create << "A7K9-X2ZQ";
            }
            create.close();
            }
        FileData.close();
    }
    pathFile1User = path + "/WifiConfigure.txt";
    pathFile2User = path + "/Wifi-User.txt";
    pathFile3User = path + "/Wifi-Ap-Speed.txt";
}

void KegiatanData(){ //-> Ke Array Kategori Kegiatan
    fstream file("DaftarKegiatan.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(findManualExists(base, "Nama       =")){
            Kegiatan[i][0] = base.substr(findManual(base, "=") + 2);
        } else if(findManualExists(base, "Kecepatan  =")){
            Kegiatan[i][1] = base.substr(findManual(base, "=") + 2);
        } else if(findManualExists(base, "================================")){
            i++;
        }
    }
}

void WifikonfigurasiList(){ //->Ke Array Kategori Wifi
    fstream file("WifiCategory.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(findManualExists(base, "MerekWiFi    :")){
            WifiCategoryList[i][0] = base.substr(findManual(base, ":") + 2);
        } else if(findManualExists(base, "AccessPoint  :")){
            WifiCategoryList[i][1] = base.substr(findManual(base, ":") + 2);
        } else if(findManualExists(base, "KecepatanWiFi:")){
            WifiCategoryList[i][2] = base.substr(findManual(base, ":") + 2);
        } else if(findManualExists(base, "KecepatanAP  :")){
            WifiCategoryList[i][3] = base.substr(findManual(base, ":") + 2);
        } else if(findManualExists(base, "MaxUser      :")){
            WifiCategoryList[i][4] = base.substr(findManual(base, ":") + 2);
        } else if(findManualExists(base, "===================================")){
            i++;
        }
    }
}

void CekDatabaseUser(){
    string connstruct = path + "/WifiConfigure.txt";
    fstream Data(connstruct, ios::in);
    string line;

    while(getline(Data, line)){
        if(findManualExists(line, "A7K9-X2ZQ")){
            PunyaDatabase = false;
            break;
        } else{
            PunyaDatabase = true;
        }
    }

}

///========Page Utama==========
void PageUtama(){
    NewPenggunna();
    CekSSemuaDataUser();
    system("cls");

    Navbar();
    cin.ignore();
    cout << "Pilihan Menu Yang Tersedia: \n";
    cout << "1. Cek Kecepatan Accses Point di setiap Lantai. \n";
    cout << "2. Cek Konfigurasi Wifi Di Setiap lantai. \n";
    cout << "3. Cek Nama Pengguna. \n";
    cout << "4. Tambah Atau Ganti Kondisi (User dan Wifi). \n";
    cout << "5. "; warnaText("Search (Cari).", WARNA_KUNING); cout << "\n";
    cout << "6. "; warnaText("Logout.", WARNA_MERAH); cout << "\n";
    cout << "Menu yang Dipilih: "; char pilih; cin >> pilih;

    switch(pilih){
    case '1':
        char key, sortType;
        ManuPagefirst(key, sortType);
        break;
    case '2':
        cetakKonfigurasWifiUser();
        break;
    case '3':
        TampilkanNama();
        break;
    case '4':
        gantiAtauTambah();
        break;
    case '5':
        Searching();
        break;
    case '6':
        cout << endl;
        UserName = "";
        Password = "";
        Sleep(800);
        cout << "Anda Telah Logout!";
        Sleep(700);
        PageAwal();
        break;
    default:
        cout << "Menu Belum Tersedia! Harap pilih denngan Benar!\n";
        Sleep(900); PageUtama();
        break;
    }

    PageUtama();
}

//===============Menu 1=================
void ManuPagefirst(char &c, char &v){
    Navbar();
    cin.ignore();
    cout << "Menu Pilihan Tambahan: \n";
    cout << "1. Cek Kecepatan normal. \n";
    cout << "2. Cek Sesuai Urutam kecepatan per-AP. \n";
    cout << "3. Cek Sesuai Urutan Kecepatan Per-Lantai. \n";
    cout << "Pilih: "; char pilih; cin >> pilih;
    switch(pilih){
        case '1':
        c = '1';
        CetakKecepatan(c, v);
        break;

        case '2':
        c = '2';
        setWarna(WARNA_CYAN);
        cout << endl;
        cout << "Urutkan Secara Asceding atau Descending (A/D): "; cin >> pilih; v = pilih;
        CetakKecepatan(c, v);
        setWarna(WARNA_NORMAL);
        break;

        case '3':
        c = '3';
        setWarna(WARNA_CYAN);
        cout << endl;
        cout << "Urutkan Secara Asceding atau Descending (A/D): "; cin >> pilih; v = pilih;
        CetakKecepatan(c, v);
        setWarna(WARNA_NORMAL);
        break;

        default:
            cout << "Pilihan Tidak Tersedia harap pilih kembali! \n";
            Sleep(600);
            ManuPagefirst(c, v);
        break;
    }
    return;
}

void CetakKecepatan(const char& type, const char &typeSort){

    if (!PunyaDatabase) {
        setWarna(WARNA_ERROR);
        cout << "Oops! Database belum diatur atau dimuat!\n";
        cout << "Silakan atur konfigurasi awal di menu 'Tambah Kondisi' terlebih dahulu.\n";
        setWarna(WARNA_NORMAL);
        pauseScreen();
        return;
    }

    switch(type){
        case '1':
            TampilkanKecepatanNormal();
            pauseScreen();
            break;
        case '2':
            TampilkanKecepatanSortPerAP(typeSort);
            pauseScreen();
            break;
        case '3':
            TampilkanKecepatanSortPerLantai(typeSort);
            pauseScreen();
            break;
        default:
            pauseScreen();
            break;
        }

}

void TampilkanKecepatanNormal() {
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN ACCESS POINT (NORMAL) =====" << endl;
    setWarna(WARNA_NORMAL);
    forLantai(0, Lantai) {
        cout << "Lantai " << i + 1 << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(10) << "AP"
            << setw(20) << "Kapasitas"
            << setw(20) << "Total User"
            << setw(15) << "Sisa (Mbps)" << endl;
        cout << "--------------------------------------------------" << endl;

        forAP(0, DataBaseUser[i]) {
            string kapasitas = APSpeed[i][j][0];
            string terpakai  = APSpeed[i][j][1];
            if (kapasitas.empty() || kapasitas == "-" || kapasitas == " ") continue;

            double APS = convertToGbpsANDMbps(kapasitas, 'M'); // Kapasitas AP
            double SAU = convertToGbpsANDMbps(terpakai, 'M');  // Speed Akumulasi User
            double SISA = APS - SAU;

            if (SISA >= 500) setWarna(WARNA_HIJAU);
            else if (SISA >= 200) setWarna(WARNA_ORANGE);
            else setWarna(WARNA_MERAH);

            cout << left << setw(10) << ("AP-" + to_string(j + 1))
                << setw(20) << kapasitas
                << setw(20) << terpakai
                << setw(15) << fixed << setprecision(2) << SISA << endl;

            setWarna(WARNA_NORMAL);
        }

        cout << "--------------------------------------------------\n" << endl;
    }
    cout << endl;
    cout << "Keterangan Warna: \n";
    setWarna(WARNA_HIJAU); cout << "1. Hijau";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Bagus!\n";
    setWarna(WARNA_ORANGE); cout << "2. Kuning";
    setWarna(WARNA_NORMAL); cout << " -> Kecepatan AP Tidak Bagus\n";
    setWarna(WARNA_MERAH); cout << "3. Merah";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Buruk (Harap Kurangi Penggunaan)\n";
    cout << endl;
}

void TampilkanKecepatanSortPerAP(const char &c){
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN ACCESS POINT (PerAP) =====" << endl;
    setWarna(WARNA_NORMAL);
    int Ap[MaxLantai][APMax];
        forLantai(0, Lantai){
            int counter = 1;
            forAP(0, DataBaseUser[i]){
                Ap[i][j] = counter;
                counter++;
            }
    }

    forLantai(0, Lantai) {
        for(int j = 0; j < DataBaseUser[i]; j++) { // bubble sort outer loop
            for(int z = 0; z < DataBaseUser[i] - 1 - j; z++) {
                double APsatu = convertToGbpsANDMbps(CloneAPSpeed[i][z][0], 'M') - convertToGbpsANDMbps(CloneAPSpeed[i][z][1], 'M');
                double APdua  = convertToGbpsANDMbps(CloneAPSpeed[i][z+1][0], 'M') - convertToGbpsANDMbps(CloneAPSpeed[i][z+1][1], 'M');

                bool ascending = (c == 'A');
                bool descending = (c == 'D');

                if ((APsatu < APdua && descending) || (APsatu > APdua && ascending)) {
                    for (int d = 0; d < 2; d++) {
                        string temp = CloneAPSpeed[i][z][d];
                        CloneAPSpeed[i][z][d] = CloneAPSpeed[i][z+1][d];
                        CloneAPSpeed[i][z+1][d] = temp;
                    }
                    int temp = Ap[i][z];
                    Ap[i][z] = Ap[i][z+1];
                    Ap[i][z+1] = temp;
                }
            }
        }
    }

    Sleep(600);
    forLantai(0, Lantai){
        cout << "Lantai " << i+1 << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(10) << "AP"
            << setw(20) << "Kapasitas"
            << setw(20) << "Total User"
            << setw(15) << "Sisa (Mbps)" << endl;
        cout << "--------------------------------------------------" << endl;

        forAP(0, DataBaseUser[i]){
            // Validasi data sebelum proses
            string kapasitas = CloneAPSpeed[i][j][0];
            string terpakai  = CloneAPSpeed[i][j][1];
            if (kapasitas.empty() || kapasitas == "-" || kapasitas == " ") continue;

            double APS = convertToGbpsANDMbps(kapasitas, 'M'); // Kapasitas AP
            double SAU = convertToGbpsANDMbps(terpakai, 'M');  // Speed Akumulasi User
            double SISA = APS - SAU;

            // Warna berdasarkan performa
            if (SISA >= 500) setWarna(WARNA_HIJAU);
            else if (SISA >= 200) setWarna(WARNA_ORANGE);
            else setWarna(WARNA_MERAH);

            // Output fancy + format rata
            cout << left << setw(10) << ("AP-" + to_string(Ap[i][j]))
                << setw(20) << kapasitas
                << setw(20) << terpakai
                << setw(15) << fixed << setprecision(2) << SISA << endl;

            setWarna(WARNA_NORMAL);
        }

        cout << "--------------------------------------------------\n" << endl;
    }


    cout << endl;
    cout << "Keterangan Warna: \n";
    setWarna(WARNA_HIJAU); cout << "1. Hijau";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Bagus!\n";
    setWarna(WARNA_ORANGE); cout << "2. Kuning";
    setWarna(WARNA_NORMAL); cout << " -> Kecepatan AP Tidak Bagus\n";
    setWarna(WARNA_MERAH); cout << "3. Merah";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Buruk (Harap Kurangi Penggunaan)\n";
    cout << endl;
}

void TampilkanKecepatanSortPerLantai(const char &c){
    double sisaKecepatan[MaxLantai];
    string CloneLantai[MaxLantai];

    forLantai(0, Lantai){
        double totalAP = 0, totalUser = 0;

        forAP(0, DataBaseUser[i]){
            totalAP = convertToGbpsANDMbps(CloneAPSpeed[i][j][0], 'M');
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[i][j][1], 'M');
        }

        sisaKecepatan[i] = totalAP - totalUser;
        CloneLantai[i] = to_string(i);
    }

    fori(0, Lantai - 1){
        forj(0, Lantai - i - 1){
            bool tukar = false;
            if((c == 'D' && sisaKecepatan[j] < sisaKecepatan[j+1]) ||
               (c == 'A' && sisaKecepatan[j] > sisaKecepatan[j+1])){
                tukar = true;
            }

            if(tukar){
                double tempNilai = sisaKecepatan[j];
                sisaKecepatan[j] = sisaKecepatan[j+1];
                sisaKecepatan[j+1] = tempNilai;

                string tempIndex = CloneLantai[j];
                CloneLantai[j] = CloneLantai[j+1];
                CloneLantai[j+1] = tempIndex;
            }
        }
    }

    // Cetak hasil
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN TOTAL PER LANTAI =====" << endl;
    setWarna(WARNA_NORMAL);

    fori(0, Lantai){
        int id = stoi(CloneLantai[i]);
        double totalUser = 0;

        forAP(0, DataBaseUser[id]){
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[id][j][1], 'M');
        }
        double WifiSpeed  = convertToGbpsANDMbps(WifiConnfigur[i][2], 'M');
        double sisa = WifiSpeed - totalUser;

        if(sisa >= 1000) setWarna(WARNA_HIJAU);
        else if(sisa >= 500) setWarna(WARNA_ORANGE);
        else setWarna(WARNA_MERAH);

        cout << "Lantai " << id+1
            << " || Total Kecepatan Wifi: " << WifiSpeed
            << " Mbps || Total Kecepatan User: " << totalUser
            << " Mbps || Sisa: " << sisa << " Mbps" << endl;

        setWarna(WARNA_NORMAL); // reset warna setelah output
    }


    cout << endl;
    cout << "Keterangan Warna: \n";
    setWarna(WARNA_HIJAU); cout << "1. Hijau";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Bagus!\n";
    setWarna(WARNA_ORANGE); cout << "2. Kuning";
    setWarna(WARNA_NORMAL); cout << " -> Kecepatan AP Tidak Bagus\n";
    setWarna(WARNA_MERAH); cout << "3. Merah";
    setWarna(WARNA_NORMAL); cout << "  -> Kecepatan AP Buruk (Harap Kurangi Penggunaan)\n";
    cout << endl;

}

//===============Mennu 3================
bool Dup(int arr[], int ukuran, int nilai) {
    for (int i = 0; i < ukuran; i++) {
        if (arr[i] == nilai) {
            return true;
        }
    }
    return false;
}

void TampilkanNama(){
    Navbar();
    char pil;
    cout << "Menu Pilihan Tambahan: \n";
    cout << "1. Cek Nama sesuai urutann connect. \n";
    cout << "2. Cek urutan sesuai kegiatan. \n";
    cout << "Pilih: "; char pilih; cin >> pilih;
    switch(pilih){
        case '1':
        tampilNormal();
        break;
        case '2':
        cetakKatalog();
        cout << endl;
        cout << "1. Urut Sesuai Katalog. \n";
        cout << "2. Bikinn Urutan Sendiri. \n";
        cout << "Pilih: "; cin >> pil;
        switch(pil){
        case '1':
            TampilUrut();
            break;
        case '2':{
            int Katlog[5]; int r = sizeof(Katlog) / sizeof(Katlog[0]);
            cout << endl << endl;
            cout << "Masukan Urutan Yang Anda ingin kann (1-5 sesuai Katalog)\n";
            for (int i = 0; i < r; i++) {
                int input;
                    cout << "Masukkan Urutan ke-" << i+1 << ": ";
                    cin >> input;
                    if (input > 5 || input < 1) {
                        cout << "Angka " << input << " tidak valid, masukkan antara 1-5!\n";
                        i--;
                        continue;
                    }

                    if (Dup(Katlog, i, input)) {
                        cout << "Angka " << input << " sudah ada, masukkan yang lain!\n";
                        i--;
                        continue;
                    }

                    Katlog[i] = input;
            }
            UrutSesuaiKatalog(Katlog);
            break;
        }
        default:
            cout << "Pilihan tidak tersedia! \n";
            pauseScreen();
            TampilkanNama();
            break;
        }
        pauseScreen();
        break;

        default:
            cout << "Pilihan Tidak Tersedia harap pilih kembali! \n";
            Sleep(600);
            TampilkanNama();
        break;
    }
    return;
}

void tampilNormal(){
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i+1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " <<"AP ke-" << j+1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][0] == "-" ||  Pengguna[i][j][k][0] == "" ||  Pengguna[i][j][k][0] == " "){
                    continue;
                } else{
                cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0] << " || " << "Kegiatan : " << Pengguna[i][j][k][1] << endl;
                ada = true;
                }
            }
            if(!ada){
                cout << setw(15) << " " <<"[NONE]\n";
            }
            cout << endl;
        }
        cout << "=====================================\n";
    }

    pauseScreen();
}

void TampilUrut() {
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User Berdasarkan Kegiatan =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i + 1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " << "AP ke-" << j + 1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;

            for (int katalog = 0; katalog < 5; katalog++) {
                forUserPerAP(0, range) {
                if(Pengguna[i][j][k][0] == "-" ||  Pengguna[i][j][k][0] == "" ||  Pengguna[i][j][k][0] == " "){
                    continue;
                }else if (Pengguna[i][j][k][1] == Kegiatan[katalog][0]) {
                        cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                        ada = true;
                    }
                }
            }

            if (!ada) {
                cout << setw(15) << " " << "[NONE]" << endl;
            }

            cout << endl;
        }
        cout << "=====================================\n";
    }
}

void UrutSesuaiKatalog(int katlog[]){
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User Berdasarkan Kegiatan =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i + 1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " << "AP ke-" << j + 1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;

            for (int katalog = 0; katalog < 5; katalog++) {
                forUserPerAP(0, range) {
                    if (Pengguna[i][j][k][0] == "-" || Pengguna[i][j][k][0] == "" || Pengguna[i][j][k][0] == " ") {
                        continue;
                    } else if (Pengguna[i][j][k][1] == Kegiatan[katlog[katalog] - 1][0]) {
                        cout << setw(25) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                        ada = true;
                    }
                }
            }

            if (!ada) {
                cout << setw(15) << " " << "[NONE]" << endl;
            }

            cout << endl;
        }
        cout << "=====================================\n";
    }
}


///==============Searching=============
void Searching(){
    Navbar();
    cout << endl;
    cout << "Kategori Search: \n";
    cout << "1. Cari Nama dan Lokasi User. \n";
    cout << "2. Tampilkan semua yang kegiatannnya sama. \n";
    cout << "Pilih: "; char pil; cin >> pil;

    switch(pil){
        case '1':{
        CariNama();
        break;
        } case '2':{
        cariBerdasarkanKegiatan();
        break;
        }default:{
        setWarna(WARNA_CYAN);
        cout << "\nMi scusi... menu belum tersedia. \n";
        setWarna(WARNA_NORMAL);
        pauseScreen();
        Searching();
        break;
        }
    }

}

void CariNama(){
    setWarna(WARNA_HEADER);
    cout << "===== Searching (PerNama) =====" << endl;
    setWarna(WARNA_NORMAL);

    setWarna(WARNA_UNGU);
    cout << "Masukan Nama "; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << " : ";
    string user; cin >> user;
    setWarna(WARNA_NORMAL);
    forLantai(0, Lantai){
        bool lanntaipass = true;
        forAP(0, DataBaseUser[i]){
        int range = stringToIntManual(WifiConnfigur[i][4]);
        bool pass = true;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][0] == user){
                    if(lanntaipass){
                        cout << "Lantai " << i+1 << ": \n";
                        lanntaipass = false;
                    }
                    if(pass){
                        cout << setw(10) << " " << "AP Ke-" << j+1 << ": \n";
                        pass = false;
                }
                    cout << setw(25) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                }
            }
        }
    }

    cout << endl;
    pauseScreen();
}

void cariBerdasarkanKegiatan(){
    setWarna(WARNA_HEADER);
    cout << "===== Searching (PerKategori Kegiatan) =====" << endl;
    setWarna(WARNA_NORMAL);

    cetakKatalog();
    setWarna(WARNA_UNGU);
    cout << "Masukan Nama Kegiatan"; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << " : ";
    string ket; cin >> ket;
    setWarna(WARNA_NORMAL);
    bool ada = false;
    forLantai(0, Lantai){
        bool lanntaipass = true;
        forAP(0, DataBaseUser[i]){
        int range = stringToIntManual(WifiConnfigur[i][4]);
        bool pass = false;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][1] == ket){
                    ada = true;
                    if(lanntaipass){
                        cout << "Lantai " << i+1 << ": \n";
                        lanntaipass = false;
                    }
                    if(pass){
                        cout << setw(10) << " " << "AP Ke-" << j+1 << ": \n";
                        pass = false;
                }
                    cout << setw(25) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                }
            }
        }
    }

    cout << endl;
    if(!ada){
        warnaText("Tidak Ada nama Kegiatan tersebut!\n", WARNA_CYAN);
    }

    pauseScreen();
}


//===============cetak==================
void cetakKategori(){
    if (WifiCategoryList[0][0].empty()) {
    cout << "Belum ada data kategori WiFi. Tambahkan di WifiCategory.txt\n";
    return;
    }
    cout << "============================================\n";
       fori(0, 10){
            cout << "Wifi Kategory ke-" << i+1 << ": \n";
            cout << "MerekWiFi : " << WifiCategoryList[i][0] << endl;
            cout << "AccessPoint : " << setw(50) << left << WifiCategoryList[i][1] <<endl;
            cout << "KecepatanWiFi : " << setw(50) << left << WifiCategoryList[i][2] << endl;
            cout << "KecepatanAP : " << setw(50) << left << WifiCategoryList[i][3]  << endl;
            cout << "MaxUser : " << setw(50) << left << WifiCategoryList[i][4] << endl;
            cout << "============================================\n";
            cout << endl;
    }
    cout << "============================================\n";
    cout << endl;
}

///==============MENNU 4=====================
void gantiAtauTambah(){
    Navbar();

    cout << "Menu pilihan: \n";
    cout << "1. Ganti Configure Wifi per Lantai. \n";
    cout << "2. Tambah user. \n";
    cout << "3. Hapus User. \n";
    cout << "4. Kosongkan pengunaan Wifi di AP yang ditentukan ("; setWarna(WARNA_MERAH); cout << "RISK!"; setWarna(WARNA_NORMAL); cout <<"). \n";
    cout << "5. Hapus Semua Pengguna Wifi ("; setWarna(WARNA_MERAH); cout << "RISK!"; setWarna(WARNA_NORMAL); cout <<"). \n";
    cout << "Menu yang dipilih: "; char p; cin >> p;

    switch(p){
    case '1':{
        ChangeConnfigure();
        pauseScreen();
        break;
    } case '2':{
        AddUser();
        break;
    } case '3':{
        RemoveUser();
        break;
    } case '4':{
        RemoveUserperLantai();
        break;
    } case '5':{
        char pil;
        cout << "Anda Yakin? Semua user akan "; setWarna(WARNA_MERAH); cout << "DIHAPUS"; setWarna(WARNA_NORMAL); cout <<"\n";
        cout << "(Y/N)"; cin >> pil;

        if(pil == 'y' || pil == 'Y'){
            forLantai(0, Lantai){
                forAP(0, DataBaseUser[i]){
                    int maxUser = stringToIntManual(WifiConnfigur[i][4]);
                    forUserPerAP(0, maxUser){
                        Pengguna[i][j][k][0] = "-";
                        Pengguna[i][j][k][1] = "-";
                    }
                }
            }
        Sleep(1200);
        SimpaDataUserPerAP();
        PageLoading2();
        PageUtama();
        }
        else{
        PageUtama();
        }
        break;
    }default:{
        cout << "Pilihan tidak tersedia!\n";
        pauseScreen();
        gantiAtauTambah();
        break;
    }
    }
}

void ChangeConnfigure(){
    int KeyLantai, KeyKatalog, keyAP; char lagi, gantiAP;
    setWarna(WARNA_HEADER);
    cout << "===== Change Configure Wifi Per-Lantai =====" << endl;
    setWarna(WARNA_NORMAL);

    cout << "Katalog Wifi yang tersedia: \n";
    cetakKategori();
    cout << endl;

    cout << "Max Lantai Perusahaan Anda: " ; warnaText(to_string(Lantai), WARNA_HIJAU); cout << endl;
    cout << "Pilih salah satu dari lantai Perusahann Anda. \n";
    do{
    cout << "Lantai yang Dipilih: "; setWarna(WARNA_KUNING); cin >> KeyLantai; setWarna(WARNA_NORMAL);
    cout << "Katageori Wifi Yang Dipilih: "; cin >> KeyKatalog;

    WifiConnfigur[KeyLantai-1][0] = WifiCategoryList[KeyKatalog-1][0]; //MerekWifi
    WifiConnfigur[KeyLantai-1][1] = WifiCategoryList[KeyKatalog-1][1]; //MerekAP
    WifiConnfigur[KeyLantai-1][2] = WifiCategoryList[KeyKatalog-1][2]; //KEcepatanWifi
    WifiConnfigur[KeyLantai-1][3] = WifiCategoryList[KeyKatalog-1][3]; //KecepatanAp
    WifiConnfigur[KeyLantai-1][4] = WifiCategoryList[KeyKatalog-1][4]; //MaxUser

    cout << "Ingin Merubah AP dilanntai ini? (Y/n) "; setWarna(WARNA_KUNING); cin >> gantiAP; setWarna(WARNA_NORMAL);

    if(gantiAP == 'y' || gantiAP == 'Y'){
        cout << "Total AP dilantai ini: "; warnaText(to_string(DataBaseUser[KeyLantai-1]),WARNA_HIJAU);
        cout << "\nUbah Menjadi: "; setWarna(WARNA_KUNING); cin >> keyAP; setWarna(WARNA_NORMAL);
        DataBaseUser[KeyLantai-1] = keyAP;
    }

    cout << "Configure Lantai Lagi? (Y/n) "; setWarna(WARNA_KUNING); cin >> lagi; setWarna(WARNA_NORMAL);
    }while(lagi == 'Y' || lagi == 'y');

    Sleep(500);
    SimpanDataWifiUser();
    PageLoading2();
    PageUtama();
}

void AddUser(){
    int keyLantai, keyAP;
    char pilih;
    string user;
    int keyGit;
    bool ulang = true;
    cout << endl;
    TampilUrut();
    cout << endl;

    do {
        do {
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);

        cetakKatalog();
        cout << "Masukan Nama User: ";
        cin >> user;

        do {
            if (!ulang) {
                cout << "Harus Sesuai Dengan Nomor Katalog (1-5)!\n";
            }
            cout << "Masukan Nomor Kegiatannya: ";
            cin >> keyGit;
            ulang = false;
        } while (keyGit < 1 || keyGit > MaxKat);

        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
        forUserPerAP(0, range) {
            if (Pengguna[keyLantai - 1][keyAP - 1][k][0] == "-" || Pengguna[keyLantai - 1][keyAP - 1][k][0] == "" || Pengguna[keyLantai - 1][keyAP - 1][k][0] == " ") {
                Pengguna[keyLantai - 1][keyAP - 1][k][0] = user;
                Pengguna[keyLantai - 1][keyAP - 1][k][1] = Kegiatan[keyGit - 1][0];
                break;
            }
        }

        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";
        cin >> pilih;
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    SimpanDataKecepatanAP();
    PageLoading2();
    PageUtama();
}


void RemoveUser(){
    int keyLantai, keyAP;
    char pilih;
    string user, kegiatan;
    int keyGit;
    bool ulang = true, cek = true;;

    cout << endl;
    TampilUrut();
    cout << endl;

    do {

        do {
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);

        while(true){
        cout << "Masukan Nama User "; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << ": ";
        cin >> user;

        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
        forUserPerAP(0, range) {
            if (Pengguna[keyLantai - 1][keyAP - 1][k][0] == user) {
                Pengguna[keyLantai - 1][keyAP - 1][k][0] = "-";
                Pengguna[keyLantai - 1][keyAP - 1][k][1] = "-";
                cek = false;
                break;
            }
            }
            if(!cek) break;
        }

        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";setWarna(WARNA_KUNING);
        cin >> pilih; setWarna(WARNA_NORMAL);
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    SimpanDataKecepatanAP();
    PageLoading2();
    PageUtama();
}

void RemoveUserperLantai(){
    int keyLantai, keyAP;
    char pilih;
    bool ulang = true;

    cout << endl;
    TampilUrut();
    cout << endl;

    do {

        do {setWarna(WARNA_KUNING);
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);


        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
            forUserPerAP(0, range) {
                    Pengguna[keyLantai - 1][keyAP - 1][k][0] = "-";
                    Pengguna[keyLantai - 1][keyAP - 1][k][1] = "-";
            }
        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";
        cin >> pilih;
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    PageLoading2();
    PageUtama();
}

///=========Page-New-User====================
void NewPenggunna(){
    if(!PunyaDatabase){
        system("cls");
        Navbar();
        cout << endl;
        cout << "Selamat Datang Di WIFI Analyze ^^\n";
        cout << "Akun Anda berhasil dibuat!\n";
        cout << "Silakan lanjutkan konfigurasi awal sistem jaringan perusahaan Anda.\n\n";

        cout << "============================================\n";\
        cout << "Setup Awal Jaringan Wifi Perusahaan\n";
        cout << "============================================\n\n";

        cout << "Berapa lantai yang dimiliki oleh perusahaan Anda? ";
        cin >> Lantai;

        cout << endl;

        fori(0, Lantai){
            cout << "> Jumlah AP (Accses Point) Lantai " << i+1 << ": ";
            cin >> DataBaseUser[i];
        }
        cout << endl;
        cout << "Selamat membangun sistem jaringan profesional Anda bersama WifiAnalyze!\n";
        PunyaDatabase = true;
        Sleep(1200);
        NewInputUnntukPenggunnaBaru();
    }
}

void NewInputUnntukPenggunnaBaru(){
    int MaxCategori = sizeof(WifiCategoryList) / sizeof(WifiCategoryList[0]);

    system("cls");
    Navbar();
    cout << endl;
    cout << "Selamat Datang Di WIFI Analyze ^^\n";
    cout << "Wifi dan AP Kategori yang Tersedia: \n\n";
    cetakKategori();

    cout << "Masukan Kategory Wifi Setiap Lantai: (Pilih Sesuai Dengan Urutan Wifi Saja)\n";
    fori(0, Lantai){
        int pilih;
        do{
        cout << "Lantai ke-" << i+1 <<": ";
        cin >> pilih; pilih--;

        if(pilih > MaxCategori || pilih < 0){
            cout << "Pilihan Tidak Tersedia! \n";
            Sleep(500);}
        }while (pilih < 0 || pilih >= MaxCategori);

        //Masukinn Ke Array WifiConnfigur
        WifiConnfigur[i][0] = WifiCategoryList[pilih][0]; //MerekWifi
        WifiConnfigur[i][1] = WifiCategoryList[pilih][1]; //MerekAP
        WifiConnfigur[i][2] = WifiCategoryList[pilih][2]; //KEcepatanWifi
        WifiConnfigur[i][3] = WifiCategoryList[pilih][3]; //KecepatanAp
        WifiConnfigur[i][4] = WifiCategoryList[pilih][4]; //MaxUser

        //Masukinn Ke Array ApSpeed
        forAP(0, DataBaseUser[i]){
            APSpeed[i][j][0] = WifiCategoryList[pilih][3];
            APSpeed[i][j][1] = "None";

            forUserPerAP(0, 1){
                Pengguna[i][j][k][0] = "Belum4daIs1nyaMasihK0SONG";
                Pengguna[i][j][k][1] = " ";
            }
        }

    }
    SimpanDataWifiUser();SimpanDataKecepatanAP(); SimpaDataUserPerAP();
    system("Pause");
}

void SimpanDataWifiUser() { //Nulis Ulang makannya nanti bakal ke reset data nya
    ofstream file(pathFile1User);

    file << "################################" << endl;
    file << "Jumlah Lantai = " << Lantai << endl;
    fori(0, Lantai) {
        file << "> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;
    }
    file << "################################" << endl << endl;

    fori(0, Lantai) {
        file << "================================" << endl;
        file << "Lantai " << i + 1 << ":" << endl;
        file << "MerekWiFi    : " << WifiConnfigur[i][0] << endl;
        file << "AccessPoint  : " << WifiConnfigur[i][1] << endl;
        file << "KecepatanWiFi: " << WifiConnfigur[i][2] << endl;
        file << "KecepatanAP  : " << WifiConnfigur[i][3] << endl;
        file << "MaxUser      : " << WifiConnfigur[i][4] << endl;
        file << "================================" << endl << endl;
    }

    file.close();
    SimpanDataKecepatanAP();
}

void SimpanDataKecepatanAP(){
    ofstream file(pathFile3User);
    string temp;
    file << "=================================" << endl;
    file << "Total Lantai = " << Lantai << endl;
    file << "=================================" << endl << endl;
    double sementaraGitulah;
    forLantai(0, Lantai){
        forAP(0, DataBaseUser[i]){
            APSpeed[i][j][0] = WifiConnfigur[i][3];
        }
    }
    forLantai(0, Lantai){
        file << ">> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;
        forAP(0, DataBaseUser[i]){
            file << setw(10) << " " << "AccessPoint = " << APSpeed[i][j][0] << " || " << "Kecepatan User = " << APSpeed[i][j][1] << endl;
        }
        file << endl << endl;
    }
    file << "=================================" << endl << endl;
    file.close();
}

void SimpaDataUserPerAP() {
    ofstream file(pathFile2User);
    file << "=================================" << endl;
    file << "Total Lantai = " << Lantai << endl;
    file << "=================================" << endl << endl;

    forLantai(0, Lantai) {
        file << ">> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;

        forAP(0, DataBaseUser[i]) {
            int maxUser = stringToIntManual(WifiConnfigur[i][4]); // pakai konversi manual kamu
            file << setw(10) << " " << "AccessPoint = " << j + 1 << endl;

            bool adaUser = false;

            forUserPerAP(0, maxUser) {
                string& nama = Pengguna[i][j][k][0];
                string& kegiatan = Pengguna[i][j][k][1];

                if (nama == "-" || nama == "" || nama == " " || nama == "Belum4daIs1nyaMasihK0SONG") continue;

                adaUser = true;
                file << setw(15) << " " << "Nama = " << nama << " || Kegiatan = " << kegiatan << endl;
            }

            if (!adaUser) {
                file << setw(15) << " " << "[None]" << endl;
            }

            file << endl;
        }

        file << endl << endl;
    }

    file << "=================================" << endl << endl;
    file.close();
}


//=======Page Pilihan Dari Menu Utama========
void cetakKonfigurasWifiUser() {
    system("cls"); // Typo kamu tulis 'sytem'
    Navbar();

    fori(0, Lantai) {
        cout << "===========================\n";
        setWarna(WARNA_LOADING);
        cout << "Konfigurasi WiFi - Lantai " << i + 1 << endl;
        setWarna(WARNA_NORMAL);
        cout << "===========================\n";
        cout << "Merek WiFi     : " << WifiConnfigur[i][0] << endl;
        cout << "Access Point   : " << WifiConnfigur[i][1] << endl;
        cout << "Kecepatan WiFi : " << WifiConnfigur[i][2] << endl;
        cout << "Kecepatan AP   : " << WifiConnfigur[i][3] << endl;
        cout << "MAX User       : " << WifiConnfigur[i][4] << endl;
        cout << endl;
    }

    pauseScreen();
    PageUtama();
}
//==========Tambahan===========
void init() {
    reconDatabase();
    KegiatanData();
    WifikonfigurasiList();
}

void CekSSemuaDataUser(){
    dataUser();
    cekbase();
    CekDatabaseUser();
    KegiatanData();

    //====Buat-Masukin Data Ke array===
    if(PunyaDatabase){
        WifiConnfigureIN();
        PenggunaIN();
        APSpeedIN();

        //Cloning Data
        CloningData();
        konfigurasiKecepatanDenganUser();
    }

}

void pauseScreen() {
    cout << "Tekan tombol untuk kembali..."; getch();
}

///============Cloing===========
void CloningData(){
    forLantai(0, Lantai){
        int maxUser = stoi(WifiConnfigur[i][4]);
        forAP(0, DataBaseUser[i]){

            //=======UtukKonnfigurasi Wifi setiap lantai=======
            forz(0, 5){CloneWifiConnfigur[i][z] = WifiConnfigur[i][z];}
            forUserPerAP(0, maxUser){
                //===========Utuk speedAP=========
                CloneAPSpeed[i][j][0] = APSpeed[i][j][0];
                CloneAPSpeed[i][j][1] = APSpeed[i][j][1];

                //=========Untuk User yanng terkonnekasi========
                ClonePengguna[i][j][k][0] = Pengguna [i][j][k][0];
                ClonePengguna[i][j][k][1] = Pengguna [i][j][k][1];
            }
        }
    }
}

int main(){
    KegiatanIN();
    init();
    PageAwal();
    return 0;
}
