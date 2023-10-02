#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

string getPasswordInput();

// Struktur data untuk pemesanan lapangan
struct Pemesanan {
    string nama;
    int hari;
    int jam;
    Pemesanan* next;
};

// Fungsi untuk menampilkan ketentuan pemeseanan
void tampilkanKetentuanPemesanan() {
    cout << "=============================================================" << endl;
    cout << "=                    Ketentuan Pemesanan                    =" << endl;
    cout << "=============================================================" << endl;
    cout << "1. Pemesanan hanya bisa dilakukan pada jam 15:00-23:00." << endl;
    cout << "2. Pemesanan dapat dilakukan untuk hari Senin-Minggu." << endl;
    cout << "3. Pemesanan harus dilakukan melalui WA." << endl;
    cout << "4. Durasi bermain yaitu 1 jam" << endl;
	cout << "5. Setiap pengguna hanya dapat memesan untuk jam yang tepat." << endl;
    cout << "   misal jam 15.00 bukan 15.15/15.30 karena durasi hanya 1 jam." << endl;
    cout << "=============================================================" << endl;
    cout << endl;
}

// Fungsi untuk melihat pemesanan berdasarkan nama
void lihatPemesananBerdasarkanNama(Pemesanan* head, const string& namaPencarian) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan lapangan." << endl;
        return;
    }
    
    cout << "1: Senin, 2: Selasa, 3: Rabu, 4: Kamis, 5: Jumat, 6: Sabtu, 7: Minggu" << endl;
    cout << "======== Daftar Pemesanan ========" << endl;

    bool found = false;
    Pemesanan* current = head;
    while (current != nullptr) {
        if (current->nama == namaPencarian) {
            cout << "Nama: " << current->nama << endl;
        
            // Mengonversi angka hari menjadi nama hari
            string namaHari;
            switch (current->hari) {
                case 1:
                    namaHari = "Senin";
                    break;
                case 2:
                    namaHari = "Selasa";
                    break;
                case 3:
                    namaHari = "Rabu";
                    break;
                case 4:
                    namaHari = "Kamis";
                    break;
                case 5:
                    namaHari = "Jumat";
                    break;
                case 6:
                    namaHari = "Sabtu";
                    break;
                case 7:
                    namaHari = "Minggu";
                    break;
                default:
                    namaHari = "Hari Tidak Valid";
                    break;
            }
            
            cout << "Hari: " << namaHari << endl;
            cout << "Jam: " << current->jam << endl;
            cout << endl;

            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Tidak ditemukan pemesanan dengan nama " << namaPencarian << "." << endl;
    }
}

