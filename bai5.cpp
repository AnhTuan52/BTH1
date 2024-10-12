#include <iostream>
using namespace std;
int ngay, thang, nam;
bool laNamNhuan(int nam) 
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}
int so_ngay(int thang, int nam)
{
    if (thang == 2)
        if (laNamNhuan(nam))
            return 29;
        else return 28;
    if (thang == 4 or thang == 6 or thang == 9 or thang == 11)
        return 30;
    else return 31;

}
void ngay_ke_tiep(int ngay, int thang, int nam) {
    if (++ngay > so_ngay(thang, nam)) {
        ngay = 1;
        if (++thang > 12) {
            thang = 1;
            nam++;
        }
    }
    cout << " Ngay ke tiep:" << ngay <<" " << thang<<" " << nam<< endl;

}
void ngay_truoc(int ngay, int thang, int nam) {
    if (--ngay < 1) {
        if (--thang < 1) {
            thang = 12;
            nam--;
        }
        ngay = so_ngay(thang, nam);
    }
    cout << " Ngay truoc: " << ngay << " " << thang<< " " << nam << endl;
}
void  ngay_thu_bao_nhieu(int ngay, int thang, int nam) 
{
    int tong_ngay = ngay;
    for (int t = 1; t < thang; ++t)
        tong_ngay += so_ngay(t, nam);
    cout<<" Ngay thu bao nhieu "<< tong_ngay<< endl;
}
int main() {
    cout << " Nhap ngay thang nam: ";
    cin >> ngay >> thang >> nam;
    ngay_ke_tiep(ngay, thang, nam);
    ngay_truoc(ngay, thang, nam);
    ngay_thu_bao_nhieu(ngay, thang, nam);

}