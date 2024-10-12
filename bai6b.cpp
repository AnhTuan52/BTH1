#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

struct HocSinh {
    string hoTen;
    float diemToan, diemVan, diemAnh, diemTrungBinh;
    string phanLoai;
};
bool KiemTraHoTen(const string& hoTen) {
    if (hoTen.empty()) return false;

    bool isFirstLetter = true;  // Đánh dấu ký tự đầu mỗi từ
    for (char c : hoTen) {
        if (isdigit(c)) return false;  // Không được chứa số
        if (!isalpha(c) && !isspace(c)) return false;  // Không được chứa ký tự đặc biệt
        if (isFirstLetter) {  // Kiểm tra ký tự đầu của mỗi từ
            if (!isupper(c)) return false;  // Ký tự đầu phải viết hoa
            isFirstLetter = false;
        }
        if (isspace(c)) isFirstLetter = true;  // Đặt lại dấu hiệu khi gặp khoảng trắng
    }
    return true;
}

float NhapDiem(const string &mon) 
     {
    float  bien_thu_diem;
        cout << "Nhap diem " << mon << " (0-10): ";
        cin >> bien_thu_diem;
        while (isalpha(bien_thu_diem) || bien_thu_diem <0 || bien_thu_diem >10)
        { 
            cout << "Diem khong hop le vui long nhap lai.\n";
            cin >> bien_thu_diem;
        } 
        return bien_thu_diem;
}
void TinhDiemTrungBinh(float &diemTrungBinh, float diemToan, float diemVan, float diemAnh) {
    diemTrungBinh = (2 * diemToan + diemVan + diemAnh) / 4;
}
void PhanLoaiHocSinh(string &phanLoai, float diemTrungBinh) {
    if (diemTrungBinh >= 9) {
        phanLoai = "Xuat sac";
    } else if (diemTrungBinh >= 8) {
        phanLoai = "Gioi";
    } else if (diemTrungBinh >= 6.5) {
        phanLoai = "Kha";
    } else if (diemTrungBinh >= 5) {
        phanLoai = "Trung binh";
    } else {
        phanLoai = "Yeu";
    }
}
void NhapThongTinHocSinh(HocSinh &hs) {
    while (true) 
    {
        cout << "Nhap Ho va Ten: ";
        getline(cin, hs.hoTen);
        if (KiemTraHoTen(hs.hoTen)) break;
        cout << "Ho Ten khong hop le, vui long nhap lai.\n";
    }
        hs.diemToan = NhapDiem("Toan");
        hs.diemVan = NhapDiem("Van");
        hs.diemAnh = NhapDiem("Ngoai ngu");
        TinhDiemTrungBinh(hs.diemTrungBinh, hs.diemToan, hs.diemVan, hs.diemAnh);
        PhanLoaiHocSinh(hs.phanLoai, hs.diemTrungBinh);
        cin.ignore();
}

void XuatThongTinHocSinh(const HocSinh &hs) {
    cout << "Ho Ten: " << hs.hoTen << endl;
    cout << "Diem Toan: " << hs.diemToan << ", Diem Van: " << hs.diemVan << ", Diem Anh: " << hs.diemAnh << endl;
    cout << "Diem trung binh: " << hs.diemTrungBinh << ", Phan loai: " << hs.phanLoai << endl;
}

void TimHocSinhDiemCaoNhat(const vector<HocSinh> &danhSachHocSinh) {
    auto maxIt = max_element(danhSachHocSinh.begin(), danhSachHocSinh.end(),
                             [](const HocSinh &a, const HocSinh &b) {
                                 return a.diemTrungBinh < b.diemTrungBinh;
                             });
    cout << "\nHoc sinh co diem trung binh cao nhat :\n";
    XuatThongTinHocSinh(*maxIt);
}

void TimHocSinhTheoTen(const vector<HocSinh> &danhSachHocSinh, const string &tuKhoa) {
    cout << "\nKet qua tim kiem theo ten \"" << tuKhoa << "\":\n";
    bool timThay = false;
    for (const auto &hs : danhSachHocSinh) {
        string hoTen = hs.hoTen;
        transform(hoTen.begin(), hoTen.end(), hoTen.begin(), ::tolower);  
        string tuKhoaThuong = tuKhoa;
        transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);
        if (hoTen.find(tuKhoaThuong) != string::npos) 
        {
            XuatThongTinHocSinh(hs);
            timThay = true;
        }
    }
    if (!timThay) {
        cout << "Khong tim thay \"" << tuKhoa << "\".\n";
    }
}

void XuatHocSinhDiemToanThapNhat(const vector<HocSinh> &danhSachHocSinh) {
    auto minIt = min_element(danhSachHocSinh.begin(), danhSachHocSinh.end(),
                             [](const HocSinh &a, const HocSinh &b) {
                                 return a.diemToan < b.diemToan;
                             });
    cout << "\nHoc sinh co diem thap nhat:\n";
    XuatThongTinHocSinh(*minIt);
}

int main() {
    int n = 3;
    vector<HocSinh> danhSachHocSinh(n);
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin hoc sinh " << i + 1 << ":\n";
        NhapThongTinHocSinh(danhSachHocSinh[i]);
    }

    // Xuat thong tin
    cout << "\nThong tin hoc sinh:\n";
    for (const auto &hs : danhSachHocSinh) {
        XuatThongTinHocSinh(hs);
        cout << endl;
    }

    // Hoc sinh co diem cao nhat và thap nhat
    TimHocSinhDiemCaoNhat(danhSachHocSinh);

    XuatHocSinhDiemToanThapNhat(danhSachHocSinh);
    // Tim kiem hoc sinh theo ten
    string tuKhoa;
    cout << "\nNhap tu khoa theo ten: ";
    cin >> tuKhoa;
    TimHocSinhTheoTen(danhSachHocSinh, tuKhoa);
    return 0;
}
