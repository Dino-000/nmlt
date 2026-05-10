#include <stdio.h>
#include <string.h>
#include "hoa_don.h"
#include "data.h"
#include "terminalIO.h"
#include "khach_hang.h"
#include "sach.h"

/*
 * tinh tong tien hoa don tai chi so indexHD
 * ap dung: giam gia the loai (>5 quyen), giam gia VIP, VAT
 * Tham so: indexHD    - chi so hoa don trong mang
 *          chiSoKH    - chi so khach hang trong mang
 *          giaTungMH - mang float nhan gia sau giam cua tung mat hang (co the NULL neu khong can)
 * Gia tri tra ve: Tong tien cuoi cung (float)
 */
float tinhTongTien(int indexHD, int chiSoKH, float giaTungMH[20]) {
    int soMatHang = soMatHangTrongHoaDon[indexHD];
    int j, k;

    // Tinh tong so luong sach o cung mot the loai trong hoa don 
    char dsTheLoai[20][50];
    int  slTheoTL[20];
    int  soTheLoai = 0;

    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[indexHD][j]);
        if (chisoLuongDauSach < 0) {
            continue;
        }

        // Tim the loai trong danh sach da co
        int chiSoTL = -1;
        for (k = 0; k < soTheLoai; k++) {
            if (strcmp(dsTheLoai[k], theLoaiSach[chisoLuongDauSach]) == 0) {
                chiSoTL = k;
                break;
            }
        }
        if (chiSoTL == -1) {
            chiSoTL = soTheLoai;
            strcpy(dsTheLoai[soTheLoai], theLoaiSach[chisoLuongDauSach]);
            slTheoTL[soTheLoai] = 0;
            soTheLoai++;
        }
        slTheoTL[chiSoTL] += soLuongDauSachTrongHoaDon[indexHD][j];
    }

    // Tinh tong tien truoc khi giam gia VIP, co ap dung giam gia the loai
    float tamTinh = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[indexHD][j]);
        if (chisoLuongDauSach < 0) {
            continue;
        }

        float thanhTien = giaBanSach[chisoLuongDauSach] * (float)soLuongDauSachTrongHoaDon[indexHD][j];

        // Kiem tra va ap dung giam gia theo so luong tung the loai (>5 quyen)
        for (k = 0; k < soTheLoai; k++) {
            if (strcmp(dsTheLoai[k], theLoaiSach[chisoLuongDauSach]) == 0) {
                if (slTheoTL[k] >= 6) {
                    thanhTien *= (1.0f - 0.05f);
                }
                break;
            }
        }

        if (giaTungMH != NULL) {
            giaTungMH[j] = thanhTien;
        }
        tamTinh += thanhTien;
    }

    // Ap dung giam gia VIP neu co
    if (loaiTheKH[chiSoKH] == 1) {
        tamTinh *= (1.0f - 0.10f);
    }

    // Tinh thue VAT
    float tongTien = tamTinh * (1.0f + 0.10f);
    return tongTien;
}

/*
 * Thu thap thong tin hoa don tu nguoi dung, kiem tra hop le,
 * tinh tong tien va luu vao he thong, dong thoi cap nhat ton kho.
 */
