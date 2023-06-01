#include <iostream>

using namespace std;
struct punct{
    long long x,y;
};

int n;
punct A,B,C,D;

void inCircleDeterminan(punct D) {
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
    if(determinant>tolerance) cout<<"INSIDE"<<endl;
    else if(determinant<-tolerance) cout<<"OUTSIDE"<<endl;
    else cout<<"BOUNDARY"<<endl;
}
long long det(punct a, punct b, punct c)
{
///function to compute the determinant of three points
///if det < 0, the three points are oriented clockwise (to the right)
///if det > 0, the three points are oriented counterclockwise (to the left)
///if det == 0, the three points are collinear
    return b.x * c.y + a.x * b.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y;
}
int main()
{

    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
    cin >> n;
    if (det(A,B,C) >= 0)
    {
        /// ABC is counterclockwise, so apply inCircle determinant for each point D
        for (int i = 0; i < n; ++i)
        {
            cin >> D.x >> D.y;
            inCircleDeterminan(D);
        }
    } else
    {
        ///reverse B and C
        swap(B, C);
        for (int i = 0; i < n; ++i)
        {
            cin >> D.x >> D.y;
            inCircleDeterminan(D);
        }
    }


    return 0;
}

