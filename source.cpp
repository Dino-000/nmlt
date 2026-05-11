#include <stdio.h>
#include "khach_hang.h"
#include "sach.h"
#include "hoa_don.h"
#include "kho.h"
#include "thong_ke.h"
#include "terminalIO.h"

// Mục đích: Hiển thị menu chính của chương trình
// Tham số: khong co
// Trả về: void 
void hienThiMenuChinh(  ) {
    printf("\n");
    printf("  QUAN LY NHA SACH ONLINE\n");
    printf("  ============================================\n");
    printf("  1. Quan ly khach hang\n");
    printf("  2. Quan ly sach\n");
    printf("  3. Lap hoa don ban hang\n");
    printf("  4. Quan ly kho\n");
    printf("  5. Thong ke\n");
    printf("  0. Thoat\n");
    printf("  Nhap lua chon: ");
}

int main() {
    int luaChon;
    do {
        hienThiMenuChinh();
        luaChon = nhapSoNguyen();
        switch (luaChon) {
            case 1:
                menuKhachHang();
                break;
            case 2:
                menuSach();
                break;
            case 3:
                menuHoaDon();
                break;
            case 4:
                menuKho();
                break;
            case 5:
                menuThongKe();
                break;
            case 0:
                printf("\n Bye bye \n\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (luaChon != 0);
    return 0;
}