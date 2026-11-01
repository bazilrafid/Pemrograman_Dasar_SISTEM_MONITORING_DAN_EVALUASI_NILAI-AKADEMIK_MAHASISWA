#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const int JUMLAH_KELAS = 3;
const int MAHASISWA_PER_KELAS = 5;
const int JUMLAH_KOMPONEN = 4;

string namaKelas[JUMLAH_KELAS] = {"TI-1A", "TI-1B", "TI-1C"};
string nama[JUMLAH_KELAS][MAHASISWA_PER_KELAS] = {
    {"Andi", "Budi", "Citra", "Deni", "Eka"},
    {"Farhan", "Gina", "Hadi", "Intan", "Joko"},
    {"Karin", "Lukman", "Maya", "Nanda", "Oki"}
};
double bobot[JUMLAH_KOMPONEN] = {0.20, 0.20, 0.25, 0.35};
string namaKomponen[JUMLAH_KOMPONEN] = {"Tugas", "Kuis", "UTS", "UAS"};

// Indeks: nilai[kelas][mahasiswa][komponen]
int nilai[JUMLAH_KELAS][MAHASISWA_PER_KELAS][JUMLAH_KOMPONEN] = {
    {
        {80, 85, 78, 90},
        {70, 75, 68, 72},
        {90, 88, 92, 95},
        {60, 65, 58, 62},
        {85, 80, 82, 88}
    },
    {
        {78, 80, 75, 82},
        {95, 90, 93, 96},
        {65, 70, 60, 68},
        {88, 85, 87, 90},
        {55, 60, 58, 50}
    },
    {
        {82, 84, 80, 86},
        {75, 78, 72, 76},
        {92, 94, 90, 93},
        {68, 65, 70, 72},
        {80, 76, 78, 82}
    }
};

double nilaiAkhir[JUMLAH_KELAS][MAHASISWA_PER_KELAS];

string keHurufKecil(string teks) {
    for (int i = 0; i < (int)teks.length(); i++) {
        teks[i] = (char)tolower((unsigned char)teks[i]);
    }
    return teks;
}

double hitungNilaiAkhir(int k, int m) {
    double total = 0;
    for (int c = 0; c < JUMLAH_KOMPONEN; c++) {
        total += nilai[k][m][c] * bobot[c];
    }
    return total;
}

void hitungSemuaNilaiAkhir() {
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            nilaiAkhir[k][m] = hitungNilaiAkhir(k, m);
        }
    }
}

string tentukanGrade(double n) {
    if (n >= 85) return "A";
    else if (n >= 75) return "B";
    else if (n >= 65) return "C";
    else if (n >= 50) return "D";
    return "E";
}

string statusKelulusan(double n) {
    return (n >= 65) ? "LULUS" : "TIDAK LULUS";
}

bool kelasValid(int k) {
    return k >= 0 && k < JUMLAH_KELAS;
}

int inputKelas() {
    int pilihan;
    cout << "Pilih kelas:\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        cout << k + 1 << ". " << namaKelas[k] << '\n';
    }
    cout << "Pilihan: ";
    cin >> pilihan;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    if (pilihan < 1 || pilihan > JUMLAH_KELAS) return -1;
    return pilihan - 1;
}

void tampilkanSatuMahasiswa(int k, int m, bool denganAkhir = false) {
    cout << "Nama   : " << nama[k][m] << '\n';
    cout << "Kelas  : " << namaKelas[k] << '\n';
    cout << "Tugas  : " << nilai[k][m][0] << '\n';
    cout << "Kuis   : " << nilai[k][m][1] << '\n';
    cout << "UTS    : " << nilai[k][m][2] << '\n';
    cout << "UAS    : " << nilai[k][m][3] << '\n';
    if (denganAkhir) {
        cout << fixed << setprecision(2);
        cout << "Nilai akhir : " << nilaiAkhir[k][m] << '\n';
        cout << "Grade       : " << tentukanGrade(nilaiAkhir[k][m]) << '\n';
        cout << "Status      : " << statusKelulusan(nilaiAkhir[k][m]) << '\n';
    }
}

