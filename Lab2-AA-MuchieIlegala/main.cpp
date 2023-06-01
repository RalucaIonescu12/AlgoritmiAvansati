#include <iostream>

using namespace std;
struct punct{
    long long x,y;
};

string inCircleDeterminan(punct A, punct B, punct C, punct D) {
    long long a11 = A.x, a12 = A.y, a13 = A.x*A.x + A.y*A.y, a14 = 1;
    long long a21 = B.x, a22 = B.y, a23 = B.x*B.x + B.y*B.y, a24 = 1;
    long long a31 = C.x, a32 = C.y, a33 = C.x*C.x + C.y*C.y, a34 = 1;
    long long a41 = D.x, a42 = D.y, a43 = D.x*D.x + D.y*D.y, a44 = 1;

    long long determinant = a11*a22*a33*a44 + a11*a23*a34*a42 + a11*a24*a32*a43
                            - a11*a24*a33*a42 - a11*a23*a32*a44 - a11*a22*a34*a43
                            - a12*a21*a33*a44 - a13*a21*a34*a42 - a14*a21*a32*a43
                            + a14*a21*a33*a42 + a13*a21*a32*a44 + a12*a21*a34*a43
                            + a12*a23*a31*a44 + a13*a24*a31*a42 + a14*a22*a31*a43
                            - a14*a23*a31*a42 - a13*a22*a31*a44 - a12*a24*a31*a43
                            - a12*a23*a34*a41 - a13*a24*a32*a41 - a14*a22*a33*a41
                            + a14*a23*a32*a41 + a13*a22*a34*a41 + a12*a24*a33*a41;
    double tolerance=1e-9;
    if(determinant>tolerance) return "INSIDE";
    else if(determinant<-tolerance) return "OUTSIDE";
    return "BOUNDARY";
}
int main()
{
    punct A,B,C,D;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y>>D.x>>D.y;


    if (inCircleDeterminan(A, B, C, D) == "INSIDE" && inCircleDeterminan(A, C, D, B) == "INSIDE")
        /// D and B in the circle determined by AC
         cout << "AC: ILLEGAL"<<endl;
    else
        cout << "AC: LEGAL"<<endl;

    if (inCircleDeterminan(B,C, D,A) == "INSIDE" && inCircleDeterminan(A, B, D, C) == "INSIDE")
        /// A and C in the circle determined by BD
        cout << "BD: ILLEGAL"<<endl;
    else
        cout << "BD: LEGAL"<<endl;
    return 0;
}

