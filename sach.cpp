#include "sach.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/* 
 * in thong tin chi tiet cua mot dau sach
 * Tham so: i - chi so trong mang du lieu
 * ------------------------------------------------------- */
void inThongTinSach(int i) {
    printf("  ISBN        : %s\n",   sach_isbn[i]);
    printf("  Ten sach    : %s\n",   sach_ten[i]);
    printf("  Tac gia     : %s\n",   sach_tacGia[i]);
    printf("  NXB         : %s\n",   sach_nxb[i]);
    printf("  Nam XB      : %d\n",   sach_namXB[i]);
    printf("  The loai    : %s\n",   sach_theLoai[i]);
    printf("  Gia nhap    : %.0f VND\n", sach_giaNhap[i]);
    printf("  Gia ban     : %.0f VND\n", sach_giaBan[i]);
    printf("  Ton kho     : %d quyen\n", sach_soLuong[i]);
}

/*
 * Tham so: isbnTim[MAX_ISBN] - ma ISBN can tim
 * Duyet mang sach_isbn de tim vi tri cua sach.
 * Gia tri tra ve: Chi so >= 0 neu tim thay, -1 neu khong tim thay
 */
int timChiSoSach(char isbnTim[MAX_ISBN]) {
    int i;
    for (i = 0; i < soSach; i++) {
        if (strcmp(sach_isbn[i], isbnTim) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * In bang danh sach tat ca sach hien co trong he thong.
 */
void xemDanhSachSach() {
    if (soSach == 0) {
        printf("\nChua co sach nao trong he thong.\n");
        return;
    }
    printf("%-4s %-14s %-28s %-20s %-12s %-8s\n", "STT", "ISBN", "Ten Sach", "Tac Gia", "The Loai", "Ton Kho");
    inDuongKe(90, '-');
    int i;
    for (i = 0; i < soSach; i++) {
        printf("%-4d %-14s %-28s %-20s %-12s %-8d\n", i + 1, sach_isbn[i], sach_ten[i], sach_tacGia[i], sach_theLoai[i], sach_soLuong[i]);
    }
    inDuongKe(90, '=');
}

/*
 * Doc thong tin tu ban phim va them dau sach moi.
 * Bao loi neu ISBN bi trung hoac mang da day.
 */
void themSach() {
    if (soSach >= MAX_SACH) {
        printf("\nDanh sach sach da day (%d/%d)!\n", soSach, MAX_SACH);
        return;
    }

    char isbnNhap[MAX_ISBN];
    printf("\n========== THEM SACH MOI ==========\n");

    printf("ISBN           : ");
    docChuoi(isbnNhap, MAX_ISBN);
    if (strlen(isbnNhap) == 0) {
        printf("ISBN khong duoc de trong.\n");
        return;
    }
    if (timChiSoSach(isbnNhap) != -1) {
        printf("ISBN '%s' da ton tai!\n", isbnNhap);
        return;
    }

    int i = soSach;
    strcpy(sach_isbn[i], isbnNhap);

    printf("Ten sach       : ");
    docChuoi(sach_ten[i], MAX_TEN);

    printf("Tac gia        : ");
    docChuoi(sach_tacGia[i], MAX_TEN);

    printf("Nha xuat ban   : ");
    docChuoi(sach_nxb[i], MAX_NXB);

    printf("Nam xuat ban   : ");
    sach_namXB[i] = nhapSoNguyen();

    printf("The loai       : ");
    docChuoi(sach_theLoai[i], MAX_THE_LOAI);

    printf("Gia nhap (VND) : ");
    sach_giaNhap[i] = nhapSoThuc();

    printf("Gia ban  (VND) : ");
    sach_giaBan[i] = nhapSoThuc();

    printf("So luong nhap  : ");
    sach_soLuong[i] = nhapSoNguyen();

    soSach++;
    printf(">> Them sach thanh cong!\n");
}

/*
 * Tim sach theo ISBN, cho phep chinh sua tung truong.
 * Nguoi dung nhan Enter de giu nguyen gia tri cu.
 */
void chinhSuaSach() {
    char isbnNhap[MAX_ISBN];
    printf("Nhap ISBN sach can chinh sua: ");
    docChuoi(isbnNhap, MAX_ISBN);

    int i = timChiSoSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Thong tin hien tai:\n");
    inThongTinSach(i);
    printf("Nhap thong tin moi (Enter de giu nguyen):\n");

    char chuoiTam[MAX_NXB];

    printf("Ten sach [%s]: ", sach_ten[i]);
    docChuoi(chuoiTam, MAX_TEN);
    if (strlen(chuoiTam) > 0) {
        strcpy(sach_ten[i], chuoiTam);
    }

    printf("Tac gia [%s]: ", sach_tacGia[i]);
    docChuoi(chuoiTam, MAX_TEN);
    if (strlen(chuoiTam) > 0) {
        strcpy(sach_tacGia[i], chuoiTam);
    }

    printf("NXB [%s]: ", sach_nxb[i]);
    docChuoi(chuoiTam, MAX_NXB);
    if (strlen(chuoiTam) > 0) {
        strcpy(sach_nxb[i], chuoiTam);
    }

    printf("Nam XB [%d] (0=giu nguyen): ", sach_namXB[i]);
    int namMoi = nhapSoNguyen();
    if (namMoi != 0) {
        sach_namXB[i] = namMoi;
    }

    printf("The loai [%s]: ", sach_theLoai[i]);
    docChuoi(chuoiTam, MAX_THE_LOAI);
    if (strlen(chuoiTam) > 0) {
        strcpy(sach_theLoai[i], chuoiTam);
    }

    printf("Gia nhap [%.0f] (-1=giu nguyen): ", sach_giaNhap[i]);
    float giaMoi = nhapSoThuc();
    if (giaMoi >= 0) {
        sach_giaNhap[i] = giaMoi;
    }

    printf("Gia ban [%.0f] (-1=giu nguyen): ", sach_giaBan[i]);
    giaMoi = nhapSoThuc();
    if (giaMoi >= 0) {
        sach_giaBan[i] = giaMoi;
    }

    printf(">> Cap nhat thong tin sach thanh cong!\n");
}

/*
 * Tim sach theo ISBN, kiem tra ton kho = 0, xac nhan roi xoa.
 * Dich chuyen mang de lap day vi tri bi xoa.
 */
void xoaSach() {
    char isbnNhap[MAX_ISBN];
    printf("Nhap ISBN sach can xoa: ");
    docChuoi(isbnNhap, MAX_ISBN);

    int i = timChiSoSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    if (sach_soLuong[i] != 0) {
        printf("Khong the xoa! Sach '%s' con %d quyen trong kho.\n", sach_ten[i], sach_soLuong[i]);
        return;
    }

    printf("Thong tin sach:\n");
    inThongTinSach(i);
    printf("Ban co chac chan muon xoa? (y/n): ");
    char xacNhan[5];
    docChuoi(xacNhan, 5);

    if (xacNhan[0] != 'y' && xacNhan[0] != 'Y') {
        printf("Huy bo xoa.\n");
        return;
    }

    // Dich chuyen cac phan tu phia sau len mot vi tri
    int j;
    for (j = i; j < soSach - 1; j++) {
        strcpy(sach_isbn[j], sach_isbn[j + 1]);
        strcpy(sach_ten[j], sach_ten[j + 1]);
        strcpy(sach_tacGia[j], sach_tacGia[j + 1]);
        strcpy(sach_nxb[j], sach_nxb[j + 1]);
        sach_namXB[j] = sach_namXB[j + 1];
        strcpy(sach_theLoai[j], sach_theLoai[j + 1]);
        sach_giaNhap[j] = sach_giaNhap[j + 1];
        sach_giaBan[j] = sach_giaBan[j + 1];
        sach_soLuong[j] = sach_soLuong[j + 1];
    }
    soSach--;
    printf(">> Xoa sach thanh cong!\n");
}

/*
 * Tim chinh xac sach theo ISBN va hien thi chi tiet.
 */
void timSachTheoISBN() {
    char isbnNhap[MAX_ISBN];
    printf("Nhap ISBN: ");
    docChuoi(isbnNhap, MAX_ISBN);

    int i = timChiSoSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
    } else {
        printf("\nThong tin sach:\n");
        inThongTinSach(i);
    }
}

/*
 * Duyet mang tim cac sach co ten chua chuoi nhap vao.
 */
void timSachTheoTen() {
    char ten[MAX_TEN];
    printf("Nhap ten sach (hoac mot phan): ");
    docChuoi(ten, MAX_TEN);

    int timThay = 0, i;
    for (i = 0; i < soSach; i++) {
        if (chuaXauCon(sach_ten[i], ten)) {
            printf("\nKet qua %d:\n", timThay + 1);
            inThongTinSach(i);
            timThay++;
        }
    }
    if (!timThay) {
        printf("Khong tim thay sach voi ten chua '%s'.\n", ten);
    } else {
        printf("\nTim thay %d dau sach.\n", timThay);
    }
}

/*
 * Vong lap menu quan ly sach, cho nguoi dung chon chuc nang.
 */
void menuSach() {
    int luaChon;
    do {
        printf("1. Xem danh sach sach\n");
        printf("2. Them sach moi\n");
        printf("3. Chinh sua thong tin sach\n");
        printf("4. Xoa sach (chi khi ton kho = 0)\n");
        printf("5. Tim kiem theo ISBN\n");
        printf("6. Tim kiem theo ten sach\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        luaChon = nhapSoNguyen();

        switch (luaChon) {
            case 1:
                xemDanhSachSach();
                break;
            case 2:
                themSach();
                break;
            case 3:
                chinhSuaSach();
                break;
            case 4:
                xoaSach();
                break;
            case 5:
                timSachTheoISBN();
                break;
            case 6:
                timSachTheoTen();
                break;
            case 0:
                break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}
