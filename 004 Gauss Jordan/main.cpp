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
    int n=0;//n es la dimensión del sistema de ecuaciones a resolver
    double s, c;//para ir guardando las constantes
    list<double> rtemp;
    list< list<double> > matriz;    
    
    cout << endl << "M\202todo de Gauss Jordan" << endl;
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
    
    //método gauss jordan
    for(int i=1; i<=n; i++)
    {
        //dividir todo el renglon para que el i,j se haga 1 
        c = gV(matriz, i, i);
        for(int j=1; j<=n+1; j++)
            change(matriz, i, j, gV(matriz, i, j) / c);
        imprimeM(matriz); cout << "_______________________" << endl << endl;
        
        //hacer ceros los arriba y abajo del pivote
        for(int j=1; j<=n; j++)
            if(i!=j)
            {
                c = gV(matriz, j, i);
                for(int k=1; k<=n+1; k++)
                    change(matriz, j, k, gV(matriz, j, k) - c * gV(matriz, i, k));
            }
        imprimeM(matriz); cout << "_______________________" << endl << endl;
    }
    
    cout << endl << "Las soluciones del sistema de ecuaciones son: " << endl << endl;
    for(int i=1; i<=n; i++)
        cout << "X" << i << "= " << gV(matriz, i, n + 1) << endl;
        
}

int main()
{
    char op='0';
    portada("Método de Gauss Jordan", "4");
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
