#include <iostream>
using namespace std;
int ucln(int n, int m)
{
    if (m == 0) return n;
    return ucln(m, n % m);
}

void rutgon(int& tu, int& mau)
{
    int uc = ucln(tu, mau);
    tu /= uc;
    mau /= uc;
}

void cong(int tu1, int mau1, int tu2, int mau2) {
    int tu = tu1 * mau2 + tu2 * mau1;
    int mau = mau1 * mau2;
    rutgon(tu, mau);
    cout << "Tong: " << tu << "/" << mau << endl;
}

void tru(int tu1, int mau1, int tu2, int mau2) {
    int tu = tu1 * mau2 - tu2 * mau1;
    int mau = mau1 * mau2;
    rutgon(tu, mau);
    cout << "Hieu: " << tu << "/" << mau << endl;
}

void nhan(int tu1, int mau1, int tu2, int mau2) {
    int tu = tu1 * tu2;
    int mau = mau1 * mau2;
    rutgon(tu, mau);
    cout << "Tich: " << tu << "/" << mau << endl;
}

void chia(int tu1, int mau1, int tu2, int mau2) {
    int tu = tu1 * mau2;
    int mau = mau1 * tu2;
    rutgon(tu, mau);
    cout << "Thuong: " << tu << "/" << mau << endl;
}

int main() {
    int tu1, mau1, tu2, mau2;
    cout << "Nhap tu va mau so cua phan so thu nhat: ";
    cin >> tu1 >> mau1;
    cout << "Nhap tu va mau so cua phan so thu hai: ";
    cin >> tu2 >> mau2;

    cong(tu1, mau1, tu2, mau2);
    tru(tu1, mau1, tu2, mau2);
    nhan(tu1, mau1, tu2, mau2);
    chia(tu1, mau1, tu2, mau2);

    return 0;
}
