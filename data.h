#pragma once

// Khach hang
extern char maKH[100][10];
extern char tenKH[100][50];
extern char sdtKH[100][11];
extern char mailKH[100][50];
extern char diaChiKH[100][50];
extern char ngayDangKyKH[100][12];
extern int loaiTheKH[100];
extern int soLuongKH;

// Sach
extern char isbnSach[100][14];
extern char tenSach[100][50];
extern char tacGiaSach[100][50];
extern char nxbSach[100][50];
extern int  namXBSach[100];
extern char theLoaiSach[100][50];
extern float giaNhapSach[100];
extern float giaBanSach[100];
extern int soLuongTonKhoSach[100];
extern int soLuongDauSach;

// Hoa don
extern char maHoaDon[100][10];
extern char maHoaDonKH[100][10];
extern char ngayLapHoaDon[100][12];
extern int soMatHangTrongHoaDon[100];
extern char isbnSachTrongHoaDon[100][20][14];
extern int soLuongDauSachTrongHoaDon[100][20];
extern float tongTienHoaDon[100];
extern int soLuongHoaDon;

void xuatDataSangFile();