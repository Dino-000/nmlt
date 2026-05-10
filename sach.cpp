#include "sach.h"
#include "data.h"
#include "terminalIO.h"
#include <stdio.h>
#include <string.h>

/* 
 * in thong tin chi tiet cua mot dau sach
 * Tham so: i - chi so trong mang du lieu
 * ------------------------------------------------------- */
void inThongTinSach(int i) {
    printf("  ISBN        : %s\n",   isbnSach[i]);
    printf("  Ten sach    : %s\n",   tenSach[i]);
    printf("  Tac gia     : %s\n",   tacGiaSach[i]);
    printf("  NXB         : %s\n",   nxbSach[i]);
    printf("  Nam XB      : %d\n",   namXBSach[i]);
    printf("  The loai    : %s\n",   theLoaiSach[i]);
    printf("  Gia nhap    : %.0f VND\n", giaNhapSach[i]);
    printf("  Gia ban     : %.0f VND\n", giaBanSach[i]);
    printf("  Ton kho     : %d quyen\n", soLuongTonKhoSach[i]);
}

/*
 * Tham so: isbnTim[14] - ma ISBN can tim
 * Duyet mang isbnSach de tim vi tri cua sach.
 * Gia tri tra ve: Chi so >= 0 neu tim thay, -1 neu khong tim thay
 */
