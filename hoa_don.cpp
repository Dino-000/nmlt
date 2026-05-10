#include "hoa_don.h"
#include "data.h"
#include "utils.h"
#include "khach_hang.h"
#include "sach.h"
#include <stdio.h>
#include <string.h>

/*
 * tinh tong tien hoa don tai chi so chiSoHD
 * ap dung: giam gia the loai (>5 quyen), giam gia VIP, VAT
 * Tham so: chiSoHD    - chi so hoa don trong mang
 *          chiSoKH    - chi so khach hang trong mang
 *          giaTungMH - mang float nhan gia sau giam cua tung mat hang (co the NULL neu khong can)
 * Gia tri tra ve: Tong tien cuoi cung (float)
 */
float tinhTongTien(int chiSoHD, int chiSoKH, float giaTungMH[MAX_MAT_HANG]) {
    int soMatHang = hd_soMatHang[chiSoHD];
    int j, k;

    // Tinh tong so luong sach o cung mot the loai trong hoa don 
    char dsTheLoai[MAX_MAT_HANG][MAX_THE_LOAI];
    int  slTheoTL[MAX_MAT_HANG];
    int  soTheLoai = 0;

    for (j = 0; j < soMatHang; j++) {
        int chiSoSach = timChiSoSach(hd_isbn[chiSoHD][j]);
        if (chiSoSach < 0) {
            continue;
        }

        // Tim the loai trong danh sach da co
        int chiSoTL = -1;
        for (k = 0; k < soTheLoai; k++) {
            if (strcmp(dsTheLoai[k], sach_theLoai[chiSoSach]) == 0) {
                chiSoTL = k;
                break;
            }
        }
        if (chiSoTL == -1) {
            chiSoTL = soTheLoai;
            strcpy(dsTheLoai[soTheLoai], sach_theLoai[chiSoSach]);
            slTheoTL[soTheLoai] = 0;
            soTheLoai++;
        }
        slTheoTL[chiSoTL] += hd_soLuong[chiSoHD][j];
    }

    // Tinh tong tien truoc khi giam gia VIP, co ap dung giam gia the loai
    float tamTinh = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chiSoSach = timChiSoSach(hd_isbn[chiSoHD][j]);
        if (chiSoSach < 0) {
            continue;
        }

        float thanhTien = sach_giaBan[chiSoSach] * (float)hd_soLuong[chiSoHD][j];

        // Kiem tra va ap dung giam gia theo so luong tung the loai (>5 quyen)
        for (k = 0; k < soTheLoai; k++) {
            if (strcmp(dsTheLoai[k], sach_theLoai[chiSoSach]) == 0) {
                if (slTheoTL[k] > NGUONG_SO_LUONG) {
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
    if (kh_loaiThe[chiSoKH] == THE_VIP) {
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
    if (soHoaDon >= MAX_HOA_DON) {
        printf("\nSo hoa don da dat gioi han (%d)!\n", MAX_HOA_DON);
        return;
    }

    // Nhap ma khach hang
    char maKH[MAX_MA];
    printf("Ma khach hang: ");
    docChuoi(maKH, MAX_MA);
    int chiSoKH = timChiSoKhachHang(maKH);
    if (chiSoKH == -1) {
        printf("Khong tim thay khach hang voi ma '%s'.\n", maKH);
        return;
    }
    printf("Khach hang: %s (%s)\n", kh_hoTen[chiSoKH], kh_loaiThe[chiSoKH] == THE_VIP ? "VIP" : "Thuong");

    // Nhap ngay lap hoa don
    char ngay[MAX_NGAY];
    printf("Ngay lap (dd/mm/yyyy): ");
    docChuoi(ngay, MAX_NGAY);
    
    // Nhap danh sach mat hang
    int soMatHang = 0;
    char dsISBNTam[MAX_MAT_HANG][MAX_ISBN];
    int soLuongTam[MAX_MAT_HANG];

    printf("Nhap tung mat hang (ISBN + so luong). Nhap 'xong' de ket thuc.\n");

    while (soMatHang < MAX_MAT_HANG) {
        char isbn[MAX_ISBN];
        printf("  ISBN mat hang %d (hoac 'xong'):  \n", soMatHang + 1);
        docChuoi(isbn, MAX_ISBN);

        if (strcmp(isbn, "xong") == 0 || strlen(isbn) == 0) {
            break;
        }

        int chiSoSach = timChiSoSach(isbn);
        if (chiSoSach == -1) {
            printf("  Khong tim thay sach ISBN '%s'. Nhap lai.\n", isbn);
            continue;
        }

        // Hien thi thong tin sach va nhap so luong mua
        printf("  Sach: %s | Gia: %.0f | Ton kho: %d\n", sach_ten[chiSoSach], sach_giaBan[chiSoSach], sach_soLuong[chiSoSach]);
        printf("  So luong mua: ");
        int soLuong = nhapSoNguyen();

        if (soLuong <= 0) {
            printf("  So luong phai lon hon 0.\n");
            continue;
        }
        if (soLuong > sach_soLuong[chiSoSach]) {
            printf("  Khong du hang! Ton kho: %d quyen.\n", sach_soLuong[chiSoSach]);
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
    int chiSoHD = soHoaDon;
    sprintf(hd_ma[chiSoHD], "HD%03d", chiSoHD + 1);
    strcpy(hd_maKH[chiSoHD], maKH);
    strcpy(hd_ngay[chiSoHD], ngay);
    hd_soMatHang[chiSoHD] = soMatHang;

    int j;
    for (j = 0; j < soMatHang; j++) {
        strcpy(hd_isbn[chiSoHD][j], dsISBNTam[j]);
        hd_soLuong[chiSoHD][j] = soLuongTam[j];
    }

    // Tinh tong tien
    float giaTungMH[MAX_MAT_HANG];
    float tongTien = tinhTongTien(chiSoHD, chiSoKH, giaTungMH);
    hd_tongTien[chiSoHD] = tongTien;

    // Hien thi tom tat hoa don
    printf("\n---------- TOM TAT HOA DON ----------\n");
    printf("Ma hoa don  : %s\n",  hd_ma[chiSoHD]);
    printf("Khach hang  : %s (%s)\n", kh_hoTen[chiSoKH], kh_loaiThe[chiSoKH] == THE_VIP ? "VIP" : "Thuong");
    printf("Ngay lap    : %s\n",  ngay);
    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");
    inDuongKe(80, '-');

    float tamTinhRaw = 0.0f;
    float tamTinhHD  = 0.0f;
    for (j = 0; j < soMatHang; j++) {
        int chiSoSach = timChiSoSach(dsISBNTam[j]);
        float thanhTienRaw = sach_giaBan[chiSoSach] * (float)soLuongTam[j];
        printf("%-14s %-28s %8d %12.0f %14.0f\n", dsISBNTam[j], sach_ten[chiSoSach], soLuongTam[j], sach_giaBan[chiSoSach], thanhTienRaw);
        tamTinhRaw += thanhTienRaw;
        tamTinhHD  += giaTungMH[j];
    }

    inDuongKe(80, '-');
    if (tamTinhHD < tamTinhRaw - 0.5f) {
        printf("%*s %14.0f\n", 66, "Tong chua giam:", tamTinhRaw);
        printf("%*s %14.0f\n", 66, "Giam cung the loai (5%):", tamTinhHD - tamTinhRaw);
    }
    printf("%*s %14.0f\n", 66, "Tong truoc giam VIP:", tamTinhHD);
    if (kh_loaiThe[chiSoKH] == THE_VIP) {
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
        int chiSoSach = timChiSoSach(dsISBNTam[j]);
        sach_soLuong[chiSoSach] -= soLuongTam[j];
    }
    soHoaDon++;
    printf(">> Lap hoa don %s thanh cong! Tong tien: %.0f VND\n", hd_ma[chiSoHD], tongTien);
}

/*
 * In bang danh sach tat ca hoa don (ma, KH, ngay, tong tien).
 */
void xemDanhSachHoaDon() {
    if (soHoaDon == 0) {
        printf("\nChua co hoa don nao trong he thong.\n");
        return;
    }
    printf("%-4s %-10s %-12s %-12s %16s\n", "STT", "Ma HD", "Ma KH", "Ngay Lap", "Tong Tien");
    inDuongKe(60, '-');
    int i;
    for (i = 0; i < soHoaDon; i++) {
        printf("%-4d %-10s %-12s %-12s %16.0f\n", i + 1, hd_ma[i], hd_maKH[i], hd_ngay[i], hd_tongTien[i]);
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

    /* Tim hoa don */
    int chiSoHD = -1, i;
    for (i = 0; i < soHoaDon; i++) {
        if (strcmp(hd_ma[i], maHD) == 0) {
            chiSoHD = i;
            break;
        }
    }
    if (chiSoHD == -1) {
        printf("Khong tim thay hoa don voi ma '%s'.\n", maHD);
        return;
    }

    int chiSoKH = timChiSoKhachHang(hd_maKH[chiSoHD]);

    printf("\n===== HOA DON: %s =====\n",    hd_ma[chiSoHD]);
    printf("Khach hang  : %s",               hd_maKH[chiSoHD]);
    if (chiSoKH >= 0) printf(" (%s - %s)", kh_hoTen[chiSoKH], kh_loaiThe[chiSoKH] == THE_VIP ? "VIP" : "Thuong");
    printf("\nNgay lap    : %s\n",            hd_ngay[chiSoHD]);

    printf("%-14s %-28s %8s %12s %14s\n", "ISBN", "Ten sach", "SL", "Don gia", "Thanh tien");
    inDuongKe(80, '-');

    float giaTungMH[MAX_MAT_HANG];
    float tongTien = (chiSoKH >= 0)
                     ? tinhTongTien(chiSoHD, chiSoKH, giaTungMH)
                     : hd_tongTien[chiSoHD];

    float tamTinh = 0.0f;
    int j;
    for (j = 0; j < hd_soMatHang[chiSoHD]; j++) {
        int chiSoSach = timChiSoSach(hd_isbn[chiSoHD][j]);
        const char* tenSach = (chiSoSach >= 0) ? sach_ten[chiSoSach] : "(da xoa)";
        float donGia = (chiSoSach >= 0) ? sach_giaBan[chiSoSach] : 0.0f;
        float thanhTien = (chiSoKH >= 0) ? giaTungMH[j] : 0.0f;

        printf("%-14s %-28s %8d %12.0f %14.0f\n", hd_isbn[chiSoHD][j], tenSach, hd_soLuong[chiSoHD][j], donGia, thanhTien);
        tamTinh += thanhTien;
    }

    inDuongKe(80, '-');
    if (chiSoKH >= 0) {
        printf("%*s %14.0f\n", 66, "Tong truoc giam:", tamTinh);
        if (kh_loaiThe[chiSoKH] == THE_VIP) {
            tamTinh *= (1.0f - GIAM_GIA_VIP);
            printf("%*s %14.0f\n", 66, "Sau giam VIP (10%):", tamTinh);
        }
        printf("%*s %14.0f\n", 66, "VAT (10%):", tamTinh * THUE_VAT);
    }
    printf("%*s %14.0f\n", 66, "TONG TIEN:", hd_tongTien[chiSoHD]);
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
