#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

/*notatii
fata 0 alba
fata 1 rosu
fata 2 albastru
fata 3 verde
fata 4 portocaliu
fata 5 galben
des vectorul matricea destinatie
prm vectorul matricea care se copie in destinatie*/

//int to string
void its(string &des, int prm)
{
    char t[30];
    des="";
    int u[30];
    int curs=0;
    if (prm==0) u[curs++]=0;
    while(prm>0)
    {
        u[curs++]=prm%10;
        prm/=10;
    }
    int i,j;
    for(i=curs-1,j=0;i>=0;i--,j++)
    {
        t[j]=char(u[i]+'0');
    }
    t[curs]='\0';
    des.append(t);
}

//citirea unei configuratii
void read(int a[6][3][3],char cit1[])
{
    std::ifstream cit(cit1);
    int i,j,k;
    for(i=0;i<6;i++)
		for(j=0;j<3;j++)
			for(k=0;k<3;k++)
				cit >> a[i][j][k];
}

//afisarea unei configuratii
void show(int a[6][3][3],char afis1[])
{
    std::ofstream afis;
    afis.open (afis1,std::ios::app);
	int i,j,k;
	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				afis << a[i][j][k] << ' ';
			}
			afis << '\n';
		}
		afis << '\n';
	}
	afis << "//" << '\n';
}

//afisarea unui string
void g(string str, char afis1[])
{
    std::ofstream afis;
    afis.open (afis1,std::ios::app);
    afis << str;
}

//sterge date fisier afis1
void clearafis(char afis1[])
{
    std::ofstream afis;
    afis.open(afis1,std::ios::out);
}

//compararea unei configuratii cu o alta
bool cmp(int a[6][3][3], int b[6][3][3])
{
    int i,j,k;
    for(i=0;i<6;i++)
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                if (a[i][j][k]!=b[i][j][k]) return false;
    return true;
}

//copierea in configuratia a a configuratiei b
void atr(int a[6][3][3], int b[6][3][3])
{
    int i,j,k;
    for(i=0;i<6;i++)
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                a[i][j][k]=b[i][j][k];
}

//1)miscari

//rotatia unei fete in mod F
void rot(int des[3][3], int prm[3][3])
{
    des[0][0]=prm[2][0];
    des[0][1]=prm[1][0];
    des[0][2]=prm[0][0];
    des[1][0]=prm[2][1];
    des[1][1]=prm[1][1];
    des[1][2]=prm[0][1];
    des[2][0]=prm[2][2];
    des[2][1]=prm[1][2];
    des[2][2]=prm[0][2];
}

//rotatia unei fete in mod F'
void rot_st(int des[3][3], int prm[3][3])
{
    int aux[3][3];
    rot(des,prm);
    rot(aux,des);
    rot(des,aux);
}

//copierea unei linii
void cplin(int des[3], int prm[3])
{
    int i;
    for(i=0;i<3;i++)
    {
        des[i]=prm[i];
    }
}

//copierea unei coloane
void cpcol(int des[3][3], int prm[3][3], int coldes, int colprm)
{
    int i;
    for(i=0;i<3;i++)
    {
        des[i][coldes]=prm[i][colprm];
    }
}

//copierea unei fete
void cpfata(int des[3][3], int prm[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            des[i][j]=prm[i][j];
        }
    }
}

//copierea unei coloane intr-o linie cu rotatie F
void cp_lin_col(int des[3], int prm[3][3], int col)
{
    des[0]=prm[2][col];
    des[1]=prm[1][col];
    des[2]=prm[0][col];
}

//copierea unei linii intr-o coloana cu rotatie F
void cp_col_lin(int des[3][3], int prm[3], int col)
{
    des[0][col]=prm[0];
    des[1][col]=prm[1];
    des[2][col]=prm[2];
}

//copierea unei coloane intr-o linie cu rotatia F'
void cp_lin_col_st(int des[3], int prm[3][3], int col)
{
    des[0]=prm[0][col];
    des[1]=prm[1][col];
    des[2]=prm[2][col];
}

//copierea unei linii intr-o coloana cu rotatia F'
void cp_col_lin_st(int des[3][3], int prm[3], int col)
{
    des[0][col]=prm[2];
    des[1][col]=prm[1];
    des[2][col]=prm[0];
}

//miscarea U
void u(int a[6][3][3])
{
    int aux1[3];
    int aux2[3][3];

    //copierea in aux1 a liniei de sus a fetei rosii
    cplin(aux1,a[1][0]);
    //copierea in linia de sus a fetei rosii a liniei de sus a fetei verzi
    cplin(a[1][0],a[3][0]);
    //copierea in linia de sus a fetei verzi a liniei de sus a fetei portocalii
    cplin(a[3][0],a[4][0]);
    //copierea in linia de sus a fetei portocalii a liniei de sus a fetei albastre
    cplin(a[4][0],a[2][0]);
    //copierea in linia de sus a fetei albastre a aux1(linia de sus a fetei rosii)
    cplin(a[2][0],aux1);

    //rotirea in aux2 a fetei galbene
    rot(aux2,a[5]);
    //copierea in fata galbena a aux2
    cplin(a[5][0],aux2[0]);
    cplin(a[5][1],aux2[1]);
    cplin(a[5][2],aux2[2]);
}

//miscarea U'
void uprm(int a[6][3][3])
{
    u(a);
    u(a);
    u(a);
}

//miscarea U2
void u2(int a[6][3][3])
{
    u(a);
	u(a);
}

//miscarea D
void d(int a[6][3][3])
{
    int aux1[3];
    int aux2[3][3];

    //copierea in aux1 a liniei de jos a fetei rosii
    cplin(aux1,a[1][2]);
    //copierea in linia de jos a fetei rosii a liniei de jos a fetei albastre
    cplin(a[1][2],a[2][2]);
    //copierea in linia de jos a fetei albastre a liniei de jos a fetei portocalii
    cplin(a[2][2],a[4][2]);
    //copierea in linia de jos a fetei portocalii a liniei de jos a fetei verzi
    cplin(a[4][2],a[3][2]);
    //copierea in linia de jos a fetei verzi a aux1(linia de jos a fetei rosii)
    cplin(a[3][2],aux1);

    //rotatia in aux2 a fetei albe
    rot(aux2,a[0]);
    //copierea in fata alba a aux2
    cplin(a[0][0],aux2[0]);
    cplin(a[0][1],aux2[1]);
    cplin(a[0][2],aux2[2]);
}

//miscarea D'
void dprm(int a[6][3][3])
{
    d(a);
    d(a);
	d(a);
}

//miscarea D2
void d2(int a[6][3][3])
{
    d(a);
	d(a);
}

//miscarea F
void f(int a[6][3][3])
{
    int aux1[3];
    int aux2[3][3];

    //copierea in aux1 a liniei de sus a fetei albe
    cplin(aux1,a[0][0]);
    //copierea in linia de sus a fetei albe a coloanei din stanga a fetei verzi
    cp_lin_col(a[0][0],a[3],0);
	//copierea in coloana din stanga a fetei verzi a liniei de jos a fetei galbene
    cp_col_lin(a[3],a[5][2],0);
	//copierea in linia de jos a fetei galbene a coloanei din dreapta a fetei albastre
    cp_lin_col(a[5][2],a[2],2);
    //copierea in coloana din dreapta a fetei albastre a aux1(linia de sus a fetei albe)
    cp_col_lin(a[2],aux1,2);

    //rotatia in aux2 a fetei rosii
    rot(aux2,a[1]);
    //copierea in fata rosie a aux2
    cplin(a[1][0],aux2[0]);
    cplin(a[1][1],aux2[1]);
    cplin(a[1][2],aux2[2]);
}

