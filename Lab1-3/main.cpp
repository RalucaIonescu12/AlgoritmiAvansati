#include <bits/stdc++.h>
using namespace std;
long long x,y,x1,ya,x2,yb,x3,yc;
int n;
pair<long long,long long> a,b,c;
stack<pair<long long,long long>> stiva,stiva2;
vector<pair<long long,long long>> v;

///nu sortam punctele incep cu
/// primul varf
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        v.push_back(make_pair(x,y));
    }

    stiva.push(v[0]);
    stiva.push(v[1]);

    int i=2;
    while(i<n)
    {
        b=stiva.top();
        stiva.pop();
        a=stiva.top();
        stiva.pop();

        c=v[i];
        x1=a.first;
        ya=a.second;
        x2=b.first;
        yb=b.second;
        x3=c.first;
        yc=c.second;
        stiva.push(a);
        stiva.push(b);
        while((x2*yc - yb*x3) - (x1*yc - ya*x3) + (x1*yb - ya*x2)<=0 && stiva.size()>=2)
        {
            stiva.pop();
            if (stiva.size()>=2)
            {
                b = stiva.top();
                stiva.pop();
                a = stiva.top();
                stiva.pop();
                x1 = a.first;
                ya = a.second;
                x2 = b.first;
                yb = b.second;
                stiva.push(a);
                stiva.push(b);
            }
        }
        stiva.push(c);
        i++;
    }
    ///verific ultimele 2 puncte cu cel de la inceput
    c=v[0];
    b=stiva.top();
    stiva.pop();
    a=stiva.top();
    stiva.pop();

    x1=a.first;
    ya=a.second;
    x2=b.first;
    yb=b.second;
    x3=c.first;
    yc=c.second;
    stiva.push(a);
    stiva.push(b);
    while((x2*yc - yb*x3) - (x1*yc - ya*x3) + (x1*yb - ya*x2)<=0 && stiva.size()>=2)
    {
        stiva.pop();
        if (stiva.size()>=2)
        {
            b = stiva.top();
            stiva.pop();
            a = stiva.top();
            stiva.pop();
            x1 = a.first;
            ya = a.second;
            x2 = b.first;
            yb = b.second;
            stiva.push(a);
            stiva.push(b);
        }
    }

    c=stiva.top();
    ///verific punctul de inceput cei 2 vecini din stanga si dreapta lui
    while(stiva.size()>0)
    {
        stiva2.push(stiva.top());
        stiva.pop();
    }
    b=stiva2.top();
    stiva2.pop();
    a=stiva2.top();
    stiva2.pop();
    x1=a.first;
    ya=a.second;
    x2=b.first;
    yb=b.second;
    x3=c.first;
    yc=c.second;

    if ((x2*yc - yb*x3) - (x1*yc - ya*x3) + (x1*yb - ya*x2)==0)
    {
        stiva2.push(a);
    }
    else
    {
        stiva2.push(a);
        stiva2.push(b);
    }

    cout<<stiva2.size()<<endl;
    while(stiva2.size()>0)
    {
        cout << stiva2.top().first << " " << stiva2.top().second << endl;
        stiva2.pop();
    }

    return 0;
}


//3
//-1 3
//-3 -2
//4 -3