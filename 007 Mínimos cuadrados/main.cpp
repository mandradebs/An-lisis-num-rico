#include "portada.h"
#include "eval/fparser.hh"//permite evaluar expresiones algebraícas ingresadas en string
#include "graph.h"
#include <algorithm>
#include <string>
#include <list>
#include <math.h>
#include <iomanip>//setprecision
#include <iostream>
using namespace std;
/* á por \240 é por \202 í por \241 ó por \242 ú por \243 */

/*struct XY{
    public:
        double x;
        double y;   
};*/

template <typename T>
std::string to_string(T const& value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

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
        //cout << endl << endl << "Se intercambiaron renglones debido a que en la diagonal hab\241a ceros" << endl << endl;
        //imprimeM(l); cout << "_______________________" << endl << endl;
        system("pause");
        verificarDiagonal(l);
        s= true;
    }
    return s;
}

double suma(list <XY> datos, int p, int q)
{
    list<XY>::iterator i;
    double suma=0; XY D;
    for(i=datos.begin(); i != datos.end(); i++)
    {
        D = *i;
        suma = suma + pow((D.x),p) * pow((D.y),q);
    }
    return suma;
}

void cargarDatos(list <XY> &datos)
{
    int n;
    XY par;
    cout << "Escribe el n\243mero de pares de datos que ingresar\240s: ";
    cin >> n;cout << endl << endl;    
    for (int i=1; i<=n; i++)
        {
            cout << "Par " << i << ": " << endl << " X= ";
            cin >> par.x;
            cout << " Y= ";
            cin >> par.y; cout << endl;
            datos.push_back(par);
        }   
}

void ajustarPolinomio(list <XY> datos)
{
    int p; string f;
    double s, c;//para ir guardando las constantes, un temporal double de dos
    list<double> rtemp;
    list< list<double> > matriz;
    
    cout << endl << endl << "Ahora ingresa el grado del polinomio que quieres ajustar: ";
    cin >> p;
    
    for(int i=1; i<= (p+1); i++)//es el número de renglones que tendrá la matriz
    {
        rtemp.clear();
        for(int j=1; j<= (p+1); j++)
        {            
            rtemp.push_back(suma(datos, i-1 + j-1, 0));
        }       
        rtemp.push_back(suma(datos, i-1, 1));
        matriz.push_back(rtemp);
    }
    
    if(!verificarDiagonal(matriz))        
    {
        //cout << endl << endl; imprimeM(matriz); cout << "_______________________" << endl << endl;
        //system("pause");
    }
    
    //método gauss jordan
    for(int i=1; i<=p+1; i++)
    {
        //dividir todo el renglon para que el i,j se haga 1 
        c = gV(matriz, i, i);
        for(int j=1; j<=p+2; j++)
            change(matriz, i, j, gV(matriz, i, j) / c);
        //imprimeM(matriz); cout << "_______________________" << endl << endl;
        
        //hacer ceros los arriba y abajo del pivote
        for(int j=1; j<=p+1; j++)
            if(i!=j)
            {
                c = gV(matriz, j, i);
                for(int k=1; k<=p+2; k++)
                    change(matriz, j, k, gV(matriz, j, k) - c * gV(matriz, i, k));
            }
        //imprimeM(matriz); cout << "_______________________" << endl << endl; system("pause");
    }
    
    cout << endl << "El polinomio ajustado a los datos es: " << endl << endl;
    f = " " + to_string(gV(matriz, 1, p + 1 + 1));
    for(int i=2; i<=p+1; i++)
    {
        f +=  " + " + to_string(gV(matriz, i, p + 1 + 1)) + "*x" ;
        //cout << " + " << gV(matriz, i, p + 1 + 1) << "*X" ;   
        if(i-1 != 1) f += "^" + to_string(i-1);
    }
     cout << "y =" << f;
     
     
     
    //gráfica
    graph(f, 600, 600, -5, 10,datos);
}

void menu(list <XY> &datos)
{
    char op='0';
    //list <XY> datos;//para guardar el "x" y el "y" 
    while(op!='x')
    {
        system("cls");
        cout << endl << "M\202todo de M\241nimos Cuadrados Polinomial" << endl;
        cout << endl << "Opciones" << endl;
        cout << endl << "1. Cargar datos";
        if(datos.size() != 0) cout << " (ya hay datos cargados)";
        cout << endl << "2. Ajustar polinomio";
        cout << endl << "x. Salir";        
        cout << endl << endl << "Selecciona una opcion: ";
        cin >> op;
        
        switch(op)
        {
            case '1':
                datos.clear();
                cargarDatos(datos); cout << endl;
                system("pause"); menu(datos);
                break;
            case '2':
                if(datos.size() != 0)
                {
                    ajustarPolinomio(datos);
                    cout << endl << endl;
                    system("pause"); 
                }
                else
                {
                    cout << endl << "Es necesario cargar datos antes de ajustar el polinomio" << endl;
                    system("pause");
                }
                menu(datos);
                break;
            case 'x':                
                break;
            default:
                cout << "No se reconoce la opcion." << endl; 
                system("pause"); menu(datos);
        }
        
        //menu();        
    }
    //cout << endl; system("pause");   
}


int main()
{
    list <XY> datos;//para guardar el "x" y el "y" 
    //portada("Método de Mínimos Cuadrados", "7");    
    menu(datos);
    return 0;
}
