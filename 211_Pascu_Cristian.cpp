#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
class Persoana
{
    private:
        char *nume;
        int an_nastere;
        char sex;
    public:
        Persoana()
        {
            an_nastere=0;
            sex='N';
            nume=new char[1];
            strcpy(nume,"");
        }
        void set_nume(char*);
        void set_an_nastere(int);
        void set_sex(char);
        ~Persoana();
        char* get_nume();
        int get_an_nastere();
        char get_sex();
        Persoana(Persoana &p)
        {
            sex=p.sex;
            an_nastere=p.an_nastere;
            nume=new char[strlen(p.nume)+1];
            strcpy(nume,p.nume);
        }
        Persoana & operator=(const Persoana &p)
        {
            if(this==&p)
                return *this;
            sex=p.sex;
            an_nastere=p.an_nastere;
            nume=new char[strlen(p.nume)+1];
            strcpy(nume,p.nume);
        }
        friend istream & operator>>(istream &in,Persoana &p);
        friend ostream & operator<<(ostream &out,Persoana &p);
};
void Persoana::set_nume(char* nume)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}
Persoana::~Persoana()
{
    delete[] nume;
    an_nastere=0;
    sex='N';
}
void Persoana::set_an_nastere(int an_nastere)
{
    this->an_nastere=an_nastere;
}
void Persoana::set_sex(char sex)
{
    this->sex=sex;
}
char* Persoana::get_nume()
{
    return nume;
}
int Persoana::get_an_nastere()
{
    return an_nastere;
}
char Persoana::get_sex()
{
    return sex;
}

