#include <iostream>
#include<string>
using namespace std;
int punctDeRupere;
string crom1,crom2;
int lungime;

int main()
{
    cin>>lungime;
    cin>>crom1>>crom2;
    cin>>punctDeRupere;
    string aux;
    if (punctDeRupere<lungime)
    {
        aux=crom1.substr(punctDeRupere);
        crom1.replace(crom1.begin()+punctDeRupere,crom1.end(),crom2.substr(punctDeRupere));
        crom2.replace(crom2.begin()+punctDeRupere,crom2.end(),aux);
    }
    cout<<crom1<<endl;
    cout<<crom2;
    return 0;
}
