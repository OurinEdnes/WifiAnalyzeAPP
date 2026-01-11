#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <direct.h>

using namespace std;

#define fori(a, b) for(int i = (a); i < (b); i++)
#define forj(a, b) for(int j = (a); j < (b); j++)
#define fork(a, b) for(int k = (a); k < (b); k++)
#define forl(a, b) for(int l = (a); l < (b); l++)


//======Penginnisialisasi Warna MEnggunakan Define Untuk Teks======
#define WARNA_HITAM   0
#define WARNA_BIRU    1
#define WARNA_HIJAU   2
#define WARNA_CYAN    3
#define WARNA_MERAH   4
#define WARNA_UNGU    5
#define WARNA_KUNING  6
#define WARNA_PUTIH   7

#define WARNA_HEADER  WARNA_CYAN
#define WARNA_ERROR   WARNA_MERAH
#define WARNA_INPUT   WARNA_KUNING
#define WARNA_LOADING WARNA_HIJAU
#define WARNA_LABEL   WARNA_UNGU
#define WARNA_NORMAL  WARNA_PUTIH

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
    int Lantai;
//=======================

//======Function=====
void Navbar();
void InterfaceAwal();
void Login();
void SignUp();
bool LoginProtection();
bool SignProtect();
void DirectP();
//=======Page========
void PageAwal();
void PageLoading();
void PageUtama();
void NewPenggunna();
void NewInputUnntukPenggunnaBaru();
void cetakKategori();
//===================

//======Folder-PerUser=====
void dataUser();
void cekbase();
void CekDatabaseUser();
void WifikonfigurasiList();
void KegiatanData();
void CekSSemuaDataUser();

void WifiConnfigureIN();
void PenggunaIN();
void APSpeedIN();
void DataBaseUserIN();

//====Set-Warnna====
void setWarna(int kodeWarna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kodeWarna);
}

//====Array-Save-Data-Buat-User====
int DataBaseUser[MaxLantai];
string Pengguna[MaxLantai][MaxAp_Per_lantai][MaxUser][2]; //2 Buat Nama Pengguna dan Kegiatan yang dilakukan
string APSpeed[MaxLantai][MaxAp_Per_lantai];
string WifiConnfigur[MaxLantai][MaxAp_Per_lantai][3]; //3 buat deklarasi Nama wifi, kecepatann wwifi, sama total penngguna
string Kegiatan[5][2];
string WifiCategoryList[10][5];


//====Array-Searching===
string findAP[MaxLantai][MaxAp_Per_lantai];


//====Cek-Database-User====
void reconDatabase(){
    fstream DataBase("User-DataBase.txt", ios::in);
    if(!DataBase){
        ofstream make("User-DataBase.txt");
        make.close();
    }
    DataBase.close();
}
//========================

void Navbar(){
    cout << "============================\n";
    cout << "|---"; setWarna(WARNA_HEADER); cout << "Wifi Analyze Company"; setWarna(WARNA_NORMAL); cout<< "---|\n";
    cout << "============================\n\n";
}

//====Page Awal====
void PageAwal(){
    system("cls");
    Navbar();
    InterfaceAwal();
}