// Fungsi untuk memesan lapangan
void pesanLapangan(Pemesanan*& head) {
    string nama;
    int hari, jam;

    cout << endl << "===================================" << endl;
    cout << "Masukkan nama Anda: ";
    getline(cin, nama);

    cout << "1: Senin, 2: Selasa, 3: Rabu, 4:Kamis, 5:Jumat, 6:Sabtu, 7:Minggu" << endl;
	cout << "Masukkan hari sesuai kode (1-7): ";
    cin >> hari;

    cout << "Masukkan jam (15-23): ";
    cin >> jam;

    // Cek ketersediaan lapangan pada hari dan jam yang sama
    Pemesanan* current = head;
    while (current != nullptr) {
        if (current->hari == hari && current->jam == jam) {
            cout << endl << "\tMaaf, lapangan sudah dipesan pada hari dan jam tersebut." << endl;
            cout << "===================================" << endl;

            // Membersihkan input buffer
            cin.ignore();
            cout << endl;
            return;
        }
        current = current->next;
    }

    // Mengecek batasan rentang jam (15-23)
    if (jam < 15 || jam > 23) {
        cout << endl << "\tMaaf, jam yang Anda masukkan tidak valid. Jam harus antara 15 hingga 23." << endl;
        cout << "===================================" << endl;

        // Membersihkan input buffer
        cin.ignore();
        cout << endl;
        return;
    }

    // Membuat node baru untuk pemesanan
    Pemesanan* newNode = new Pemesanan;
    newNode->nama = nama;
    newNode->hari = hari;
    newNode->jam = jam;
    newNode->next = nullptr;

    // Memeriksa apakah linked list kosong
    if (head == nullptr) {
        head = newNode;
    } else {
        // Menemukan posisi tempat node baru akan disisipkan
        current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    cout << endl << "\tPemesanan berhasil!" << endl;
    cout << "===================================" << endl;

    // Membersihkan input buffer
    cin.ignore();
    cout << endl;
}

// Fungsi untuk melihat pemesanan
void lihatPemesanan(Pemesanan* head) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan lapangan." << endl;
        return;
    }
    
    cout << "1: Senin, 2: Selasa, 3: Rabu, 4: Kamis, 5: Jumat, 6: Sabtu, 7: Minggu" << endl;
    cout << "======== Daftar Pemesanan ========" << endl;
    
    // Menghitung jumlah pemesanan
    int count = 0;
    Pemesanan* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    
    // Membuat array untuk menyimpan pemesanan
    Pemesanan** pemesananArr = new Pemesanan*[count];
    
    // Mengisi array dengan pemesanan
    current = head;
    for (int i = 0; i < count; i++) {
        pemesananArr[i] = current;
        current = current->next;
    }
    
    // Melakukan bubble sort berdasarkan hari dan jam
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // Membandingkan hari
            if (pemesananArr[j]->hari > pemesananArr[j + 1]->hari) {
                // Tukar posisi jika hari lebih besar
                Pemesanan* temp = pemesananArr[j];
                pemesananArr[j] = pemesananArr[j + 1];
                pemesananArr[j + 1] = temp;
            }
            // Jika hari sama, bandingkan jam
            else if (pemesananArr[j]->hari == pemesananArr[j + 1]->hari &&
                     pemesananArr[j]->jam > pemesananArr[j + 1]->jam) {
                // Tukar posisi jika jam lebih besar
                Pemesanan* temp = pemesananArr[j];
                pemesananArr[j] = pemesananArr[j + 1];
                pemesananArr[j + 1] = temp;
            }
        }
    }
    
    // Menampilkan hasil sorting
    for (int i = 0; i < count; i++) {
        cout << "Nama: " << pemesananArr[i]->nama << endl;
        
        // Mengonversi angka hari menjadi nama hari
        string namaHari;
        switch (pemesananArr[i]->hari) {
            case 1:
                namaHari = "Senin";
                break;
            case 2:
                namaHari = "Selasa";
                break;
            case 3:
                namaHari = "Rabu";
                break;
            case 4:
                namaHari = "Kamis";
                break;
            case 5:
                namaHari = "Jumat";
                break;
            case 6:
                namaHari = "Sabtu";
                break;
            case 7:
                namaHari = "Minggu";
                break;
            default:
                namaHari = "Hari Tidak Valid";
                break;
        }
        
        cout << "Hari: " << namaHari << endl;
        cout << "Jam: " << pemesananArr[i]->jam << endl;
        cout << endl;
    }
    
    // Menghapus array
    delete[] pemesananArr;
}



