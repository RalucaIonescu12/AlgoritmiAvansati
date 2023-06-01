#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
using namespace std;

float a,b,d; //capete intervale
int precizie;
int mTeste;
string tip,sir;
int nrBiti;
float nr;
int calculNrBiti()
{
    return ceil(log((b-a)*pow(10,precizie))/log(2));
}
float pasDiscretizare()
{
    return (float)(b-a)/pow(2,nrBiti);
}

int main() {
    cin >> a >> b;
    cin >> precizie >> mTeste;

    nrBiti=calculNrBiti();
    d=pasDiscretizare();
//    cout<<nrBiti<<" "<<d<<endl;

    for (int i = 1; i <= mTeste; i++)
    {
        cin>>tip;
        if(tip=="TO")
        {
            cin>>nr;
            int interval = floor((float)(nr-a)/d);
//            cout<<interval<<endl;
            bitset<32> bits(interval);
            string bitstring=bits.to_string().substr(32-nrBiti);
            cout<<bitstring<<endl;
        }
        else{
            cin>>sir;
            int interval = stoi(sir,nullptr,2);
            cout<<a+interval*d <<endl;

        }
    }

    return 0;
}
