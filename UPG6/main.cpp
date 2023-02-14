/*
================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år:s2020

Inlämningsuppgift nr 6b

Namn: Charles Sandholm

Personummer: 87 06 02 - 47 11

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja
Om Nej, beskriv vilka testdata som ger problem:-

Jag har använt kompilator/editor (namn/version): codeblocks 20.03-r11983 (29 Mars 2020). compiler: MinGW 8.1.0

Jag har använt följande dator (t.ex. PC, Mac, Annat):        PC
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : Windows 10

Jag har arbetat ungefär  20 timmar med denna uppgift

================================================================================
*/


#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int menu(int &val);                   //Meny funktion
string namnVal(string allaKompisar); //menyval

const int null = 0;

////////////////////////////
////////////////////////////
////////////////////////////

 class Transaktion
 {
  private:
   string datum;
   string typ;
   string namn;
   double belopp;
   int ant_kompisar;
   string *kompisar;

  public:
   Transaktion();
   ~Transaktion();
   Transaktion& operator=( const Transaktion& t);
   string haemta_namn();
   double haemta_belopp();
   int haemta_ant_kompisar();
   bool finnsKompis( string namnet );
   bool laesEnTrans( istream &is );
   void skrivEnTrans( ostream &os );
    //...eventuellt div. annat...
 };
////////////////////////////
////////////////////////////
////////////////////////////
class Person
 {
 private:
   string namn;
   double betalat_andras;   // ligger ute med totalt
   double skyldig;          // skyldig totalt

 public:
   Person();
   Person( string n, double b, double s );
   Person& operator=( const Person& pny );
   string haemta_personNamn();
   double haemta_betalat();
   double haemta_skyldig();
   void skrivUt();
    //...eventuellt div. annat...
};
////////////////////////////
////////////////////////////
////////////////////////////

class PersonLista
 {
 private:
   int antal_pers;
   Person *pers;

 public:
   PersonLista();
   ~PersonLista();
   void laggTillEn( Person pny );
   void skrivUtOchFixa();
   double summaSkyldig();
   double summaBetalat();
   bool finnsPerson(string namn);
    //...eventuellt div. annat...
 };
////////////////////////////
////////////////////////////
////////////////////////////

class TransaktionsLista
{
 private:
    Transaktion *trans;
    int antalTrans;

 public:
    TransaktionsLista();
    ~TransaktionsLista();

    void laesin( istream & is );
    void skrivut( ostream & os );
    void laggTill( Transaktion & t );
    double totalkostnad();
    double liggerUteMed( string namnet );
    double aerSkyldig( string namnet );
    PersonLista FixaPersoner();
    //...eventuellt div. annat... */
 };

////////////////////////////
////////////////////////////
////////////////////////////



////////////////////////////
////////////////////////////
////////////////////////////

