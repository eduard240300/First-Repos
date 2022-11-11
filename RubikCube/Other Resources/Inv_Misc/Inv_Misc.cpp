#include <fstream>
#include <cstring>

using namespace std;

ifstream f("Inv_Misc.in");
ofstream g("Inv_Misc.out");

int main()
{
    char vect[500][500],linie[500];
    int curs=0,i,n,nrlinie=0,curslinie,j=0;
    int aux[500];
    while(f.getline(linie,500))
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
        j=0;
        for(i=curs;i>=0;i--)
        {
            char me[3];
            me[0]=char(aux[i]/3);
            me[1]='\0';
            strcpy(vect[nrlinie]+j,me);
            j++;
            if (aux[i]%3==0)
            {
                me[0]=char(39);
                strcpy(vect[nrlinie]+j,me);
                j++;
            }
            else if (aux[i]%3==2)
            {
                me[0]='2';
                strcpy(vect[nrlinie]+j,me);
                j++;
            }
            me[0]=' ';
            strcpy(vect[nrlinie]+j,me);
            j++;
        }
        nrlinie++;
    }
    for(curslinie=nrlinie-1;curslinie>=0;curslinie--)
    {
        g<<vect[curslinie];
        g << '\n';
    }
    return 0;
}
