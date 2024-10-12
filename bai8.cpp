#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

struct SoTietKiem {
    string maSo;
    string loaiTietKiem;
    string hoTenKH;
    long long cmnd;
    string ngayMoSo;
    double soTienGui;
    double laiSuat;
};

// Kiem tra dinh dang CMND hop le 9 hoac 12 chu so
bool kiemTraCMND(long long cmnd) {
    string cmndStr = to_string(cmnd);
    return cmndStr.length() == 9 || cmndStr.length() == 12;
}

// Kiem tra ngay thang hop le
bool kiemTraNgayHopLe(int ngay, int thang, int nam) {
    if (thang < 1 || thang > 12 || ngay < 1 || ngay > 31) return false;
    if (thang == 2) {
        bool namNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
        if (namNhuan) return ngay <= 29;
        return ngay <= 28;
    }
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) return ngay <= 30;
    return true;
}

// Nhap thong tin so tiet kiem
void nhapSoTietKiem(SoTietKiem& stk) {
    cout << "Nhap ma so khong qua 5 ky tu: ";
    cin >> stk.maSo;
    while (stk.maSo.length() > 5 || stk.maSo.find_first_of(" !@#$%^&*()") != string::npos) {
        cout << "Ma so khong hop le. Nhap lai: ";
        cin >> stk.maSo;
    }

    cout << "Nhap loai tiet kiem ngan han, dai han: ";
    cin >> stk.loaiTietKiem;

    cout << "Nhap ho ten khach hang: ";
    cin.ignore();
    getline(cin, stk.hoTenKH);
    while (stk.hoTenKH.find_first_of("0123456789!@#$%^&*()") != string::npos || stk.hoTenKH.length() > 30) {
        cout << "Ho ten khong hop le. Nhap lai: ";
        getline(cin, stk.hoTenKH);
    }
    cout << "Nhap CMND 9 hoac 12 chu so: ";
    cin >> stk.cmnd;
    while (!kiemTraCMND(stk.cmnd)) {
        cout << "CMND khong hop le. Nhap lai: ";
        cin >> stk.cmnd;
    }

    int ngay, thang, nam;
    cout << "Nhap ngay mo so dd mm yyyy: ";
    cin >> ngay >> thang >> nam;
    while (!kiemTraNgayHopLe(ngay, thang, nam)) {
        cout << "Ngay khong hop le. Nhap lai: ";
        cin >> ngay >> thang >> nam;
    }
    stk.ngayMoSo = to_string(ngay) + "/" + to_string(thang) + "/" + to_string(nam);

    cout << "Nhap so tien gui: ";
    cin >> stk.soTienGui;
    while (stk.soTienGui <= 0) {
        cout << "So tien gui phai la so duong. Nhap lai: ";
        cin >> stk.soTienGui;
    }
}

// Xuat thong tin so tiet kiem
void xuatSoTietKiem(const SoTietKiem& stk) {
    cout << "Ma so: " << stk.maSo << ", Loai: " << stk.loaiTietKiem << ", Ho ten: " << stk.hoTenKH
        << ", CMND: " << stk.cmnd << ", Ngay mo so: " << stk.ngayMoSo
        << ", So tien gui: " << stk.soTienGui << endl;
}

// Tinh lai suat
double tinhLaiSuat(const SoTietKiem& stk, int soThangGui) {
    if (stk.loaiTietKiem == "ngan han" && soThangGui <= 6)
        return stk.soTienGui * stk.laiSuat * soThangGui / 12;
    else if (stk.loaiTietKiem == "dai han" && soThangGui > 6)
        return stk.soTienGui * stk.laiSuat * soThangGui / 12;
    else
        return stk.soTienGui * 0.5 / 100 * soThangGui / 12; // Lai suat thap neu rut truoc han
}

// Ham cap nhat lai suat cho cac so tiet kiem
void capNhatLaiSuat(vector<SoTietKiem>& dsSoTietKiem) {
    double laiSuatMoi;
    cout << "Nhap lai suat moi %/nam: ";
    cin >> laiSuatMoi;
    for (auto& stk : dsSoTietKiem) {
        stk.laiSuat = laiSuatMoi;
    }
    cout << "Da cap nhat lai suat moi cho tat ca so tiet kiem.\n";
}

// Tim kiem so tiet kiem theo CMND
void timKiemTheoCMND(const vector<SoTietKiem>& dsSoTietKiem, long long cmnd) {
    bool timThay = false;
    for (const auto& stk : dsSoTietKiem) {
        if (stk.cmnd == cmnd) {
            xuatSoTietKiem(stk);
            timThay = true;
        }
    }
    if (!timThay) cout << "Khong tim thay so tiet kiem voi CMND " << cmnd << endl;
}

// Sap xep danh sach theo so tien gui giam dan
void sapXepTheoSoTien(vector<SoTietKiem>& dsSoTietKiem) {
    sort(dsSoTietKiem.begin(), dsSoTietKiem.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
        return a.soTienGui > b.soTienGui;
        });
    cout << "Danh sach da duoc sap xep theo so tien gui giam dan.\n";
}

// Sap xep danh sach theo ngay mo so tang dan
void sapXepTheoNgayMoSo(vector<SoTietKiem>& dsSoTietKiem) {
    sort(dsSoTietKiem.begin(), dsSoTietKiem.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
        return a.ngayMoSo < b.ngayMoSo;
        });
    cout << "Danh sach da duoc sap xep theo ngay mo so tang dan.\n";
}

int main() {
    vector<SoTietKiem> dsSoTietKiem;
    int luaChon;
    do {
        cout << "\nQuan ly so tiet kiem\n";
        cout << "1. Them so tiet kiem\n";
        cout << "2. Xuat danh sach so tiet kiem\n";
        cout << "3. Tim kiem so tiet kiem theo CMND\n";
        cout << "4. Cap nhat lai suat\n";
        cout << "5. Sap xep so tiet kiem theo so tien gui\n";
        cout << "6. Sap xep so tiet kiem theo ngay mo so\n";
        cout << "7. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            SoTietKiem stk;
            nhapSoTietKiem(stk);
            dsSoTietKiem.push_back(stk);
            break;
        }
        case 2:
            for (const auto& stk : dsSoTietKiem) {
                xuatSoTietKiem(stk);
            }
            break;
        case 3: {
            long long cmnd;
            cout << "Nhap CMND: ";
            cin >> cmnd;
            timKiemTheoCMND(dsSoTietKiem, cmnd);
            break;
        }
        case 4:
            capNhatLaiSuat(dsSoTietKiem);
            break;
        case 5:
            sapXepTheoSoTien(dsSoTietKiem);
            break;
        case 6:
            sapXepTheoNgayMoSo(dsSoTietKiem);
            break;
        case 7:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 7);

    return 0;
}
    