int main()
{

    int val = -1; //menu while loop initieras alltid
    string namn;
    int antalTransaktioner=0;
    string allaKompisarNamn="Eva Paul Bosse Torsten Kristin Stina";
    //Transaktion *transaktioner; //Nytt objekt array
    Transaktion transaktion;    //nytt transaktionsobjekt
    TransaktionsLista lista;    //ny tranaktionslista objekt lista
    PersonLista personlista;    //nytt objekt personlista
    cout<<"Hej. Filen trans.txt behovs for att fortsaetta."<<endl;
    cout<<"Om utfil.txt int finns kommer den skapar vid val 0."<<endl;
    ifstream infil("trans.txt");    //laeser in fil
    lista.laesin(infil);    //laeser in fil info genom laesin
    infil.close();  //staenger fil

    while(val != 0) //meny
    {
        int val = -1;

        menu(val);

        if(val == 0)
        {
            ofstream utfil("utfil.txt");    //oppnar utfil
            cout<<"Programmet avslutas. Skriver ur till filen utfil.txt."<<endl;
            lista.skrivut(utfil);
            utfil.close();
            return 0;
        }
        else if(val == 1)   //laeser in transaktion manuellt
        {
            cout<<"Skriv in info manuellt:"<<endl;
            transaktion.laesEnTrans(cin);
            //transaktioner[antalTransaktioner];
            antalTransaktioner++;
            lista.laggTill(transaktion);
        }
        else if(val == 2)   //skriver ut samtliga transaktioner
        {
            cout<<"Skriver ut all transaktioner:"<<endl;
            cout<<"\n"<<endl;
            lista.skrivut(cout);
            cout<<"\n"<<endl;
        }
        else if(val == 3) //skriver ut totalkostnaden
        {
            cout<<lista.totalkostnad()<<"kr."<<endl;
            cout<<"\n"<<endl;
        }
        else if(val == 4) //skriver ut enskilds skuld
        {
            double skuld = 0;
            cout<<"Vem vill du veta skulden av?"<<endl;
            namn = namnVal(allaKompisarNamn);           //anropar namnVal for vaelja namn
            cout<<"Kollar: "<<namn<<endl;
            skuld = lista.aerSkyldig(namn);     //haemtar skyldigsumma
            cout<<"\n"<<endl;
            cout<<namn<<" är skyldig "<<skuld<<"kr till potten."<<endl;
            cout<<"\n"<<endl;
        }
        else if(val == 5)   //Skriver ut enskilds utgifter
        {
            double betaldaUtgifter;
            cout<<"Vem vill du veta utgifterna av?"<<endl;
            namn = namnVal(allaKompisarNamn);       //namnval
            cout<<"Kollar: "<<namn<<endl;
            betaldaUtgifter = lista.liggerUteMed(namn); //haemtar utgift
            cout<<"\n"<<endl;
            cout<<namn<<" ligger ute med "<<betaldaUtgifter<<" totalt."<<endl;
            cout<<"\n"<<endl;
        }
        else if(val == 6)   //skapar personlista av personer och skriver ut skulder, utgifter och pottdelning
        {
            personlista = lista.FixaPersoner();
            cout<<"\n"<<endl;
            personlista.skrivUtOchFixa();
        }
    }


    return 0;
}
////////////////////////////
////////////////////////////
////////////////////////////
int menu(int &val)  //Menu funktion
{
    while(val<0 || val>6)
    {
        cout<<"Hej. Vad vill du gora?"<<endl;
        cout<<"\n"<<endl;
        cout<<"0. Avslutar programmet. Alla transaktioner sparas på fil."<<endl;
        cout<<"1. Läs in en transaktion fran tangetbord."<<endl;
        cout<<"2. Skriv ut information om alla transaktioner."<<endl;
        cout<<"3. Beräkna totala kostnaden."<<endl;
        cout<<"4. Hur mycket är en viss person skyldig?"<<endl;
        cout<<"5. Hur mycket ligger en viss person ute med?"<<endl;
        cout<<"6. Lista alla personer, potten och pottutdelning."<<endl;
        cout<<"\n"<<endl;
        cin>>val;
        if(val<0 || val>6)
        {
            cout<<"Var snäll slå in ett nummer 0 till 6. Tack"<<endl;
        }
    }
    return val;
}
string namnVal(string allaKompisar) //anvaendaren vaeljer namn genom inmatning 0 - 5
{
    string val;

    cout<<"Vem av "<<allaKompisar<<" vill du kolla?"<<endl;

    cin>>val;
    return val;
}
////////////////////////////
////////////////////////////
////////////////////////////
//----------Transaktion klass------------//
//----------Konstruktororer------------//
Transaktion::Transaktion()
{
    ant_kompisar = 0;
    belopp = 0;
    datum;
    typ;
    namn;
    kompisar=0;
}

Transaktion::~Transaktion()
{

}
Transaktion& Transaktion::operator=( const Transaktion& t)
{
if (this != &t)
    {
      datum = t.datum;
      typ = t.typ;
      namn = t.namn;
      belopp = t.belopp;
      ant_kompisar = t.ant_kompisar;
      kompisar = new string[ant_kompisar];
      for (int i=0; i < ant_kompisar; i++)
      {
        kompisar[i] = t.kompisar[i];
      }
}
return *this;
}
//----------Funktioner (metoder)------------//
bool Transaktion::laesEnTrans( istream &is ) //laeser in en transaktion
{
    is>>datum>>typ>>namn>>belopp>>ant_kompisar; //tilldelar attribut efter ordning i transaktionen
    kompisar = new string [ant_kompisar];
    //cout<<"Hittade "<<datum<<" "<<typ<<" "<<namn<<" "<<belopp<<" "<<ant_kompisar<<" "<<endl;
    for(int i=0;i<ant_kompisar;++i)
    {
        is>>kompisar[i];
        //cout<<kompisar[i]<<" ";
    }
    //cout<<"\n"<<endl;
    return !is.eof();
}
string Transaktion::haemta_namn()
{
    return namn;
}
double Transaktion::haemta_belopp()
{
    return belopp;
}
int Transaktion::haemta_ant_kompisar()
{
    return ant_kompisar;
}
bool Transaktion::finnsKompis( string namnet ) //kollar om namnet(kompis) finns i transaktion
{
    for(int i=0;i<ant_kompisar;i++)
    {
        //cout<<"Kollar efter namnet: "<<namnet<<endl;
        if(kompisar[i] == namnet)
        {
            //cout<<kompisar[i]<<" = "<<namnet<<endl;
            return true;
        }
    }
    return false;
}
void Transaktion::skrivEnTrans( ostream &os ) //skriver ut transaktion
{
    os<<datum<<" "<<typ<<" "<<namn<<" "<<belopp<<" "<<ant_kompisar<<" ";

    for(int i=0;i<ant_kompisar;i++)
    {
        os<<kompisar[i]<<" ";
    }

    os<<endl;
}