void lapHoaDon() {
    if (soLuongHoaDon >= 100) {
        printf("\nSo hoa don da dat gioi han (%d)!\n", 100);
        return;
    }

    // Nhap ma khach hang
    char maKH[10];
    printf("Ma khach hang: ");
    docChuoi(maKH, 10);
    int chiSoKH = timdexKH(maKH);
    if (chiSoKH == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maKH);
        return;
    }
    printf("Khach hang: %s (%s)\n", tenKH[chiSoKH], loaiTheKH[chiSoKH] == 1 ? "VIP" : "Thuong");

    // Nhap ngay lap hoa don
    char ngay[12];
    printf("Ngay lap (dd/mm/yyyy): ");
    docChuoi(ngay, 12);
    
    // Nhap danh sach mat hang
    int soMatHang = 0;
    char dsISBNTam[20][14];
    int soLuongTam[20];

    printf("Nhap tung mat hang (ISBN + so luong). Nhap 'xong' de ket thuc.\n");

    while (soMatHang < 20) {
        char isbn[14];
        printf("  ISBN mat hang %d (hoac 'xong'):  \n", soMatHang + 1);
        docChuoi(isbn, 14);

        if (strcmp(isbn, "xong") == 0 || strlen(isbn) == 0) {
            break;
        }

        int chisoLuongDauSach = timChisoLuongDauSach(isbn);
        if (chisoLuongDauSach == -1) {
            printf("  Khong tim thay sach ISBN '%s'. Nhap lai.\n", isbn);
            continue;
        }

        // Hien thi thong tin sach va nhap so luong mua
        printf("  Sach: %s | Gia: %.0f | Ton kho: %d\n", tenSach[chisoLuongDauSach], giaBanSach[chisoLuongDauSach], soLuongTonKhoSach[chisoLuongDauSach]);
        printf("  So luong mua: ");
        int soLuong = nhapSoNguyen();

        if (soLuong <= 0) {
            printf("  So luong phai lon hon 0.\n");
            continue;
        }
        if (soLuong > soLuongTonKhoSach[chisoLuongDauSach]) {
            printf("  Khong du hang! Ton kho: %d quyen.\n", soLuongTonKhoSach[chisoLuongDauSach]);
            continue;
        }

        strcpy(dsISBNTam[soMatHang], isbn);
        soLuongTam[soMatHang] = soLuong;
        soMatHang++;
    }

    if (soMatHang == 0) {
        printf("Hoa don khong co mat hang nao. Huy bo.\n");
        return;
    }

    // Luu hoa don tam vao vi tri indexHD de tinh tong tien
    int indexHD = soLuongHoaDon;
    sprintf(maHoaDon[indexHD], "HD%03d", indexHD + 1);
    strcpy(maHoaDonKH[indexHD], maKH);
    strcpy(ngayLapHoaDon[indexHD], ngay);
    soMatHangTrongHoaDon[indexHD] = soMatHang;

    int j;
    for (j = 0; j < soMatHang; j++) {
        strcpy(isbnSachTrongHoaDon[indexHD][j], dsISBNTam[j]);
        soLuongDauSachTrongHoaDon[indexHD][j] = soLuongTam[j];
    }

    // Tinh tong tien
    float giaTungMH[20];
    float tongTien = tinhTongTien(indexHD, chiSoKH, giaTungMH);
    tongTienHoaDon[indexHD] = tongTien;

    // Hien thi tom tat hoa don
    printf("\n---------- TOM TAT HOA DON ----------\n");
    printf("Ma hoa don  : %s\n",  maHoaDon[indexHD]);
    printf("Khach hang  : %s (%s)\n", tenKH[chiSoKH], loaiTheKH[chiSoKH] == 1 ? "VIP" : "Thuong");
    printf("Ngay lap    : %s\n",  ngay);
    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");

    float tamTinhRaw = 0.0f;
    float tamTinhHD  = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(dsISBNTam[j]);
        float thanhTienRaw = giaBanSach[chisoLuongDauSach] * (float)soLuongTam[j];
        printf("%-14s %-28s %8d %12.0f %14.0f\n", dsISBNTam[j], tenSach[chisoLuongDauSach], soLuongTam[j], giaBanSach[chisoLuongDauSach], thanhTienRaw);
        tamTinhRaw += thanhTienRaw;
        tamTinhHD  += giaTungMH[j];
    }

    // Check va ap dung giam gia neu co giam gia theo so luong tung the loai
    if (tamTinhHD < tamTinhRaw - 0.5f) {
        printf("%*s %14.0f\n", 66, "Tong chua giam:", tamTinhRaw);
        printf("%*s %14.0f\n", 66, "Giam cung the loai (5%):", tamTinhHD - tamTinhRaw);
    }
    printf("%*s %14.0f\n", 66, "Tong truoc giam VIP:", tamTinhHD);
    // Check va ap dung giam gia neu co giam gia VIP
    if (loaiTheKH[chiSoKH] == 1) {
        printf("%*s %13.0f%%\n", 66, "Giam gia VIP (10%):", (float)(0.10f * 100));
        tamTinhHD *= (1.0f - 0.10f);
        printf("%*s %14.0f\n", 66, "Sau giam VIP:", tamTinhHD);
    }
    printf("%*s %14.0f\n", 66, "Thue VAT (10%):", tamTinhHD * 0.10f);
    printf("%*s %14.0f\n", 66, "TONG TIEN:", tongTien);

    // Luu chinh thuc va cap nhat ton kho
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(dsISBNTam[j]);
        soLuongTonKhoSach[chisoLuongDauSach] -= soLuongTam[j];
    }
    soLuongHoaDon++;
    printf(">> Lap hoa don %s thanh cong! Tong tien: %.0f VND\n", maHoaDon[indexHD], tongTien);
}

