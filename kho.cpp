#include "kho.h"
#include "data.h"
#include "terminalIO.h"
#include "sach.h"
#include <stdio.h>
#include <string.h>

/*
 * Tim sach theo ISBN, nhap so luong hang moi ve va cong vao ton kho.
 */
void nhapHangMoi() {
    char isbnNhap[14];
    printf("Nhap ISBN sach: ");
    docChuoi(isbnNhap, 14);

    int i = timChisoLuongDauSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Sach       : %s\n", tenSach[i]);
    printf("Ton kho hien tai: %d quyen\n", soLuongTonKhoSach[i]);
    printf("So luong nhap them: ");
    int soLuong = nhapSoNguyen();

    if (soLuong <= 0) {
        printf("So luong phai lon hon 0.\n");
        return;
    }

    soLuongTonKhoSach[i] += soLuong;
    printf(">> Cap nhat thanh cong! Ton kho moi: %d quyen.\n", soLuongTonKhoSach[i]);
}

/*
 * Tim sach theo ISBN, nhap gia tri thay doi (duong: nhap them, am: giam).
 * Kiem tra khong cho phep ton kho am.
 */
void dieuChinhSoLuong() {
    char isbnNhap[14];
    printf("Nhap ISBN sach: ");
    docChuoi(isbnNhap, 14);

    int i = timChisoLuongDauSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Sach            : %s\n", tenSach[i]);
    printf("Ton kho hien tai: %d quyen\n", soLuongTonKhoSach[i]);
    printf("Nhap so luong thay doi (+/-, vd: +20 hoac -5): ");
    int thayDoi = nhapSoNguyen();

    if (soLuongTonKhoSach[i] + thayDoi < 0) {
        printf("Khong hop le! so luong ton kho khong duoc phep am (%d + %d = %d).\n", soLuongTonKhoSach[i], thayDoi, soLuongTonKhoSach[i] + thayDoi);
        return;
    }

    soLuongTonKhoSach[i] += thayDoi;
    printf(">> Dieu chinh thanh cong! Ton kho moi: %d quyen.\n", soLuongTonKhoSach[i]);
}

/*
 * In bang trang thai ton kho, danh dau sap het hang (< 5) va het hang (= 0).
 */
void xemTonKho() {
    if (soLuongDauSach == 0) {
        printf("\nChua co sach nao trong he thong.\n");
        return;
    }

    printf("%-14s %-32s %-12s %8s  %s\n", "ISBN", "Ten Sach", "The Loai", "Ton Kho", "Trang Thai");

    int i;
    for (i = 0; i < soLuongDauSach; i++) {
        char trangThaiBuf[50];
        if (soLuongTonKhoSach[i] == 0) {
            strcpy(trangThaiBuf, "[HET HANG]");
        } else if (soLuongTonKhoSach[i] < 5) {
            strcpy(trangThaiBuf, "[SAP HET]");
        } else {
            trangThaiBuf[0] = '\0';
        }
        printf("%-14s %-32s %-12s %8d  %s\n", isbnSach[i], tenSach[i], theLoaiSach[i], soLuongTonKhoSach[i], trangThaiBuf);
    }
}

/*
 * Vong lap menu quan ly kho, cho nguoi dung chon chuc nang.
 */
void menuKho() {
    int luaChon;
    do {
        printf("\n===== QUAN LY KHO =====\n");
        printf("1. Nhap hang moi ve\n");
        printf("2. Dieu chinh so luong ton kho\n");
        printf("3. Xem trang thai ton kho\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        luaChon = nhapSoNguyen();

        switch (luaChon) {
            case 1:
                nhapHangMoi();
                break;
            case 2:
                dieuChinhSoLuong();
                break;
            case 3:
                xemTonKho();
                break;
            case 0:
                break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}
