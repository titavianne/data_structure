// SISTEM ANTRIAN & KLASIFIKASI PASIEN RUMAH SAKIT
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Struct untuk Linked List Pasien
struct Pasien {
    int id;
    string nama;
    string poli;
    Pasien* next;
};

Pasien* head = NULL;
queue<Pasien*> antrian;

// Struct untuk Tree (klasifikasi poli)
struct NodeTree {
    string poli;
    NodeTree* left;
    NodeTree* right;
};

NodeTree* root = NULL;

// ===== Fungsi Linked List =====
void tambahPasien(int id, string nama, string poli) {
    Pasien* baru = new Pasien;
    baru->id = id;
    baru->nama = nama;
    baru->poli = poli;
    baru->next = NULL;

    if (!head) head = baru;
    else {
        Pasien* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
    antrian.push(baru);
    cout << "\n[?] Pasien berhasil ditambahkan ke antrian.\n";
}

void tampilkanPasien() {
    cout << "\n== DAFTAR PASIEN (Linked List) ==\n";
    Pasien* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Nama: " << temp->nama << ", Poli: " << temp->poli << endl;
        temp = temp->next;
    }
}

// ===== Fungsi Queue =====
void prosesAntrian() {
    if (antrian.empty()) cout << "\n[!] Tidak ada pasien dalam antrian.\n";
    else {
        Pasien* p = antrian.front();
        antrian.pop();
        cout << "\n[?] Memproses pasien: " << p->nama << " (" << p->poli << ")\n";
    }
}

// ===== Fungsi Tree =====
NodeTree* insertTree(NodeTree* node, string poli) {
    if (!node) {
        NodeTree* baru = new NodeTree;
        baru->poli = poli;
        baru->left = NULL;
        baru->right = NULL;
        return baru;
    }
    if (poli < node->poli) node->left = insertTree(node->left, poli);
    else if (poli > node->poli) node->right = insertTree(node->right, poli);
    return node;
}

void tampilTree(NodeTree* node) {
    if (!node) return;
    tampilTree(node->left);
    cout << "Poli: " << node->poli << endl;
    tampilTree(node->right);
}

// ===== Main Menu =====
int main() {
    int pilihan, id;
    string nama, poli;

    do {
        cout << "\n===== MENU SISTEM PASIEN RS =====\n";
        cout << "1. Tambah Pasien\n2. Lihat Daftar Pasien\n3. Proses Antrian\n4. Lihat Klasifikasi Poli (Tree)\n5. Keluar\nPilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "\nMasukkan ID Pasien: "; cin >> id; cin.ignore();
                cout << "Masukkan Nama Pasien: "; getline(cin, nama);
                cout << "Masukkan Poli Tujuan: "; getline(cin, poli);
                tambahPasien(id, nama, poli);
                root = insertTree(root, poli);
                break;
            case 2:
                tampilkanPasien();
                break;
            case 3:
                prosesAntrian();
                break;
            case 4:
                cout << "\n== KLASIFIKASI POLI (Tree InOrder) ==\n";
                tampilTree(root);
                break;
            case 5:
                cout << "\nTerima kasih!\n";
                break;
            default:
                cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
