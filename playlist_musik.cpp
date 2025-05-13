#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// ============================
// APLIKASI 1: Playlist Musik (Doubly Linked List)
// ============================

struct Lagu {
    string judul;
    Lagu* next;
    Lagu* prev;
};

Lagu* head = NULL;
Lagu* tail = NULL;
Lagu* current = NULL;

void tambahLagu(string judul) {
    Lagu* baru = new Lagu;
    baru->judul = judul;
    baru->next = NULL;
    baru->prev = NULL;

    if (!head) {
        head = tail = current = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    cout << "Lagu \"" << judul << "\" ditambahkan.\n";
}

void hapusLagu(string judul) {
    Lagu* temp = head;
    while (temp) {
        if (temp->judul == judul) {
            if (temp->prev) temp->prev->next = temp->next;
            else head = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            else tail = temp->prev;
            delete temp;
            cout << "Lagu dihapus.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Lagu tidak ditemukan.\n";
}

void nextLagu() {
    if (current && current->next) {
        current = current->next;
        cout << "Sekarang memutar: " << current->judul << "\n";
    } else {
        cout << "Tidak ada lagu berikutnya.\n";
    }
}

void prevLagu() {
    if (current && current->prev) {
        current = current->prev;
        cout << "Sekarang memutar: " << current->judul << "\n";
    } else {
        cout << "Tidak ada lagu sebelumnya.\n";
    }
}

void tampilkanPlaylist() {
    Lagu* temp = head;
    cout << "Playlist Saat Ini:\n";
    while (temp) {
        cout << "- " << temp->judul << "\n";
        temp = temp->next;
    }
}

// ============================
// APLIKASI 2: Antrian Rumah Sakit (Queue)
// ============================

struct Pasien {
    string nama;
    Pasien* next;
};

Pasien* front = NULL;
Pasien* rear = NULL;

void tambahPasien(string nama) {
    Pasien* baru = new Pasien;
    baru->nama = nama;
    baru->next = NULL;

    if (!rear) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }
    cout << "Pasien \"" << nama << "\" ditambahkan ke antrian.\n";
}

void panggilPasien() {
    if (!front) {
        cout << "Antrian kosong.\n";
        return;
    }
    Pasien* temp = front;
    front = front->next;
    if (!front) rear = NULL;
    cout << "Memanggil pasien: " << temp->nama << "\n";
    delete temp;
}

void tampilkanAntrian() {
    Pasien* temp = front;
    cout << "Antrian Pasien Saat Ini:\n";
    while (temp) {
        cout << "- " << temp->nama << "\n";
        temp = temp->next;
    }
}

void resetAntrian() {
    while (front) panggilPasien();
    cout << "Semua antrian direset.\n";
}

// ============================
// MENU UTAMA
// ============================

void menu() {
    string input;
    int pilihan = -1;

    do {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Hapus Lagu\n";
        cout << "3. Next Lagu\n";
        cout << "4. Prev Lagu\n";
        cout << "5. Tampilkan Playlist\n";
        cout << "6. Tambah Pasien\n";
        cout << "7. Panggil Pasien\n";
        cout << "8. Lihat Antrian\n";
        cout << "9. Reset Antrian\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";

        getline(cin, input);
        pilihan = atoi(input.c_str());

        switch (pilihan) {
            case 1:
                cout << "Judul lagu: ";
                getline(cin, input);
                tambahLagu(input);
                break;
            case 2:
                cout << "Judul lagu yang dihapus: ";
                getline(cin, input);
                hapusLagu(input);
                break;
            case 3:
                nextLagu();
                break;
            case 4:
                prevLagu();
                break;
            case 5:
                tampilkanPlaylist();
                break;
            case 6:
                cout << "Nama pasien: ";
                getline(cin, input);
                tambahPasien(input);
                break;
            case 7:
                panggilPasien();
                break;
            case 8:
                tampilkanAntrian();
                break;
            case 9:
                resetAntrian();
                break;
            case 0:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}
