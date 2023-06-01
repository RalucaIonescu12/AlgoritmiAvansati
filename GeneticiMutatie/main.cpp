#include <iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
    int n, nr, poz;
    string sirBiti;
    cin>>n;
    cin>>nr;

    cin>>sirBiti;

    for(int i=0;i<nr;i++)
    {
      cin>>poz;
      if(sirBiti[poz]=='1') sirBiti[poz]='0';
      else sirBiti[poz]='1';
    }

    cout<<sirBiti;


    return 0;
}
