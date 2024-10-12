#include <iostream>
#include <cmath>
using namespace std;
float x, S, T, Luythua, Giaithua;
int main() {
    
    int i, dau = -1;
    cout << "Nhap gia tri cua x (radian): ";// Nhap gia tri cua x
    cin >> x;

    Giaithua = 1;
    S = T = Luythua = x;
    // vong lap chuoi Taylor
    for (i = 3; fabs(T) > 0.00001; i += 2, dau = -dau)// tính luy thua va giai thua sau do tinh so hang tiep theo
    {
        T = ((Luythua *= x * x) / (Giaithua *= i * (i - 1)));
        S += dau * T; // Cong hoac tru so hang 
    }
    cout << "sin(x) =" << S << endl;
    return 0;
}
