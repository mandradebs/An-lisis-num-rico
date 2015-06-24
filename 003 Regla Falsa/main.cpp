#include "portada.h"
#include "eval/fparser.hh"//permite evaluar expresiones algebra�cas ingresadas en string
#include <string>
#include <math.h>
#include <iomanip>//setprecision
#include <iostream>
using namespace std;
/* � por \240 � por \202 � por \241 � por \242 � por \243 */

void outdoublexy(int x, int y, double n)
{
    string text;
    ostringstream convert;
    convert << setprecision(12) << n;
    text = convert.str();
    char *t = new char[text.length() + 1];
	strcpy(t, text.c_str());
	outtextxy(x, y, t);
}

void graph(string f, int W, int H, double xi, double xf)
{
    //f es la funci�n a graficar, W y H son las dimensiones de la gr�fica
    //xi y xf es el rango en el que se graficar�

    char *t = new char[f.length() + 1];
    double vals[2][10001], val[] = {0}, miny, maxy;
    FunctionParser fparser;
    int cero;//pixel donde estar� el eje x
    int nit=10000;//es el n�mero de puntos que se utilizar�n para dibujar la gr�fica, debe ser el taba�o del vals -1
    int margen = 20;//
    
	strcpy(t, f.c_str());
    initwindow(W, H, t, 0, 0, false, false);
    floodfill(15, 15, 15);//pongo pantalla en blanco
    setbkcolor(15);
    setcolor(COLOR(128, 128, 128));//color gris    
    
    //puntidos gu�a
    setcolor(COLOR(220, 220, 220));//color gris suave
    setlinestyle(DOTTED_LINE , 1, 1);
    for(int i=1; i<10; i++)
    {        
        line(0+margen, margen+i*(H-2*margen)/10, W-margen, margen+i*(H-2*margen)/10);
        line(margen+i*(W-2*margen)/10, 0+margen, margen+i*(W-2*margen)/10, H-margen);
    }  
    
    setlinestyle(SOLID_LINE , 1, 1);  
    setcolor(COLOR(128, 128, 128));//color gris    
    fparser.Parse(f, "x");
    for(int i=0; i<=nit; i++)
    {
        vals[0][i] = xi + i*(xf-xi)/nit;
        val[0] = vals[0][i];        
        vals[1][i] = fparser.Eval(val);
        if(i==0) {miny = vals[1][i]; maxy = miny;}
        if(miny > vals[1][i]) miny = vals[1][i];
        if(maxy < vals[1][i]) maxy = vals[1][i];        
    }

    //eje y    
    for(int i=1; i<10; i++)
    {        
        line(margen+(W-2*margen)/2-5, margen+i*(H-2*margen)/10, margen+(W-2*margen)/2+5,margen+i*(H-2*margen)/10);
        if(i%2 != 0)            
            outdoublexy(margen+(W-margen)/2+5, margen+i*(H-2*margen)/10 - 15, maxy - i*(maxy-miny)/10);//
    }
    
    //eje x    
    if(min(maxy, miny) < 0)//es decir, si la gr�fica cruza al eje x
    {
        cero = margen + maxy * (H-2*margen)/(maxy-miny);
        for(int i=1; i<10; i++)
        {
            line(margen+i*(W-2*margen)/10, cero - 5, margen+i*(W-2*margen)/10, cero + 5);
            if(i%2 != 0)
                outdoublexy(margen+i*(W-2*margen)/10, cero + 5, xi + i*(xf-xi)/10);
        }        
        line(margen+0, cero, W-margen, cero);//linea horizontal, eje x
    }
    else
        outtextxy(0, 15, "Selecciona un rango m�s amplio para ver si la gr�fica intersecta al eje x");
    line(margen+(W-2*margen)/2, margen+0, margen+(W-2*margen)/2, H-margen);//linea vertidal, eje y
    
    //GR�FICA
    //setlinestyle(SOLID_LINE , 1, 1);
    setcolor(COLOR(254, 0, 0));//color rojo    
    for(int i=1; i<=nit; i++)
        line(margen+(vals[0][i-1] - xi)*(W-2*margen)/(xf-xi), -margen+H - (vals[1][i-1] - miny)*(H-2*margen)/(maxy-miny),margen+(vals[0][i] - xi)*(W-2*margen)/(xf-xi), -margen+H - (vals[1][i] - miny)*(H-2*margen)/(maxy-miny));
    
    setcolor(COLOR(128, 128, 128));//color gris    
    outtextxy(0, 0, "Para salir, presione una tecla...");
    
    while(!kbhit())
    {}
    closegraph();   
}

