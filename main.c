#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ID 18
#define MAX_NAME 51
#define MAX_PASSWORD 21
#define MAX_PHONE 14
#define MAX_BIRTH_DATE 11
#define MAX_REG_DATE 20

extern void sistem_peminjaman(); // Deklarasi fungsi dari pinjam_kembali.c

int is_numeric(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int contains_digit(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) return 1;
    }
    return 0;
}

const char* get_member_type(int type) {
    switch (type) {
        case 1: return "Pelajar";
        case 2: return "Pemilik KTP";
        default: return "Tidak Dikenal";
    }
}

const char* get_gender(char gender) {
    return (gender == 'L') ? "Laki-laki" : (gender == 'W') ? "Wanita" : "Tidak Dikenal";
}

int is_logged_in = 0; // Menyimpan status login
char stored_expiration_date[MAX_REG_DATE]; // Menyimpan tanggal kadaluarsa
char stored_registration_date[MAX_REG_DATE]; // Menyimpan tanggal registrasi

void registrasi() {
    if (is_logged_in) {
        printf("Anda harus keluar dari program ini dulu!\n");
        return;
    }

    char no_identitas[MAX_ID];
    char nama_lengkap[MAX_NAME];
    char password[MAX_PASSWORD];
    char no_hp[MAX_PHONE];
    int jenis_anggota;
    char tanggal_lahir[MAX_BIRTH_DATE];
    char jenis_kelamin;
    char registration_date[MAX_REG_DATE];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Input Jenis Anggota
    while (1) {
        printf("Pilih Jenis Anggota (1: Pelajar, 2: Pemilik KTP): ");
        scanf("%d", &jenis_anggota);
        getchar(); // Membersihkan newline
        if (jenis_anggota < 1 || jenis_anggota > 2) {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        } else {
            break;
        }
    }

    // Input No. Identitas
    while (1) {
        int max_length = (jenis_anggota == 1) ? 10 : 16;
        printf("Masukkan No. Identitas (maks. %d angka): ", max_length);
        fgets(no_identitas, sizeof(no_identitas), stdin);
        no_identitas[strcspn(no_identitas, "\n")] = 0;
        if (strlen(no_identitas) > max_length || !is_numeric(no_identitas)) {
            printf("Anda harus memasukkan %d angka!\n", max_length);
        } else {
            break;
        }
    }

    // Input Nama Lengkap
    while (1) {
        printf("Masukkan Nama Lengkap (maks. 50 huruf): ");
        fgets(nama_lengkap, sizeof(nama_lengkap), stdin);
        nama_lengkap[strcspn(nama_lengkap, "\n")] = 0;
        if (strlen(nama_lengkap) > 50) {
            printf("Anda harus memasukkan maksimal 50 huruf!\n");
        } else {
            for (int i = 0; nama_lengkap[i]; i++) {
                nama_lengkap[i] = toupper(nama_lengkap[i]);
            }
            break;
        }
    }

    // Input No. HP
    while (1) {
        printf("Masukkan No. HP (maks. 13 angka): ");
        fgets(no_hp, sizeof(no_hp), stdin);
        no_hp[strcspn(no_hp, "\n")] = 0;
        if (strlen(no_hp) > 13 || !is_numeric(no_hp)) {
            printf("Anda harus memasukkan 13 angka!\n");
        } else {
            break;
        }
    }

    // Input Tanggal Lahir
    while (1) {
        printf("Masukkan Tanggal Lahir (format YYYY/MM/DD): ");
        fgets(tanggal_lahir, sizeof(tanggal_lahir), stdin);
        tanggal_lahir[strcspn(tanggal_lahir, "\n")] = 0;
        if (strlen(tanggal_lahir) != 10 || tanggal_lahir[4] != '/' || tanggal_lahir[7] != '/') {
            printf("Format tanggal tidak valid. Silakan coba lagi.\n");
        } else {
            break;
        }
    }

    // Input Jenis Kelamin
    while (1) {
        printf("Masukkan Jenis Kelamin (L: Laki-laki, W: Wanita): ");
        scanf(" %c", &jenis_kelamin);
        getchar(); // Membersihkan newline
        if (jenis_kelamin != 'L' && jenis_kelamin != 'W') {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        } else {
            break;
        }
    }

    // Input Password
    while (1) {
        printf("Buat Password (minimal mengandung 1 digit angka): ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        if (!contains_digit(password)) {
            printf("Password harus mengandung minimal satu digit.\n");
            continue;
        }
        break;
    }

    // Simpan tanggal registrasi
    strftime(registration_date, sizeof(registration_date), "%Y/%m/%d %H:%M:%S", tm_info);
    strcpy(stored_registration_date, registration_date); // Simpan tanggal registrasi

    // Menghitung tanggal kadaluarsa keanggotaan
    tm_info->tm_year += 5;
    mktime(tm_info);
    strftime(stored_expiration_date, sizeof(stored_expiration_date), "%Y/%m/%d", tm_info);

    // Menyimpan data ke file
    FILE *file = fopen("data_registrasi.txt", "a");
    if (file != NULL) {
        fprintf(file, "No. Identitas: %s\n", no_identitas);
        fprintf(file, "Nama Lengkap: %s\n", nama_lengkap);
        fprintf(file, "No. HP: %s\n", no_hp);
        fprintf(file, "Jenis Anggota: %s\n", get_member_type(jenis_anggota));
        fprintf(file, "Tanggal Lahir: %s\n", tanggal_lahir);
        fprintf(file, "Jenis Kelamin: %s\n", get_gender(jenis_kelamin));
        fprintf(file, "Password: %s\n", password);
        fprintf(file, "Tanggal Registrasi: %s\n", registration_date);
        fprintf(file, "Tanggal Kadaluarsa: %s\n", stored_expiration_date);
        fclose(file);
        printf("Data berhasil disimpan!\n");
        printf("Terima kasih! Sudah terdaftar di sistem :)\n");
    } else {
        printf("Error membuka file untuk menyimpan data.\n");
    }
}

