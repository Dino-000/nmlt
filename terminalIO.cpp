#include "terminalIO.h"
#include <stdio.h>
#include <string.h>

// Mục đích: Xóa buffer stdin đến dòng mới hoặc EOF
// Tham số: khong co
// Trả về: void
void xoaBuffer() {
    int kyTu;
    while ((kyTu = getchar()) != '\n' && kyTu != EOF);
}

// Mục đích: Đọc một dòng từ stdin, loại bỏ ký tự xuống dòng
// Tham số: `char chuoi[]`, `int doDaiToiDa`
// Trả về: void
void docChuoi(char chuoi[], int doDaiToiDa) {
    if (fgets(chuoi, doDaiToiDa, stdin) != NULL) {
        int doDai = (int)strlen(chuoi);
        if (doDai > 0 && chuoi[doDai - 1] == '\n') {
            chuoi[doDai - 1] = '\0';
        } else {
            xoaBuffer();
        }
    }
}

// Mục đích: Đọc số nguyên từ stdin và xóa buffer
// Tham số: khong co
// Trả về: `int` (giá trị nhập, 0 nếu lỗi)
int nhapSoNguyen() {
    int soNguyen = 0;
    scanf("%d", &soNguyen);
    xoaBuffer();
    return soNguyen;
}

// Mục đích: Đọc số thực từ stdin và xóa buffer
// Tham số: khong co
// Trả về: `float` (giá trị nhập, 0.0 nếu lỗi)
float nhapSoThuc() {
    float soThuc = 0.0f;
    scanf("%f", &soThuc);
    xoaBuffer();
    return soThuc;
}

// Mục đích: Kiểm tra chuỗi con bằng `strstr`
// Tham số: `const char chuoi[]`, `const char mau[]`
// Trả về: `int` (1 nếu chứa, 0 nếu không)
int chuaXauCon(const char chuoi[], const char mau[]) {
    return (strstr(chuoi, mau) != NULL) ? 1 : 0;
}
