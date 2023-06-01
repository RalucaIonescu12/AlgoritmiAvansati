#include <cstdlib>
#include <ctime>
#include<vector>
#include<string>
#include<fstream>
#include<random>
#include <cfloat>
#include<cmath>
#include <iostream>
#include<unordered_map>
using namespace std;
int nrCromozomi,st,dr,n,lungimeCromozom;
vector<string> populatie;
float mx=-FLT_MIN;
int worstPoz=0;
float worst =-FLT_MIN;
float medieFitness=0;
string fittest;
int etapa;
int fittestPoz;
unordered_map<string,float>pi;
vector<string>cromozomiTrecutiDeSelectie;
vector<int> trecDeSelectie;
vector<int>recombinare;
float maxx;
float suma;
float probIncrucisare,probMutatie,precizie,a,b,c;
unordered_map<string,float>xi;
vector<float>qi;
ofstream fout("Evolutie.txt");

///mutatie
string mutatie(int poz, string cromozom)
{
    if(cromozom[poz]=='1') cromozom[poz]='0';
    else cromozom[poz]='1';

    return cromozom;
}

//selectie
float functieSelectie(float x)
{
    return a*x*x+b*x+c;

};


void probSelectie()
{
    for(string cromozom:populatie)
    {
        pi[cromozom]= (float)(functieSelectie(xi[cromozom])/suma);
    }
}


///codificare
int calculNrBitiCodificare()
{
    return ceil(log2f((dr-st)*pow(10,precizie)));
}

float codificare(string cromozom)
{
    int interval = stoi(cromozom,nullptr,2);
    return  ((dr-st) / (pow(2,lungimeCromozom)-1))*interval + st;

}

void generare_populatie_initiala()
{
    string cromozom;
    srand((unsigned) time(NULL));

    for(int i=0;i<nrCromozomi;i++)
    {
        cromozom.clear();
        for(int i=0;i<lungimeCromozom;++i)
        {
            int bit =rand() % 2;
            if (bit==1) cromozom.push_back('1');
            else cromozom.push_back('0');
        }
        populatie.push_back(cromozom);
        xi[cromozom]= codificare(cromozom);
    }

}
void scriere_populatie_initiala()
{
    if(etapa==1)
         fout<<"Populatia initiala:\n";
    int i=0;
    for(string cromozom:populatie)
    {
        i++;
        if(etapa==1)
            fout<<i<<": "<<cromozom<<" x= "<<xi[cromozom]<<" f= "<<functieSelectie(xi[cromozom])<<endl;
        suma+= functieSelectie(xi[cromozom]);
        if(functieSelectie(xi[cromozom])>maxx)
        {
            maxx=functieSelectie(xi[cromozom]);
            fittestPoz= i-1;
        }
    }
    fittest=populatie[fittestPoz];
}

void probabilitate_selectie_pe_cromozom()
{
    if(etapa==1)
        fout<<"Probabilitati selectie"<< endl;
    int i=0;

    probSelectie();
    for(string cromozom:populatie)
    {
        i++;
        if(etapa==1)
             fout << "cromozom " << i << " probabilitate " << pi[cromozom] << endl;
    }
}
int last;
int cautare_binara(float u,int stanga,int dreapta)
{
    int mij;
    while (stanga <= dreapta) {
        mij = (stanga + dreapta) / 2;
        if (qi[mij] <= u)
        {
            last = mij;
            stanga = mij + 1;
        }
        else if (qi[mij] > u)
            dreapta = mij - 1;
    }
    return last+1;
}
void intervale_probabilitati_selectie()
{
    if(etapa==1)
        fout<<"Intervale probabilitate selectie"<<endl;
    qi.clear();
    qi.push_back(0);
    float sumInt=0;
    if(etapa==1)
        fout<<sumInt<<" ";
    for(string cromozom:populatie)
    {
        sumInt+=pi[cromozom];
        qi.push_back(sumInt);
        if(etapa==1)
            fout<<sumInt<<" ";
    }

}
void selectare_interval()
{
    trecDeSelectie.clear();
    trecDeSelectie.resize(nrCromozomi,0);
    srand((unsigned) time(NULL));
    for(int i=0;i<nrCromozomi;i++)
    {
        float u =(float)(rand()) / RAND_MAX;
        int crom = cautare_binara(u,0,nrCromozomi)-1;
        if(etapa==1)
            fout<<"u= "<< u <<" selectam cromozomul "<< (crom+1)<<endl;
        trecDeSelectie[i]=crom;
    }
    if(etapa==1)
        fout<<endl;
}

void dupa_selectie()
{
    if(etapa==1)
        fout<<"Dupa selectie:\n";
    cromozomiTrecutiDeSelectie.clear();
    for(int i=0;i<nrCromozomi;i++)
    {
        if(etapa==1)
        fout << i + 1 << ": " << populatie[trecDeSelectie[i]] << xi.at(populatie[trecDeSelectie[i]]) << " f= "
             << functieSelectie(xi.at(populatie[trecDeSelectie[i]])) << endl;
        cromozomiTrecutiDeSelectie.push_back(populatie[trecDeSelectie[i]]);
    }

    populatie.clear();
    populatie.insert(populatie.begin(),cromozomiTrecutiDeSelectie.begin(),cromozomiTrecutiDeSelectie.end());
    if(etapa==1)
        fout<<endl;
}
void probabilitatea_de_incrucisare()
{
    if(etapa==1)
        fout<<"Probabilitatea de incrucisare "<<probIncrucisare<<endl;
    random_device rd;
    mt19937 gen(rd());
    recombinare.clear();
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    for(int i=0;i<nrCromozomi;i++)
    {
        float u = dis(gen);
        if(u<probIncrucisare)
        {
            if(etapa==1)
                fout<<i+1<<": "<<populatie[i]<<" u= "<<u<<" < "<<probIncrucisare<< " participa"<<endl;
            recombinare.push_back(i);
        }
        else if(etapa==1) fout<<i+1<<": "<<populatie[i]<<" u= "<<u<<endl;
    }
}

