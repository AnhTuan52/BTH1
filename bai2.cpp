#include<iostream>
using namespace std;
//ham tim uoc chung lon nhat cua 2 so
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
int  main()
{
    int tu, mau;
    cout << "Nhap tu so: ";
    cin >> tu;
    cout << "Nhap mau so: ";
    cin >> mau;
    while (mau == 0)
    {
        cout << "Nhap lai mau so: ";
        cin >> mau;
    }

    rutgon(tu, mau);
    cout << "Phan so da rut gon: " << tu << "/" << mau;
    return 0;

}