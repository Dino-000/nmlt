#pragma once
#include "meta.h"

// Khach hang
extern char maKH[MAX_RECORD][MAX_MA];
extern char tenKH[MAX_RECORD][MAX_TEN];
extern char sdtKH[MAX_RECORD][MAX_SDT];
extern char mailKH[MAX_RECORD][MAX_EMAIL];
extern char diaChiKH[MAX_RECORD][MAX_DIA_CHI];
extern char ngayDangKyKH[MAX_RECORD][MAX_NGAY];
extern int loaiTheKH[MAX_RECORD];
extern int soLuongKH;

// Sach
extern char isbnSach[MAX_RECORD][MAX_ISBN];
extern char tenSach[MAX_RECORD][MAX_TEN];
extern char tacGiaSach[MAX_RECORD][MAX_TEN];
extern char nxbSach[MAX_RECORD][MAX_NXB];
extern int  namXBSach[MAX_RECORD];
extern char theLoaiSach[MAX_RECORD][MAX_THE_LOAI];
extern float giaNhapSach[MAX_RECORD];
extern float giaBanSach[MAX_RECORD];
extern int soLuongTonKhoSach[MAX_RECORD];
extern int soLuongDauSach;

// Hoa don
extern char maHoaDon[MAX_RECORD][MAX_MA];
extern char maHoaDonKH[MAX_RECORD][MAX_MA];
extern char ngayLapHoaDon[MAX_RECORD][MAX_NGAY];
extern int soMatHangTrongHoaDon[MAX_RECORD];
extern char isbnSachTrongHoaDon[MAX_RECORD][MAX_SACH_HOA_DON][MAX_ISBN];
extern int soLuongDauSachTrongHoaDon[MAX_RECORD][MAX_SACH_HOA_DON];
extern float tongTienHoaDon[MAX_RECORD];
extern int soLuongHoaDon;

void xuatDataSangFile();