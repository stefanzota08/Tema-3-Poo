#include <bits/stdc++.h>

using namespace std;
ifstream f("Filme.in");
ifstream g("Actori.in");
ifstream h("Regizori.in");

class Personal {
protected:
    string cnp;
    string nume;
    string nume_film;
public:
    Personal(string cnp = " ", string nume = " ", string nume_film= " ")
    {
        this->cnp = cnp;
        this->nume = nume;
        this->nume_film= nume_film;
    }

    Personal(const Personal &personal)
    {
        cnp = personal.cnp;
        nume = personal.nume;
        nume_film= personal.nume_film;
    }

    virtual ~Personal() {
        cnp = "";
        nume = "";
        nume_film= "";
    };

    Personal &operator=(const Personal &personal)
    {
        if (this == &personal)
            return *this;
        cnp = personal.cnp;
        nume = personal.nume;
        nume_film= personal.nume_film;
        return *this;
    }

    friend istream &operator>>(istream &citire, Personal &personal)
    {
        citire>>personal.cnp>>personal.nume>>personal.nume_film;
        return citire;
    }

    virtual void afisare() const
    {
        cout<<cnp<<" "<<nume<<" "<<nume_film;
    }

    string getNume() const
    {
        return nume;
    }

    string getNumeFilm() const
    {
        return nume_film;
    }

    void setCNP(string cnp)
    {
        this->cnp = cnp;
    }

    void setNume(string nume)
    {
        this->nume = nume;
    }
    void setNumeFilme(string numeFilm)
    {
        this->nume_film = numeFilm;
    }
};


class Actor : public Personal {
    bool principal;
public:
    Actor(string cnp = " ", string nume = " ", string nume_film = " ", bool principal = false) : Personal{cnp, nume, nume_film}
        {
            this->principal = principal;
        }

    Actor(const Actor &actor) : Personal{actor}
    {
        principal = actor.principal;
    }

    ~Actor()
    {
        principal = 0;
    };

    Actor &operator=(const Actor &actor)
    {
        if(this == &actor)
            return *this;
        *this = actor;
        this->principal = actor.principal;
        return *this;
    }

    friend istream &operator>>(istream &citire, Actor &actor)
    {
        Personal *p = &actor;
        citire>>*p;
        citire>>actor.principal;
        return citire;
    }

    void afisare() const override
    {
        cout<<cnp<<" "<<nume<<" "<<nume_film<<" "<<principal;
    }

    bool getRol() const
    {
        return principal;
    }

    void setRol(bool princ)
    {
        this->principal = princ;
    }
};


class Regizor : public Personal {
    int suma_fixa;
public:
    Regizor(string cnp = " ", string nume = " ", string nume_film = " ", int suma_fixa = 0) : Personal{cnp, nume, nume_film}
    {
         this->suma_fixa = suma_fixa;
    }

    Regizor(const Regizor &regizor) : Personal{regizor}
    {
        suma_fixa = regizor.suma_fixa;
    }

    ~Regizor()
    {
        suma_fixa = 0;
    }

    Regizor &operator=(const Regizor &regizor)
    {
        if(this == &regizor)
            return *this;
        *this = regizor;
        this->suma_fixa = regizor.suma_fixa;
        return *this;
    }

    friend istream &operator>>(istream &citire, Regizor &regizor)
    {
        Personal *aux = &regizor;
        citire>>*aux;
        citire>>regizor.suma_fixa;
        return citire;
    }

    void afisare() const override
    {
        cout<<cnp<<" "<<nume<<" "<<nume_film<<" "<<suma_fixa;
    }

    int getsuma_fixa() const
    {
        return suma_fixa;
    }
    void setSuma(int suma)
    {
        suma_fixa = suma;
    }
};


class Film {
    string nume, tip;
    int durata;
public:
    Film(string nume = "", string tip = "", int durata = 0)
    {
        this->nume = nume;
        this->tip = tip;
        this->durata = durata;
    }

    Film(const Film &film)
    {
        nume = film.nume;
        tip = film.tip;
        durata = film.durata;
    }

