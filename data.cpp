#include "data.h"

// Thong tin lien quan den khach hang
char kh_ma      [MAX_KHACH_HANG][MAX_MA];
char kh_hoTen   [MAX_KHACH_HANG][MAX_TEN];
char kh_sdt     [MAX_KHACH_HANG][MAX_SDT];
char kh_email   [MAX_KHACH_HANG][MAX_EMAIL];
char kh_diaChi  [MAX_KHACH_HANG][MAX_DIA_CHI];
char kh_ngayDK  [MAX_KHACH_HANG][MAX_NGAY];
int  kh_loaiThe [MAX_KHACH_HANG];
int  soKhachHang = 0;

// Thong tin lien quan den sach
char  sach_isbn    [MAX_SACH][MAX_ISBN];
char  sach_ten     [MAX_SACH][MAX_TEN];
char  sach_tacGia  [MAX_SACH][MAX_TEN];
char  sach_nxb     [MAX_SACH][MAX_NXB];
int   sach_namXB   [MAX_SACH];
char  sach_theLoai [MAX_SACH][MAX_THE_LOAI];
float sach_giaNhap [MAX_SACH];
float sach_giaBan  [MAX_SACH];
int   sach_soLuong [MAX_SACH];
int   soSach = 0;

// Thong tin lien quan den hoa don
char  hd_ma        [MAX_HOA_DON][MAX_MA];
char  hd_maKH      [MAX_HOA_DON][MAX_MA];
char  hd_ngay      [MAX_HOA_DON][MAX_NGAY];
int   hd_soMatHang [MAX_HOA_DON];
char  hd_isbn      [MAX_HOA_DON][MAX_MAT_HANG][MAX_ISBN];
int   hd_soLuong   [MAX_HOA_DON][MAX_MAT_HANG];
float hd_tongTien  [MAX_HOA_DON];
int   soHoaDon = 0;