// Fungsi untuk menghapus semua pemesanan
void hapusSemuaPemesanan(Pemesanan*& head) {
    Pemesanan* current = head;
    while (current != nullptr) {
        Pemesanan* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << "Semua pemesanan lapangan telah dihapus." << endl;
}

// Fungsi untuk menghapus pemesanan berdasarkan hari dan jam
void hapusPemesanan(Pemesanan*& head, int hari, int jam) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan lapangan." << endl;
        return;
    }

    Pemesanan* current = head;
    Pemesanan* previous = nullptr;

    // Jika node yang akan dihapus berada di awal linked list
    if (current->hari == hari && current->jam == jam) {
        head = current->next;
        delete current;
        cout << "Pemesanan pada hari " << hari << " jam " << jam << " telah dihapus." << endl;
        return;
    }

    // Mencari node yang akan dihapus
    while (current != nullptr) {
        if (current->hari == hari && current->jam == jam) {
            previous->next = current->next;
            delete current;
            cout << "Pemesanan pada hari " << hari << " jam " << jam << " telah dihapus." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    // Jika node tidak ditemukan
    cout << "Pemesanan pada hari " << hari << " jam " << jam << " tidak ditemukan." << endl;
}

// Fungsi untuk mengedit pemesanan berdasarkan hari dan jam
void editPemesanan(Pemesanan*& head, int hari, int jam) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan lapangan." << endl;
        return;
    }

    Pemesanan* current = head;

    // Mencari node yang akan diedit
    while (current != nullptr) {
        if (current->hari == hari && current->jam == jam) {
            cout << "Pemesanan pada hari " << hari << " jam " << jam << " ditemukan." << endl;

            string nama;
            int newHari, newJam;

            cout << "Masukkan nama baru: ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan hari baru (1-7): ";
            cin >> newHari;

            cout << "Masukkan jam baru (15-23): ";
            cin >> newJam;

            // Mengecek ketersediaan lapangan pada hari dan jam yang baru
            Pemesanan* checkAvailability = head;
            while (checkAvailability != nullptr) {
                if (checkAvailability != current && checkAvailability->hari == newHari && checkAvailability->jam == newJam) {
                    cout << "Maaf, lapangan sudah dipesan pada hari dan jam tersebut." << endl;
                    return;
                }
                checkAvailability = checkAvailability->next;
            }

            // Mengecek batasan rentang jam (15-23)
            if (newJam < 15 || newJam > 23) {
                cout << "Maaf, jam yang Anda masukkan tidak valid. Jam harus antara 15 hingga 23." << endl;
                return;
            }

            // Mengedit data pemesanan
            current->nama = nama;
            current->hari = newHari;
            current->jam = newJam;

            cout << "Pemesanan berhasil diubah!" << endl;
            return;
        }
        current = current->next;
    }

    // Jika node tidak ditemukan
    cout << "Pemesanan pada hari " << hari << " jam " << jam << " tidak ditemukan." << endl;
}

// Struktur data untuk login user dan admin
struct User {
    string username;
    string password;
    User* next;
};

// Global variables
Pemesanan* head = nullptr;
User* userList = nullptr;
User* adminList = nullptr;

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* newUser = new User;
    newUser->username = username;
    newUser->password = password;
    newUser->next = nullptr;

    if (userList == nullptr) {
        userList = newUser;
    } else {
        User* current = userList;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }

    cout << "User registered successfully!" << endl;
}

// Function to perform user login
bool userLogin() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
	
	password = getPasswordInput();
    cout << "Password: " << password << endl;
    
    User* current = userList;
    while (current != nullptr) {
        if (current->username == username && current->password == password) {
            cout << "User login successful!" << endl;
            return true;
        }
        current = current->next;
    }

    cout << "Invalid username or password. User login failed." << endl;
    return false;
}

// Function to perform admin login
bool adminLogin() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";

	password = getPasswordInput();
    cout << "Password: " << password << endl;
    
    User* current = adminList;
    while (current != nullptr) {
        if (current->username == username && current->password == password) {
            cout << "Admin login successful!" << endl;
            return true;
        }
        current = current->next;
    }

    cout << "Invalid username or password. Admin login failed." << endl;
    return false;
}