void InterfaceAwal(){
    cout << "Selamat Datang... \nHarap Masuk terlebih Dahulu!\n\n";
    cout << "Menu Pilihan: \n";
    cout << "1. Login. \n";
    cout << "2. SignUp. \n";
    cout << "Pilih Menu: ";
    int req; cin >> req;

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
    cout << "username: ";
    cin >> UserName;
    cout << "Password: ";
    cin >> Password;
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
        if(sameboth == 2){
            same = true;
            break;
        }

        if(base.find("username ##") != string::npos){
            string usernameBase = base.substr(base.find("##") + 3);
            if(UserName == usernameBase){
                sameboth++;
            }
        } else if(base.find("password ##") != string::npos){
            string PasswordBase = base.substr(base.find("##") + 3);
            if(PasswordBase == Password){
                sameboth++;
            }
        } else if(base.find("==============") != string::npos){
            sameboth = 0;
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
    cin >> Password;
    if(SignProtect()){
        setWarna(3);
        cout <<"\nAkun Berhasil Dibuat!\n";
        setWarna(7);
        cout <<"Harap Loginn Lagi Terlebih Dahulu";
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
        if(base.find("username ##") != string::npos){
            string usernameBase = base.substr(base.find("##") + 3);
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

//=======Page Loadig=======
void PageLoading(){
    fori(0, 3){
    system("cls");
    cout << "Loading";

        for(int i = 0; i < 3; i++){
            cout << ".";
            cout.flush();
            Sleep(500);
        }
    }
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
}

void KegiatanData(){
    fstream file("DaftarKegiatan.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(base.find("Nama       =") != string::npos){
            Kegiatan[i][0] = base.substr(base.find("=") + 2);
        } else if(base.find("Kecepatan  =") != string::npos){
            Kegiatan[i][1] = base.substr(base.find('=') + 2);
        } else if(base.find("================================") != string::npos){
            i++;
        }
    }
}

void WifikonfigurasiList(){
    fstream file("WifiCategory.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(base.find("MerekWiFi    :") != string::npos){
            WifiCategoryList[i][0] = base.substr(base.find(':') + 2);
        } else if(base.find("AccessPoint  :") != string::npos){
            WifiCategoryList[i][1] = base.substr(base.find(':') + 2);
        } else if(base.find("KecepatanWiFi:") != string::npos){
            WifiCategoryList[i][2] = base.substr(base.find(':') + 2);
        } else if(base.find("KecepatanAP  :") != string::npos){
            WifiCategoryList[i][3] = base.substr(base.find(':') + 2);
        } else if(base.find("MaxUser      :") != string::npos){
            WifiCategoryList[i][4] = base.substr(base.find(':') + 2);
        } else if(base.find("===================================") != string::npos){
            i++;
        }
    }
}

void CekDatabaseUser(){
    string connstruct = path + "/WifiConfigure.txt";
    fstream Data(connstruct, ios::in);
    string line;

    while(getline(Data, line)){
        if(line.find("A7K9-X2ZQ") != string::npos){
            PunyaDatabase = false;
            break;
        } else{
            PunyaDatabase = true;
        }
    }

}

void CekSSemuaDataUser(){
    dataUser();
    cekbase();
    CekDatabaseUser();
    KegiatanData();

    //====Buat-Masukin Data Ke array===
    if(PunyaDatabase){
        //WifiConnfigureIN();
        //PenggunaIN();
        //APSpeedIN();
        //DataBaseUserIN();
    }
}


//========Page Utama==========
void PageUtama(){
    NewPenggunna();
    system("cls");

    Navbar();
    cout << "Pilihan Menu Yang Tersedia: \n";
    cout << "1. Cek Kecepatan Accses Point di setiap Lantai. \n";
    cout << "2. Cek Nama wifi dan Penggunanya. \n";
    cout << "3. Tambah Kondisi (lantai/ganti Wifi). \n";
    cout << "Menu yang Dipilih: "; char pilih; cin >> pilih;

    switch(pilih){
    case '1':

        break;
    case '2':

        break;
    case '3':

        break;
    default:

        break;
    }
}

void cetakKategori(){
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
    cout << endl;
}

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

    }
    system("Pause");

}





int main(){
    reconDatabase();KegiatanData();WifikonfigurasiList();

    PageAwal();

    //char p[6] = "Hello";
    //mkdir(p);


    //string dir = "Hello";
    //string cs = dir + "/test.txt";
    //fstream Data(cs, ios::in);
    //string base;
    //while(getline(Data, base)){
      //cout << base;
    //}
    //Data.close();
    //const char* poi = "Halloo0o0";
    //mkdir(poi);

    return 0;
}
