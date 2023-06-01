#include<iostream>
#include<vector>
using namespace std;


float functie(float x,int a,int b ,int c)
{
    return a*x*x+b*x+c;

};
int main()
{
    int a,b,c;
    int n;
    float x;
    vector<float> puncte;

    cin>>a>>b>>c;
    cin>>n; //dim populatiei de cromozomi

    for(int i=0;i<n;i++)
    {
        cin>>x;
        puncte.push_back(x);
    }
    float suma=0;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        suma+= functie(puncte[i],a,b,c);
    }
    cout<<(float)0<<endl;
    float suma2=0;
    for(int i=0;i<n;i++)
    {
        suma2+=functie(puncte[i],a,b,c);
        cout<<(float)(suma2/suma)<<endl;
    }

    return 0;
}
