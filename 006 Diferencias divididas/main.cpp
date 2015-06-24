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

double g(list<XY> datos, int i, int j)
{
    list<XY>::iterator it;
    double suma=0; XY D; int k;
    k = 1;
    for(it=datos.begin(); it != datos.end(); it++)
    {
        D = *it;
        if(k == i)
            if(j == 1)
                suma = D.x;
            else
                suma = D.y;
        k++;
    }
    return suma;
}

double diferencias(list <XY> datos, double x, int bo)
{    
    int n = datos.size();
    double s, c=0, mat[100][100];
    double estim[100];
    double xterm; string xx = "", f="";
    
    
    for(int i=0; i<=n-1; i++)
            mat[i][0] = g(datos,i+1,2);//igual a yi
    
    for(int j=1; j<=n-1; j++)
            for(int i=0; i<=n-1-j; i++)
                    mat[i][j] = (mat[i+1][j-1] - mat[i][j-1]) / (g(datos,i+j+1,1) - g(datos,i+1,1));
    
    xterm = 1;
    estim[0] = mat[0][0];
    
    for(int k=1; k<=n-1; k++)
    {
            xterm = xterm * (x - g(datos,k-1+1,1));
            estim[k] = estim[k-1] + mat[0][k] * xterm;
    }
    if(bo == 0)
    {
          cout << endl << "La funcion para interpolar es: " << endl << "f(x) = ";
     for(int i=0; i<=n-1; i++)
     {
             if(i!=0)
             {
                     cout << " + " << mat[0][i] << "*" << xx;
                     f += " + " + to_string(mat[0][i]) + "*" + xx;
                     }
             else
             {
                 cout << mat[0][i];
                 f += to_string(mat[0][i]);
                 }
             xx = xx + (i!=0 ? "*" : "") + "(x - " + to_string(g(datos,i+1,1)) + ")";
     }
     char *t = new char[xx.length() + 1];
    double val[] = {0};
    
    FunctionParser fparser;
	strcpy(t, xx.c_str());
    fparser.Parse(f, "x");
    val[0] = x;
     cout << endl << endl << "f(" << x << ") = " << fparser.Eval(val);
                            
     }
     
    return c;
    //gráfica
    //graph(f, 600, 600, minX(datos) - (maxX(datos) - minX(datos))/4, maxX(datos) - (maxX(datos) - minX(datos))/4, datos);
}

void menu(list <XY> &datos)
{
    char op='0';
    double x;
    //list <XY> datos;//para guardar el "x" y el "y" 
    while(op!='x')
    {
        system("cls");
        cout << endl << "M\202todo Diferencias Divididas de Newton" << endl;
        cout << endl << "Opciones" << endl;
        cout << endl << "1. Cargar datos";
        if(datos.size() != 0) cout << " (ya hay datos cargados)";
        cout << endl << "2. Interpolar";
        cout << endl << "3. Graficar";
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
                    cout << "Valor de x que quieres interpolar: "; cin >> x;
                    cout << endl << endl;// << "La interporlacion es: ";
                    cout << diferencias(datos, x, 0);
                    cout << endl << endl;
                    system("pause"); 
                }
                else
                {
                    cout << endl << "Es necesario cargar datos antes de interpolar" << endl;
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
    //portada("Método de Diferencias Divididas de Newton", "6");    
    menu(datos);
    return 0;
}