    ~Film() = default;

    Film &operator=(const Film &film)
    {
        if(this == &film)
            return *this;
        nume = film.nume;
        tip = film.tip;
        durata = film.durata;
        return *this;
    }

    friend istream &operator>>(istream &citire, Film &film)
    {
        citire>>film.nume>>film.tip>>film.durata;
        return citire;
    }

    friend ostream &operator<<(ostream &afis, Film &film)
    {
        afis<<film.nume<<" "<<film.tip<<" "<<film.durata;
        return afis;
    }

    string getNume() const
    {
        return nume;
    }
    void afisare()
    {
        cout<<nume<<" "<<tip<<" "<<durata<<endl;
    }
};


template<typename T>
class FirmaDistributie {
    static int numarPersoane, numarActori;
    static set<tuple<T *, Film *, int>> structura;
public:
    FirmaDistributie()
    {
        numarActori = 0;
        numarPersoane = 0;
        set<tuple<T*, Film*, int> > stuctura;
    }

    FirmaDistributie(FirmaDistributie &firma) = default;

    ~FirmaDistributie() = default;

    void adauga(T *personal, Film *film)
    {
        numarPersoane++;
        Actor *actor;
        Regizor *regizor;
        tuple<T *, Film *, int> tuplu;
        if (typeid(personal) == typeid(actor)) {
            numarActori++;
            actor = dynamic_cast<Actor*>(personal);
            if (actor->getRol())
                tuplu = make_tuple(personal, film, 10);
            else
                tuplu = make_tuple(personal, film, 0);
        }
        else
            tuplu = make_tuple(personal, film, 0);
        structura.insert(tuplu);
        }

        static void afisare()
        {
            cout<<"Nr Personal: "<<numarPersoane<<"\n";
            T *aux = new T;
            Film *film = new Film;
            int bonus;
            for (auto element : structura) {
                tie(aux, film, bonus) = element;
                cout<<"Nume: "<<aux->getNume()<<" | Filmul: "<<film->getNume()<<"\n";
            }
        }

};

template<typename T>
int FirmaDistributie<T>::numarPersoane = 0;

template<typename T>
int FirmaDistributie<T>::numarActori = 0;

template<typename T>
set<tuple<T *, Film *, int>> FirmaDistributie<T>::structura;

int main()
{
    string n, t, cnp, nume, nume_f, pr;
    int d, idxReg = 0, idxFilm = 0, idxAct = 0, suma;

    Film *filme;
    filme = new Film[10];
    while(f>>n>>t>>d)
    {
        Film aux(n,t,d);
        filme[idxFilm++] = aux;
    }

    Actor *actori;
    actori = new Actor[10];
    while(g>>cnp>>nume>>nume_f>>pr)
    {
        actori[idxAct].setCNP(cnp);
        actori[idxAct].setNume(nume);
        actori[idxAct].setNumeFilme(nume_f);
        if(pr == "true"){
            actori[idxAct].setRol(true);
        }
        idxAct++;
    }

    Regizor *regizori;
    regizori = new Regizor[10];
    while(h>>cnp>>nume>>nume_f>>suma)
    {
        regizori[idxReg].setCNP(cnp);
        regizori[idxReg].setNume(nume);
        regizori[idxReg].setNumeFilme(nume_f);
        regizori[idxReg++].setSuma(suma);
    }
    FirmaDistributie <Personal> firma;
    int i, j;
    for(i = 0; i < idxReg; i++){
        string film = regizori[i].getNumeFilm();
        for(j = 0; j < idxFilm; j++){
            if(filme[j].getNume() == film)
                break;
        }
        Regizor *r = &regizori[i];
        Film *x = &filme[j];
        firma.adauga(r, x);
    }

    for(i = 0; i < idxAct; i++){
        string film = actori[i].getNumeFilm();
        for(j = 0; j < idxFilm; j++){
            if(filme[j].getNume() == film)
                break;
        }
        Actor *a = &actori[i];
        Film *x = &filme[j];
        firma.adauga(a, x);
    }

    firma.afisare();
    return 0;
}