//miscarea F'
void fprm(int a[6][3][3])
{
    f(a);
    f(a);
	f(a);
}

//miscarea F2
void f2(int a[6][3][3])
{
    f(a);
	f(a);
}

//miscarea B
void b(int a[6][3][3])
{
    int aux1[3];
    int aux2[3][3];

    //copiere in aux1 a liniei de jos a fetei albe
    cplin(aux1,a[0][2]);
    //copiere in linia de jos a fetei albe a coloanei din stanga a fetei albastre (miscare F')
    cp_lin_col_st(a[0][2],a[2],0);
    //copiere in coloana din stanga a fetei albastre a liniei de sus a fetei galbene (miscare F')
    cp_col_lin_st(a[2],a[5][0],0);
    //copiere in linia de sus a fetei galbene a coloanei din dreapta a fetei verzi (miscare F')
    cp_lin_col_st(a[5][0],a[3],2);
    //copiere in coloana de dreapta a fetei verzi a aux1(linia de jos a fetei albe) (miscare F')
    cp_col_lin_st(a[3],aux1,2);
    //rotatia in aux2 a fetei portocalii
    rot(aux2,a[4]);
    //copierea in fata portocalie a aux2
    cplin(a[4][0],aux2[0]);
    cplin(a[4][1],aux2[1]);
    cplin(a[4][2],aux2[2]);
}

//miscarea B'
void bprm(int a[6][3][3])
{
    b(a);
    b(a);
	b(a);
}

//miscarea B2
void b2(int a[6][3][3])
{
    b(a);
	b(a);
}

//miscarea R
void r(int a[6][3][3])
{
    int aux1[3][3];
    int aux2[3][3];

    //copierea in aux1[][2] a coloanei din dreapta a fetei galbene
    cpcol(aux1,a[5],2,2);
    //rotirea dubla a aux1(prin intermediul lui aux2)(deoarece fata portocalie este rotita dublu)
    rot(aux2,aux1);
    rot(aux1,aux2);
    //copierea in coloana din dreapta a fetei galbene a coloanei din dreapta a fetei rosii
    cpcol(a[5],a[1],2,2);
    //copierea in coloana din dreapta a fetei rosii a coloanei din dreapta a fetei albe
    cpcol(a[1],a[0],2,2);
    //copierea in coloana din dreapta a fetei albe a coloanei din stanga a fetei portocalii(rotita dublu)
    {
        a[0][0][2]=a[4][2][0];
        a[0][1][2]=a[4][1][0];
        a[0][2][2]=a[4][0][0];
    }
    //copierea in coloana din stanga a fetei portocalii a aux1[][0](coloana din dreapta a fetei galbene rotita dublu)
    cpcol(a[4],aux1,0,0);

    //rotirea in aux2 a fetei albastre
    rot(aux2,a[3]);
    //copierea in fata albastra a aux2
    cplin(a[3][0],aux2[0]);
    cplin(a[3][1],aux2[1]);
    cplin(a[3][2],aux2[2]);
}

//miscarea R'
void rprm(int a[6][3][3])
{
    r(a);
    r(a);
	r(a);
}

//miscarea R2
void r2(int a[6][3][3])
{
    r(a);
	r(a);
}

//miscarea L
void l(int a[6][3][3])
{
    int aux1[3][3];
    int aux2[3][3];

    //copierea in aux1 a1[][0] a coloanei din stanga a fetei albe
    cpcol(aux1,a[0],0,0);
    //rotirea dubla a aux1(prin intermediul lui aux2)(deoarece fata portocalie este rotita dublu)
    rot(aux2,aux1);
    rot(aux1,aux2);
    //copierea in coloana din stanga a fetei albe a coloanei din stanga a fetei rosii
    cpcol(a[0],a[1],0,0);
    //copierea in coloana din stanga a fetei rosii a coloanei din stanga a fetei galbene
    cpcol(a[1],a[5],0,0);
    //copierea in coloana din stanga a fetei galbene a coloanei din dreapta a fetei portocalii(rotita dublu)
    {
        a[5][2][0]=a[4][0][2];
        a[5][1][0]=a[4][1][2];
        a[5][0][0]=a[4][2][2];
    }
    //copierea in coloana din dreapta a fetei portocalii a aux1[][2](coloana din stanga a fetei albe rotita dublu)
    cpcol(a[4],aux1,2,2);

    //rotirea in aux2 a fetei albastre
    rot(aux2,a[2]);
    //copierea in fata albasta a aux2
    cplin(a[2][0],aux2[0]);
    cplin(a[2][1],aux2[1]);
    cplin(a[2][2],aux2[2]);
}

//miscarea L'
void lprm(int a[6][3][3])
{
    l(a);
    l(a);
	l(a);
}

//miscarea L2
void l2(int a[6][3][3])
{
    l(a);
	l(a);
}

//miscarea "Go to Up"
void xprm(int a[6][3][3])
{
    int fataux[3][3];
    //copiere in fataux a fetei a[0]
    cpfata(fataux,a[0]);
    //copiere in fata a[0] a fetei a[1]
    cpfata(a[0],a[1]);
    //copiere in fata a[1] a fetei a[5]
    cpfata(a[1],a[5]);
    //rotirea dubla in fata a[5] a fetei a[4]
    rot(a[5],a[4]);
    rot(a[4],a[5]);
    cpfata(a[5],a[4]);
    //rotirea dubla in fata a[4] a fataux(fata a[0])
    rot(a[4],fataux);
    rot(fataux,a[4]);
    cpfata(a[4],fataux);
    //rotirea fetei a[2] in mod F'
    rot(fataux,a[2]);
    cpfata(a[2],fataux);
    //rotirea fetei a[3] in mod F
    rot_st(fataux,a[3]);
    cpfata(a[3],fataux);
}

//miscarea "Go to Down"
void x(int a[6][3][3])
{
    xprm(a);
    xprm(a);
    xprm(a);
}

//miscarea "Go to Right"
void y(int a[6][3][3])
{
    int fataux[3][3];
    //rotirea in mod F a fetei a[5]
    rot(fataux,a[5]);
    cpfata(a[5],fataux);
    //rotirea in mod F' a fetei a[0]
    rot_st(fataux,a[0]);
    cpfata(a[0],fataux);
    //copierea in fataux a fetei a[1]
    cpfata(fataux,a[1]);
    //copierea in fata a[1] a fetei a[3]
    cpfata(a[1],a[3]);
    //copierea in fata a[3] a fetei a[4]
    cpfata(a[3],a[4]);
    //copierea in fata a[4] a fetei a[2]
    cpfata(a[4],a[2]);
    //copierea in fata a[2] a fetei fataux(fata a[1])
    cpfata(a[2],fataux);
}

//miscarea "Go to Left"
void yprm(int a[6][3][3])
{
    y(a);
    y(a);
    y(a);
}

//miscarea "Go to Back"
void y2(int a[6][3][3])
{
    y(a);
    y(a);
}

// 2) Pasi