void login() {
    char no_hp[MAX_PHONE];
    char password[MAX_PASSWORD];
    char stored_no_identitas[MAX_ID];
    char stored_nama_lengkap[MAX_NAME];
    char stored_no_hp[MAX_PHONE];
    char stored_jenis_anggota[20];
    char stored_tanggal_lahir[MAX_BIRTH_DATE];
    char stored_jenis_kelamin[20];
    char stored_password[MAX_PASSWORD];

    // Input No. HP
    printf("Masukkan No. HP: ");
    fgets(no_hp, sizeof(no_hp), stdin);
    no_hp[strcspn(no_hp, "\n")] = 0;

    // Input Password
    printf("Masukkan Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    // Membuka file untuk login
    FILE *file = fopen("data_registrasi.txt", "r");
    if (file == NULL) {
        printf("Tidak dapat membuka file data_registrasi.txt\n");
        return;
    }

    int login_success = 0;

    // Membaca data dari file
    while (fscanf(file, "No. Identitas: %[^\n]\n", stored_no_identitas) != EOF) {
        fscanf(file, "Nama Lengkap: %[^\n]\n", stored_nama_lengkap);
        fscanf(file, "No. HP: %[^\n]\n", stored_no_hp);
        fscanf(file, "Jenis Anggota: %[^\n]\n", stored_jenis_anggota);
        fscanf(file, "Tanggal Lahir: %[^\n]\n", stored_tanggal_lahir);
        fscanf(file, "Jenis Kelamin: %[^\n]\n", stored_jenis_kelamin);
        fscanf(file, "Password: %[^\n]\n", stored_password);
        fscanf(file, "Tanggal Registrasi: %[^\n]\n", stored_registration_date); // Baca tanggal registrasi
        fscanf(file, "Tanggal Kadaluarsa: %[^\n]\n", stored_expiration_date); // Baca tanggal kadaluarsa

        // Memeriksa Login Berhasil atau Gagal
        if (strcmp(no_hp, stored_no_hp) == 0 && strcmp(password, stored_password) == 0) {
            login_success = 1;
            is_logged_in = 1; // Set status login

            // Tampilkan informasi setelah login berhasil
            printf("\nLogin berhasil!\n");
            printf("Nama Lengkap: %s\n", stored_nama_lengkap);
            printf("Jenis Anggota: %s\n", stored_jenis_anggota);
            printf("Tanggal Registrasi: %s\n", stored_registration_date);
            printf("Tanggal Kadaluarsa: %s\n", stored_expiration_date);

            // Panggil sistem peminjaman
            sistem_peminjaman();

            break;
        }
    }

    if (!login_success) {
        printf("Login gagal. No. HP atau password salah.\n");
    }

    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\n=== SELAMAT DATANG DI SISTEM LOGIN DAN REGISTER PERPUSTAKAAN UMUM KOTA DEPOK ===\n");
        printf("\n=== Apa yang anda ingin lakukan? ===\n");
        printf("1. Registrasi Akun Membership Perpustakaan\n");
        printf("2. Login Akun Membership Perpustakaan\n");
        printf("3. Keluar dari Sistem.\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan newline

        switch (choice) {
            case 1:
                registrasi();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Terima kasih sudah mendaftar! Anda bisa mencari dan meminjam buku :)\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }

    return 0;
}