void fitur1TampilkanSemua() {
    cout << "\n=== SELURUH DATA MAHASISWA ===\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        cout << "\n--- KELAS " << namaKelas[k] << " ---\n";
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            cout << "\nMahasiswa ke-" << m + 1 << '\n';
            tampilkanSatuMahasiswa(k, m);
        }
    }
}

void fitur2BerdasarkanKelas() {
    int k = inputKelas();
    if (!kelasValid(k)) {
        cout << "Pilihan kelas tidak valid.\n";
        return;
    }
    cout << "\n=== DATA KELAS " << namaKelas[k] << " ===\n";
    for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
        cout << "\nMahasiswa ke-" << m + 1 << '\n';
        tampilkanSatuMahasiswa(k, m);
    }
}

void fitur3NilaiAkhir() {
    hitungSemuaNilaiAkhir();
    cout << fixed << setprecision(2);
    cout << "\n=== LAPORAN NILAI AKHIR SELURUH MAHASISWA ===\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        cout << "\nLAPORAN NILAI AKHIR KELAS " << namaKelas[k] << '\n';
        cout << left << setw(5) << "No" << setw(14) << "Nama"
             << setw(14) << "Nilai Akhir" << setw(8) << "Grade"
             << "Status\n";
        cout << "------------------------------------------------------\n";
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            cout << left << setw(5) << m + 1
                 << setw(14) << nama[k][m]
                 << setw(14) << nilaiAkhir[k][m]
                 << setw(8) << tentukanGrade(nilaiAkhir[k][m])
                 << statusKelulusan(nilaiAkhir[k][m]) << '\n';
        }
    }
}

void fitur4CariMahasiswa() {
    string cari;
    cout << "Masukkan nama mahasiswa yang dicari: ";
    getline(cin, cari);
    string target = keHurufKecil(cari);
    bool ditemukan = false;

    for (int k = 0; k < JUMLAH_KELAS; k++) {
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            if (keHurufKecil(nama[k][m]) == target) {
                hitungSemuaNilaiAkhir();
                cout << "\n=== MAHASISWA DITEMUKAN ===\n";
                tampilkanSatuMahasiswa(k, m, true);
                ditemukan = true;
            }
        }
    }
    if (!ditemukan) cout << "Mahasiswa tidak ditemukan.\n";
}

void fitur5UbahNilai() {
    int k = inputKelas();
    if (!kelasValid(k)) {
        cout << "Pilihan kelas tidak valid.\n";
        return;
    }

    cout << "\nMahasiswa di kelas " << namaKelas[k] << ":\n";
    for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
        cout << m + 1 << ". " << nama[k][m] << '\n';
    }
    int m;
    cout << "Pilih nomor mahasiswa (1-5): ";
    cin >> m;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid.\n";
        return;
    }
    if (m < 1 || m > MAHASISWA_PER_KELAS) {
        cin.ignore(10000, '\n');
        cout << "Pilihan mahasiswa tidak valid.\n";
        return;
    }
    m--;
    cout << "\nKomponen nilai:\n";
    for (int c = 0; c < JUMLAH_KOMPONEN; c++) {
        cout << c + 1 << ". " << namaKomponen[c]
             << " (nilai sekarang: " << nilai[k][m][c] << ")\n";
    }
    int c;
    cout << "Pilih komponen (1-4): ";
    cin >> c;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid.\n";
        return;
    }
    if (c < 1 || c > JUMLAH_KOMPONEN) {
        cin.ignore(10000, '\n');
        cout << "Pilihan komponen tidak valid.\n";
        return;
    }
    c--;

    int nilaiBaru;
    cout << "Masukkan nilai baru (0-100): ";
    cin >> nilaiBaru;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input nilai tidak valid.\n";
        return;
    }
    cin.ignore(10000, '\n');
    if (nilaiBaru < 0 || nilaiBaru > 100) {
        cout << "Nilai harus berada pada rentang 0 sampai 100. Perubahan dibatalkan.\n";
        return;
    }

    nilai[k][m][c] = nilaiBaru;
    hitungSemuaNilaiAkhir();
    cout << "Nilai berhasil diperbarui.\n";
    cout << "Nilai akhir terbaru " << nama[k][m] << ": "
         << fixed << setprecision(2) << nilaiAkhir[k][m] << '\n';
    cout << "Grade: " << tentukanGrade(nilaiAkhir[k][m])
         << " | Status: " << statusKelulusan(nilaiAkhir[k][m]) << '\n';
}