//Pasul 1: Crucea
void pas1crucea(int a[6][3][3], char z[])
{
    //Pasul 1
    g("Pasul 1) ",z);

    //fata curenta
    int n=1;

    //variabila conditie cruce
    bool cond=false;

    //VERIFICARE POZITII SIMPLE
    if ((a[0][0][1]==0) and (a[0][1][0]==0) and (a[0][1][2]==0) and (a[0][2][1]==0))
    {
        //POZITIA FINALA
        if ((a[1][2][1]==1) and (a[2][2][1]==2) and (a[3][2][1]==3) and (a[4][2][1]==4)) cond=true;
        //POZITIA CE NECESITA D
        if ((a[1][2][1]==3) and (a[2][2][1]==1) and (a[3][2][1]==4) and (a[4][2][1]==2)) {g("D ",z); d(a);}
        //POZITIA CE NECESITA D'
        if ((a[1][2][1]==2) and (a[2][2][1]==4) and (a[3][2][1]==1) and (a[4][2][1]==3)) {g("D' ",z); dprm(a);}
        //POZITIA CE NECESITA D2
        if ((a[1][2][1]==4) and (a[2][2][1]==3) and (a[3][2][1]==2) and (a[4][2][1]==1)) {g("D2 ",z); d2(a);}
    }

    //MUCHIA ROSIE
    //verificare daca avem crucea
    if (!cond)
    {

        //JOS

        //muchia rosie e sub centrul rosu
        if ((a[0][0][1]==0) and (a[1][2][1]==1)) {}
        //muchia rosie e sub centrul albastru
        else if ((a[0][1][0]==0) and (a[2][2][1]==1)) {g("D ",z); d(a);}
        //muchia rosie e sub centrul verde
        else if ((a[0][1][2]==0) and (a[3][2][1]==1)) {g("D' ",z); dprm(a);}
        //muchia rosie e sub centrul portocaliu
        else if ((a[0][2][1]==0) and (a[4][2][1]==1)) {g("D2 ",z); d2(a);}

        //JOS INVERS

        //muchia rosie e sub centrul rosu invers
        else if ((a[0][0][1]==1) and (a[1][2][1]==0)) {g("D R F ",z); d(a); r(a); f(a);}
        //muchia rosie e sub centrul albastru invers
        else if ((a[0][1][0]==1) and (a[2][2][1]==0)) {g("L' F' ",z); lprm(a); fprm(a);}
        //muchia rosie e sub centrul verde invers
        else if ((a[0][1][2]==1) and (a[3][2][1]==0)) {g("R F ",z); r(a); f(a);}
        //muchia rosie e sub centrul portocaliu invers
        else if ((a[0][2][1]==1) and (a[4][2][1]==0)) {g("D L' F' ",z); d(a); lprm(a); fprm(a);}

        //CENTRU

        //muchia rosie e intre centrul albastru si centrul rosu
        //alb spre dreapta
        else if ((a[2][1][2]==1) and (a[1][1][0]==0)) {g("L D ",z); l(a); d(a);}
        //alb spre stanga
        else if ((a[2][1][2]==0) and (a[1][1][0]==1)) {g("F' ",z); fprm(a);}
        //muchia rosie e intre centrul rosu si centrul verde
        //alb spre dreapta
        else if ((a[1][1][2]==1) and (a[3][1][0]==0)) {g("F ",z); f(a);}
        //alb spre stanga
        else if ((a[1][1][2]==0) and (a[3][1][0]==1)) {g("R' D' ",z); rprm(a); dprm(a);}
        //muchia rosie e intre centrul verde si centrul portocaliu
        //alb spre dreapta
        else if ((a[3][1][2]==1) and (a[4][1][0]==0)) {g("R D' ",z); r(a); dprm(a);}
        //alb spre stanga
        else if ((a[3][1][2]==0) and (a[4][1][0]==1)) {g("R2 F ",z); r2(a); f(a);}
        //muchia rosie e intre centrul portocaliu si centrul albastru
        //alb spre dreapta
        else if ((a[4][1][2]==1) and (a[2][1][0]==0)) {g("B D2 ",z); b(a); d2(a);}
        //alb spre stanga
        else if ((a[4][1][2]==0) and (a[2][1][0]==1)) {g("L' D ",z); lprm(a); d(a);}

        //SUS

        //muchia rosie e deasuprea centrului rosu
        else if ((a[5][2][1]==0) and (a[1][0][1]==1)) {g("F2 ",z); f2(a);}
        //muchia rosie e deasuprea centrului albastru
        else if ((a[5][1][0]==0) and (a[2][0][1]==1)) {g("U' F2 ",z); uprm(a); f2(a);}
        //muchia rosie e deasuprea centrului verde
        else if ((a[5][1][2]==0) and (a[3][0][1]==1)) {g("U F2 ",z); u(a); f2(a);}
        //muchia rosie e deasuprea centrului portocaliu
        else if ((a[5][0][1]==0) and (a[4][0][1]==1)) {g("U2 F2 ",z); u2(a); f2(a);}

        //SUS INVERS

        //muchia rosie e deasuprea centrului rosu
        else if ((a[5][2][1]==1) and (a[1][0][1]==0)) {g("F R U F2 ",z); f(a); r(a); u(a); f2(a);}
        //muchia rosie e deasuprea centrului albastru
        else if ((a[5][1][0]==1) and (a[2][0][1]==0)) {g("U' F R U F2 ",z); uprm(a); f(a); r(a); u(a); f2(a);}
        //muchia rosie e deasuprea centrului verde
        else if ((a[5][1][2]==1) and (a[3][0][1]==0)) {g("U F R U F2 ",z); u(a); f(a); r(a); u(a); f2(a);}
        //muchia rosie e deasuprea centrului portocaliu
        else if ((a[5][0][1]==1) and (a[4][0][1]==0)) {g("U2 F R U F2 ",z); u2(a); f(a); r(a); u(a); f2(a);}
    }

    //verificare daca avem crucea
    if ((a[0][0][1]==0) and (a[0][1][0]==0) and (a[0][1][2]==0) and (a[0][2][1]==0) and (a[1][2][1]==1) and (a[2][2][1]==2) and (a[3][2][1]==3) and (a[4][2][1]==4)) cond=true;

    //MUCHIA ALBASTRA
    //verificare daca avem crucea
    if (!cond)
    {
        //miscare "Go to Left"
        g("Y' ",z); yprm(a);
        //modificare stare fata
        n--;

        //JOS

        //muchia albastra e sub centrul albastru
        if ((a[0][0][1]==0) and (a[1][2][1]==2)) {}
        //muchia albastra e sub centrul portocaliu
        else if ((a[0][1][0]==0) and (a[2][2][1]==2)) {g("L2 U' F2 ",z); l2(a); uprm(a); f2(a);}
        //muchia albastra e sub centrul verde
        else if ((a[0][2][1]==0) and (a[4][2][1]==2)) {g("B2 U2 F2 ",z); b2(a); u2(a); f2(a);}

        //JOS INVERS

        //muchia albastra e sub centrul albastru invers
        else if ((a[0][0][1]==2) and (a[1][2][1]==0)) {g("R D' L' R' F' ",z); r(a); dprm(a); lprm(a); rprm(a); fprm(a);}
        //muchia albastra e sub centrul portocaliu invers
        else if ((a[0][1][0]==2) and (a[2][2][1]==0)) {g("L' F' ",z); lprm(a); fprm(a);}
        //muchia albastra e sub centrul verde invers
        else if ((a[0][2][1]==2) and (a[4][2][1]==0)) {g("B' L' R D R' ",z); bprm(a); lprm(a); r(a); d(a); rprm(a);}

        //CENTRU

        //muchia albastra e intre centrul portocaliu si centrul albastru
        //alb spre dreapta
        else if ((a[2][1][2]==2) and (a[1][1][0]==0)) {g("R L D R' ",z); r(a); l(a); d(a); rprm(a);}
        //alb spre stanga
        else if ((a[2][1][2]==0) and (a[1][1][0]==2)) {g("F' ",z); fprm(a);}
        //muchia albastra e intre centrul albastru si centrul rosu
        //alb spre dreapta
        else if ((a[1][1][2]==2) and (a[3][1][0]==0)) {g("F ",z); f(a);}
        //alb spre stanga
        else if ((a[1][1][2]==0) and (a[3][1][0]==2)) {g("R' D' R ",z); rprm(a); dprm(a); r(a);}
        //muchia albastra e intre centrul rosu si centrul verde
        //alb spre dreapta
        else if ((a[3][1][2]==2) and (a[4][1][0]==0)) {g("R D' R' ",z); r(a); dprm(a); rprm(a);}
        //alb spre stanga
        else if ((a[3][1][2]==0) and (a[4][1][0]==2)) {g("B U2 F2 ",z); b(a); u2(a); f2(a);}
        //muchia albastra e intre centrul verde si centrul portocaliu
        //alb spre dreapta
        else if ((a[4][1][2]==2) and (a[2][1][0]==0)) {g("L2 F' ",z); l2(a); fprm(a);}
        //alb spre stanga
        else if ((a[4][1][2]==0) and (a[2][1][0]==2)) {g("L' R D R' ",z); lprm(a); r(a); d(a); rprm(a);}

        //SUS

        //muchia albastra e deasuprea centrului albastru
        else if ((a[5][2][1]==0) and (a[1][0][1]==2)) {g("F2 ",z); f2(a);}
        //muchia albastra e deasuprea centrului portocaliu
        else if ((a[5][1][0]==0) and (a[2][0][1]==2)) {g("U' F2 ",z); uprm(a); f2(a);}
        //muchia albastra e deasuprea centrului rosu
        else if ((a[5][1][2]==0) and (a[3][0][1]==2)) {g("U F2 ",z); u(a); f2(a);}
        //muchia albastra e deasuprea centrului verde
        else if ((a[5][0][1]==0) and (a[4][0][1]==2)) {g("U2 F2 ",z); u2(a); f2(a);}

        //SUS INVERS

        //muchia albastra e deasuprea centrului albastru
        else if ((a[5][2][1]==2) and (a[1][0][1]==0)) {g("U L F' ",z); u(a); l(a); fprm(a);}
        //muchia albastra e deasuprea centrului portocaliu
        else if ((a[5][1][0]==2) and (a[2][0][1]==0)) {g("L F' ",z); l(a); fprm(a);}
        //muchia albastra e deasuprea centrului rosu
        else if ((a[5][1][2]==2) and (a[3][0][1]==0)) {g("U2 L F' ",z); u2(a); l(a); fprm(a);}
        //muchia albastra e deasuprea centrului verde
        else if ((a[5][0][1]==2) and (a[4][0][1]==0)) {g("U' L F' ",z); uprm(a); l(a); fprm(a);}
    }

    //verificare daca avem crucea
    if ((a[0][0][1]==0) and (a[0][1][0]==0) and (a[0][1][2]==0) and (a[0][2][1]==0) and (a[1][2][1]==2) and (a[2][2][1]==4) and (a[3][2][1]==1) and (a[4][2][1]==3)) cond=true;

    //MUCHIA VERDE
    //verificare daca avem crucea
    if (!cond)
    {
        //miscare "Go to Back"
        g("Y2 ",z); y2(a);
        //modificare stare fata
        n=n+2;

        //JOS

        //muchia verde e sub centrul verde
        if ((a[0][0][1]==0) and (a[1][2][1]==3)) {}
        //muchia verde e sub centrul portocaliu
        else if ((a[0][1][2]==0) and (a[3][2][1]==3)) {g("R D R' D' ",z); r(a); d(a); rprm(a); dprm(a);}

        //JOS INVERS

        //muchia verde e sub centrul verde invers
        else if ((a[0][0][1]==3) and (a[1][2][1]==0)) {g("D R D' F ",z); d(a); r(a); dprm(a); f(a);}
        //muchia verde e sub centrul portocaliu invers
        else if ((a[0][1][2]==3) and (a[3][2][1]==0)) {g("R F ",z); r(a); f(a);}

        //CENTRU

        //muchia verde e intre centrul rosu si centrul verde
        //alb spre dreapta
        else if ((a[2][1][2]==3) and (a[1][1][0]==0)) {g("D' L D ",z); dprm(a); l(a); d(a);}
        //alb spre stanga
        else if ((a[2][1][2]==0) and (a[1][1][0]==3)) {g("F' ",z); fprm(a);}
        //muchia verde e intre centrul verde si centrul portocaliu
        //alb spre dreapta
        else if ((a[1][1][2]==3) and (a[3][1][0]==0)) {g("F ",z); f(a);}
        //alb spre stanga
        else if ((a[1][1][2]==0) and (a[3][1][0]==3)) {g("D R' D' ",z); d(a); rprm(a); dprm(a);}
        //muchia verde e intre centrul portocaliu si centrul albastru
        //alb spre dreapta
        else if ((a[3][1][2]==3) and (a[4][1][0]==0)) {g("R' U F2 ",z); rprm(a); u(a); f2(a);}
        //alb spre stanga
        else if ((a[3][1][2]==0) and (a[4][1][0]==3)) {g("D2 B' D2 ",z); d2(a); bprm(a); d2(a);}
        //muchia verde e intre centrul albastru si centrul rosu
        //alb spre dreapta
        else if ((a[4][1][2]==3) and (a[2][1][0]==0)) {g("B' U2 B F2 ",z); bprm(a); u2(a); b(a); f2(a);}
        //alb spre stanga
        else if ((a[4][1][2]==0) and (a[2][1][0]==3)) {g("D' L' D ",z); dprm(a); lprm(a); d(a);}

        //SUS

        //muchia verde e deasuprea centrului verde
        else if ((a[5][2][1]==0) and (a[1][0][1]==3)) {g("F2 ",z); f2(a);}
        //muchia verde e deasuprea centrului rosu
        else if ((a[5][1][0]==0) and (a[2][0][1]==3)) {g("U' F2 ",z); uprm(a); f2(a);}
        //muchia verde e deasuprea centrului portocaliu
        else if ((a[5][1][2]==0) and (a[3][0][1]==3)) {g("U F2 ",z); u(a); f2(a);}
        //muchia verde e deasuprea centrului albastru
        else if ((a[5][0][1]==0) and (a[4][0][1]==3)) {g("U2 F2 ",z); u2(a); f2(a);}

        //SUS INVERS

        //muchia verde e deasuprea centrului verde
        else if ((a[5][2][1]==3) and (a[1][0][1]==0)) {g("U' R' F ",z); uprm(a); rprm(a); f(a);}
        //muchia verde e deasuprea centrului rosu
        else if ((a[5][1][0]==3) and (a[2][0][1]==0)) {g("U2 R' F ",z); u2(a); rprm(a); f(a);}
        //muchia verde e deasuprea centrului portocaliu
        else if ((a[5][1][2]==3) and (a[3][0][1]==0)) {g("R' F ",z); rprm(a); f(a);}
        //muchia verde e deasuprea centrului albastru
        else if ((a[5][0][1]==3) and (a[4][0][1]==0)) {g("U R' F ",z); u(a); rprm(a); f(a);}
    }

    //verificare daca avem crucea
    if ((a[0][0][1]==0) and (a[0][1][0]==0) and (a[0][1][2]==0) and (a[0][2][1]==0) and (a[1][2][1]==3) and (a[2][2][1]==1) and (a[3][2][1]==4) and (a[4][2][1]==2)) cond=true;

    //MUCHIA PORTOCALIE
    //verificare daca avem crucea
    if (!cond)
    {
        //miscare "Go to Right"
        g("Y ",z); y(a);
        //modificare stare fata
        n++;

        //JOS

        //muchia portocalie e sub centrul portocaliu
        if ((a[0][0][1]==0) and (a[1][2][1]==4)) {}

        //JOS INVERS

        //muchia portocalie e sub centrul portocaliu invers
        else if ((a[0][0][1]==4) and (a[1][2][1]==0)) {g("D R D' F ",z); d(a); r(a); dprm(a); f(a);}

        //CENTRU

        //muchia portocalie e intre centrul verde si centrul portocaliu
        //alb spre dreapta
        else if ((a[2][1][2]==4) and (a[1][1][0]==0)) {g("D' L D ",z); dprm(a); l(a); d(a);}
        //alb spre stanga
        else if ((a[2][1][2]==0) and (a[1][1][0]==4)) {g("F' ",z); fprm(a);}
        //muchia portocalie e intre centrul portocaliu si centrul albastru
        //alb spre dreapta
        else if ((a[1][1][2]==4) and (a[3][1][0]==0)) {g("F ",z); f(a);}
        //alb spre stanga
        else if ((a[1][1][2]==0) and (a[3][1][0]==4)) {g("D R' D' ",z); d(a); rprm(a); dprm(a);}
        //muchia portocalie e intre centrul albastru si centrul rosu
        //alb spre dreapta
        else if ((a[3][1][2]==4) and (a[4][1][0]==0)) {g("R' U F2 R ",z); rprm(a); u(a); f2(a); r(a);}
        //alb spre stanga
        else if ((a[3][1][2]==0) and (a[4][1][0]==4)) {g("D2 B' D2 ",z); d2(a); bprm(a); d2(a);}
        //muchia portocalie e intre centrul rosu si centrul verde
        //alb spre dreapta
        else if ((a[4][1][2]==4) and (a[2][1][0]==0)) {g("B' U2 B F2 ",z); bprm(a); u2(a); b(a); f2(a);}
        //alb spre stanga
        else if ((a[4][1][2]==0) and (a[2][1][0]==4)) {g("D' L' D ",z); dprm(a); lprm(a); d(a);}

        //SUS

        //muchia portocalie e deasuprea centrului portocaliu
        else if ((a[5][2][1]==0) and (a[1][0][1]==4)) {g("F2 ",z); f2(a);}
        //muchia portocalie e deasuprea centrului verde
        else if ((a[5][1][0]==0) and (a[2][0][1]==4)) {g("U' F2 ",z); uprm(a); f2(a);}
        //muchia portocalie e deasuprea centrului albastru
        else if ((a[5][1][2]==0) and (a[3][0][1]==4)) {g("U F2 ",z); u(a); f2(a);}
        //muchia portocalie e deasuprea centrului rosu
        else if ((a[5][0][1]==0) and (a[4][0][1]==4)) {g("U2 F2 ",z); u2(a); f2(a);}

        //SUS INVERS

        //muchia portocalie e deasuprea centrului portocaliu
        else if ((a[5][2][1]==4) and (a[1][0][1]==0)) {g("U' R' F R ",z); uprm(a); rprm(a); f(a); r(a);}
        //muchia portocalie e deasuprea centrului verde
        else if ((a[5][1][0]==4) and (a[2][0][1]==0)) {g("U2 R' F R ",z); u2(a); rprm(a); f(a); r(a);}
        //muchia portocalie e deasuprea centrului albastru
        else if ((a[5][1][2]==4) and (a[3][0][1]==0)) {g("R' F R ",z); rprm(a); f(a); r(a);}
        //muchia portocalie e deasuprea centrului rosu
        else if ((a[5][0][1]==4) and (a[4][0][1]==0)) {g("U R' F R ",z); u(a); rprm(a); f(a); r(a);}
    }

    //stabilire miscare urmatoare
    //miscare "Go to Right"
    if (n==1) {g("Y' ",z); yprm(a);}
    //miscare "Go to Left"
    else if (n==2) {g("Y2 ",z); y2(a);}
    //miscare "Go to Back"
    else if (n==3) {g("Y ",z); y(a);}
    //linii noi
    g("\n",z);
}