void tampilkanMenuAdmin() {
    int pilihan;
    do {
        cout << "===================================" << endl;
        cout << "=         Galactic Futsal         =" << endl;
        cout << "=  Jln. Jalan No.31 Klaten Utara  =" << endl;
        cout << "=         WA 0851234123499        =" << endl;
        cout << "===================================" << endl;
        cout << "1. Tambah Pesanan" << endl;
        cout << "2. Lihat Pemesanan" << endl;
        cout << "3. Hapus Semua Pemesanan" << endl;
        cout << "4. Hapus Pemesanan Berdasarkan Hari dan Jam" << endl;
        cout << "5. Edit Pemesanan Berdasarkan Hari dan Jam" << endl;
        cout << "6. Tambah User" << endl;
        cout << "7. Cari Pemesanan Berdasarkan Nama" << endl;
        cout << "8. Keluar" << endl;
        cout << "Pilih menu (1-8): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cin.ignore();
                pesanLapangan(head);
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                lihatPemesanan(head);
                system("pause");
                system("cls");
                break;
            case 3:
                hapusSemuaPemesanan(head);
                system("pause");
                system("cls");
                break;
            case 4:
                int hapusHari, hapusJam;
                cout << "Masukkan hari pemesanan yang akan dihapus (1-7): ";
                cin >> hapusHari;
                cout << "Masukkan jam pemesanan yang akan dihapus (15-23): ";
                cin >> hapusJam;
                hapusPemesanan(head, hapusHari, hapusJam);
                system("pause");
                system("cls");
                break;
            case 5:
                int editHari, editJam;
                cout << "Masukkan hari pemesanan yang akan diedit (1-7): ";
                cin >> editHari;
                cout << "Masukkan jam pemesanan yang akan diedit (15-23): ";
                cin >> editJam;
                editPemesanan(head, editHari, editJam);
                system("pause");
                system("cls");
                break;
            case 6:
            	system("cls");
                registerUser();
                system("pause");
                system("cls");
                break;
            case 7:
            	{
            	cin.ignore();
                string namaPencarian;
                cout << "Masukkan nama yang ingin dicari: ";
                getline(cin, namaPencarian);
                system("cls");
                lihatPemesananBerdasarkanNama(head, namaPencarian);
                system("pause");
                system("cls");
                break;
				} 
            case 8:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << endl;
    } while (pilihan != 8);
}

void tampilkanMenuUser() {
    int pilihan;
    system("cls");
    do {
        cout << "===================================" << endl;
        cout << "=         Galactic Futsal         =" << endl;
        cout << "=  Jln. Jalan No.31 Klaten Utara  =" << endl;
        cout << "=         WA 0851234123499        =" << endl;
        cout << "===================================" << endl;
        cout << "1. Lihat Pemesanan" << endl;
        cout << "2. Cari Pemesanan Berdasarkan Nama" << endl;
        cout << "3. Ketentuan Pemesanan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                lihatPemesanan(head);
                system("pause");
                system("cls");
                break;
            case 2:
                {
				cin.ignore();
                string namaPencarian;
                cout << "Masukkan nama yang ingin dicari: ";
                getline(cin, namaPencarian);
                system("cls");
                lihatPemesananBerdasarkanNama(head, namaPencarian);
                system("pause");
                system("cls");
                break;
            	}
            case 3:
            	system("cls");
            	tampilkanKetentuanPemesanan();
            	system("pause");
                system("cls");
            	break;
            case 4:
                cout << "Terima kasih!" << endl;
                system("pause");
                system("cls");
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << endl;
    } while (pilihan != 4);
}


// Function to display the main menu
void displayMainMenu() {
    int pilihan;
    do {
        cout << "===================================" << endl;
        cout << "=         Galactic Futsal         =" << endl;
        cout << "=  Jln. Jalan No.31 Klaten Utara  =" << endl;
        cout << "=         WA 0851234123499        =" << endl;
        cout << "===================================" << endl;
        cout << "1. User Login" << endl;
        cout << "2. Admin Login" << endl;
        cout << "3. Register User" << endl;
        cout << "4. Exit" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                if (userLogin()) {
                	system("cls");
                    tampilkanMenuUser();
                }
                break;
            case 2:
                if (adminLogin()) {
                	system("cls");
                    tampilkanMenuAdmin();
                }
                break;
            case 3:
            	system("cls");
            	registerUser();
            	system("pause");
                system("cls");
            	break;
            case 4:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                exit(0);
        }

        cout << endl;
    } while (pilihan != 4);
}

// Fungsi untuk menyimpan data pemesanan ke file
void simpanPemesananKeFile(Pemesanan* head) {
    ofstream file("pemesanan.txt");
    if (file.is_open()) {
        Pemesanan* current = head;
        while (current != nullptr) {
            file << current->nama << "," << current->hari << "," << current->jam << endl;
            current = current->next;
        }
        file.close();
        cout << "Data pemesanan telah disimpan ke file pemesanan.txt." << endl;
    } else {
        cout << "Gagal membuka file pemesanan.txt." << endl;
    }
}

