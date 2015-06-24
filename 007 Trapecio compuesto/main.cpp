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

double integrar(string f, double a, double b, int n)
{
     FunctionParser fparser;
     double val[] = {0}, I = 0;
     
     fparser.Parse(f, "x");

     for(int i=0; i<=n; i++)
     {
             val[0] = a + i*(b-a)/n;
             if(i==0)
                 I += fparser.Eval(val);
             else if(i == n)
                 I += fparser.Eval(val);
             else
                 I += 2*fparser.Eval(val);
     }
     
     I = (b-a)*I/(2*n);
     //cout << endl << "I = " << I << endl;
     return I;
     
}

void menu(string fn, char &op)
{    
    //list <XY> datos;//para guardar el "x" y el "y"
    double a,b, I, I1, I2, i;
    int n;
    
    while(op!='x')
    {
        system("cls");
        cout << endl << "M\202todo del trapecio para integrales" << endl;
        cout << endl << "Opciones" << endl;
        cout << endl << "1. Ingresar la funci\242n que quieres integrar";
        if(fn != "") cout << " (se ha leido f(x) = " << fn << "  )";
        cout << endl << "2. Integrar";
        cout << endl << "3. Graficar";
        cout << endl << "x. Salir";        
        cout << endl << endl << "Selecciona una opcion: ";
        cin >> op;
        
        switch(op)
        {
            case '1':
                fn = "";
                cout << "Ingresa la funci\202n: f(x) = ";
                //cin >> fn; cout << endl << endl;
                //cin.clear(); cin.ignore(1000,'\n');
                fn = "0.2+25*x-200*x^2+675*x^3-900*x^4+400*x^5";
                system("pause"); menu(fn, op);
                break;
            case '2':
                if(fn != "")
                {
                    cout << "Ingresa el intervalo en el que quieres integrar \n\ (a,b): \n \t a: ";
                    cin >> a; cout << "\n \t b: "; cin >> b;
                    cout << endl << endl << "Ahora ingresa el n\243mero de segmentos: "; cin >> n;
                    cin.clear(); cin.ignore(1000,'\n');
                    I = integrar(fn,a,b,n);                    
                    I2 = integrar(fn,a,b,n + 1); I1 = I; i=2;
                    while(100*abs((I2-I1)/I2)>0.00000005)
                    {
                        I1 = I2;
                        I2 = integrar(fn,a,b,n + i);
                        i+=10;
                        //cout << endl << I2;
                    }
                    cout << endl << "I = " << setprecision(12) << I << endl;
                    cout << endl;
                    cout << "Integral con 8 digitos significativos: " << setprecision(12) << I2;
                    cout << endl << "Er = " << setprecision(12) << 100*abs(I2-I)/I2 << " %";
                    cout << endl << endl;
                    system("pause"); 
                }
                else
                {
                    cout << endl << "No has ingresado una funcion" << endl;
                    system("pause");
                }
                menu(fn, op);
                break;
            case 'x':                
                break;
            default:
                cout << "No se reconoce la opcion." << endl; 
                system("pause"); menu(fn, op);
        }
        
        //menu();        
    }
    //cout << endl; system("pause");   
}


int main()
{
    string fn = "";
    char op='0';
    //portada("Método del trapecio para integrales", "7");    
    menu(fn, op);
    return 0;
}
