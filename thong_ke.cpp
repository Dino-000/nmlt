#include "thong_ke.h"
#include "data.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

/*
 * Cong toan bo sach_soLuong[i] va hien thi ket qua.
 */
void thongKeTongSoSach() {
    if (soSach == 0) {
        printf("Chua co sach nao trong he thong.\n");
        return;
    }

    int tongSoQuyen = 0, i;
    for (i = 0; i < soSach; i++) {
        tongSoQuyen += sach_soLuong[i];
    }

    printf("Tong so dau sach : %d\n", soSach);
    printf("Tong so quyen : %d quyen\n", tongSoQuyen);
}

/*
 * Xay dung danh sach the loai duy nhat, dem so dau sach
 * va tong so quyen theo tung the loai roi hien thi.
 */
void thongKeSachTheoTheLoai() {
    if (soSach == 0) {
        printf("Chua co sach nao trong he thong.\n");
        return;
    }

    char dsTheLoai[MAX_SACH][MAX_THE_LOAI];
    int  soDauSachTheoTheLoai[MAX_SACH], tongQuyenSachTheoTheLoai[MAX_SACH];
    int  tongSoTheLoai = 0;
    int  i, j;

    //
    for (i = 0; i < soSach; i++) {
        bool sachCungTheLoai = false;
        for (j = 0; j < tongSoTheLoai; j++) {
            if (strcmp(dsTheLoai[j], sach_theLoai[i]) == 0) {
                soDauSachTheoTheLoai[j]++;
                tongQuyenSachTheoTheLoai[j] += sach_soLuong[i];
                sachCungTheLoai = true;
                break;
            }
        }
        // Tao moi record neu chua ton tai
        if (!sachCungTheLoai) {
            strcpy(dsTheLoai[tongSoTheLoai], sach_theLoai[i]);
            soDauSachTheoTheLoai[tongSoTheLoai] = 1;
            tongQuyenSachTheoTheLoai[tongSoTheLoai] = sach_soLuong[i];
            tongSoTheLoai++;
        }
    }

    printf("%-20s %12s %12s\n", "The Loai", "So Dau Sach", "Tong Quyen");
    for (j = 0; j < tongSoTheLoai; j++) {
        printf("%-20s %12d %12d\n", dsTheLoai[j], soDauSachTheoTheLoai[j], tongQuyenSachTheoTheLoai[j]);
    }
}

/*
 * Dem so khach hang Thuong va VIP va hien thi.
 */
void thongKeKhachHangTheoLoaiThe() {
    if (soKhachHang == 0) {
        printf("Chua co khach hang nao trong he thong.\n");
        return;
    }

    int soThuong = 0, soVIP = 0, i;
    for (i = 0; i < soKhachHang; i++) {
        kh_loaiThe[i] == THE_VIP ? soVIP++ : soThuong++;
    }

    printf("Tong so khach hang : %d\n",  soKhachHang);
    printf("  The Thuong        : %d\n", soThuong);
    printf("  The VIP           : %d\n", soVIP);
}

/*
 * Cho nguoi dung chon tinh theo ngay (dd/mm/yyyy) hoac thang (mm/yyyy).
 * Duyet danh sach hoa don, cong tong hd_tongTien cua cac hoa don khop.
 */
void tinhDoanhThu() {
    printf("1. Theo ngay  (dd/mm/yyyy)\n");
    printf("2. Theo thang (mm/yyyy)\n");
    printf("Chon: ");
    int chon = nhapSoNguyen();

    if (chon != 1 && chon != 2) {
        printf("Lua chon khong hop le.\n");
        return;
    }

    char thoiGian[MAX_NGAY];
    if (chon == 1) {
        printf("Nhap ngay (dd/mm/yyyy): ");
    } else {
        printf("Nhap thang (mm/yyyy): ");
    }
    docChuoi(thoiGian, MAX_NGAY);

    float tongDoanhThu = 0.0f;
    int soHoaDonKhop = 0, i;

    for (i = 0; i < soHoaDon; i++) {
        int trungKhop = 0;
        if (chon == 1) {
            // So sanh chinh xac toan bo ngay dd/mm/yyyy
            trungKhop = (strcmp(hd_ngay[i], thoiGian) == 0);
        } else {
            // So sanh phan mm/yyyy: hd_ngay[i] = "dd/mm/yyyy", bo 3 ki tu dau
            trungKhop = (strcmp(hd_ngay[i] + 3, thoiGian) == 0);
        }
        if (trungKhop) {
            tongDoanhThu += hd_tongTien[i];
            soHoaDonKhop++;
        }
    }

    if (chon == 1) {
        printf("Ngay %s: %d hoa don, doanh thu = %.0f VND\n", thoiGian, soHoaDonKhop, tongDoanhThu);
    } else {
        printf("Thang %s: %d hoa don, doanh thu = %.0f VND\n", thoiGian, soHoaDonKhop, tongDoanhThu);
    }
}

/*
 * Duyet mang, in thong tin cac sach co sach_soLuong = 0.
 */
void thongKeSachHetHang() {
    int timThay = 0, i;
    for (i = 0; i < soSach; i++) {
        if (sach_soLuong[i] == 0) {
            if (timThay == 0) {
                printf("%-14s %-32s %-20s %-12s\n", "ISBN", "Ten Sach", "Tac Gia", "The Loai");
                inDuongKe(82, '-');
            }
            printf("%-14s %-32s %-20s %-12s\n", sach_isbn[i], sach_ten[i], sach_tacGia[i], sach_theLoai[i]);
            timThay++;
        }
    }
    if (!timThay) {
        printf("Khong co sach nao het hang.\n");
    } else {
        printf("\nTong cong: %d dau sach het hang.\n", timThay);
    }
}

/*
 * Vong lap menu thong ke, cho nguoi dung chon chuc nang.
 */
void menuThongKe() {
    int luaChon;
    do {
        printf("\n===== THONG KE =====\n");
        printf("1. Tong so sach trong kho\n");
        printf("2. So sach theo the loai\n");
        printf("3. Khach hang theo loai the\n");
        printf("4. Doanh thu theo ngay/thang\n");
        printf("5. Danh sach sach het hang\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        luaChon = nhapSoNguyen();

        switch (luaChon) {
            case 1:
                thongKeTongSoSach();
                break;
            case 2:
                thongKeSachTheoTheLoai();
                break;
            case 3:
                thongKeKhachHangTheoLoaiThe();
                break;
            case 4:
                tinhDoanhThu();
                break;
            case 5:
                thongKeSachHetHang();
                break;
            case 0:
                break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);
}
