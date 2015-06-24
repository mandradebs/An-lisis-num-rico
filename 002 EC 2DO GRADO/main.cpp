#include <iostream>
//#include "C:\Users\Marco\Desktop\000 PORTADA\portada.h"
#include "portada.h"
#include <math.h>
using namespace std;
/* á por \240 é por \202 í por \241 ó por \242 ú por \243 */

bool valida(double &v)
{
    bool t = false;
    cin >> v;
    if(cin.good()) t = true;
    cin.clear();
    cin.ignore(1000,'\n');
    
    return t;
    
}

void segundoG()
{
    char o;
    double a,b,c,x1,x2,D;
    
    system("cls");
    cout << endl << "ECUACIONES DE 2DO GRADO" << endl;
    cout << endl << "Opciones: " << endl;
    cout << "1. Resolver ecuaci\242n de 2do grado"<< endl;
    cout << "x. Salir";
    cout << endl << "Ingresa el n\243mero de la opci\242n o presiona x para salir: ";
    cin >> o;
    switch(o)
    {
        case '1':
            cout << endl << endl << "La ecuaci\242n a resolver es del tipo: ax^2+bx+c=0";
            cout << endl << endl << "Ingresa los valores de las constantes a, b y c";
            cout << endl << endl << "a: ";
            //cin >> a;
            if(!valida(a))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); segundoG(); break;
            }
            cout << endl << "b: ";
            //cin >> b;
            if(!valida(b))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); segundoG(); break;
            }
            cout << endl << "c: ";
            //cin >> c;
            if(!valida(c))
            {
                cout << endl << "El valor ingresado no es v\240lido" << endl << endl;
                system("PAUSE"); segundoG(); break;
            }
            if(a == 0)
            {
                if(b == 0)
                    cout << endl << "Para resolver esta ecuaci\242n, al menos b debe ser diferente de cero";
                else
                {
                    cout << endl << "La soluci\242n de la ecuaci\242n " << a << "x^2+" << b << "x+" << c << "=0 es:";
                    cout << endl << "x = " << -c/b;
                }
            }
            else
            {
                D = b*b - 4 * a * c;
                if(D == 0)//las soluciones son iguales x1 = x2 o una sola solución
                {
                    x1 = -b / (2 * a);
                    cout << endl << "La soluci\242n de la ecuaci\242n " << a << "x^2+" << b << "x+" << c << "=0 es:";
                    cout << endl << "x = " << x1;
                }
                else if(D > 0)//dos soluciones diferentes reales
                {
                    x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
                    x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
                    cout << endl << "Las soluciones de la ecuaci\242n " << a << "x^2+" << b << "x+" << c << "=0 son:";
                    cout << endl << "x1=" << x1 << " y x2=" << x2;
                }
                else
                {
                    x1 = -b/(2*a);
                    cout << endl << "Las soluciones de la ecuaci\242n " << a << "x^2+" << b << "x+" << c << "=0 son complejas:";
                    cout << "x1=" << x1 << "+" << sqrt(-D)/(2*a) << "i, ";
                    cout << "x2=" << x1 << "-" << sqrt(-D)/(2*a) << "i";
                }
            }
            cout << endl;
            system("PAUSE");
            segundoG();
            break;
        case 'x':
            break;
        default:
            cout << endl << endl << "La opci\242n ingresada no es v\240lida"<< endl;
            system("PAUSE");
            segundoG();
    }
}

int main()
{
    portada("Ecuaciones de 2do grado", "2");
    segundoG();
    return 0;
}