////////////////////////////
////////////////////////////
////////////////////////////
//----------TransaktionsLista------------//
//----------Konstruktororer------------//
TransaktionsLista::TransaktionsLista(): antalTrans(0)
{
    trans=0;
}

TransaktionsLista::~TransaktionsLista()
{
    delete [] trans;
}

//----------Funktioner (metoder)------------//



void TransaktionsLista::laesin( istream & is ) //laeser in transaktioner till -lista
{
    Transaktion transaktion;    //skapar transaktion objekt
    //cout<<"laesin"<<endl;
    TransaktionsLista lista;
    while(transaktion.laesEnTrans(is)) //sa lange det finns att laesa in
    {
        laggTill(transaktion);  //laegg till i lista
    }
    if(antalTrans == 9)
    {
        laggTill(transaktion);  //laegg till sista transaktion(annars forlorad)
    }
}

void TransaktionsLista::laggTill(Transaktion & t)
{
    Transaktion *p = 0;
    int n = antalTrans+1;

    if(n>0)
    {
        p = new Transaktion[n];
        int i;
        for(i=0 ; i<n && i<antalTrans ; i++)
        {
            p[i] = trans[i];
            //cout<<"Kopierar trans till p"<<endl;
        }
        for( ; i<n ; i++)
        {
            Transaktion transaktion;
            p[i] =  t;
            //cout<<"Fyller p[i] med trans."<<endl;
        }
    }
    delete [] trans;
    trans = p;
    antalTrans = n;
    //cout<<"Antaltrans = "<<antalTrans<<endl;
}
void TransaktionsLista::skrivut( ostream & os ) //skriver ut från transaktioner från t-lista
{
    for(int i=0;i<antalTrans;i++)
    {
        trans[i].skrivEnTrans(os);
    }
}

double TransaktionsLista::totalkostnad() //alla utgifter sammanlagt
{
    double summa = 0;
    for(int i=0;i<antalTrans;i++)
    {
        summa+=trans[i].haemta_belopp();
    }
    return summa;
}
double TransaktionsLista::liggerUteMed( string namnet ) //enskilds utgifter minus egen del
{
    double utgifter = 0;
    double tempUtgift;
    int antalKompisar;
    for(int i=0;i<antalTrans;i++)
    {
        if(namnet == trans[i].haemta_namn())
        {
            tempUtgift = 0;
            antalKompisar = trans[i].haemta_ant_kompisar()+1;
            tempUtgift = trans[i].haemta_belopp();
            utgifter += tempUtgift - (tempUtgift/antalKompisar);
        }
    }
    return utgifter;
}
double TransaktionsLista::aerSkyldig( string namnet ) //enskilds skuld
{
    double skuld = 0;
    double tempSkuld;
    double tempBelopp;
    int tempAntalKompisar;

    for(int i=0;i<antalTrans;i++)
    {
        //cout<<"Kollar skulder "<<namnet<<endl;
        if(trans[i].finnsKompis(namnet)==true)
        {
            tempAntalKompisar = trans[i].haemta_ant_kompisar()+1;
            //cout<<"Antal kompisar: "<<tempAntalKompisar<<endl;
            tempBelopp = trans[i].haemta_belopp();
            //cout<<"Enstaka belopp: "<<tempBelopp<<endl;
            tempSkuld = tempBelopp/tempAntalKompisar;
            //cout<<"Enstaka skuld: "<<tempSkuld<<endl;
            skuld += tempSkuld;
            //cout<<"Total skuld: "<<skuld<<endl;
        }
    }

    return skuld;
}

////////////////////////////
////////////////////////////
////////////////////////////
//----------Person------------//

