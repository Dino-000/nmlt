#include "kho.h"
#include "data.h"
#include "utils.h"
#include "sach.h"
#include <stdio.h>
#include <string.h>

/*
 * Tim sach theo ISBN, nhap so luong hang moi ve va cong vao ton kho.
 */
void nhapHangMoi() {
    char isbnNhap[MAX_ISBN];
    printf("Nhap ISBN sach: ");
    docChuoi(isbnNhap, MAX_ISBN);

    int i = timChiSoSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Sach       : %s\n", sach_ten[i]);
    printf("Ton kho hien tai: %d quyen\n", sach_soLuong[i]);
    printf("So luong nhap them: ");
    int soLuong = nhapSoNguyen();

    if (soLuong <= 0) {
        printf("So luong phai lon hon 0.\n");
        return;
    }

    sach_soLuong[i] += soLuong;
    printf(">> Cap nhat thanh cong! Ton kho moi: %d quyen.\n", sach_soLuong[i]);
}

/*
 * Tim sach theo ISBN, nhap gia tri thay doi (duong: nhap them, am: giam).
 * Kiem tra khong cho phep ton kho am.
 */
void dieuChinhSoLuong() {
    char isbnNhap[MAX_ISBN];
    printf("Nhap ISBN sach: ");
    docChuoi(isbnNhap, MAX_ISBN);

    int i = timChiSoSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Sach            : %s\n", sach_ten[i]);
    printf("Ton kho hien tai: %d quyen\n", sach_soLuong[i]);
    printf("Nhap so luong thay doi (+/-, vd: +20 hoac -5): ");
    int thayDoi = nhapSoNguyen();

    if (sach_soLuong[i] + thayDoi < 0) {
        printf("Khong hop le! so luong ton kho khong duoc phep am (%d + %d = %d).\n", sach_soLuong[i], thayDoi, sach_soLuong[i] + thayDoi);
        return;
    }

    sach_soLuong[i] += thayDoi;
    printf(">> Dieu chinh thanh cong! Ton kho moi: %d quyen.\n", sach_soLuong[i]);
}

/*
 * In bang trang thai ton kho, danh dau sap het hang (< 5) va het hang (= 0).
 */
void xemTonKho() {
    if (soSach == 0) {
        printf("\nChua co sach nao trong he thong.\n");
        return;
    }

    printf("%-14s %-32s %-12s %8s  %s\n", "ISBN", "Ten Sach", "The Loai", "Ton Kho", "Trang Thai");
    inDuongKe(82, '-');

    int i;
    for (i = 0; i < soSach; i++) {
        const char* trangThai;
        if (sach_soLuong[i] == 0) {
            trangThai = "[HET HANG]";
        } else if (sach_soLuong[i] < 5) {
            trangThai = "[SAP HET]";
        } else {
            trangThai = "";
        }
        printf("%-14s %-32s %-12s %8d  %s\n", sach_isbn[i], sach_ten[i], sach_theLoai[i], sach_soLuong[i], trangThai);
    }
    inDuongKe(82, '=');
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
