#include <stdio.h>
#include <string.h>
#include "hoa_don.h"
#include "data.h"
#include "utils.h"
#include "khach_hang.h"
#include "sach.h"

/*
 * tinh tong tien hoa don tai chi so chiSoHD
 * ap dung: giam gia the loai (>5 quyen), giam gia VIP, VAT
 * Tham so: chiSoHD    - chi so hoa don trong mang
 *          chiSoKH    - chi so khach hang trong mang
 *          giaTungMH - mang float nhan gia sau giam cua tung mat hang (co the NULL neu khong can)
 * Gia tri tra ve: Tong tien cuoi cung (float)
 */
float tinhTongTien(int chiSoHD, int chiSoKH, float giaTungMH[MAX_SACH_HOA_DON]) {
    int soMatHang = soMatHangTrongHoaDon[chiSoHD];
    int j, k;

    // Tinh tong so luong sach o cung mot the loai trong hoa don 
    char dsTheLoai[MAX_SACH_HOA_DON][MAX_THE_LOAI];
    int  slTheoTL[MAX_SACH_HOA_DON];
    int  soTheLoai = 0;

    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[chiSoHD][j]);
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
        slTheoTL[chiSoTL] += soLuongDauSachTrongHoaDon[chiSoHD][j];
    }

    // Tinh tong tien truoc khi giam gia VIP, co ap dung giam gia the loai
    float tamTinh = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[chiSoHD][j]);
        if (chisoLuongDauSach < 0) {
            continue;
        }

        float thanhTien = giaBanSach[chisoLuongDauSach] * (float)soLuongDauSachTrongHoaDon[chiSoHD][j];

        // Kiem tra va ap dung giam gia theo so luong tung the loai (>5 quyen)
        for (k = 0; k < soTheLoai; k++) {
            if (strcmp(dsTheLoai[k], theLoaiSach[chisoLuongDauSach]) == 0) {
                if (slTheoTL[k] >= SO_SACH_CUNG_LOAI_MIN) {
                    thanhTien *= (1.0f - GIAM_GIA_SO_LUONG);
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
    if (loaiTheKH[chiSoKH] == THE_VIP) {
        tamTinh *= (1.0f - GIAM_GIA_VIP);
    }

    // Tinh thue VAT
    float tongTien = tamTinh * (1.0f + THUE_VAT);
    return tongTien;
}

/*
 * Thu thap thong tin hoa don tu nguoi dung, kiem tra hop le,
 * tinh tong tien va luu vao he thong, dong thoi cap nhat ton kho.
 */
void lapHoaDon() {
    if (soLuongHoaDon >= MAX_RECORD) {
        printf("\nSo hoa don da dat gioi han (%d)!\n", MAX_RECORD);
        return;
    }

    // Nhap ma khach hang
    char maKH[MAX_MA];
    printf("Ma khach hang: ");
    docChuoi(maKH, MAX_MA);
    int chiSoKH = timChisoLuongKH(maKH);
    if (chiSoKH == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maKH);
        return;
    }
    printf("Khach hang: %s (%s)\n", tenKH[chiSoKH], loaiTheKH[chiSoKH] == THE_VIP ? "VIP" : "Thuong");

    // Nhap ngay lap hoa don
    char ngay[MAX_NGAY];
    printf("Ngay lap (dd/mm/yyyy): ");
    docChuoi(ngay, MAX_NGAY);
    
    // Nhap danh sach mat hang
    int soMatHang = 0;
    char dsISBNTam[MAX_SACH_HOA_DON][MAX_ISBN];
    int soLuongTam[MAX_SACH_HOA_DON];

    printf("Nhap tung mat hang (ISBN + so luong). Nhap 'xong' de ket thuc.\n");

    while (soMatHang < MAX_SACH_HOA_DON) {
        char isbn[MAX_ISBN];
        printf("  ISBN mat hang %d (hoac 'xong'):  \n", soMatHang + 1);
        docChuoi(isbn, MAX_ISBN);

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

    // Luu hoa don tam vao vi tri chiSoHD de tinh tong tien
    int chiSoHD = soLuongHoaDon;
    sprintf(maHoaDon[chiSoHD], "HD%03d", chiSoHD + 1);
    strcpy(maHoaDonKH[chiSoHD], maKH);
    strcpy(ngayLapHoaDon[chiSoHD], ngay);
    soMatHangTrongHoaDon[chiSoHD] = soMatHang;

    int j;
    for (j = 0; j < soMatHang; j++) {
        strcpy(isbnSachTrongHoaDon[chiSoHD][j], dsISBNTam[j]);
        soLuongDauSachTrongHoaDon[chiSoHD][j] = soLuongTam[j];
    }

    // Tinh tong tien
    float giaTungMH[MAX_SACH_HOA_DON];
    float tongTien = tinhTongTien(chiSoHD, chiSoKH, giaTungMH);
    tongTienHoaDon[chiSoHD] = tongTien;

    // Hien thi tom tat hoa don
    printf("\n---------- TOM TAT HOA DON ----------\n");
    printf("Ma hoa don  : %s\n",  maHoaDon[chiSoHD]);
    printf("Khach hang  : %s (%s)\n", tenKH[chiSoKH], loaiTheKH[chiSoKH] == THE_VIP ? "VIP" : "Thuong");
    printf("Ngay lap    : %s\n",  ngay);
    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");
    inDuongKe(80, '-');

    float tamTinhRaw = 0.0f;
    float tamTinhHD  = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(dsISBNTam[j]);
        float thanhTienRaw = giaBanSach[chisoLuongDauSach] * (float)soLuongTam[j];
        printf("%-14s %-28s %8d %12.0f %14.0f\n", dsISBNTam[j], tenSach[chisoLuongDauSach], soLuongTam[j], giaBanSach[chisoLuongDauSach], thanhTienRaw);
        tamTinhRaw += thanhTienRaw;
        tamTinhHD  += giaTungMH[j];
    }

    inDuongKe(80, '-');
    // Check va ap dung giam gia neu co giam gia theo so luong tung the loai
    if (tamTinhHD < tamTinhRaw - 0.5f) {
        printf("%*s %14.0f\n", 66, "Tong chua giam:", tamTinhRaw);
        printf("%*s %14.0f\n", 66, "Giam cung the loai (5%):", tamTinhHD - tamTinhRaw);
    }
    printf("%*s %14.0f\n", 66, "Tong truoc giam VIP:", tamTinhHD);
    // Check va ap dung giam gia neu co giam gia VIP
    if (loaiTheKH[chiSoKH] == THE_VIP) {
        printf("%*s %13.0f%%\n", 66, "Giam gia VIP (10%):", (float)(GIAM_GIA_VIP * 100));
        tamTinhHD *= (1.0f - GIAM_GIA_VIP);
        printf("%*s %14.0f\n", 66, "Sau giam VIP:", tamTinhHD);
    }
    printf("%*s %14.0f\n", 66, "Thue VAT (10%):", tamTinhHD * THUE_VAT);
    printf("%*s %14.0f\n", 66, "TONG TIEN:", tongTien);
    inDuongKe(80, '=');

    printf("Xac nhan tao hoa don? (y/n): ");
    char xacNhan[5];
    docChuoi(xacNhan, 5);
    if (xacNhan[0] != 'y' && xacNhan[0] != 'Y') {
        printf("Huy bo hoa don.\n");
        return;
    }

    // Luu chinh thuc va cap nhat ton kho
    for (j = 0; j < soMatHang; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(dsISBNTam[j]);
        soLuongTonKhoSach[chisoLuongDauSach] -= soLuongTam[j];
    }
    soLuongHoaDon++;
    printf(">> Lap hoa don %s thanh cong! Tong tien: %.0f VND\n", maHoaDon[chiSoHD], tongTien);
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
    inDuongKe(60, '-');
    int i;
    for (i = 0; i < soLuongHoaDon; i++) {
        printf("%-4d %-10s %-12s %-12s %16.0f\n", i + 1, maHoaDon[i], maHoaDonKH[i], ngayLapHoaDon[i], tongTienHoaDon[i]);
    }
    inDuongKe(60, '=');
}

/*
 * Nhap ma hoa don, tim va hien thi chi tiet tung mat hang,
 * giam gia ap dung va tong tien.
 */
void xemChiTietHoaDon() {
    char maHD[MAX_MA];
    printf("Nhap ma hoa don: ");
    docChuoi(maHD, MAX_MA);

    // Tim hoa don
    int chiSoHD = -1, i;
    for (i = 0; i < soLuongHoaDon; i++) {
        if (strcmp(maHoaDon[i], maHD) == 0) {
            chiSoHD = i;
            break;
        }
    }
    if (chiSoHD == -1) {
        printf("Khong tim thay hoa don voi ma '%s'.\n", maHD);
        return;
    }

    int chiSoKH = timChisoLuongKH(maHoaDonKH[chiSoHD]);

    printf("\n===== HOA DON: %s =====\n",    maHoaDon[chiSoHD]);
    printf("Khach hang  : %s",               maHoaDonKH[chiSoHD]);
    if (chiSoKH >= 0) printf(" (%s - %s)", tenKH[chiSoKH], loaiTheKH[chiSoKH] == THE_VIP ? "VIP" : "Thuong");
    printf("\nNgay lap    : %s\n",            ngayLapHoaDon[chiSoHD]);

    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");
    inDuongKe(80, '-');

    float giaTungMH[MAX_SACH_HOA_DON];
    float tongTien = (chiSoKH >= 0)
                     ? tinhTongTien(chiSoHD, chiSoKH, giaTungMH)
                     : tongTienHoaDon[chiSoHD];

    float tamTinh = 0.0f;
    int j;
    for (j = 0; j < soMatHangTrongHoaDon[chiSoHD]; j++) {
        int chisoLuongDauSach = timChisoLuongDauSach(isbnSachTrongHoaDon[chiSoHD][j]);
        char tenSachBuf[MAX_TEN];
        if (chisoLuongDauSach >= 0) {
            strcpy(tenSachBuf, tenSach[chisoLuongDauSach]);
        } else {
            strcpy(tenSachBuf, "(da xoa)");
        }
        float donGia = (chisoLuongDauSach >= 0) ? giaBanSach[chisoLuongDauSach] : 0.0f;
        float thanhTien = (chiSoKH >= 0) ? giaTungMH[j] : 0.0f;

        printf("%-14s %-28s %8d %12.0f %14.0f\n", isbnSachTrongHoaDon[chiSoHD][j], tenSachBuf, soLuongDauSachTrongHoaDon[chiSoHD][j], donGia, thanhTien);
        tamTinh += thanhTien;
    }

    inDuongKe(80, '-');
    if (chiSoKH >= 0) {
        printf("%*s %14.0f\n", 66, "Tong truoc giam:", tamTinh);
        if (loaiTheKH[chiSoKH] == THE_VIP) {
            tamTinh *= (1.0f - GIAM_GIA_VIP);
            printf("%*s %14.0f\n", 66, "Sau giam VIP (10%):", tamTinh);
        }
        printf("%*s %14.0f\n", 66, "VAT (10%):", tamTinh * THUE_VAT);
    }
    printf("%*s %14.0f\n", 66, "TONG TIEN:", tongTienHoaDon[chiSoHD]);
    inDuongKe(80, '=');
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