bool lebihUnggul(int k1, int m1, int k2, int m2) {
    const double EPS = 0.000001;
    if (nilaiAkhir[k1][m1] > nilaiAkhir[k2][m2] + EPS) return true;
    if (nilaiAkhir[k2][m2] > nilaiAkhir[k1][m1] + EPS) return false;
    return keHurufKecil(nama[k1][m1]) < keHurufKecil(nama[k2][m2]);
}

void fitur6Peringkat() {
    int k = inputKelas();
    if (!kelasValid(k)) {
        cout << "Pilihan kelas tidak valid.\n";
        return;
    }
    hitungSemuaNilaiAkhir();

    int urutan[MAHASISWA_PER_KELAS];
    for (int i = 0; i < MAHASISWA_PER_KELAS; i++) urutan[i] = i;

    // Selection sort manual: nilai tertinggi lebih dahulu.
    for (int i = 0; i < MAHASISWA_PER_KELAS - 1; i++) {
        int posisiTerbaik = i;
        for (int j = i + 1; j < MAHASISWA_PER_KELAS; j++) {
            if (lebihUnggul(k, urutan[j], k, urutan[posisiTerbaik])) {
                posisiTerbaik = j;
            }
        }
        int sementara = urutan[i];
        urutan[i] = urutan[posisiTerbaik];
        urutan[posisiTerbaik] = sementara;
    }

    cout << fixed << setprecision(2);
    cout << "\n=== PERINGKAT KELAS " << namaKelas[k] << " ===\n";
    cout << left << setw(8) << "Rank" << setw(14) << "Nama"
         << setw(14) << "Nilai Akhir" << setw(8) << "Grade" << "Status\n";
    for (int i = 0; i < MAHASISWA_PER_KELAS; i++) {
        int m = urutan[i];
        cout << left << setw(8) << i + 1 << setw(14) << nama[k][m]
             << setw(14) << nilaiAkhir[k][m]
             << setw(8) << tentukanGrade(nilaiAkhir[k][m])
             << statusKelulusan(nilaiAkhir[k][m]) << '\n';
    }
}

