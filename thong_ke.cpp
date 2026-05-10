#include "thong_ke.h"
#include "data.h"
#include "terminalIO.h"
#include <stdio.h>
#include <string.h>

/*
 * Cong toan bo soLuongTonKhoSach[i] va hien thi ket qua.
 */
void thongKeTongsoLuongDauSach() {
    if (soLuongDauSach == 0) {
        printf("Chua co sach nao trong he thong.\n");
        return;
    }

    int tongSoQuyen = 0, i;
    for (i = 0; i < soLuongDauSach; i++) {
        tongSoQuyen += soLuongTonKhoSach[i];
    }

    printf("Tong so dau sach : %d\n", soLuongDauSach);
    printf("Tong so quyen : %d quyen\n", tongSoQuyen);
}

/*
 * Xay dung danh sach the loai duy nhat, dem so dau sach
 * va tong so quyen theo tung the loai roi hien thi.
 */
void thongKeSachTheoTheLoai() {
    if (soLuongDauSach == 0) {
        printf("Chua co sach nao trong he thong.\n");
        return;
    }

    char dsTheLoai[100][50];
    int  soDauSachTheoTheLoai[100], tongQuyenSachTheoTheLoai[100];
    int  tongSoTheLoai = 0;
    int  i, j;

    //
    for (i = 0; i < soLuongDauSach; i++) {
        bool sachCungTheLoai = false;
        for (j = 0; j < tongSoTheLoai; j++) {
            if (strcmp(dsTheLoai[j], theLoaiSach[i]) == 0) {
                soDauSachTheoTheLoai[j]++;
                tongQuyenSachTheoTheLoai[j] += soLuongTonKhoSach[i];
                sachCungTheLoai = true;
                break;
            }
        }
        // Tao moi record neu chua ton tai
        if (!sachCungTheLoai) {
            strcpy(dsTheLoai[tongSoTheLoai], theLoaiSach[i]);
            soDauSachTheoTheLoai[tongSoTheLoai] = 1;
            tongQuyenSachTheoTheLoai[tongSoTheLoai] = soLuongTonKhoSach[i];
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
    if (soLuongKH == 0) {
        printf("Chua co khach hang nao trong he thong.\n");
        return;
    }

    int soThuong = 0, soVIP = 0, i;
    for (i = 0; i < soLuongKH; i++) {
        loaiTheKH[i] == 1 ? soVIP++ : soThuong++;
    }

    printf("Tong so khach hang : %d\n",  soLuongKH);
    printf("  The Thuong        : %d\n", soThuong);
    printf("  The VIP           : %d\n", soVIP);
}

/*
 * Cho nguoi dung chon tinh theo ngay (dd/mm/yyyy) hoac thang (mm/yyyy).
 * Duyet danh sach hoa don, cong tong tongTienHoaDon cua cac hoa don khop.
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

    char thoiGian[12];
    if (chon == 1) {
        printf("Nhap ngay (dd/mm/yyyy): ");
    } else {
        printf("Nhap thang (mm/yyyy): ");
    }
    docChuoi(thoiGian, 12);

    float tongDoanhThu = 0.0f;
    int soLuongHoaDonKhop = 0, i;

    for (i = 0; i < soLuongHoaDon; i++) {
        int trungKhop = 0;
        if (chon == 1) {
            // So sanh chinh xac toan bo ngay dd/mm/yyyy
            trungKhop = (strcmp(ngayLapHoaDon[i], thoiGian) == 0);
        } else {
            // So sanh phan mm/yyyy: ngayLapHoaDon[i] = "dd/mm/yyyy", bo 3 ki tu dau
            trungKhop = (strcmp(ngayLapHoaDon[i] + 3, thoiGian) == 0);
        }
        if (trungKhop) {
            tongDoanhThu += tongTienHoaDon[i];
            soLuongHoaDonKhop++;
        }
    }

    if (chon == 1) {
        printf("Ngay %s: %d hoa don, doanh thu = %.0f VND\n", thoiGian, soLuongHoaDonKhop, tongDoanhThu);
    } else {
        printf("Thang %s: %d hoa don, doanh thu = %.0f VND\n", thoiGian, soLuongHoaDonKhop, tongDoanhThu);
    }
}

/*
 * Duyet mang, in thong tin cac sach co soLuongTonKhoSach = 0.
 */
void thongKeSachHetHang() {
    int timThay = 0, i;
    for (i = 0; i < soLuongDauSach; i++) {
        if (soLuongTonKhoSach[i] == 0) {
            if (timThay == 0) {
                printf("%-14s %-32s %-20s %-12s\n", "ISBN", "Ten Sach", "Tac Gia", "The Loai");
            }
            printf("%-14s %-32s %-20s %-12s\n", isbnSach[i], tenSach[i], tacGiaSach[i], theLoaiSach[i]);
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
                thongKeTongsoLuongDauSach();
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
