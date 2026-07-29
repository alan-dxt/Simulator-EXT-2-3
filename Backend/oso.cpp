#include <iostream>
#include <cstring>

using namespace std;

int main(){
    cout<<"Oso polar\n";
    string origen = "flofiflofiflofi__";
    char destino[15];

    strncpy(destino, origen.c_str(), 15);

    cout<<destino<<"\n";

    memset(destino, '\0', 15);

    cout<<"["<<destino<<"]\n";

    return 0;
}