void fitur7StatistikKelas() {
    int k = inputKelas();
    if (!kelasValid(k)) {
        cout << "Pilihan kelas tidak valid.\n";
        return;
    }
    hitungSemuaNilaiAkhir();

    int indeksTertinggi = 0, indeksTerendah = 0;
    double totalAkhir = 0;
    double totalKomponen[JUMLAH_KOMPONEN] = {0, 0, 0, 0};
    int lulus = 0, tidakLulus = 0;

    for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
        totalAkhir += nilaiAkhir[k][m];
        if (nilaiAkhir[k][m] > nilaiAkhir[k][indeksTertinggi]) indeksTertinggi = m;
        if (nilaiAkhir[k][m] < nilaiAkhir[k][indeksTerendah]) indeksTerendah = m;
        if (nilaiAkhir[k][m] >= 65) lulus++;
        else tidakLulus++;
        for (int c = 0; c < JUMLAH_KOMPONEN; c++) {
            totalKomponen[c] += nilai[k][m][c];
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n=== STATISTIK KELAS " << namaKelas[k] << " ===\n";
    cout << "Nilai akhir tertinggi : " << nama[k][indeksTertinggi]
         << " (" << nilaiAkhir[k][indeksTertinggi] << ")\n";
    cout << "Nilai akhir terendah  : " << nama[k][indeksTerendah]
         << " (" << nilaiAkhir[k][indeksTerendah] << ")\n";
    cout << "Rata-rata nilai akhir : " << totalAkhir / MAHASISWA_PER_KELAS << '\n';
    cout << "Jumlah lulus          : " << lulus << '\n';
    cout << "Jumlah tidak lulus     : " << tidakLulus << '\n';

    int komponenTerendah = 0;
    for (int c = 0; c < JUMLAH_KOMPONEN; c++) {
        cout << "Rata-rata " << left << setw(6) << namaKomponen[c] << ": "
             << totalKomponen[c] / MAHASISWA_PER_KELAS << '\n';
        if (totalKomponen[c] / MAHASISWA_PER_KELAS <
            totalKomponen[komponenTerendah] / MAHASISWA_PER_KELAS) {
            komponenTerendah = c;
        }
    }
    cout << "Komponen dengan rata-rata terendah: "
         << namaKomponen[komponenTerendah] << '\n';
}

void fitur8StatistikSemuaKelas() {
    hitungSemuaNilaiAkhir();
    double rataKelas[JUMLAH_KELAS] = {0, 0, 0};
    int totalLulus = 0, totalTidakLulus = 0;
    double nilaiMaks = nilaiAkhir[0][0], nilaiMin = nilaiAkhir[0][0];

    cout << fixed << setprecision(2);
    cout << "\n=== ANALISIS SELURUH KELAS ===\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        double total = 0;
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            total += nilaiAkhir[k][m];
            if (nilaiAkhir[k][m] >= 65) totalLulus++;
            else totalTidakLulus++;
            if (nilaiAkhir[k][m] > nilaiMaks) nilaiMaks = nilaiAkhir[k][m];
            if (nilaiAkhir[k][m] < nilaiMin) nilaiMin = nilaiAkhir[k][m];
        }
        rataKelas[k] = total / MAHASISWA_PER_KELAS;
        cout << "Rata-rata kelas " << namaKelas[k] << ": " << rataKelas[k] << '\n';
    }

    double rataTertinggi = rataKelas[0];
    for (int k = 1; k < JUMLAH_KELAS; k++) {
        if (rataKelas[k] > rataTertinggi) rataTertinggi = rataKelas[k];
    }
    cout << "Kelas dengan rata-rata tertinggi (" << rataTertinggi << "): ";
    bool pertama = true;
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        if (rataKelas[k] == rataTertinggi) {
            if (!pertama) cout << ", ";
            cout << namaKelas[k];
            pertama = false;
        }
    }
    cout << '\n';

    cout << "Jumlah seluruh mahasiswa lulus      : " << totalLulus << '\n';
    cout << "Jumlah seluruh mahasiswa tidak lulus: " << totalTidakLulus << '\n';
    cout << "Persentase kelulusan                : "
         << (double)totalLulus / (JUMLAH_KELAS * MAHASISWA_PER_KELAS) * 100
         << "%\n";

    cout << "Nilai akhir tertinggi (" << nilaiMaks << "):\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            if (nilaiAkhir[k][m] == nilaiMaks) {
                cout << "- " << nama[k][m] << " (" << namaKelas[k] << ")\n";
            }
        }
    }
    cout << "Nilai akhir terendah (" << nilaiMin << "):\n";
    for (int k = 0; k < JUMLAH_KELAS; k++) {
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            if (nilaiAkhir[k][m] == nilaiMin) {
                cout << "- " << nama[k][m] << " (" << namaKelas[k] << ")\n";
            }
        }
    }
}

