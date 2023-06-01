#include <iostream>
#include <vector>
using namespace std;
long long x,y,x1,y1,x2,y2,x3,y3;
int n,acDr=0,vrSt=0,vrDr=0;
vector<pair<long long,long long>> v;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        v.push_back(make_pair(x,y));
    }
    x1=v[0].first;
    y1=v[0].second;
    x2=v[1].first;
    y2=v[1].second;
    for(int i=2;i<n;i++)
    {
        x3=v[i].first;
        y3=v[i].second;
        long long D = (x2*y3 - y2*x3) - (x1*y3 - y1*x3) + (x1*y2 - y1*x2);
        if (D==0) acDr += 1;
        else if (D<0) vrSt += 1;
        else vrDr += 1;
        x1 = v[i-1].first;
        y1 = v[i-1].second;
        x2 = v[i].first;
        y2 = v[i].second;
    }
    x3 = v[0].first;
    y3 = v[0].second;
    int D = (x2*y3 - y2*x3) - (x1*y3 - y1*x3) + (x1*y2 - y1*x2);
    if (D==0) acDr += 1;
    else if (D<0) vrSt+=1;
    else vrDr+=1;
    cout<<vrDr<<" "<<vrSt<<" "<<acDr<<endl;
    return 0;
}
//7
//1 1
//2 2
//2 0
//3 0
//4 0
//5 0
//6 0











