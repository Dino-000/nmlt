#include "terminalIO.h"
#include <stdio.h>
#include <string.h>

/*
 * Doc va loai bo moi ki tu con lai trong stdin cho den '\n' hoac EOF,
 * tranh tinh trang 'thieu dong' khi doc chuoi bang fgets sau scanf.
 */
void xoaBuffer() {
    int kyTu;

    while ((kyTu = getchar()) != '\n' && kyTu != EOF);
}

/*
 * Tham so: chuoi      - buffer nhan chuoi
 *          doDaiToiDa - do dai toi da ke ca null terminator
 * Doc mot dong tu stdin, cat bo ki tu xuong dong o cuoi neu co.
 */
void docChuoi(char chuoi[], int doDaiToiDa) {
    if (fgets(chuoi, doDaiToiDa, stdin) != NULL) {
        int doDai = (int)strlen(chuoi);
        if (doDai > 0 && chuoi[doDai - 1] == '\n') {
            chuoi[doDai - 1] = '\0';
        } else {
            /* Buffer day, con ky tu tren dong trong stdin -> xoa het */
            xoaBuffer();
        }
    }
}

/*
 * Doc so nguyen tu stdin; xoa buffer sau khi doc de tranh loi fgets tiep theo.
 * Gia tri tra ve: So nguyen da nhap (mac dinh 0 neu nhap sai dinh dang)
 */
int nhapSoNguyen() {
    int soNguyen = 0;
    scanf("%d", &soNguyen);
    xoaBuffer();
    return soNguyen;
}

/*
 * Doc so thuc tu stdin; xoa buffer sau khi doc.
 * Gia tri tra ve: So thuc da nhap (mac dinh 0.0 neu nhap sai dinh dang)
 */
float nhapSoThuc() {
    float soThuc = 0.0f;
    scanf("%f", &soThuc);
    xoaBuffer();
    return soThuc;
}

/*
 * Tham so: chuoi - chuoi nguon
 *          mau   - xau con can tim
 * Dung strstr de kiem tra sự xuat hien cua 'mau' trong 'chuoi'.
 * Gia tri tra ve: 1 neu tim thay, 0 neu khong
 */
int chuaXauCon(const char chuoi[], const char mau[]) {
    return (strstr(chuoi, mau) != NULL) ? 1 : 0;
}