/*
 * In bang danh sach tat ca hoa don (ma, KH, ngay, tong tien).
 */
void xemDanhSachHoaDon() {
    if (soLuongHoaDon == 0) {
        printf("\nChua co hoa don nao trong he thong.\n");
        return;
    }
    printf("%-4s %-10s %-12s %-12s %16s\n", "STT", "Ma HD", "Ma KH", "Ngay Lap", "Tong Tien");
    int i;
    for (i = 0; i < soLuongHoaDon; i++) {
        printf("%-4d %-10s %-12s %-12s %16.0f\n", i + 1, maHoaDon[i], maHoaDonKH[i], ngayLapHoaDon[i], tongTienHoaDon[i]);
    }
}

/*
 * Nhap ma hoa don, tim va hien thi chi tiet tung mat hang,
 * giam gia ap dung va tong tien.
 */
void xemChiTietHoaDon() {
    char maHD[10];
    printf("Nhap ma hoa don: ");
    docChuoi(maHD, 10);

    // Tim hoa don
    int indexHD = -1, i;
    for (i = 0; i < soLuongHoaDon; i++) {
        if (strcmp(maHoaDon[i], maHD) == 0) {
            indexHD = i;
            break;
        }
    }
    if (indexHD == -1) {
        printf("Khong tim thay hoa don voi ma '%s'.\n", maHD);
        return;
    }

    int chiSoKH = timdexKH(maHoaDonKH[indexHD]);

    printf("\n===== HOA DON: %s =====\n",    maHoaDon[indexHD]);
    printf("Khach hang  : %s",               maHoaDonKH[indexHD]);
    if (chiSoKH >= 0) printf(" (%s - %s)", tenKH[chiSoKH], loaiTheKH[chiSoKH] == 1 ? "VIP" : "Thuong");
    printf("\nNgay lap    : %s\n",            ngayLapHoaDon[indexHD]);

    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");

    float giaTungMH[20];
    float tongTien = (chiSoKH >= 0)
                     ? tinhTongTien(indexHD, chiSoKH, giaTungMH)
                     : tongTienHoaDon[indexHD];

    float tamTinh = 0.0f;
    int j;
    for (j = 0; j < soMatHangTrongHoaDon[indexHD]; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[indexHD][j]);
        char tenSachBuf[50];
        if (chisoLuongDauSach >= 0) {
            strcpy(tenSachBuf, tenSach[chisoLuongDauSach]);
        } else {
            strcpy(tenSachBuf, "(da xoa)");
        }
        float donGia = (chisoLuongDauSach >= 0) ? giaBanSach[chisoLuongDauSach] : 0.0f;
        float thanhTien = (chiSoKH >= 0) ? giaTungMH[j] : 0.0f;

        printf("%-14s %-28s %8d %12.0f %14.0f\n", isbnSachTrongHoaDon[indexHD][j], tenSachBuf, soLuongDauSachTrongHoaDon[indexHD][j], donGia, thanhTien);
        tamTinh += thanhTien;
    }

    if (chiSoKH >= 0) {
        printf("%*s %14.0f\n", 66, "Tong truoc giam:", tamTinh);
        if (loaiTheKH[chiSoKH] == 1) {
            tamTinh *= (1.0f - 0.10f);
            printf("%*s %14.0f\n", 66, "Sau giam VIP (10%):", tamTinh);
        }
        printf("%*s %14.0f\n", 66, "VAT (10%):", tamTinh * 0.10f);
    }
    printf("%*s %14.0f\n", 66, "TONG TIEN:", tongTienHoaDon[indexHD]);
}

/*
 * Vong lap menu quan ly hoa don, cho nguoi dung chon chuc nang.
 */
void menuHoaDon() {
    int luaChon;
    do {
        printf("\n===== QUAN LY HOA DON =====\n");
        printf("1. Lap hoa don moi\n");
        printf("2. Xem danh sach hoa don\n");
        printf("3. Xem chi tiet hoa don\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        luaChon = nhapSoNguyen();

        switch (luaChon) {
            case 1:
                lapHoaDon();
                break;
            case 2:
                xemDanhSachHoaDon();
                break;
            case 3:
                xemChiTietHoaDon();
                break;
            case 0:
                break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}
