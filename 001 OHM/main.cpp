#include <iostream>
//#include "C:\Users\Marco\Desktop\000 PORTADA\portada.h"
#include "portada.h"
using namespace std;

/*
á por \240
é por \202
í por \241
ó por \242
ú por \243 
*/

bool valida(double &v)
{
    bool t = false;
    cin >> v;
    if(cin.good()) t = true;
    cin.clear();
    cin.ignore(1000,'\n');
    
    return t;
    
}

void ohm()
{
    char o; string temp;    
    double v,i,r;
    system("cls");
    cout << "LEY DE OHM" << endl << endl;
    cout << endl << "Cu\240l de las siguientes variables quieres calcular?" << endl << endl << endl;
    cout << "1. Voltaje" << endl;
    cout << "2. Corriente" << endl;
    cout << "3. Resistencia" << endl;
    
    cout << endl << "Ingresa la opci\242n o presiona x para salir: ";
    
    cin >> o;
    switch(o)
    {
        case '1'://quiere calcular voltaje
            cout << endl << "Ingresa la resistencia: ";            
            //cin >> r;
            if(!valida(r))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); ohm();
            }
            else
            {
                cout << endl << "Ingresa la corriente: ";
                //cin >> i;
                if(!valida(i))
                {
                    cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                    system("PAUSE"); ohm(); break;
                }
                else
                {
                    v=r*i;
                    cout << endl << endl << "El voltaje es: " << v << " volts" << endl << endl;
                    system("PAUSE"); ohm();
                }
            }
            break;
        case '2'://quiere calcular corriente
            cout << endl << "Ingresa la resistencia: ";
            //cin >> r;
            if(!valida(r))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); ohm();
            }
            else
            {
                cout << endl << "Ingresa el voltaje: ";
                //cin >> v;
                if(!valida(v))
                {
                    cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                    system("PAUSE"); ohm(); break;
                }
                else
                {
                    i=v/r;
                    cout << endl << endl << "La corriente es: " << i << " Amperes" << endl << endl;
                    system("PAUSE"); ohm();
                }
            }
            break;
        case '3'://quiere calcular resistencia
            cout << endl << "Ingresa la corriente: ";
            //cin >> i;
            if(!valida(i))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); ohm();
            }
            else
            {
                cout << endl << "Ingresa el voltaje: ";
                //cin >> v;
                if(!valida(v))
                {
                    cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                    system("PAUSE"); ohm();
                }
                else
                {
                    r=v/i;
                    cout << endl << endl << "La resistencia es: " << r << " Ohms" << endl << endl;
                    system("PAUSE"); ohm();
                }
            }
            break;
        case 'x'://quiere salir
            break;
        default:
            cout << endl << "la opci\242n ingresada no es v\240lida" << endl << endl;
            system("PAUSE"); ohm();
    }
}

int main()
{
    portada("Ley de Ohm", "1");
    ohm();    
    return 0;
}