void fitur9Remedial() {
    hitungSemuaNilaiAkhir();
    int kelasRemedial[JUMLAH_KELAS * MAHASISWA_PER_KELAS];
    int mahasiswaRemedial[JUMLAH_KELAS * MAHASISWA_PER_KELAS];
    int jumlah = 0;

    for (int k = 0; k < JUMLAH_KELAS; k++) {
        for (int m = 0; m < MAHASISWA_PER_KELAS; m++) {
            if (nilaiAkhir[k][m] < 65) {
                kelasRemedial[jumlah] = k;
                mahasiswaRemedial[jumlah] = m;
                jumlah++;
            }
        }
    }

    // Urutkan remedial dari nilai akhir terendah ke tertinggi.
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            int k1 = kelasRemedial[j], m1 = mahasiswaRemedial[j];
            int k2 = kelasRemedial[j + 1], m2 = mahasiswaRemedial[j + 1];
            bool tukar = nilaiAkhir[k1][m1] > nilaiAkhir[k2][m2];
            if (nilaiAkhir[k1][m1] == nilaiAkhir[k2][m2] &&
                keHurufKecil(nama[k1][m1]) > keHurufKecil(nama[k2][m2])) {
                tukar = true;
            }
            if (tukar) {
                swap(kelasRemedial[j], kelasRemedial[j + 1]);
                swap(mahasiswaRemedial[j], mahasiswaRemedial[j + 1]);
            }
        }
    }

    cout << fixed << setprecision(2);
    cout << "\n=== DAFTAR MAHASISWA REMEDIAL ===\n";
    if (jumlah == 0) {
        cout << "Tidak ada mahasiswa yang perlu remedial.\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        int k = kelasRemedial[i], m = mahasiswaRemedial[i];
        cout << "\nNama      : " << nama[k][m] << '\n';
        cout << "Kelas     : " << namaKelas[k] << '\n';
        cout << "Nilai akhir: " << nilaiAkhir[k][m] << '\n';

        int nilaiTerendah = nilai[k][m][0];
        for (int c = 1; c < JUMLAH_KOMPONEN; c++) {
            if (nilai[k][m][c] < nilaiTerendah) nilaiTerendah = nilai[k][m][c];
        }
        cout << "Komponen nilai terendah: ";
        bool komponenPertama = true;
        for (int c = 0; c < JUMLAH_KOMPONEN; c++) {
            if (nilai[k][m][c] == nilaiTerendah) {
                if (!komponenPertama) cout << ", ";
                cout << namaKomponen[c] << " (" << nilai[k][m][c] << ")";
                komponenPertama = false;
            }
        }
        cout << '\n';
    }
}

int main() {
    hitungSemuaNilaiAkhir();
    int pilihan;

    do {
        cout << "\n========================================\n";
        cout << " SISTEM MONITORING NILAI MAHASISWA\n";
        cout << "========================================\n";
        cout << "1. Tampilkan Seluruh Data Mahasiswa\n";
        cout << "2. Tampilkan Nilai Berdasarkan Kelas\n";
        cout << "3. Hitung dan Tampilkan Nilai Akhir\n";
        cout << "4. Cari Mahasiswa\n";
        cout << "5. Ubah Nilai Mahasiswa\n";
        cout << "6. Tampilkan Peringkat Mahasiswa\n";
        cout << "7. Analisis Statistik Per Kelas\n";
        cout << "8. Analisis Seluruh Kelas\n";
        cout << "9. Tampilkan Mahasiswa Remedial\n";
        cout << "0. Keluar\n";
        cout << "========================================\n";
        cout << "Pilih Menu: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input menu tidak valid.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        switch (pilihan) {
            case 1: fitur1TampilkanSemua(); break;
            case 2: fitur2BerdasarkanKelas(); break;
            case 3: fitur3NilaiAkhir(); break;
            case 4: fitur4CariMahasiswa(); break;
            case 5: fitur5UbahNilai(); break;
            case 6: fitur6Peringkat(); break;
            case 7: fitur7StatistikKelas(); break;
            case 8: fitur8StatistikSemuaKelas(); break;
            case 9: fitur9Remedial(); break;
            case 0: cout << "Program selesai. Terima kasih!\n"; break;
            default: cout << "Menu tidak tersedia. Silakan pilih 0-9.\n";
        }
    } while (pilihan != 0);

    return 0;
}