istream & operator>>(istream &in,Persoana &p)
{
    char nume[100];
    int an_nastere;
    char sex;
    cout<<"Numele: ";
    in.get(nume,200);
    in.get();
    p.nume=new char[strlen(nume)+1];
    strcpy(p.nume,nume);
    cout<<"Sex: ";
    in>>sex;
    in.get();
    p.sex=sex;
    cout<<"Anul nasterii: ";
    in>>an_nastere;
    in.get();
    p.an_nastere=an_nastere;
}
ostream & operator<<(ostream &out,Persoana &p)
{
    out<<p.nume<<" "<<p.sex<<" "<<p.an_nastere<<"\n";
}
class Baza_de_Date
{
    private:
        int dimAlocata,dimUtilizata;
        Persoana *v;
        void rezerva(int n);
    public:
        int getDim();
        void sortare_an_nastere();
        void sortare_nume();
        void stergere(char*);
        void stergere(int);
        void stergere(char);
        void adaugaPersoana(Persoana p);
        Baza_de_Date(int n=0)
        {
            dimUtilizata=n;
            dimAlocata=n;
            v=new Persoana[dimAlocata];
        }
        Baza_de_Date(Baza_de_Date& b)
        {
            dimUtilizata=b.dimUtilizata;
            dimAlocata=b.dimAlocata;
            v=new Persoana[dimAlocata];
            for(int i=0;i<dimUtilizata;i++)
                v[i]=b.v[i];
        }
        ~Baza_de_Date()
        {
            delete[] v;
        }
        friend ostream & operator<<(ostream &out,Baza_de_Date &b);
};
ostream & operator<<(ostream &out,Baza_de_Date &b)
{
    if(b.dimUtilizata==0)
        out<<"Baza de date vida\n";
    for(int i=0;i<b.dimUtilizata;i++)
        out<<b.v[i];
}
void Baza_de_Date::stergere(char* nume)
{
    Persoana* temp=new Persoana[dimUtilizata];
    int sz=0;
    for(int i=0;i<dimUtilizata;i++)
    {
        if(strcmp(v[i].get_nume(),nume))
        {
            temp[sz]=v[i];
            sz++;
        }
    }
    dimUtilizata=sz;
    for(int i=0;i<dimUtilizata;i++)
        v[i]=temp[i];
    delete []temp;
}
void Baza_de_Date::stergere(int an_nastere)
{
    Persoana* temp=new Persoana[dimUtilizata];
    int sz=0;
    for(int i=0;i<dimUtilizata;i++)
    {
        if(v[i].get_an_nastere()!=an_nastere)
        {
            temp[sz]=v[i];
            sz++;
        }
    }
    dimUtilizata=sz;
    for(int i=0;i<dimUtilizata;i++)
        v[i]=temp[i];
    delete []temp;
}
void Baza_de_Date::stergere(char sex)
{
    Persoana* temp=new Persoana[dimUtilizata];
    int sz=0;
    for(int i=0;i<dimUtilizata;i++)
    {
        if(v[i].get_sex()!=sex)
        {
            temp[sz]=v[i];
            sz++;
        }
    }
    dimUtilizata=sz;
    for(int i=0;i<dimUtilizata;i++)
        v[i]=temp[i];
    delete []temp;
}
void Baza_de_Date::sortare_nume()
{
    for(int i=0;i<dimUtilizata;i++)
    {
        for(int j=i+1;j<dimUtilizata;j++)
        {
            if(strcmp(v[i].get_nume(),v[j].get_nume())>0)
            {
                Persoana aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}
void Baza_de_Date::sortare_an_nastere()
{
    for(int i=0;i<dimUtilizata;i++)
    {
        for(int j=i+1;j<dimUtilizata;j++)
        {
            if(v[i].get_an_nastere()>v[j].get_an_nastere())
            {
                Persoana aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}
void Baza_de_Date::adaugaPersoana(Persoana p)
{
    if(dimUtilizata==dimAlocata)
        rezerva(dimAlocata*2+1);
    v[dimUtilizata]=p;
    dimUtilizata++;
}
void Baza_de_Date::rezerva(int n)
{
    if(n>dimAlocata)
    {
        dimAlocata=n;
        Persoana* temp=v;
        v=new Persoana[dimAlocata];
        for(int i=0;i<dimUtilizata;i++)
            v[i]=temp[i];
        delete []temp;
    }
}
void menu()
{
    cout<<"OPTIUNI:\n";
    cout<<"1.Adauga persoana\n";
    cout<<"2.Sterge persoane dupa nume\n";
    cout<<"3.Sterge persoane dupa an_nastere\n";
    cout<<"4.Sterge persoane dupa sex\n";
    cout<<"5.Sortare persoane alfabetic\n";
    cout<<"6.Sortare persoane dupa an_nastere\n";
    cout<<"7.Afisare baza de date\n";
    cout<<"8.Oprire program\n";
}
int main()
{
    Baza_de_Date b;

    bool ok=1;
    cout<<"PASCU CRISTIAN VLAD, GRUPA 211, TEMA 13, PROIECT 1\n";
    while(ok)
    {
        menu();
        int opt;
        cout<<"opt=";cin>>opt;
        cin.get();
        switch(opt)
        {
            case 1:
            {
                Persoana p;
                cin>>p;
                b.adaugaPersoana(p);
                system("cls");
                break;
            }
            case 2:
            {
                char s[100];
                cout<<"Citeste nume: ";cin.get(s,100);
                cin.get();
                b.stergere(s);
                system("cls");
                break;
            }
            case 3:
            {
                int an;
                cout<<"Citeste an: ";cin>>an;
                cin.get();
                b.stergere(an);
                system("cls");
                break;
            }
            case 4:
            {
                char sx;
                cout<<"Citeste sex: ";cin>>sx;
                cin.get();
                b.stergere(sx);
                system("CLS");
                break;
            }
            case 5:
            {
                b.sortare_nume();
                system("cls");
                break;
            }
            case 6:
            {
                b.sortare_an_nastere();
                system("cls");
                break;
            }
            case 7:
            {cout<<"Baza de date: \n\n";
                cout<<b;
                cout<<"\n\n";

                break;
            }
            case 8:
            {
                ok=0;

                break;
            }
        }
    }
    return 0;
}
