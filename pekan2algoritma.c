#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// fungsi untuk input angka bulat saja, huruf ditolak dan diminta ulang
int inputAngka(const char *label) {
    char buffer[100];
    int nilai;
    int valid;

    do {
        valid = 1;
        printf("%s", label);
        scanf("%s", buffer);

        // cek tiap karakter, boleh diawali '-' untuk negatif
        for (int j = 0; buffer[j] != '\0'; j++) {
            if (j == 0 && buffer[j] == '-') continue;
            if (!isdigit(buffer[j])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("  [!] Input tidak valid! Masukkan angka saja.\n");
        }
    } while (!valid);

    nilai = atoi(buffer);
    return nilai;
}

int main() {
    int N, i;
    char nama[100];
    int tesTulis, wawancara;
    float nilaiAkhir;
    float totalNilaiAkhir;
    float rataRata;
    char status[20];
    int jmlValid, jmlTidakValid, jmlLulus;
    float max1, max2;
    char namaMax1[100], namaMax2[100];

    N = inputAngka("Masukkan jumlah pelamar: ");

    jmlValid        = 0;
    jmlTidakValid   = 0;
    jmlLulus        = 0;
    totalNilaiAkhir = 0;
    max1            = -1;
    max2            = -1;
    strcpy(namaMax1, "-");
    strcpy(namaMax2, "-");

    for (i = 1; i <= N; i++) {
        printf("\n--- Pelamar ke-%d ---\n", i);
        printf("Nama       : ");
        scanf("%s", nama);

        tesTulis  = inputAngka("Tes Tulis  : ");
        wawancara = inputAngka("Wawancara  : ");

        if (tesTulis < 0 || tesTulis > 100 ||
            wawancara < 0 || wawancara > 100) {

            strcpy(status, "DATA TIDAK VALID");
            jmlTidakValid = jmlTidakValid + 1;
            printf("Nama: %s | Nilai Akhir: - | Status: %s\n", nama, status);

        } else {
            nilaiAkhir      = (0.6 * tesTulis) + (0.4 * wawancara);
            jmlValid        = jmlValid + 1;
            totalNilaiAkhir = totalNilaiAkhir + nilaiAkhir;

            if (nilaiAkhir >= 75) {
                strcpy(status, "LULUS");
                jmlLulus = jmlLulus + 1;

                if (nilaiAkhir > max1) {
                    max2 = max1;
                    strcpy(namaMax2, namaMax1);
                    max1 = nilaiAkhir;
                    strcpy(namaMax1, nama);
                } else {
                    if (nilaiAkhir > max2 && nilaiAkhir != max1) {
                        max2 = nilaiAkhir;
                        strcpy(namaMax2, nama);
                    }
                }
            } else {
                strcpy(status, "TIDAK LULUS");
            }

            printf("Nama: %s | Nilai Akhir: %.2f | Status: %s\n", nama, nilaiAkhir, status);
        }
    }

    if (jmlValid > 0) {
        rataRata = totalNilaiAkhir / jmlValid;
    } else {
        rataRata = 0;
    }

    printf("\n========== REKAP HASIL ==========\n");
    printf("Jumlah valid          : %d\n", jmlValid);
    printf("Jumlah tidak valid    : %d\n", jmlTidakValid);
    printf("Jumlah lulus          : %d\n", jmlLulus);
    printf("Rata-rata nilai akhir : %.2f\n", rataRata);

    printf("\nDua nilai akhir tertinggi (LULUS):\n");
    if (max1 == -1) {
        printf("  Tidak ada pelamar yang LULUS\n");
    } else {
        printf("  Tertinggi 1 : %s (%.2f)\n", namaMax1, max1);
        if (max2 == -1) {
            printf("  Tertinggi 2 : Belum ada nilai tertinggi ke-2 yang berbeda\n");
        } else {
            printf("  Tertinggi 2 : %s (%.2f)\n", namaMax2, max2);
        }
    }

    return 0;
}