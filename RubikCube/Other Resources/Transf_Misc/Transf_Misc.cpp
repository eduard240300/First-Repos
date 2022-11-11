#include <fstream>
#include <cstring>

using namespace std;

ifstream f("Transf_Misc.in");
ofstream g("Transf_Misc.out");

int main()
{
    char linie[1000];
    int curs=0,i,n;
    int aux[1000];
    while(f.getline(linie,1000))
    {
        curs=0;
        n=strlen(linie);
        if (linie[n-1]==' ') n--;
        for(i=0;i<n;i++)
        {
            if (isalpha(linie[i])) aux[curs]=int(linie[i])*3;
            else
            {
                if (linie[i]==char(39)) aux[curs]++;
                else if (linie[i]=='2') aux[curs]+=2;
                else if (linie[i]==' ') curs++;
            }
        }
        if (isalpha(linie[i])) aux[curs]=int(linie[i])*3;
        else
        {
            if (linie[i]==char(39)) aux[curs]++;
            else if (linie[i]=='2') aux[curs]+=2;
            else if (linie[i]==' ') curs++;
        }
        for(i=0;i<=curs;i++)
        {
            g << char((aux[i]/3)+32);
            if (linie[i]%3==1)
            {
                g << char(39);
            }
            else if (linie[i]%3==2)
            {
                g << '2';
            }
            g << "(a); ";
        }
        g <<'\n';
    }
}
