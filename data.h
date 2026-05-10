#pragma once

#include "constants.h"

extern char kh_ma      [MAX_KHACH_HANG][MAX_MA];
extern char kh_hoTen   [MAX_KHACH_HANG][MAX_TEN];
extern char kh_sdt     [MAX_KHACH_HANG][MAX_SDT];
extern char kh_email   [MAX_KHACH_HANG][MAX_EMAIL];
extern char kh_diaChi  [MAX_KHACH_HANG][MAX_DIA_CHI];
extern char kh_ngayDK  [MAX_KHACH_HANG][MAX_NGAY];
extern int  kh_loaiThe [MAX_KHACH_HANG];
extern int  soKhachHang;

extern char  sach_isbn    [MAX_SACH][MAX_ISBN];
extern char  sach_ten     [MAX_SACH][MAX_TEN];
extern char  sach_tacGia  [MAX_SACH][MAX_TEN];
extern char  sach_nxb     [MAX_SACH][MAX_NXB];
extern int   sach_namXB   [MAX_SACH];
extern char  sach_theLoai [MAX_SACH][MAX_THE_LOAI];
extern float sach_giaNhap [MAX_SACH];
extern float sach_giaBan  [MAX_SACH];
extern int   sach_soLuong [MAX_SACH];
extern int   soSach;

extern char  hd_ma        [MAX_HOA_DON][MAX_MA];
extern char  hd_maKH      [MAX_HOA_DON][MAX_MA];
extern char  hd_ngay      [MAX_HOA_DON][MAX_NGAY];
extern int   hd_soMatHang [MAX_HOA_DON];
extern char  hd_isbn      [MAX_HOA_DON][MAX_MAT_HANG][MAX_ISBN];
extern int   hd_soLuong   [MAX_HOA_DON][MAX_MAT_HANG];
extern float hd_tongTien  [MAX_HOA_DON];
extern int   soHoaDon;
