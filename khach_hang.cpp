#include "khach_hang.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/* -------------------------------------------------------
 * Ham noi bo: in thong tin chi tiet cua mot khach hang
 * Tham so: i - chi so trong mang du lieu
 * ------------------------------------------------------- */
void inThongTinKhachHang(int i) {
    printf("  Ma KH      : %s\n", maKH[i]);
    printf("  Ho ten     : %s\n", tenKH[i]);
    printf("  SDT        : %s\n", sdtKH[i]);
    printf("  Email      : %s\n", mailKH[i]);
    printf("  Dia chi    : %s\n", diaChiKH[i]);
    printf("  Ngay DK    : %s\n", ngayDangKyKH[i]);
    printf("  Loai the   : %s\n", loaiTheKH[i] == 1 ? "VIP" : "Thuong");
}

/*
 * Tham so: maKHCanTim[10] - ma khach hang can tim
 * Duyet mang maKH de tim vi tri cua khach hang.
 * Gia tri tra ve: index cua khach hang >= 0 neu tim thay, -1 neu khong tim thay
 */
int timdexKH(char maKHCanTim[10]) {
    int i;
    for (i = 0; i < soLuongKH; i++) {
        if (strcmp(maKH[i], maKHCanTim) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * In bang danh sach tat ca khach hang.
 */
void xemDanhSachKhachHang() {
    if (soLuongKH == 0) {
        printf("\nChua co khach hang nao trong he thong.\n");
        return;
    }
    printf("%-4s %-12s %-30s %-14s %-8s\n", "STT", "Ma KH", "Ho Ten", "SDT", "Loai The");
    inDuongKe(74, '-');
    int i;
    for (i = 0; i < soLuongKH; i++) {
        printf("%-4d %-12s %-30s %-14s %-8s\n", i + 1, maKH[i], tenKH[i], sdtKH[i], loaiTheKH[i] == 1 ? "VIP" : "Thuong");
    }
    inDuongKe(74, '=');
}

/*
 * Doc thong tin tu ban phim va them khach hang moi.
 * Bao loi neu ma bi trung hoac mang da day.
 */
void themKhachHang() {
    if (soLuongKH >= 100) {
        printf("\nDanh sach khach hang da day (%d/%d)!\n", soLuongKH, 100);
        return;
    }

    char maNhap[10];
    printf("Ma khach hang    : ");
    docChuoi(maNhap, 10);
    if (strlen(maNhap) == 0) {
        printf("Ma khong duoc de trong.\n");
        return;
    }
    if (timdexKH(maNhap) != -1) {
        printf("Ma khach hang '%s' da ton tai!\n", maNhap);
        return;
    }

    int i = soLuongKH;
    strcpy(maKH[i], maNhap);

    printf("Ho ten           : ");
    docChuoi(tenKH[i], 50);

    printf("So dien thoai    : ");
    docChuoi(sdtKH[i], 11);

    printf("Email            : ");
    docChuoi(mailKH[i], 50);

    printf("Dia chi          : ");
    docChuoi(diaChiKH[i], 50);

    printf("Ngay dang ky (dd/mm/yyyy): ");
    docChuoi(ngayDangKyKH[i], 12);

    printf("Loai the (0=Thuong, 1=VIP): ");
    int loaiNhap = nhapSoNguyen();
    loaiTheKH[i] = (loaiNhap == 1) ? 1 : 0;

    soLuongKH++;
    printf(">> Them khach hang thanh cong!\n");
}

/*
 * Tim khach hang theo ma, cho phep chinh sua tung truong.
 * Nguoi dung nhan Enter de giu nguyen gia tri cu.
 */
void chinhSuaKhachHang() {
    char maNhap[10];
    printf("Nhap ma khach hang can chinh sua: ");
    docChuoi(maNhap, 10);

    int i = timdexKH(maNhap);
    if (i == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maNhap);
        return;
    }

    printf("Thong tin hien tai:\n");
    inThongTinKhachHang(i);
    printf("Nhap thong tin moi (Enter de giu nguyen):\n");

    char chuoiTam[50];

    printf("Ho ten [%s]: ", tenKH[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(tenKH[i], chuoiTam);
    }

    printf("SDT [%s]: ", sdtKH[i]);
    docChuoi(chuoiTam, 11);
    if (strlen(chuoiTam) > 0) {
        strcpy(sdtKH[i], chuoiTam);
    }

    printf("Email [%s]: ", mailKH[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(mailKH[i], chuoiTam);
    }

    printf("Dia chi [%s]: ", diaChiKH[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(diaChiKH[i], chuoiTam);
    }

    printf("Ngay dang ky [%s]: ", ngayDangKyKH[i]);
    docChuoi(chuoiTam, 12);
    if (strlen(chuoiTam) > 0) {
        strcpy(ngayDangKyKH[i], chuoiTam);
    }

    printf("Loai the (0=Thuong, 1=VIP) [%d]: ", loaiTheKH[i]);
    docChuoi(chuoiTam, 5);
    if (strlen(chuoiTam) > 0) {
        loaiTheKH[i] = (chuoiTam[0] == '1') ? 1 : 0;
    }

    printf(">> Cap nhat thong tin khach hang thanh cong!\n");
}

/*
 * Tim khach hang theo ma, xac nhan roi xoa.
 * Dich chuyen mang de lap day vi tri bi xoa.
 */
void xoaKhachHang() {
    char maNhap[10];
    printf("Nhap ma khach hang can xoa: ");
    docChuoi(maNhap, 10);

    int i = timdexKH(maNhap);
    if (i == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maNhap);
        return;
    }

    printf("Thong tin khach hang:\n");
    inThongTinKhachHang(i);
    printf("Ban co chac chan muon xoa? (y/n): ");
    char xacNhan[5];
    docChuoi(xacNhan, 5);

    if (xacNhan[0] != 'y' && xacNhan[0] != 'Y') {
        printf("Huy bo xoa.\n");
        return;
    }

    // Dich chuyen cac phan tu phia sau len mot vi tri
    int j;
    for (j = i; j < soLuongKH - 1; j++) {
        strcpy(maKH[j],     maKH[j + 1]);
        strcpy(tenKH[j],  tenKH[j + 1]);
        strcpy(sdtKH[j],    sdtKH[j + 1]);
        strcpy(mailKH[j],  mailKH[j + 1]);
        strcpy(diaChiKH[j], diaChiKH[j + 1]);
        strcpy(ngayDangKyKH[j], ngayDangKyKH[j + 1]);
        loaiTheKH[j] = loaiTheKH[j + 1];
    }
    soLuongKH--;
    printf(">> Xoa khach hang thanh cong!\n");
}

/*
 * Duyet mang tim khach hang co so dien thoai chua chuoi nhap vao.
 */
void timKhachHangTheoSDT() {
    char sdt[11];
    printf("Nhap so dien thoai (hoac phan SDT): ");
    docChuoi(sdt, 11);

    int timThay = 0, i;
    for (i = 0; i < soLuongKH; i++) {
        if (chuaXauCon(sdtKH[i], sdt)) {
            printf("\nKet qua %d:\n", timThay + 1);
            inThongTinKhachHang(i);
            timThay++;
        }
    }
    if (!timThay) {
        printf("Khong tim thay khach hang voi SDT chua '%s'.\n", sdt);
    } else {
        printf("\nTim thay %d khach hang.\n", timThay);
    }
}

// Duyet mang tim khach hang co ho ten chua chuoi nhap vao.
void timKhachHangTheoHoTen() {
    char ten[50];
    printf("Nhap ho ten (hoac mot phan): ");
    docChuoi(ten, 50);

    int timThay = 0, i;
    for (i = 0; i < soLuongKH; i++) {
        if (chuaXauCon(tenKH[i], ten)) {
            printf("\nKet qua %d:\n", timThay + 1);
            inThongTinKhachHang(i);
            timThay++;
        }
    }
    if (!timThay) {
        printf("Khong tim thay khach hang voi ten chua '%s'.\n", ten);
    } else {
        printf("\nTim thay %d khach hang.\n", timThay);
    }
}

// Vong lap menu quan ly khach hang, cho nguoi dung chon chuc nang.
void menuKhachHang() {
    int luaChon;
    do {
        printf("\n===== QUAN LY KHACH HANG =====\n");
        printf("1. Xem danh sach khach hang\n");
        printf("2. Them khach hang moi\n");
        printf("3. Chinh sua thong tin khach hang\n");
        printf("4. Xoa thong tin khach hang\n");
        printf("5. Tim kiem theo so dien thoai\n");
        printf("6. Tim kiem theo ho ten\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        luaChon = nhapSoNguyen();

        switch (luaChon) {
            case 1:
                xemDanhSachKhachHang();
                break;
            case 2:
                themKhachHang();
                break;
            case 3:
                chinhSuaKhachHang();
                break;
            case 4:
                xoaKhachHang();
                break;
            case 5:
                timKhachHangTheoSDT();
                break;
            case 6:
                timKhachHangTheoHoTen();
                break;
            case 0:
                break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}