//Rezolvarea unui colt
void rezcolt(int a[6][3][3], char z[], int n1, int n2)
{
    //verificare pozitie colt

    //pozitii jos

    //intre fetele 1-3
    if ((a[0][0][2]==n2) and (a[1][2][2]==0) and (a[3][2][0]==n1)) {g("R' F R F2 U' F ",z); rprm(a); f(a); r(a); f2(a); uprm(a); f(a);}
    else if ((a[0][0][2]==n1) and (a[1][2][2]==n2) and (a[3][2][0]==0)) {g("R' F R F' R U2 R' U' R U R' ",z); rprm(a); f(a); r(a); fprm(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}

    //intre fetele 3-4
    if ((a[0][2][2]==n2) and (a[3][2][2]==0) and (a[4][2][0]==n1)) {g("B' R B R' U F' U' F ",z); bprm(a); r(a); b(a); rprm(a); u(a); fprm(a); uprm(a); f(a);}
    else if ((a[0][2][2]==n1) and (a[3][2][2]==n2) and (a[4][2][0]==0)) {g("B' R B R' U R U2 R' U' R U R' ",z); bprm(a); r(a); b(a); rprm(a); u(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}
    else if ((a[0][2][2]==0) and (a[3][2][2]==n1) and (a[4][2][0]==n2)) {g("B' R B R' U R U R' ",z); bprm(a); r(a); b(a); rprm(a); u(a); r(a); u(a); rprm(a);}

    //intre fetele 4-2
    if ((a[0][2][0]==n2) and (a[4][2][2]==0) and (a[2][2][0]==n1)) {g("L' B L B' U2 F' U' F ",z); lprm(a); b(a); l(a); bprm(a); u2(a); fprm(a); uprm(a); f(a);}
    else if ((a[0][2][0]==n1) and (a[4][2][2]==n2) and (a[2][2][0]==0)) {g("L' B L B' U2 R U2 R' U' R U R' ",z); lprm(a); b(a); l(a); bprm(a); u2(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}
    else if ((a[0][2][0]==0) and (a[4][2][2]==n1) and (a[2][2][0]==n2)) {g("L' B L B' U2 R U R' ",z); lprm(a); b(a); l(a); bprm(a); u2(a); r(a); u(a); rprm(a);}

    //intre fetele 2-1
    if ((a[0][0][0]==n2) and (a[2][2][2]==0) and (a[1][2][0]==n1)) {g("F' L F L' U' F' U' F ",z); fprm(a); l(a); f(a); lprm(a); uprm(a); fprm(a); uprm(a); f(a);}
    else if ((a[0][0][0]==n1) and (a[2][2][2]==n2) and (a[1][2][0]==0)) {g("F' L F L' U' R U2 R' U' R U R' ",z); fprm(a); l(a); f(a); lprm(a); uprm(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}
    else if ((a[0][0][0]==0) and (a[2][2][2]==n1) and (a[1][2][0]==n2)) {g("F' L F L' U' R U R' ",z); fprm(a); l(a); f(a); lprm(a); uprm(a); r(a); u(a); rprm(a);}

    //pozitii sus

    //intre fetele 1-3
    if ((a[5][2][2]==n1) and (a[1][0][2]==0) and (a[3][0][0]==n2)) {g("F' U' F ",z); fprm(a); uprm(a); f(a);}
    else if ((a[5][2][2]==n2) and (a[1][0][2]==n1) and (a[3][0][0]==0)) {g("R U R' ",z); r(a); u(a); rprm(a);}
    else if ((a[5][2][2]==0) and (a[1][0][2]==n2) and (a[3][0][0]==n1)) {g("R U2 R' U' R U R' ",z); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}

    //intre fetele 3-4
    if ((a[5][0][2]==n1) and (a[3][0][2]==0) and (a[4][0][0]==n2)) {g("U F' U' F ",z); u(a); fprm(a); uprm(a); f(a);}
    else if ((a[5][0][2]==n2) and (a[3][0][2]==n1) and (a[4][0][0]==0)) {g("U R U R' ",z); u(a); r(a); u(a); rprm(a);}
    else if ((a[5][0][2]==0) and (a[3][0][2]==n2) and (a[4][0][0]==n1)) {g("U R U2 R' U' R U R' ",z); u(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}

    //intre fetele 4-2
    if ((a[5][0][0]==n1) and (a[4][0][2]==0) and (a[2][0][0]==n2)) {g("U2 F' U' F ",z); u2(a); fprm(a); uprm(a); f(a);}
    else if ((a[5][0][0]==n2) and (a[4][0][2]==n1) and (a[2][0][0]==0)) {g("U2 R U R' ",z); u2(a); r(a); u(a); rprm(a);}
    else if ((a[5][0][0]==0) and (a[4][0][2]==n2) and (a[2][0][0]==n1)) {g("U2 R U2 R' U' R U R' ",z); u2(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}

    //intre fetele 2-1
    if ((a[5][2][0]==n1) and (a[2][0][2]==0) and (a[1][0][0]==n2)) {g("U' F' U' F ",z); uprm(a); fprm(a); uprm(a); f(a);}
    else if ((a[5][2][0]==n2) and (a[2][0][2]==n1) and (a[1][0][0]==0)) {g("U' R U R' ",z); uprm(a); r(a); u(a); rprm(a);}
    else if ((a[5][2][0]==0) and (a[2][0][2]==n2) and (a[1][0][0]==n1)) {g("U' R U2 R' U' R U R' ",z); uprm(a); r(a); u2(a); rprm(a); uprm(a); r(a); u(a); rprm(a);}

    //linie noua
    g("\n",z);
}

//Pasul 2: Colturi
void pas2colturi(int a[6][3][3], char z[])
{
    //Pasul 2
    g("Pasul 2) ",z);

    bool t=false; //variabila ce indica necesitatea unei linii noi
    int n=0; //stare fata
    bool boolval[4]={false,false,false,false}; //vector cu valori de adevar colturi
    if ((a[0][0][2]==0) and (a[1][2][2]==2) and (a[3][2][0]==1)) boolval[0]=true; //verificare colt albastru-rosu
    if ((a[0][2][2]==0) and (a[3][2][2]==1) and (a[4][2][0]==3)) boolval[1]=true; //verificare colt rosu-verde
    if ((a[0][2][0]==0) and (a[4][2][2]==3) and (a[2][2][0]==4)) boolval[2]=true; //verificare colt verde-portocaliu
    if ((a[0][0][0]==0) and (a[2][2][2]==4) and (a[1][2][0]==2)) boolval[3]=true; //verificare colt portocaliu-albastru
    if ((boolval[0]) and (boolval[1]) and (boolval[2]) and (boolval[3])) t=true; //variabila ce indica necesitatea unei linii noi

    //colt albastru-rosu
    if (!boolval[0])
    {
        rezcolt(a,z,2,1);  //n=0
        boolval[0]=true;
        if ((a[0][2][2]==0) and (a[3][2][2]==1) and (a[4][2][0]==3)) boolval[1]=true; //verificare colt rosu-verde
        if ((a[0][2][0]==0) and (a[4][2][2]==3) and (a[2][2][0]==4)) boolval[2]=true; //verificare colt verde-portocaliu
        if ((a[0][0][0]==0) and (a[2][2][2]==4) and (a[1][2][0]==2)) boolval[3]=true; //verificare colt portocaliu-albastru
    }

    //colt rosu-verde
    if (!boolval[1])
    {
        g("Y ",z); y(a); n=1;
        rezcolt(a,z,1,3); //n=1
        boolval[1]=true;
        if ((a[0][2][2]==0) and (a[3][2][2]==3) and (a[4][2][0]==4)) boolval[2]=true; //verificare colt verde-portocaliu
        if ((a[0][2][0]==0) and (a[4][2][2]==4) and (a[2][2][0]==2)) boolval[3]=true; //verificare colt portocaliu-albastru
    }

    //colt verde-portocaliu
    if (!boolval[2])
    {
        if (n==0) {g("Y2 ",z); y2(a); n=2;}
        else if (n==1) {g("Y ",z); y(a); n=2;}
        rezcolt(a,z,3,4); //n=2
        boolval[2]=true;
        if ((a[0][2][2]==0) and (a[3][2][2]==4) and (a[4][2][0]==2)) boolval[3]=true; //verificare colt portocaliu-albastru
    }

    //colt portocaliu-albastru
    if (!boolval[3])
    {
        if (n==0) {g("Y' ",z); yprm(a); n=3;}
        else if (n==1) {g("Y2 ",z); y2(a); n=3;}
        else if (n==2) {g("Y ",z); y(a); n=3;}
        rezcolt(a,z,4,2); //n=3
        boolval[3]=true;
    }

    //mutare fata la n=0
    if (n==0) {g("Y' ",z); yprm(a); n=3;}
    else if (n==1) {g("Y2 ",z); y2(a); n=3;}
    else if (n==2) {g("Y ",z); y(a); n=3;}

    //linie noua
    if (t==true) g("\n",z);
}

//Rezolvarea unei muchii
void rezmuch(int a[6][3][3], char z[], int n1, int n2)
{
    //verificare pozitie colt

    //pozitii jos

    //intre fetele 1-3
    //intors
    if ((a[1][1][2]==n2) and (a[3][1][0]==n1)) {g("U R U' R' F R' F' R U' R U' R' F R' F' R ",z); u(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a); uprm(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}

    //intre fetele 3-4
    //intors
    if ((a[3][1][2]==n2) and (a[4][1][0]==n1)) {g("U B U' B' R B' R' B R U' R' F R' F' R ",z); u(a); b(a); uprm(a); bprm(a); r(a); bprm(a); rprm(a); b(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //normal
    else if ((a[3][1][2]==n1) and (a[4][1][0]==n2)) {g("U B U' B' R B' R' B U F' U F R' F R F' ",z); u(a); b(a); uprm(a); bprm(a); r(a); bprm(a); rprm(a); b(a); u(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //intre fetele 4-2
    //intors
    if ((a[4][1][2]==n2) and (a[2][1][0]==n1)) {g("U L U' L' B L' B' L U R U' R' F R' F' R ",z); u(a); l(a); uprm(a); lprm(a); b(a); lprm(a); bprm(a); l(a); u(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //normal
    else if ((a[4][1][2]==n1) and (a[2][1][0]==n2)) {g("U L U' L' B L' B' L U2 F' U F R' F R F' ",z); u(a); l(a); uprm(a); lprm(a); b(a); lprm(a); bprm(a); l(a); u2(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //intre fetele 2-1
    //intors
    if ((a[2][1][2]==n2) and (a[1][1][0]==n1)) {g("U F U' F' L F' L' F U2 R U' R' F R' F' R ",z); u(a); f(a); uprm(a); fprm(a); l(a); fprm(a); lprm(a); f(a); u2(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //normal
    else if ((a[2][1][2]==n1) and (a[1][1][0]==n2)) {g("U F U' F' L F' L' F U' F' U F R' F R F' ",z); u(a); f(a); uprm(a); fprm(a); l(a); fprm(a); lprm(a); f(a); uprm(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //pozitii sus

    //deasupra centrului 1
    //normal
    if ((a[5][2][1]==n2) and (a[1][0][1]==n1)) {g("U R U' R' F R' F' R ",z); u(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //invers
    else if ((a[5][2][1]==n1) and (a[1][0][1]==n2)) {g("U2 F' U F R' F R F' ",z); u2(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //deasupra centrului 2
    //normal
    if ((a[5][1][0]==n2) and (a[2][0][1]==n1)) {g("R U' R' F R' F' R ",z); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //invers
    else if ((a[5][1][0]==n1) and (a[2][0][1]==n2)) {g("U F' U F R' F R F' ",z); u(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //deasupra centrului 3
    //normal
    if ((a[5][1][2]==n2) and (a[3][0][1]==n1)) {g("U2 R U' R' F R' F' R ",z); u2(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //invers
    else if ((a[5][1][2]==n1) and (a[3][0][1]==n2)) {g("U' F' U F R' F R F' ",z); uprm(a); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //deasupra centrului 4
    //normal
    if ((a[5][0][1]==n2) and (a[4][0][1]==n1)) {g("U' R U' R' F R' F' R ",z); uprm(a); r(a); uprm(a); rprm(a); f(a); rprm(a); fprm(a); r(a);}
    //invers
    else if ((a[5][0][1]==n1) and (a[4][0][1]==n2)) {g("F' U F R' F R F' ",z); fprm(a); u(a); f(a); rprm(a); f(a); r(a); fprm(a);}

    //linie noua
    g("\n",z);
}

//Pasul 3: Muchii
void pas3muchii(int a[6][3][3], char z[])
{
    //Pasul 3
    g("Pasul 3) ",z);

    bool t=false; //variabila ce indica necesitatea unei linii noi
    int n=3; //stare fata
    bool boolval[4]={false,false,false,false}; //vector cu valori de adevar muchii
    if ((a[1][1][2]==4) and (a[3][1][0]==2)) boolval[0]=true; //verificare muchie portocaliu-albastru
    if ((a[3][1][2]==2) and (a[4][1][0]==1)) boolval[1]=true; //verificare muchie albastru-rosu
    if ((a[4][1][2]==1) and (a[2][1][0]==3)) boolval[2]=true; //verificare muchie rosu-verde
    if ((a[2][1][2]==3) and (a[1][1][0]==4)) boolval[3]=true; //verificare muchie verde-portocaliu
    if ((boolval[0]) and (boolval[1]) and (boolval[2]) and (boolval[3])) t=true; //variabila ce indica necesitatea unei linii noi

    //muchie portocaliu-albastru
    if (!boolval[0])
    {
        rezmuch(a,z,4,2); //n=3
        boolval[0]=true;
        if ((a[3][1][2]==2) and (a[4][1][0]==1)) boolval[1]=true; //verificare muchie albastru-rosu
        if ((a[4][1][2]==1) and (a[2][1][0]==3)) boolval[2]=true; //verificare muchie rosu-verde
        if ((a[2][1][2]==3) and (a[1][1][0]==4)) boolval[3]=true; //verificare muchie verde-portocaliu
    }

    //muchie albastru-rosu
    if (!boolval[1])
    {
        g("Y ",z); {y(a); n=0;}
        rezmuch(a,z,2,1); //n=0
        boolval[1]=true;
        if ((a[3][1][2]==1) and (a[4][1][0]==3)) boolval[2]=true; //verificare muchie rosu-verde
        if ((a[4][1][2]==3) and (a[2][1][0]==4)) boolval[3]=true; //verificare muchie verde-portocaliu
    }

    //muchie rosu-verde
    if (!boolval[2])
    {
        if (n==3) {g("Y2 ",z); y2(a); n=1;}
        else if (n==0) {g("Y ",z); y(a); n=1;}
        rezmuch(a,z,1,3); //n=1
        boolval[2]=true;
        if ((a[3][1][2]==3) and (a[4][1][0]==4)) boolval[3]=true; //verificare muchie verde-portocaliu
    }

    //muchie verde-portocaliu
    if (!boolval[3])
    {
        if (n==3) {g("Y' ",z); yprm(a); n=2;}
        else if (n==0) {g("Y2 ",z); y2(a); n=2;}
        else if (n==1) {g("Y ",z); y(a); n=2;}
        rezmuch(a,z,3,4); //n=2
        boolval[3]=true;
    }

    //mutare fata la n=2
    if (n==3) {g("Y' ",z); yprm(a); n=2;}
    else if (n==0) {g("Y2 ",z); y2(a); n=2;}
    else if (n==1) {g("Y ",z); y(a); n=2;}

    //linie noua
    if (t==true) g("\n",z);
}

//pasul 4
void pas4cruce(int a[6][3][3], char z[])
{
    //Pasul 4
    g("Pasul 4) ",z);

    //cruce
    if ((a[5][0][1]==5) and (a[5][1][0]==5) and (a[5][1][2]==5) and (a[5][2][1]==5)) {}

    //punct
    else if ((a[5][0][1]!=5) and (a[5][1][0]!=5) and (a[5][1][2]!=5) and (a[5][2][1]!=5))
    {
        g("F R U R' U' F' U2 F U R U' R' F' ",z);
        f(a); r(a); u(a); rprm(a); uprm(a); fprm(a); u2(a); f(a); u(a); r(a); uprm(a); rprm(a); fprm(a);
    }

    //linie normala
    else if ((a[5][0][1]!=5) and (a[5][1][0]==5) and (a[5][1][2]==5) and (a[5][2][1]!=5))
    {
        g("F R U R' U' F' ",z);
        f(a); r(a); u(a); rprm(a); uprm(a); fprm(a);
    }

    //linie rotita
    else if ((a[5][0][1]==5) and (a[5][1][0]!=5) and (a[5][1][2]!=5) and (a[5][2][1]==5))
    {
        g("U F R U R' U' F' ",z);
        u(a); f(a); r(a); u(a); rprm(a); uprm(a); fprm(a);
    }

    //L normal
    else if ((a[5][0][1]==5) and (a[5][1][0]==5) and (a[5][1][2]!=5) and (a[5][2][1]!=5))
    {
        g("F U R U' R' F' ",z);
        f(a); u(a); r(a); uprm(a); rprm(a); fprm(a);
    }

    //L cu rotatie U
    else if ((a[5][0][1]==5) and (a[5][1][0]!=5) and (a[5][1][2]==5) and (a[5][2][1]!=5))
    {
        g("U' F U R U' R' F' ",z);
        uprm(a); f(a); u(a); r(a); uprm(a); rprm(a); fprm(a);
    }

    //L cu rotatie U2
    else if ((a[5][0][1]!=5) and (a[5][1][0]!=5) and (a[5][1][2]==5) and (a[5][2][1]==5))
    {
        g("U2 F U R U' R' F' ",z);
        u2(a); f(a); u(a); r(a); uprm(a); rprm(a); fprm(a);
    }

    //L cu rotatie U'
    else if ((a[5][0][1]!=5) and (a[5][1][0]==5) and (a[5][1][2]!=5) and (a[5][2][1]==5))
    {
        g("U F U R U' R' F' ",z);
        u(a); f(a); u(a); r(a); uprm(a); rprm(a); fprm(a);
    }

    //linii noi
    g("\n",z);
}

//pasul 5
void pas5muchii(int a[6][3][3], char z[])
{
    //Pasul 5
    g("Pasul 5) ",z);

    if (a[3][0][1]==3) {g("U ",z); u(a);}
    else if (a[4][0][1]==3) {g("U2 ",z); u2(a);}
    else if (a[2][0][1]==3) {g("U' ",z); uprm(a);}

    //spate corect
    if ((a[4][0][1]==2) and (a[2][0][1]==4) and (a[3][0][1]==1))
    {g("R U R' U R U2 R' U' F U2 F' U' F U' F' ",z); r(a); u(a); rprm(a); u(a); r(a); u2(a); rprm(a); uprm(a); f(a); u2(a); fprm(a); uprm(a); f(a); uprm(a); fprm(a);}
    //stanga corect
    else if ((a[4][0][1]==4) and (a[2][0][1]==1) and (a[3][0][1]==2))
    {g("U B U B' U B U2 B' ",z); u(a); b(a); u(a); bprm(a); u(a); b(a); u2(a); bprm(a);}
    //dreapta corect
    else if ((a[4][0][1]==1) and (a[2][0][1]==2) and (a[3][0][1]==4))
    {g("U' F U2 F' U' F U' F' ",z); uprm(a); f(a); u2(a); fprm(a); uprm(a); f(a); uprm(a); fprm(a);}
    //sunt invers sensului acelor de ceasornic
    if ((a[4][0][1]==4) and (a[2][0][1]==2) and (a[3][0][1]==1))
    {g("R U2 R' U' R U' R' ",z); r(a); u2(a); rprm(a); uprm(a); r(a); uprm(a); rprm(a);}
    //sunt in sensul acelor de ceasornic
    if ((a[4][0][1]==1) and (a[2][0][1]==4) and (a[3][0][1]==2))
    {g("R U R' U R U2 R' ",z); r(a); u(a); rprm(a); u(a); r(a); u2(a); rprm(a);}

    //linii noi
    g("\n",z);
}

//pasul 6
void pas6colturi(int a[6][3][3], char z[])
{
    int n=0; //stare rotatie
    int np; //stare rotatie initiala
    //Pasul 6
    g("Pasul 6) ",z);

    //verificare daca e rezolvat
    if (!((a[5][0][2]==5) and (a[5][2][2]==5) and (a[5][2][0]==5) and (a[5][0][0]==5)))
    {
        while(n<4)
        {
            np=n;
            while((a[5][0][2]==5) and (n<5))
            {
                n++;
                uprm(a);
            }
            if (n-np==1) g("U' ",z);
            else if (n-np==2) g("U2 ",z);
            else if (n-np==3) g("U ",z);
            if (a[3][0][2]==5)
            {
                g("R D R' D' R D R' D' ",z);
                r(a); d(a); rprm(a); dprm(a);
                r(a); d(a); rprm(a); dprm(a);
            }
            else if (a[4][0][0]==5)
            {
                g("D R D' R' D R D' R' ",z);
                d(a); r(a); dprm(a); rprm(a);
                d(a); r(a); dprm(a); rprm(a);
            }
        }
    }

    //linii noi
    g("\n",z);
}

//pasul 7
void pas7ordcolt(int a[6][3][3], char z[])
{
    //Pasul 7
    g("Pasul 7) ",z);

    if (a[2][0][1]==3) {g("U' ",z); uprm(a);}
    if (a[3][0][1]==3) {g("U ",z); u(a);}
    if (a[4][0][1]==3) {g("U2 ",z); u2(a);}

    //verificare totala
    if ((a[2][0][2]==1) and (a[1][0][0]==3) and (a[1][0][2]==3) and (a[3][0][0]==4) and (a[3][0][2]==4) and (a[4][0][0]==2) and (a[4][0][2]==2) and (a[2][0][0]==1)) {g("Y' ",z); yprm(a);}

    //situatie fara colt care sa se potriveasca
    //situatie 1
    if ((a[1][0][0]==1) and (a[1][0][2]==4) and (a[2][0][0]==3) and (a[2][0][2]==2) and (a[3][0][0]==2) and (a[3][0][2]==3) and (a[4][0][0]==4) and (a[4][0][2]==1))
    {
        g("R' F R' B2 R F' R' B2 R2 Y R' F R' B2 R F' R' B2 R2 Y2 ",z);
        rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a);
        y(a);
        rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a);
        y2(a);
    }
    //situatie 2
    else if ((a[1][0][0]==4) and (a[1][0][2]==1) and (a[2][0][0]==2) and (a[2][0][2]==3) and (a[3][0][0]==3) and (a[3][0][2]==2) and (a[4][0][0]==1) and (a[4][0][2]==4))
    {
        g("R2 B2 R F R' B2 R F' R Y' R2 B2 R F R' B2 R F' R ",z);
        r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a);
        yprm(a);
        r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a);
    }

    //situatie 3
    else if ((a[1][0][0]==2) and (a[1][0][2]==2) and (a[2][0][0]==4) and (a[2][0][2]==4) and (a[3][0][0]==1) and (a[3][0][2]==1) and (a[4][0][0]==3) and (a[4][0][2]==3))
    {
        g("R2 B2 R F R' B2 R F' R Y R2 B2 R F R' B2 R F' R Y2 ",z);
        r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a); y(a);
        r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a); y2(a);
    }

    //coltul rosu-verde bun
    if ((a[2][0][2]==1) and (a[1][0][0]==3))
    {
        //colturile sunt in sensul acelor de ceasornic
        if (a[1][0][2]==4)
        {
            g("R2 B2 R F R' B2 R F' R Y' ",z);
            r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a); yprm(a);
        }
        else if (a[1][0][2]==2)
        {
            g("R' F R' B2 R F' R' B2 R2 Y' ",z);
            rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a); yprm(a);
        }
    }
    //coltul verde-portocaliu bun
    else if ((a[1][0][2]==3) and (a[3][0][0]==4))
    {
        g("Y ",z); y(a);
        //colturile sunt in sensul acelor de ceasornic
        if (a[1][0][2]==2)
        {
            g("R2 B2 R F R' B2 R F' R Y2 ",z);
            r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a); y2(a);
        }
        else if (a[1][0][2]==1)
        {
            g("R' F R' B2 R F' R' B2 R2 Y2 ",z);
            rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a); y2(a);
        }
    }
    //coltul portocaliu-albastru bun
    else if ((a[3][0][2]==4) and (a[4][0][0]==2))
    {
        g("Y2 ",z); y2(a);
        //colturile sunt in sensul acelor de ceasornic
        if (a[1][0][2]==1)
        {
            g("R2 B2 R F R' B2 R F' R Y ",z);
            r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a); y(a);
        }
        else if (a[1][0][2]==3)
        {
            g("R' F R' B2 R F' R' B2 R2 Y ",z);
            rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a); y(a);
        }
    }
    //coltul albastru-rosu bun
    else if ((a[4][0][2]==2) and (a[2][0][0]==1))
    {
        g("Y' ",z); yprm(a);
        //colturile sunt in sensul acelor de ceasornic
        if (a[1][0][2]==3)
        {
            g("R2 B2 R F R' B2 R F' R ",z);
            r2(a); b2(a); r(a); f(a); rprm(a); b2(a); r(a); fprm(a); r(a);
        }
        else if (a[1][0][2]==4)
        {
            g("R' F R' B2 R F' R' B2 R2 ",z);
            rprm(a); f(a); rprm(a); b2(a); r(a); fprm(a); rprm(a); b2(a); r2(a);
        }
    }
}

//rezolvare configuratie a
void rez(int a[6][3][3], char afis1[])
{
    pas1crucea(a,afis1);
    pas2colturi(a,afis1);
    pas3muchii(a,afis1);
    pas4cruce(a,afis1);
    pas5muchii(a,afis1);
    pas6colturi(a,afis1);
    pas7ordcolt(a,afis1);
    g("\n",afis1);
}

void testing_function(char afis[], char cit[])
{
    int a[6][3][3];
    int c[6][3][3];
    int i,j,n=0;
    clearafis(afis);
    clearafis("gresit.out");
    read(c,cit);
    for(i=0;i<10000;i++)
    {
        atr(a,c);
        for(j=0;j<200;j++)
        {
            int x=rand()%6;
            if (x==0) {uprm(a); g("U' ",afis);}
            else if (x==1) {d(a); g("D ",afis);}
            else if (x==2) {f(a); g("F ",afis);}
            else if (x==3) {b(a); g("B ",afis);}
            else if (x==4) {r(a); g("R ",afis);}
            else if (x==5) {l(a); g("L ",afis);}
        }
        rez(a,afis);
        if (cmp(c,a)) n++;
        else{
            string t;
            its(t,i);
            g(t,"gresit.out");
            g("\n","gresit.out");
        }
    }
    string s;
    clearafis(afis);
    its(s,n);
    g(s,afis);
}

