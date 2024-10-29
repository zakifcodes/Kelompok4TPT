#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TITLE 100
#define MAX_BORROWERS 50

void pinjam() {
    char book_title[MAX_TITLE];
    char borrower[MAX_BORROWERS];
    time_t now = time(NULL);
    char borrow_date[20];

    // Mendapatkan informasi peminjam
    printf("Masukkan Nama Peminjam: ");
    fgets(borrower, sizeof(borrower), stdin);
    borrower[strcspn(borrower, "\n")] = 0;

    // Mendapatkan judul buku
    printf("Masukkan Judul Buku: ");
    fgets(book_title, sizeof(book_title), stdin);
    book_title[strcspn(book_title, "\n")] = 0;

    // Mencatat tanggal peminjaman
    strftime(borrow_date, sizeof(borrow_date), "%Y/%m/%d", localtime(&now));

    // Simpan data peminjaman
    FILE *file = fopen("data_pinjam.txt", "a");
    if (file != NULL) {
        fprintf(file, "Peminjam: %s\n", borrower);
        fprintf(file, "Judul Buku: %s\n", book_title);
        fprintf(file, "Tanggal Pinjam: %s\n", borrow_date);
        fclose(file);
        printf("Buku berhasil dipinjam!\n");
    } else {
        printf("Error membuka file untuk menyimpan data peminjaman.\n");
    }
}

void kembali() {
    // Logika pengembalian buku
    printf("Fitur pengembalian buku belum diimplementasikan.\n");
}

void sistem_peminjaman() {
    int choice;

    while (1) {
        printf("\n=== Sistem Peminjaman Buku ===\n");
        printf("1. Pinjam Buku\n");
        printf("2. Kembalikan Buku\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan newline

        switch (choice) {
            case 1:
                pinjam();
                break;
            case 2:
                kembali();
                break;
            case 3:
                printf("Kembali ke menu utama.\n");
                return;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }
}