//----------konstruktor------------//
Person::Person()
{
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}
Person::Person( string n, double b, double s )
{
    namn = n;
    betalat_andras = b;
    skyldig = s;
}
//----------Funktioner (metoder)------------//
double Person::haemta_betalat()
{
    return skyldig;
}
double Person::haemta_skyldig()
{
    return betalat_andras;
}
void Person::skrivUt() //skriver ut skuld och utgifter(- egen del)
{
        cout<<namn<<" aer skyldig "<<skyldig<<" och har lagt ut "<<betalat_andras<<"kr. ";
        if(betalat_andras>skyldig)
        {
            cout<<namn<<" Ska fa "<<betalat_andras-skyldig<<" fran potten."<<endl;
        }
        else if(betalat_andras<skyldig)
        {
            cout<<namn<<" Ska laegga "<<skyldig-betalat_andras<<" fran potten."<<endl;
        }
}

////////////////////////////
////////////////////////////
////////////////////////////
//----------PersonLista------------//

//----------konstruktor------------//
PersonLista::PersonLista():antal_pers(0)
{
    pers = new Person[antal_pers];
    antal_pers=0;
}
PersonLista::~PersonLista()
{

}
Person& Person::operator=( const Person& pny )
{
    if (this != &pny)
    {
        namn = pny.namn;
        betalat_andras = pny.betalat_andras;
        skyldig = pny.skyldig;
    }
  return *this;
}
//----------Funktioner (metoder)------------//
PersonLista TransaktionsLista::FixaPersoner() //listar personer med namn, skuld och utgift i personlista
{
    PersonLista personlista; //nytt objekt personlista
    string personNamn;
    double personUtgifter;
    double personSkuld;

    for(int i=0;i<antalTrans;i++)     //Alla MÅSTE ha betalat minst en gång för utskriften att fungera.
    {
        //cout<<"Letar efter "<<trans[i].haemta_namn()<<endl;
        if(!personlista.finnsPerson(trans[i].haemta_namn())) //om namn ej finns i listan redan
        {
            personNamn = trans[i].haemta_namn();
            //cout<<"Listar "<<personNamn<<endl;
            personUtgifter = liggerUteMed(personNamn);
            //cout<<"Med utgifter "<<personUtgifter<<endl;
            personSkuld = aerSkyldig(personNamn);
            //cout<<"Med skuld "<<personSkuld<<endl;
            Person nyPerson = Person(personNamn,personUtgifter,personSkuld); //ny person objekt med namn, skuld och utgifter
            personlista.laggTillEn(nyPerson); //laegger till personen i PersonLista- pers[]
        }
    }
    return personlista;
}

void PersonLista::laggTillEn( Person pny )
{
    Person *p = 0;
    int n = antal_pers+1;

    if(n>0)
    {
        p = new Person[n];
        int i;
        for(i=0 ; i<n && i<antal_pers ; i++)
        {
            p[i] = pers[i];
            //cout<<"Kopierar pers till p"<<endl;
        }
        for( ; i<n ; i++)
        {
            p[i] =  pny;
            //cout<<"Fyller p[i] med pers."<<endl;
        }
    }
    delete [] pers;
    pers = p;
    antal_pers = n;
    //cout<<"antal_pers = "<<antal_pers<<endl;

    //cout<<antal_pers<<" antalpers"<<endl;
}
void PersonLista::skrivUtOchFixa() //skriver ut personinfo fran personlista
{
    for(int i=0;i<antal_pers;i++)
    {
        pers[i].skrivUt();
    }
    cout<<"\n"<<endl;
}
double PersonLista::summaSkyldig()
{
    double tempSkuld=0;

    for(int i=0;i<antal_pers;i++)
    {
        tempSkuld += pers[i].haemta_skyldig();
    }
    return tempSkuld;
}
double PersonLista::summaBetalat()
{
    double tempUtgifter=0;
    for(int i=0;i<antal_pers;i++)
    {
        tempUtgifter += pers[i].haemta_betalat();
    }
    return tempUtgifter;

}
string Person::haemta_personNamn()
{
    return namn;
}
bool PersonLista::finnsPerson(string namn)
{
    for(int i=0;i<antal_pers;i++)
    {
        if(pers[i].haemta_personNamn() == namn)
        {
            return true;
        }
    }
    return false;
}
/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================
TESTDATA:
Hej. Filen trans.txt behovs for att fortsaetta.
Om utfil.txt int finns kommer den skapar vid val 0.
Hej. Vad vill du gora?


