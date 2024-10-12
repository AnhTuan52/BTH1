#include<iostream>
using namespace std;
int tu1, mau1, tu2, mau2;
// ham so sanh 2 phan so
int ucln(int n, int m)
{
    if (m == 0)
        return n;
    return ucln(m, n % m);
}
int sosanh(int tu1, int mau1, int tu2, int mau2)
{
    int bcnn = (mau1 * mau2) / ucln(mau1, mau2);
    return tu1 * (bcnn / mau1) - tu2 * (bcnn / mau2);
}
int  main()
{
    cout << "Nhap phan so thu nhat: ";
    cin >> tu1 >> mau1;
    while (mau1 == 0)
    {
        cout << "Mau phai khac 0, vui long nhap lai mau: ";
        cin >> mau1;
    }

    cout << "Nhap phan so thu hai: ";
    cin >> tu2 >> mau2;
    while (mau2 == 0)
    {
        cout << "Mau phai khac 0, vui long nhap lai mau: ";
        cin >> mau2;
    }
    if (sosanh(tu1, mau1, tu2, mau2) > 0)
        cout << "Phan so thu nhat lon hon:";
    else if (sosanh(tu1, mau1, tu2, mau2) < 0)
        cout << " Phan so thu 2 lon hon:";
    else
        cout << " Hai phan so bang nhau: ";
    return 0;

}