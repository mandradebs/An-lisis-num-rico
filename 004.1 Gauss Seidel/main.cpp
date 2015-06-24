#include "portada.h"
#include "eval/fparser.hh"//permite evaluar expresiones algebraícas ingresadas en string
//#include "graph.h"
#include <algorithm>
#include <string>
#include <list>
#include <math.h>
#include <iomanip>//setprecision
#include <iostream>
using namespace std;
/* á por \240 é por \202 í por \241 ó por \242 ú por \243 */

/*struct renglon
{
    public:
        list<double> r;
    public:
        renglon();
};
renglon::renglon(){};*/

/*
EJEMPLO

-4,1,0,1,0,0,0,0,0,-100
1,-4,1,0,1,0,0,0,0,-100
0,1,-4,0,0,1,0,0,0,-200
1,0,0,-4,1,0,1,0,0,0
0,1,0,1,-4,1,0,1,0,0
0,0,1,0,1,-4,0,0,1,-100
0,0,0,1,0,0,-4,1,0,0
0,0,0,0,1,0,1,-4,1,0
0,0,0,0,0,1,0,1,-4,-100

*/

double getValueR(list<double> l, int p)
{//regresa el valor de una lista de tipo double en la posición p
    list <double>::iterator iter = l.begin();
    for(int i=1; i<p; i++)
        iter++;
    return *iter;
}

double gV(list< list<double> > l, int i, int j)
{//regresa el valor de una lista de tipo double en la posición p
    list< list <double> >::iterator iter = l.begin();
    for(int k=1; k<i; k++)
        iter++;
    return getValueR(*iter, j);    
}

void change(list< list<double> > &l, int i, int j, double v)
{
    list< list <double> >::iterator iter1 = l.begin();
    list <double>::iterator iter2;
    for(int k=1; k<i; k++)
        iter1++;
    iter2 = (*iter1).begin();
    for(int k=1; k<j; k++)
        iter2++;
    *iter2 = v;
}

void changeR(list<double> &l, int p, double v)
{
    list <double>::iterator iter = l.begin();
    for(int k=1; k<p; k++)
        iter++;
    *iter = v;
}

void imprimeM(list< list<double> > l)
{
    list< list <double> >::iterator iter1 = l.begin();
    list <double>::iterator iter2;
    for(int i=1; i<=l.size(); i++)
    {
        iter2 = (*iter1).begin();
        for(int j=1; j<=l.size()+1; j++)
        {
            cout << *iter2;
            if(j!=l.size()+1) cout << ","; else cout << endl;
            iter2++;
        }
        iter1++;
    }
}
bool verificarDiagonal(list< list<double> > &l)//verifica que en la diagonal no haya ceros
{
    int t = l.size(), i; bool s=false;
    list< list <double> >::iterator it1; list<double> it2;
    for(i=1; i<=t; i++)
        if(gV(l, i, i) == 0) i=2*t;
    if(i == 2*t + 1)
    {
        it1 = l.begin(); it2 = *it1;
        l.pop_front();
        l.push_back(it2);  
        cout << endl << endl << "Se intercambiaron renglones debido a que en la diagonal hab\241a ceros" << endl << endl;
        imprimeM(l); cout << "_______________________" << endl << endl;
        system("pause");
        verificarDiagonal(l);
        s= true;
    }
    return s;
}

void menu()
{
    int n=0, iteracion=1;//n es la dimensión del sistema de ecuaciones a resolver
    double error, s, c;//para ir guardando las constantes
    list<double> rtemp;
    list< list<double> > matriz;
    list<double> soluciones;//aquí se van guardando los valores de las X
    
    cout << endl << "M\202todo de Gauss Seidel" << endl;
    cout << endl << "Ingresa el n\243mero de ecuaciones: "; cin >> n;
    cout << endl << endl << "El sistema a resolver es de la forma: " << endl << endl;
    cout << endl << "A11X1 + A12X2 + ... + A1nXn = C1" << endl;
    cout << endl << "A21X1 + A22X2 + ... + A2nXn = C2" << endl;
    cout << "." << endl << "." << endl << "." << endl;
    cout << endl << "An1X1 + An2X2 + ... + AnnXn = Cn" << endl << endl;

    cout << endl << "A continuaci\242n se te solicitar\240n los valores de las constantes A y las constantes C" << endl << endl;
    
    for(int i=1; i<=n; i++)//es el número de renglones que tendrá la matriz
    {
        rtemp.clear();
        for(int j=1; j<=n; j++)
        {
            cout << endl << "Ingresa el valor de A" << i << "," << j << ": ";
            cin >> c;
            rtemp.push_back(c);
        }
        cout << endl << "Ingresa el valor de C" << i << ": ";
        cin >> c;
        rtemp.push_back(c);
        matriz.push_back(rtemp);
    }
    
    if(!verificarDiagonal(matriz))        
    {
        cout << endl << endl; imprimeM(matriz); cout << "_______________________" << endl << endl;
        system("pause");
    }
    
    //método gauss seidel
    
    //valores iniciales todos cero
    for(int i = 1; i <= n; i++)
        soluciones.push_back(0);
    
    error = 0.005*n + 1;
    while(error > 0)
    {
        error = 0;
        cout << endl << "Iteraci\242n " << iteracion << endl << endl;
        for(int i = 1; i <= n; i++)//cada  uno de los i corresponde a una variable
            {
                c = getValueR(soluciones, i);//valor anterior de la variable
                
                s = gV(matriz, i, n+1);//al final del siguiente for quedará aquí el nuevo valor de la variable
                for(int j = 1; j <= n; j++)//despeje
                    if(i!=j)
                        s -= getValueR(soluciones, j) * gV(matriz, i, j);
                s = s / gV(matriz, i, i); // aquí ya esta el nuevo valor
                cout << "X" << i << "= " << setprecision(12) << s;
                cout << ", era=" << setprecision(12) << 100*abs((s - getValueR(soluciones, i))/s) << endl;
                error += (100 * abs((s - getValueR(soluciones, i))/s) > 0.005) ? 1 : 0;
                changeR(soluciones, i, s);
            }
        cout << "_______________________" << endl << endl;
        //system("pause");
        iteracion++;
    }

    
    cout << endl << "Las soluciones del sistema de ecuaciones son aproximadamente: " << endl << endl;
    for(int i=1; i<=n; i++)
        cout << "X" << i << "= " << getValueR(soluciones, i) << endl;
        
}

int main()
{
    char op='0';
    //portada("Método de Gauss Seidel", "4.1");
    while(op!='x')
    {
        system("cls");
        menu();
        cout << endl << endl << "Presione 'x' para salir o 'c' para continuar: ";
        cin >> op;        
    }
    //cout << endl; system("pause");
    return 0;
}
