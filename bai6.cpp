#include <iostream>
#include <vector>
using namespace std;
string s, t; 
int m, n; 
// Tinh mang KMP
void mang_KMP(const string& s, vector<int>& kmp) {
    int m = s.size();
    int k= kmp[0] = 0;
    for (int i = 1; i < m; i++) { // Bat dau tu phan
        while (k > 0 && s[i] != s[k]) {
            k = kmp[k - 1]; // Tim vi tri da biet
        }
        if (s[i] == s[k]) {
            k++; // Tang den vi tri phu hop
        }
        kmp[i] = k; // Gan gia tri vao mang KMP
    }
}
// Tim chuoi con
void KMP(const string& s, const string& t) {
    int m = s.size();
    int n = t.size();
    vector<int> kmp(m);
    mang_KMP(s, kmp); 

    int k = 0; // Vi tri  trong s
    vector<int> Khop;// Danh sach luu tru cac vi tri khop
    for (int i = 0; i < n; i++)
    { 
        while (k > 0 && t[i] != s[k]) {
            k = kmp[k - 1]; //Tim vi tri da biet
        }
        if (t[i] == s[k]) {
            k++; // Tang do dai khop
        }
        if (k == m) { 
            Khop.push_back(i - m + 1); // Luu vi tri cua khop
            k = kmp[k - 1]; // lui de tim kiem tiep
        }
    }
    int so_lan_suat_hien = Khop.size();
    if (Khop.empty()) {
        cout << "Khong co mang con" << endl;
    }
    else 
    {
        cout << "So lan suat hien: " << so_lan_suat_hien << endl;
        cout << "Mang con suat hien o cac vi tri: ";
        for (int j : Khop) {
            cout << j << " ";
        }
        cout << endl;
    }
}
int main() {
    cout << "Nhap mang A : ";
    cin >> s;
    cout << "Nhap mang B : ";
    cin >> t;
    KMP(s, t);
    return 0;
}
