#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cctype>
#include <sstream>

using namespace std;
int soNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// Cau truc chuyen bay
struct ChuyenBay {
    string maChuyenBay;
    string ngayBay;
    string gioBay;
    string noiDi;
    string noiDen;
};
// Kiem tra ma chuyen bay, 5 ki tu
bool check_chuyen_bay(const string& ma) {
    if (ma.length() > 5) return false;
    for (char c : ma) {
        if (!isalnum(c)) return false; 
    }
    return true;
}
// Kiem tra dinh dang ngay bay (DD/TT/XXXX)
bool check_ngay_bay(const string& ngay) {
    if (ngay.size() != 10 || ngay[2] != '/' || ngay[5] != '/') return false;
    int DD, TT, XXXX;
    DD = stoi(ngay.substr(0, 2));
    TT = stoi(ngay.substr(3, 2));
    XXXX = stoi(ngay.substr(6, 4));
    if (DD < 1 || TT < 1 || XXXX < 1 || TT > 12) return false;
    if ((XXXX % 4 == 0 && XXXX % 100 != 0) || (XXXX % 400 == 0)) soNgayTrongThang[1] = 29; // NAM NHUAN
    if (DD > soNgayTrongThang[TT - 1]) return false;
    return true;
}
// Kiem tra gio(HH:MM)
bool Check_gio(const string& gio) {
    if (gio.size() != 5 || gio[2] != ':') return false;
    int hh = stoi(gio.substr(0, 2));
    int mm = stoi(gio.substr(3, 2));
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) return false;
    return true;
}
// Kiem tra dia diem 
bool Check_DiaDanh(const string& diaDanh) {
    if (diaDanh.size() > 20) return false;
    for (char c : diaDanh) {
        if (!isalpha(c) && !isspace(c)) return false; // Chi chua chu cai va khoang trang
    }
    return true;
}
// Nhap thong tin chuyen bay
void nhapThongTinChuyenBay(ChuyenBay& cb) {
    do {
        cout << "Nhap ma chuyen bay toi da 5 ky tu: ";
        cin >> cb.maChuyenBay;
    } while (!check_chuyen_bay(cb.maChuyenBay));
    do {
        cout << "Nhap ngay bay (DD/MM/YYYY):";
        cin >> cb.ngayBay;
    } while (!check_ngay_bay(cb.ngayBay));

    do {
        cout << "Nhap gio bay ( HH:MM): ";
        cin >> cb.gioBay;
    } while (!Check_gio(cb.gioBay));

    cin.ignore();
    do {
        cout << "Nhap noi di: ";
        getline(cin, cb.noiDi);
    } while (!Check_DiaDanh(cb.noiDi));

    do {
        cout << "Nhap noi den: ";
        getline(cin, cb.noiDen);
    } while (!Check_DiaDanh(cb.noiDen));
}
void in_ra(const ChuyenBay& cb) {
    cout << setw(8) << left << cb.maChuyenBay << " | "
        << setw(12) << cb.ngayBay << " | "
        << setw(6) << cb.gioBay << " | "
        << setw(20) << cb.noiDi << " | "
        << setw(20) << cb.noiDen << endl;
}

// Ham so sanh
bool soSanh(const ChuyenBay& a, const ChuyenBay& b) {
    if (a.ngayBay != b.ngayBay) return a.ngayBay < b.ngayBay;
    return a.gioBay < b.gioBay;
}

// Tim kiem chuyen bay
void timKiem(const vector<ChuyenBay>& dsChuyenBay, const string& key) {
    cout << "\nKet qua:\n";
    bool timThay = false;
    for (const auto& cb : dsChuyenBay) {
        if (cb.maChuyenBay == key || cb.noiDi == key || cb.noiDen == key) {
            in_ra(cb);
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay.\n";
    }
}
// Sap xep chuyen bay
void sapXep(vector<ChuyenBay>& dsChuyenBay) {
    sort(dsChuyenBay.begin(), dsChuyenBay.end(), soSanh);
}
void lietKeTheoNgay(const vector<ChuyenBay>& dsChuyenBay, const string& noiDi, const string& ngayBay) {
    bool coChuyenBay = false;
    for (const auto& cb : dsChuyenBay) {
        if (cb.noiDi == noiDi && cb.ngayBay == ngayBay) {
            in_ra(cb);
            coChuyenBay = true;
        }
    }

    if (!coChuyenBay) {
        cout << "Khong co chuyen bay nao.\n";
    }
}

//Đem so chuyen bay tu noi di den noi den
int demChuyenBay(const vector<ChuyenBay>& dsChuyenBay, const string& noiDi, const string& noiDen) {
    int count = 0;
    for (const auto& cb : dsChuyenBay) {
        if (cb.noiDi == noiDi && cb.noiDen == noiDen) {
            count++;
        }
    }
    return count;
}
int main() {
    int n;
    cout << "Nhap so chuyen bay: ";
    cin >> n;
    vector<ChuyenBay> dsChuyenBay(n);
    for (int i = 0; i < n; ++i) {
        cout << "\nNhap thong tin chuyen bay: " << i + 1 << ":\n";
        nhapThongTinChuyenBay(dsChuyenBay[i]);
    }
    for (const auto& cb : dsChuyenBay) {
        in_ra(cb);
    }

    // Sap xep chuyen bay
    sapXep(dsChuyenBay);
    cout << "\nDanh sach chuyen bay sau khi sap xep:\n";
    for (const auto& cb : dsChuyenBay) {
        in_ra(cb);
    }

    //tim kiem chuyen bay   
    string key;
    cout << "\nNhap ma chuyen bay hoac noi di hoac noi den: ";
    cin.ignore(); 
    getline(cin, key);
    timKiem(dsChuyenBay, key);
    // liet ke cac chuyen bay khoi hanh tu mot noi cu the trong mot ngay chi ding
    string noiDi, ngayBay;
    cout << "\nNhap noi di: ";
    cin.ignore();
    getline(cin, noiDi);
    cout << "Nhap ngay di ( DD/MM/YYYY): ";
    getline(cin, ngayBay);
    lietKeTheoNgay(dsChuyenBay, noiDi, ngayBay);
    //Đem so luong chuyen bay 
    string noiDen;
    cout << "\nNhap noi di va noi den :\n";
    cout << "Noi di: ";
    getline(cin, noiDi);
    cout << "Noi den: ";
    getline(cin, noiDen);

    int soLuongChuyenBay = demChuyenBay(dsChuyenBay, noiDi, noiDen);
    cout << "So chuyen bay " << noiDi << " den " << noiDen << ": " << soLuongChuyenBay << endl;
    return 0;
}