void recombinare_crom()
{
    if(etapa==1) fout<<endl;
    srand((unsigned) time(NULL));
    while(recombinare.size()>1)
    {
        int i=recombinare.size()-1;
        int j=recombinare.size()-2;
        int poz=rand() %lungimeCromozom;
        if(etapa==1)
            fout<<"Recombinare intre cromozomul "<< recombinare[i]+1<<" cu cromozomul "<< recombinare[j]+1<<endl;
        if(etapa==1)fout<<populatie[recombinare[i]]<<" "<<populatie[recombinare[j]]<<" punct de rupere "<<poz<<endl;

        string aux,crom1,crom2;
        aux=populatie[recombinare[i]].substr(poz);
        crom1=populatie[recombinare[i]];
        crom2=populatie[recombinare[j]];
        crom1.replace(crom1.begin()+poz,crom1.end(),crom2.substr(poz));
        crom2.replace(crom2.begin()+poz,crom2.end(),aux);

        populatie[recombinare[i]]=crom1;
        populatie[recombinare[j]]=crom2;
        if(etapa==1)fout<<"Rezultat "<<populatie[recombinare[i]]<<" "<<populatie[recombinare[j]]<<endl;
        recombinare.pop_back();
        recombinare.pop_back();
    }
}

void dupa_recombinare()
{
    if(etapa==1)
    fout<<"Dupa recombinare"<<endl;
    int i=0;
    for(string cromozom:populatie)
    {
        xi[cromozom]= codificare(cromozom);
        i++;
        if(etapa==1)
        fout<<i<<": "<<cromozom<<" x= "<<xi[cromozom]<<" f= "<<functieSelectie(xi[cromozom])<<endl;
    }
}
void populatia_dupa_mutatiile_aleatoare()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    if(etapa==1)
         fout<<"Probabilitate de mutatie pentru fiecare gena "<<probMutatie<<endl;
    if(etapa==1)
        fout<<"Au fost modificati cromozomii: ";
    for(int i=0;i<nrCromozomi;i++)
    {
        float u = dis(gen)-0.4;
        if(u<probMutatie)
        {
            int poz=rand() %lungimeCromozom;
            populatie[i]= mutatie(poz,populatie[i]);
            if(etapa==1)fout<<i+1<<" ";
        }
    }
}
void dupa_mutatie()
{
    if(etapa==1)fout<<"Dupa mutatie"<<endl;
    int i=0;

    for(string cromozom:populatie)
    {
        xi[cromozom]= codificare(cromozom);
        i++;
        if(etapa==1)
            fout<<i<<": "<<cromozom<<" x= "<<xi[cromozom]<<" f= "<<functieSelectie(xi[cromozom])<<endl;
        if(mx<functieSelectie(xi[cromozom])) mx=functieSelectie(xi[cromozom]);

        medieFitness+=functieSelectie(xi[cromozom]);
//        tip elitist individul cu fitness-ul cel mai mare va trece automat în
//          generația următoare
        if(functieSelectie(xi[cromozom]) < worst)
        {
            worst = functieSelectie(xi[cromozom]);
            worstPoz = i-1;
        }

    }
    populatie[worstPoz]=fittest;
    if(maxx>mx)mx=maxx;
    medieFitness=(float)((medieFitness-worst+maxx)/nrCromozomi);
    if(etapa==1)
        fout<<endl<<"Evolutia maximului"<<endl;
    fout<<"Populatia "<<etapa<< " Valoarea maxima: "<<mx<<" Media: "<< medieFitness<<endl;
}
int main()
{
//    cin>>nrCromozomi;
//    cin>>st>>dr; //capete domeniul functiei
//    cin>>a>>b>>c;
//    cin>>precizie;   ///discretizarea
//    cin>>probIncrucisare;
//    cin>>probMutatie;
//    cin>>n;  //etape

    nrCromozomi=20;
    st=-1;
    dr=2;
    a=-1;b=1;c=2; precizie=6;
    probIncrucisare=0.25;
    probMutatie= 0.01;
    n=100;
    lungimeCromozom=calculNrBitiCodificare();
    generare_populatie_initiala();
    for(etapa=1;etapa<=n;etapa++)
    {
        mx=-FLT_MIN;
        worstPoz=0;
        worst =-FLT_MIN;
        medieFitness=0;
        maxx=-FLT_MIN;
        suma=0;
        scriere_populatie_initiala();

        if(etapa==1) fout<<endl;
        probabilitate_selectie_pe_cromozom();

        intervale_probabilitati_selectie();
        if(etapa==1) fout<<endl;
        selectare_interval();

        if(etapa==1) fout<<endl;
        dupa_selectie();

        probabilitatea_de_incrucisare();

        recombinare_crom();

        dupa_recombinare();
        if(etapa==1) fout<<endl;
        populatia_dupa_mutatiile_aleatoare();
        if(etapa==1) fout<<endl<<endl;
        dupa_mutatie();
    }

    return 0;
}