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
    printf("  Ma KH      : %s\n", kh_ma[i]);
    printf("  Ho ten     : %s\n", kh_hoTen[i]);
    printf("  SDT        : %s\n", kh_sdt[i]);
    printf("  Email      : %s\n", kh_email[i]);
    printf("  Dia chi    : %s\n", kh_diaChi[i]);
    printf("  Ngay DK    : %s\n", kh_ngayDK[i]);
    printf("  Loai the   : %s\n", kh_loaiThe[i] == THE_VIP ? "VIP" : "Thuong");
}

/*
 * Tham so: maTim[MAX_MA] - ma khach hang can tim
 * Duyet mang kh_ma de tim vi tri cua khach hang.
 * Gia tri tra ve: index cua khach hang >= 0 neu tim thay, -1 neu khong tim thay
 */
int timChiSoKhachHang(char maTim[MAX_MA]) {
    int i;
    for (i = 0; i < soKhachHang; i++) {
        if (strcmp(kh_ma[i], maTim) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * In bang danh sach tat ca khach hang.
 */
void xemDanhSachKhachHang() {
    if (soKhachHang == 0) {
        printf("\nChua co khach hang nao trong he thong.\n");
        return;
    }
    printf("%-4s %-12s %-30s %-14s %-8s\n", "STT", "Ma KH", "Ho Ten", "SDT", "Loai The");
    inDuongKe(74, '-');
    int i;
    for (i = 0; i < soKhachHang; i++) {
        printf("%-4d %-12s %-30s %-14s %-8s\n", i + 1, kh_ma[i], kh_hoTen[i], kh_sdt[i], kh_loaiThe[i] == THE_VIP ? "VIP" : "Thuong");
    }
    inDuongKe(74, '=');
}

/*
 * Doc thong tin tu ban phim va them khach hang moi.
 * Bao loi neu ma bi trung hoac mang da day.
 */
void themKhachHang() {
    if (soKhachHang >= MAX_KHACH_HANG) {
        printf("\nDanh sach khach hang da day (%d/%d)!\n", soKhachHang, MAX_KHACH_HANG);
        return;
    }

    char maNhap[MAX_MA];
    printf("Ma khach hang    : ");
    docChuoi(maNhap, MAX_MA);
    if (strlen(maNhap) == 0) {
        printf("Ma khong duoc de trong.\n");
        return;
    }
    if (timChiSoKhachHang(maNhap) != -1) {
        printf("Ma khach hang '%s' da ton tai!\n", maNhap);
        return;
    }

    int i = soKhachHang;
    strcpy(kh_ma[i], maNhap);

    printf("Ho ten           : ");
    docChuoi(kh_hoTen[i], MAX_TEN);

    printf("So dien thoai    : ");
    docChuoi(kh_sdt[i], MAX_SDT);

    printf("Email            : ");
    docChuoi(kh_email[i], MAX_EMAIL);

    printf("Dia chi          : ");
    docChuoi(kh_diaChi[i], MAX_DIA_CHI);

    printf("Ngay dang ky (dd/mm/yyyy): ");
    docChuoi(kh_ngayDK[i], MAX_NGAY);

    printf("Loai the (0=Thuong, 1=VIP): ");
    int loaiNhap = nhapSoNguyen();
    kh_loaiThe[i] = (loaiNhap == THE_VIP) ? THE_VIP : THE_THUONG;

    soKhachHang++;
    printf(">> Them khach hang thanh cong!\n");
}

/*
 * Tim khach hang theo ma, cho phep chinh sua tung truong.
 * Nguoi dung nhan Enter de giu nguyen gia tri cu.
 */
void chinhSuaKhachHang() {
    char maNhap[MAX_MA];
    printf("Nhap ma khach hang can chinh sua: ");
    docChuoi(maNhap, MAX_MA);

    int i = timChiSoKhachHang(maNhap);
    if (i == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maNhap);
        return;
    }

    printf("Thong tin hien tai:\n");
    inThongTinKhachHang(i);
    printf("Nhap thong tin moi (Enter de giu nguyen):\n");

    char chuoiTam[MAX_DIA_CHI];

    printf("Ho ten [%s]: ", kh_hoTen[i]);
    docChuoi(chuoiTam, MAX_TEN);
    if (strlen(chuoiTam) > 0) {
        strcpy(kh_hoTen[i], chuoiTam);
    }

    printf("SDT [%s]: ", kh_sdt[i]);
    docChuoi(chuoiTam, MAX_SDT);
    if (strlen(chuoiTam) > 0) {
        strcpy(kh_sdt[i], chuoiTam);
    }

    printf("Email [%s]: ", kh_email[i]);
    docChuoi(chuoiTam, MAX_EMAIL);
    if (strlen(chuoiTam) > 0) {
        strcpy(kh_email[i], chuoiTam);
    }

    printf("Dia chi [%s]: ", kh_diaChi[i]);
    docChuoi(chuoiTam, MAX_DIA_CHI);
    if (strlen(chuoiTam) > 0) {
        strcpy(kh_diaChi[i], chuoiTam);
    }

    printf("Ngay dang ky [%s]: ", kh_ngayDK[i]);
    docChuoi(chuoiTam, MAX_NGAY);
    if (strlen(chuoiTam) > 0) {
        strcpy(kh_ngayDK[i], chuoiTam);
    }

    printf("Loai the (0=Thuong, 1=VIP) [%d]: ", kh_loaiThe[i]);
    docChuoi(chuoiTam, 5);
    if (strlen(chuoiTam) > 0) {
        kh_loaiThe[i] = (chuoiTam[0] == '1') ? THE_VIP : THE_THUONG;
    }

    printf(">> Cap nhat thong tin khach hang thanh cong!\n");
}

/*
 * Tim khach hang theo ma, xac nhan roi xoa.
 * Dich chuyen mang de lap day vi tri bi xoa.
 */
void xoaKhachHang() {
    char maNhap[MAX_MA];
    printf("Nhap ma khach hang can xoa: ");
    docChuoi(maNhap, MAX_MA);

    int i = timChiSoKhachHang(maNhap);
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
    for (j = i; j < soKhachHang - 1; j++) {
        strcpy(kh_ma[j],     kh_ma[j + 1]);
        strcpy(kh_hoTen[j],  kh_hoTen[j + 1]);
        strcpy(kh_sdt[j],    kh_sdt[j + 1]);
        strcpy(kh_email[j],  kh_email[j + 1]);
        strcpy(kh_diaChi[j], kh_diaChi[j + 1]);
        strcpy(kh_ngayDK[j], kh_ngayDK[j + 1]);
        kh_loaiThe[j] = kh_loaiThe[j + 1];
    }
    soKhachHang--;
    printf(">> Xoa khach hang thanh cong!\n");
}

/*
 * Duyet mang tim khach hang co so dien thoai chua chuoi nhap vao.
 */
void timKhachHangTheoSDT() {
    char sdt[MAX_SDT];
    printf("Nhap so dien thoai (hoac phan SDT): ");
    docChuoi(sdt, MAX_SDT);

    int timThay = 0, i;
    for (i = 0; i < soKhachHang; i++) {
        if (chuaXauCon(kh_sdt[i], sdt)) {
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
    char ten[MAX_TEN];
    printf("Nhap ho ten (hoac mot phan): ");
    docChuoi(ten, MAX_TEN);

    int timThay = 0, i;
    for (i = 0; i < soKhachHang; i++) {
        if (chuaXauCon(kh_hoTen[i], ten)) {
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