0. Avslutar programmet. Alla transaktioner sparas p├Ñ fil.
1. L├ñs in en transaktion fran tangetbord.
2. Skriv ut information om alla transaktioner.
3. Ber├ñkna totala kostnaden.
4. Hur mycket ├ñr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer, potten och pottutdelning.


2
Skriver ut all transaktioner:


050615 transp Eva 6000 5 Bosse Kristin Paul Torsten Stina
050721 mat Eva 300 2 Bosse Kristin
050721 mat Paul 400 2 Torsten Stina
050721 transp Bosse 5000 3 Eva Kristin Paul
050721 transp Stina 5000 1 Torsten
050722 boende Kristin 200 1 Eva
050722 mat Eva 300 2 Kristin Bosse
050723 mat Torsten 300 2 Paul Stina
050724 mat Paul 200 1 Stina
050725 transp Eva 600 3 Bosse Kristin Paul


Hej. Vad vill du gora?


0. Avslutar programmet. Alla transaktioner sparas p├Ñ fil.
1. L├ñs in en transaktion fran tangetbord.
2. Skriv ut information om alla transaktioner.
3. Ber├ñkna totala kostnaden.
4. Hur mycket ├ñr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer, potten och pottutdelning.


3
18300kr.


Hej. Vad vill du gora?


0. Avslutar programmet. Alla transaktioner sparas p├Ñ fil.
1. L├ñs in en transaktion fran tangetbord.
2. Skriv ut information om alla transaktioner.
3. Ber├ñkna totala kostnaden.
4. Hur mycket ├ñr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer, potten och pottutdelning.


4
Vem vill du veta skulden av?
Vem av Eva Paul Bosse Torsten Kristin Stina vill du kolla?
Eva
Kollar: Eva


Eva ├ñr skyldig 1350kr till potten.


Hej. Vad vill du gora?


0. Avslutar programmet. Alla transaktioner sparas p├Ñ fil.
1. L├ñs in en transaktion fran tangetbord.
2. Skriv ut information om alla transaktioner.
3. Ber├ñkna totala kostnaden.
4. Hur mycket ├ñr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer, potten och pottutdelning.


5
Vem vill du veta utgifterna av?
Vem av Eva Paul Bosse Torsten Kristin Stina vill du kolla?
Torsten
Kollar: Torsten


Torsten ligger ute med 200 totalt.


Hej. Vad vill du gora?


0. Avslutar programmet. Alla transaktioner sparas p├Ñ fil.
1. L├ñs in en transaktion fran tangetbord.
2. Skriv ut information om alla transaktioner.
3. Ber├ñkna totala kostnaden.
4. Hur mycket ├ñr en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer, potten och pottutdelning.


0
Programmet avslutas. Skriver ur till filen utfil.txt.

Process returned 0 (0x0)   execution time : 17.366 s
Press any key to continue.




================================================================================
Här skriver du en kort rapport om uppgiften:

Komplettering:

Det finns nu inte MAX_TRANSAKTIONER och MAX_PERSONER. I metoderna som lägger
till transaktioner till lista och personer till personlista (laggtill),
skapar en temporär lista som utökar arrayn med ett för varje nytt objekt.
Till listan kopieras redan existerande och en extra läggs till. Minnet
från trans och pers avallokeras och och kopierar den temporära.
Eftersom den temporära är lokal behöver man inte använda delete, minnet kommer
avallokeras automatiskt.


Jag förstår att jag kommer att få komplettera. Det har vart en stor utmaning.
JAg antar att array-deklarationerna alla är ok, men att jag behöver tänjbara arrayer och
sätta attributen i konstruktorerna. Men jaf behöver lite pointers... på vart jag
måste lägga ned mer tid på, och på vad som är ok i nuläget.

Koden är körbar iaf, och det ser jag som stor framgång.

================================================================================

Andra delen gick ut på att använda sig av dynamiska arrayer mellan objekt och klasser
istället för dynamiska arrayer.


Pekare är mer abstrakt än tydliga deklarationer och det gäller att få med sin
all data mellan objekt och klasser.

Allt, faktiskt. Det här var väldigt utmanande. Första två dagarnas kod fick jag börja
om med. Jag hade missförstått från början och slarvat. Det kostande enormt mycket tid.

Genom diskussioner i forumet, youtube kanaler och kursens information och övningsexempel.

Frågor

1.
Det är ett objekt vi tilldelar trans i TransaktionsLista och för att få med all info som
lästes in så behöver vi kopiera informationen till trans.

Om inte denna pekarens "ägarklass".. typ.


*/
