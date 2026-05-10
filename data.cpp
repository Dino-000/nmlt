#include <stdio.h>
#include "data.h"

// Thong tin lien quan den khach hang
char maKH[MAX_RECORD][MAX_MA];
char tenKH[MAX_RECORD][MAX_TEN];
char sdtKH[MAX_RECORD][MAX_SDT];
char mailKH[MAX_RECORD][MAX_EMAIL];
char diaChiKH [MAX_RECORD][MAX_DIA_CHI];
char ngayDangKyKH [MAX_RECORD][MAX_NGAY];
int loaiTheKH [MAX_RECORD];
int soLuongKH = 0;

// Thong tin lien quan den sach
char isbnSach[MAX_RECORD][MAX_ISBN];
char tenSach[MAX_RECORD][MAX_TEN];
char tacGiaSach[MAX_RECORD][MAX_TEN];
char nxbSach[MAX_RECORD][MAX_NXB];
int namXBSach[MAX_RECORD];
char theLoaiSach[MAX_RECORD][MAX_THE_LOAI];
float giaNhapSach[MAX_RECORD];
float giaBanSach[MAX_RECORD];
int soLuongTonKhoSach[MAX_RECORD];
int soLuongDauSach = 0;

// Thong tin lien quan den hoa don
char maHoaDon[MAX_RECORD][MAX_MA];
char maHoaDonKH[MAX_RECORD][MAX_MA];
char ngayLapHoaDon[MAX_RECORD][MAX_NGAY];
int soMatHangTrongHoaDon[MAX_RECORD];
char isbnSachTrongHoaDon[MAX_RECORD][MAX_SACH_HOA_DON][MAX_ISBN];
int soLuongDauSachTrongHoaDon[MAX_RECORD][MAX_SACH_HOA_DON];
float tongTienHoaDon[MAX_RECORD];
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