int timChisoLuongDauSach(char isbnTim[14]) {
    int i;
    for (i = 0; i < soLuongDauSach; i++) {
        if (strcmp(isbnSach[i], isbnTim) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * In bang danh sach tat ca sach hien co trong he thong.
 */
void xemDanhSachSach() {
    if (soLuongDauSach == 0) {
        printf("\nChua co sach nao trong he thong.\n");
        return;
    }
    printf("%-4s %-14s %-28s %-20s %-12s %-8s\n", "STT", "ISBN", "Ten Sach", "Tac Gia", "The Loai", "Ton Kho");
    int i;
    for (i = 0; i < soLuongDauSach; i++) {
        printf("%-4d %-14s %-28s %-20s %-12s %-8d\n", i + 1, isbnSach[i], tenSach[i], tacGiaSach[i], theLoaiSach[i], soLuongTonKhoSach[i]);
    }
}

/*
 * Doc thong tin tu ban phim va them dau sach moi.
 * Bao loi neu ISBN bi trung hoac mang da day.
 */
void themSach() {
    if (soLuongDauSach >= 100) {
        printf("\nDanh sach sach da day (%d/%d)!\n", soLuongDauSach, 100);
        return;
    }

    char isbnNhap[14];
    printf("\n========== THEM SACH MOI ==========\n");

    printf("ISBN           : ");
    docChuoi(isbnNhap, 14);
    if (strlen(isbnNhap) == 0) {
        printf("ISBN khong duoc de trong.\n");
        return;
    }
    if (timChisoLuongDauSach(isbnNhap) != -1) {
        printf("ISBN '%s' da ton tai!\n", isbnNhap);
        return;
    }

    int i = soLuongDauSach;
    strcpy(isbnSach[i], isbnNhap);

    printf("Ten sach       : ");
    docChuoi(tenSach[i], 50);

    printf("Tac gia        : ");
    docChuoi(tacGiaSach[i], 50);

    printf("Nha xuat ban   : ");
    docChuoi(nxbSach[i], 50);

    printf("Nam xuat ban   : ");
    namXBSach[i] = nhapSoNguyen();

    printf("The loai       : ");
    docChuoi(theLoaiSach[i], 50);

    printf("Gia nhap (VND) : ");
    giaNhapSach[i] = nhapSoThuc();

    printf("Gia ban  (VND) : ");
    giaBanSach[i] = nhapSoThuc();

    printf("So luong nhap  : ");
    soLuongTonKhoSach[i] = nhapSoNguyen();

    soLuongDauSach++;
    printf(">> Them sach thanh cong!\n");
}

/*
 * Tim sach theo ISBN, cho phep chinh sua tung truong.
 * Nguoi dung nhan Enter de giu nguyen gia tri cu.
 */
void chinhSuaSach() {
    char isbnNhap[14];
    printf("Nhap ISBN sach can chinh sua: ");
    docChuoi(isbnNhap, 14);

    int i = timChisoLuongDauSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    printf("Thong tin hien tai:\n");
    inThongTinSach(i);
    printf("Nhap thong tin moi (Enter de giu nguyen):\n");

    char chuoiTam[50];

    printf("Ten sach [%s]: ", tenSach[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(tenSach[i], chuoiTam);
    }

    printf("Tac gia [%s]: ", tacGiaSach[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(tacGiaSach[i], chuoiTam);
    }

    printf("NXB [%s]: ", nxbSach[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(nxbSach[i], chuoiTam);
    }

    printf("Nam XB [%d] (0=giu nguyen): ", namXBSach[i]);
    int namMoi = nhapSoNguyen();
    if (namMoi != 0) {
        namXBSach[i] = namMoi;
    }

    printf("The loai [%s]: ", theLoaiSach[i]);
    docChuoi(chuoiTam, 50);
    if (strlen(chuoiTam) > 0) {
        strcpy(theLoaiSach[i], chuoiTam);
    }

    printf("Gia nhap [%.0f] (-1=giu nguyen): ", giaNhapSach[i]);
    float giaMoi = nhapSoThuc();
    if (giaMoi >= 0) {
        giaNhapSach[i] = giaMoi;
    }

    printf("Gia ban [%.0f] (-1=giu nguyen): ", giaBanSach[i]);
    giaMoi = nhapSoThuc();
    if (giaMoi >= 0) {
        giaBanSach[i] = giaMoi;
    }

    printf(">> Cap nhat thong tin sach thanh cong!\n");
}

/*
 * Tim sach theo ISBN, kiem tra ton kho = 0, xac nhan roi xoa.
 * Dich chuyen mang de lap day vi tri bi xoa.
 */
void xoaSach() {
    char isbnNhap[14];
    printf("Nhap ISBN sach can xoa: ");
    docChuoi(isbnNhap, 14);

    int i = timChisoLuongDauSach(isbnNhap);
    if (i == -1) {
        printf("Khong tim thay sach voi ISBN '%s'.\n", isbnNhap);
        return;
    }

    if (soLuongTonKhoSach[i] != 0) {
        printf("Khong the xoa! Sach '%s' con %d quyen trong kho.\n", tenSach[i], soLuongTonKhoSach[i]);
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
    for (j = i; j < soLuongDauSach - 1; j++) {
        strcpy(isbnSach[j], isbnSach[j + 1]);
        strcpy(tenSach[j], tenSach[j + 1]);
        strcpy(tacGiaSach[j], tacGiaSach[j + 1]);
        strcpy(nxbSach[j], nxbSach[j + 1]);
        namXBSach[j] = namXBSach[j + 1];
        strcpy(theLoaiSach[j], theLoaiSach[j + 1]);
        giaNhapSach[j] = giaNhapSach[j + 1];
        giaBanSach[j] = giaBanSach[j + 1];
        soLuongTonKhoSach[j] = soLuongTonKhoSach[j + 1];
    }
    soLuongDauSach--;
    printf(">> Xoa sach thanh cong!\n");
}

/*
 * Tim chinh xac sach theo ISBN va hien thi chi tiet.
 */
void timSachTheoISBN() {
    char isbnNhap[14];
    printf("Nhap ISBN: ");
    docChuoi(isbnNhap, 14);

    int i = timChisoLuongDauSach(isbnNhap);
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
    char ten[50];
    printf("Nhap ten sach (hoac mot phan): ");
    docChuoi(ten, 50);

    int timThay = 0, i;
    for (i = 0; i < soLuongDauSach; i++) {
        if (chuaXauCon(tenSach[i], ten)) {
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
