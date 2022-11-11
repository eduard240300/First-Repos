#include "rubikCubeCommands.cpp"
#include <stdlib.h>
#include <cstring>
#include <string>

using namespace std;

char afis[15]="rubik.out\0";
char cit[15]="rubik.in\0";

int main()
{
    int a[6][3][3]; //vector cu configuratia cubului rubik
    /*clearafis(afis);
    read(a,cit);
    rez(a,afis);
    show(a,afis);*/
    testing_function(afis,cit);
    return 0;
}