// Fungsi untuk membaca data pemesanan dari file
Pemesanan* bacaPemesananDariFile() {
    Pemesanan* head = nullptr;
    ifstream file("pemesanan.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string nama, hariStr, jamStr;
            int hari, jam;

            getline(ss, nama, ',');
            getline(ss, hariStr, ',');
            getline(ss, jamStr, ',');

            hari = stoi(hariStr);
            jam = stoi(jamStr);

            Pemesanan* newNode = new Pemesanan;
            newNode->nama = nama;
            newNode->hari = hari;
            newNode->jam = jam;
            newNode->next = nullptr;

            // Memeriksa apakah linked list kosong
            if (head == nullptr) {
                head = newNode;
            } else {
                // Menemukan posisi tempat node baru akan disisipkan
                Pemesanan* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file pemesanan.txt." << endl;
    }
    return head;
}

// Fungsi untuk menampilkan data pemesanan dari linked list ke layar
void tampilkanPemesananKeFile(Pemesanan* head) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan lapangan." << endl;
        return;
    }

    cout << "1: Senin, 2: Selasa, 3: Rabu, 4:Kamis, 5:Jumat, 6:Sabtu, 7:Minggu" << endl;
    cout << "======== Daftar Pemesanan ========" << endl;
    Pemesanan* current = head;
    while (current != nullptr) {
        cout << "Nama: " << current->nama << endl;
        cout << "Hari: " << current->hari << endl;
        cout << "Jam: " << current->jam << endl;
        cout << endl;
        current = current->next;
    }
}

// Fungsi untuk menyimpan data user ke file
void simpanUserKeFile(User* userList) {
    ofstream file("user.txt");
    if (file.is_open()) {
        User* current = userList;
        while (current != nullptr) {
            file << current->username << "," << current->password << endl;
            current = current->next;
        }
        file.close();
        cout << "Data user telah disimpan ke file user.txt." << endl;
    } else {
        cout << "Gagal membuka file user.txt." << endl;
    }
}

// Fungsi untuk membaca data user dari file
User* bacaUserDariFile() {
    User* userList = nullptr;
    ifstream file("user.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;

            getline(ss, username, ',');
            getline(ss, password, ',');

            User* newUser = new User;
            newUser->username = username;
            newUser->password = password;
            newUser->next = nullptr;

            // Memeriksa apakah linked list kosong
            if (userList == nullptr) {
                userList = newUser;
            } else {
                // Menemukan posisi tempat node baru akan disisipkan
                User* current = userList;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newUser;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file user.txt." << endl;
    }
    return userList;
}

// Fungsi untuk menampilkan data user dari linked list ke layar
void tampilkanUserKeFile(User* userList) {
    if (userList == nullptr) {
        cout << "Belum ada data user." << endl;
        return;
    }

    cout << "======== Daftar User ========" << endl;
    User* current = userList;
    while (current != nullptr) {
        cout << "Username: " << current->username << endl;
        cout << "Password: " << current->password << endl;
        cout << endl;
        current = current->next;
    }
}

string getPasswordInput() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch(); // Read a single character without echoing it

        if (ch == 13) { // 13 is the ASCII value for the enter key
            cout << endl;
            break;
        } else if (ch == 8) { // 8 is the ASCII value for the backspace key
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move the cursor back, overwrite the character with a space, and move the cursor back again
            }
        } else {
            password.push_back(ch);
            cout << "*";
        }
    }

    return password;
}

int main() {
    head = bacaPemesananDariFile(); // Membaca data pemesanan dari file
    userList = bacaUserDariFile(); // Membaca data user dari file
    
	// Create an admin account
    User* admin = new User;
    admin->username = "admin";
    admin->password = "admin123";
    admin->next = nullptr;
    adminList = admin; 
    displayMainMenu();
    
    simpanPemesananKeFile(head); // Menyimpan data pemesanan ke file sebelum program berakhir
    simpanUserKeFile(userList); // Menyimpan data user ke file sebelum program berakhir

    return 0;
}
