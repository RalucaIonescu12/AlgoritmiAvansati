#include <iostream>

using namespace std;
struct punct{
    int x,y;
};

int nrX, nrY, n;
bool cresteX, cresteY;
punct A,B,C;
int main()
{

    ////if the x or y switches more than 2 times from decrease to increase than its not monotone
    cin >> n;
    nrY = nrX = 0;
    cin >> A.x >> A.y >> B.x >> B.y;

    if (A.x < B.x)
        cresteX = true;

    if (A.y < B.y)
        cresteY = true;

    for (int i = 0; i < n - 2; i++)
    {
        cin >> C.x >> C.y;
        if (cresteX && B.x > C.x)
        {
            nrX++;
            cresteX = false;
        }
        else if (!cresteX && B.x < C.x)
        {
            nrX++;
            cresteX = true;
        }

        if (cresteY && B.y > C.y)
        {
            nrY++;
            cresteY = false;
        }
        else if (!cresteY && B.y < C.y)
        {
            nrY++;
            cresteY = true;
        }

        B.x =  C.x;
        B.y =  C.y;
    }

    if (cresteX && B.x > A.x)
    {
        nrX++;
        cresteX = false;
    }
    else if (!cresteX && B.x < A.x)
    {
        nrX++;
        cresteY = true;
    }

    if (cresteY && B.y > A.y)
    {
        nrY++;
        cresteY = false;
    }
    else if (!cresteY && B.y < A.y)
    {
        nrY++;
        cresteY = true;
    }

    if (nrX <= 2)
        cout << "YES\n";
    else
        cout << "NO\n";

    if (nrY <= 2)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}