void menu()
{
    char op;
    string expresion;
    FunctionParser fparser;
    double xi, xm, xra = 0, xr, fxi, fxm, fxr, erpa, vals[] = {0}; int i = 1;
    int p = 12, res;//presici�n y errores en expresi�n
    
    while(op != 'x')
    {
        system("cls");
        cout << "M\242todo Regla Falsa" << endl << endl;
        
        if(expresion.size() != 0)//se ha cargado una expresi�n matem�tica
            cout << endl << "Expresi\242n cargada: " << expresion << endl;
        
        cout << endl << "Opciones" << endl << endl;
        cout << "1. Ingresar una funci\242n" << endl;
        cout << "2. Encontrar una ra\241z de la funci\242n" << endl;
        cout << "3. Graficar la funci\242n" << endl;
        cout << "x. Salir" << endl;
        cout << endl << "Ingresa la opci\242n que quieras ejecutar: ";
        cin >> op; cin.clear(); cin.ignore(1000,'\n');
        switch(op)
        {
            case '1'://ingresar funci�n
                cout << endl << "Ingresa una funci\242n dependiente de x, por ejemplo: exp(-x)-x" << endl << endl;
                std::getline(std::cin, expresion);
                res = fparser.Parse(expresion, "x");
                if (res>0)
                {
                    std::cout << std::string(res, ' ') << "^\n" << fparser.ErrorMsg() << "\n\n";
                    expresion = "";
                }
                break;
            case '2':
                erpa = 100; i=1;
                if(expresion.size() != 0)
                {
                    cout << endl << "Para comenzar las iteraciones ingresa los siguientes datos:" << endl << endl;
                    cout << "xi= "; cin >> xi;
                    cout << "xm= "; cin >> xm;
                    
                    while(erpa > 0.0005)
                    {
                        vals[0] = xi; fxi = fparser.Eval(vals);                                           
                        vals[0] = xm; fxm = fparser.Eval(vals);
                        xr = xm - fxm*(xi-xm)/(fxi - fxm);
                        vals[0] = xr; fxr = fparser.Eval(vals);
                                                
                        erpa = 100 * sqrt(pow((xr-xra)/xr,2));
                        if(fxi*fxr < 0) xm = xr;
                        else if(fxi*fxr > 0) xi = xr;
                        else erpa = 0;//se encontr� la ra�z exacta
                        
                        cout << endl << "____________________________" << endl;
                        cout << "Iteraci\242n: " << "   " << i << endl;
                        cout << "Xi: " << " " << setprecision(p) << xi << endl;        
                        cout << "Xm: " << " " << setprecision(p) << xm << endl;        
                        cout << "Xr: " << " " << setprecision(p) << xr << endl;
                        cout << "FXi: " << " " << setprecision(p) << fxi << endl;        
                        cout << "FXm: " << " " << setprecision(p) << fxm << endl;        
                        cout << "FXr: " << " " << setprecision(p) << fxr << endl;        
                        cout << "Erpa(%): " << "    " << erpa << setprecision(p) << endl << endl;                        
                        xra = xr; i++;
                    }
                    cout << endl << endl << "La ra\241z es aproximadamente " << xr << endl << endl;
                    //system("pause");
                }
                else
                    cout << endl << "Primero debes ingresar la funci\242n..." << endl << endl;
                break;
            case '3':
                if(expresion.size() != 0)
                {
                    cout << endl << "El necesario definir el rango donde se graficar\240  la funci\242n:" << endl << endl;
                    cout << "xi= "; cin >> xi;
                    cout << "xm= "; cin >> xm;
                    graph(expresion, 600, 600, xi, xm);
                }
                else
                    cout << endl << "Primero debes ingresar la funci\242n..." << endl << endl;
                break;                
            case 'x'://salir
                cout << endl;             
                break;
            default:
                cout << endl << "La opci\242 ingresada no es v\240lida" << endl << endl;
        }
        system("pause");
    }
}

int main()
{
    portada("M�todo Regla Falsa", "2");    
    menu();  
    return 0;
}
