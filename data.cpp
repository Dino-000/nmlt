#include <stdio.h>
#include "data.h"

// Thong tin lien quan den khach hang
char maKH[100][10];
char tenKH[100][50];
char sdtKH[100][11];
char mailKH[100][50];
char diaChiKH [100][50];
char ngayDangKyKH [100][12];
int loaiTheKH [100];
int soLuongKH = 0;

// Thong tin lien quan den sach
char isbnSach[100][14];
char tenSach[100][50];
char tacGiaSach[100][50];
char nxbSach[100][50];
int namXBSach[100];
char theLoaiSach[100][50];
float giaNhapSach[100];
float giaBanSach[100];
int soLuongTonKhoSach[100];
int soLuongDauSach = 0;

// Thong tin lien quan den hoa don
char maHoaDon[100][10];
char maHoaDonKH[100][10];
char ngayLapHoaDon[100][12];
int soMatHangTrongHoaDon[100];
char isbnSachTrongHoaDon[100][20][14];
int soLuongDauSachTrongHoaDon[100][20];
float tongTienHoaDon[100];
int soLuongHoaDon = 0;

void xuatDataSangFile() {
    for (int i = 0; i < soLuongKH; i++) {
        printf("KH|%s|%s|%s|%s|%s|%s|%d\n", maKH[i], tenKH[i], sdtKH[i], mailKH[i], diaChiKH[i], ngayDangKyKH[i], loaiTheKH[i]);
    }
    for (int i = 0; i < soLuongDauSach; i++) {
        printf("SACH|%s|%s|%s|%s|%d|%s|%.0f|%.0f|%d\n", isbnSach[i], tenSach[i], tacGiaSach[i], nxbSach[i], namXBSach[i], theLoaiSach[i], giaNhapSach[i], giaBanSach[i], soLuongTonKhoSach[i]);
    }
    for (int i = 0; i < soLuongHoaDon; i++) {
        printf("HD|%s|%s|%s|%d", maHoaDon[i], maHoaDonKH[i], ngayLapHoaDon[i], soMatHangTrongHoaDon[i]);
        for (int j = 0; j < soMatHangTrongHoaDon[i]; j++) {
            printf("|%s|%d", isbnSachTrongHoaDon[i][j], soLuongDauSachTrongHoaDon[i][j]);
        }
        printf("|%.0f\n", tongTienHoaDon[i]);
    }
}
