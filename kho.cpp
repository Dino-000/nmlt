#include "kho.h"
#include "data.h"
#include "terminalIO.h"
#include "sach.h"
#include <stdio.h>
#include <string.h>

// Mục đích: Nhập số lượng hàng mới theo ISBN và cộng vào tồn kho
// Tham số: khong co
// Trả về: void
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

// Mục đích: Điều chỉnh số lượng tồn kho theo ISBN (không cho âm)
// Tham số: khong co
// Trả về: void
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

// Mục đích: Hiển thị trạng thái tồn kho và gắn nhãn sắp hết/hết hàng
// Tham số: khong co
// Trả về: void
void xemTonKho() {
    if (soLuongDauSach == 0) {
        printf("\nChua co sach nao trong he thong.\n");
        return;
    }

    printf("%-14s %-32s %-12s %8s\n", "ISBN", "Ten Sach", "The Loai", "Ton Kho");

    int i;
    for (i = 0; i < soLuongDauSach; i++) {
        printf("%-14s %-32s %-12s %8d\n", isbnSach[i], tenSach[i], theLoaiSach[i], soLuongTonKhoSach[i]);
    }
}

// Mục đích: Hiển thị menu quản lý kho
// Tham số: khong co
// Trả về: void
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
