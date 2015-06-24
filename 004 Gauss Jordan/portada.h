#include "graphics.h"
#include <string.h>
#include <ctime>
//#include <windows.h>//para la función Sleep
#include <iostream>
#include <list>
//#include <conio.h>
using namespace std;

struct recs
{
    public:
        int v;//velocidad
        int h;//altura
    public:
        recs(int p, int h);
};

void espera(int t)
{
    //delay(t);
    int top=t*250000;
    for(int i=0; i<top; i++)
    {}
}

recs::recs(int p, int h){this->v = p; this->h=h;};

string convertInt(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void desvanTexto(int x, int y, int v, string t, int r, int g, int b)
{    
    char *text = new char[t.length() + 1];	
	strcpy(text, t.c_str());   
    for(int i=0; i< 255; i = i + 8)
    {    
        setcolor(COLOR(254-(254-r)*i/254, 254-(254-g)*i/254, 254-(254-b)*i/254));
        outtextxy(x, y, text);
        espera(v);//delay(v);//Sleep(v);
    }
}

void cirLocos(int x1, int y1, int x2, int y2, int n, int velocidad, int e, int color)
{
    //rectangle(x1, y1, x2, y2);    
    int rw = (x2 - x1) / n, rmh = (y2 - y1), dif = 10, pixeles = 1, htmp = 0, vtmp = 0, i, k=0, c = 0, salto = -1;
    list<recs> alturas;
    recs *ele;
    
    pixeles = velocidad;
    dif = e;
    
    ele = new recs(pixeles, 0);    
    for(int i=0; i<n; i++)//lleno la lista con las alturas iniciales
        alturas.push_back(*ele);
        
    while(!kbhit( ))
    {
        i = 0;
        for(list <recs>::iterator iter = alturas.begin(); iter != alturas.end(); iter++)
        {
            setcolor(15);
            setfillstyle(SOLID_FILL, WHITE);
            fillellipse(x1 + i*rw, y2 - iter->h, 5, 5);
            if((abs(iter->h - htmp) >= dif || vtmp != iter->v) || iter == alturas.begin())
            {
                if(iter->h == rmh)
                    iter->v = -pixeles;
                if(iter->h == 0)
                    iter->v = pixeles;
                if(iter->v > 0)
                    iter->h = min(iter->h + iter->v, rmh);
                else
                    iter->h = max(iter->h + iter->v, 0);
            }         
            
            htmp = iter->h;
            vtmp = iter->v;            
            /*if(iter->h == rmh && i == c)
            {
                if(i == 0) salto = 1;
                if(i == n - 1) salto = -1;                
                c += salto;
            } */           
            
            if(i == c)
            {                
                setcolor(COLOR(255, 140, 0));
                setfillstyle(SOLID_FILL, COLOR(255, 140, 0));
            }
            else
            {            
                setcolor(color);            
                setfillstyle(SOLID_FILL, color);
            }            
            
            fillellipse(x1 + i*rw, y2 - iter->h, 5, 5);
            //rectangle(x1 + i*rw, y2 - iter->h, x1 + rw*(i+1), y2);
            espera(1);//delay(1);
            //Sleep(1);
            i++;
        }     
        k++;
        //para mover a la oveja negra de las bolitas
        if(k > pixeles && k%(pixeles) == 0) c += salto;
        if(c == 0 || c == n - 1) salto = -salto;    
    }
}

int portada(string p, string n)
{
    
    int W = 920, H = 600;
    string fecha;
    p = "PROGRAMA: " + p;
	n = "PROGRAMA NO. " + n;
	char *t = new char[p.length() + 1];	
	strcpy(t, p.c_str());
	
	time_t ti = time(0);   // get time now
    struct tm *now = localtime(&ti);
    fecha = convertInt(now->tm_mday) + "/" + convertInt(now->tm_mon + 1) + "/" + convertInt(now->tm_year + 1900);
    fecha += ",  " + convertInt((now->tm_hour) == 0 ? 12 : (now->tm_hour)) + ":" + convertInt(now->tm_min) + ":" + convertInt(now->tm_sec); 

	//Documentación http://www.cs.colorado.edu/~main/bgi/
	//int initwindow(int width, int height, const char* title="Windows BGI", int left=0, int top=0, bool dbflag=false, closeflag=true);
    initwindow(W, H, t);     
            
        //ENCABEZADOS
        floodfill(15, 15, 15);//pongo pantalla en blanco       
        setbkcolor(15);        
        settextstyle(4, 0, 4);
            desvanTexto(50, 10, 50, "INSTITUTO POLITÉCNICO NACIONAL", 0, 0, 0);
        settextstyle(4, 0, 3);
            desvanTexto(50, 50, 50, "Escuela Superior de Ingeniería Mecánica y Eléctrica", 0, 100, 0);
        settextstyle(4, 0, 3);
            desvanTexto(110, 90, 50, "Ingeniería en Comunicaciones y Electrónica", 220, 20, 60);
        
        //ESPECIFICOS
        settextstyle(BOLD_FONT, 0, 2);
            desvanTexto(110, 200, 10, "MATERIA: Análisis Numérico", 25, 25, 112);
            desvanTexto(110, 250, 10, "ESTUDIANTE: Marco Antonio Andrade Barrera", 25, 25, 112);
            desvanTexto(110, 300, 10, "BOLETA: 2013300064", 25, 25, 112);
            desvanTexto(110, 350, 10, p, 25, 25, 112);
            desvanTexto(110, 400, 10, n, 25, 25, 112);
        settextstyle(DEFAULT_FONT, 0, 2);            
            desvanTexto(110, 440, 10, fecha, 254, 0, 0);
            desvanTexto(110, 480, 10, "Presiona una tecla para continuar", 254, 0, 0);
            //desvanTexto(110, 350, 10, "PROGRAMA: Portada con animaciones", 25, 25, 112);
            //desvanTexto(110, 400, 10, "PROGRAMA No. 0", 25, 25, 112);
         /*
         FUNCION cirLocos: primeros 4 argumentos como en rectangle
         arg 5: número circulos a dibujar en el marco dado por los cuatro argumentos anteriores
         arg 6: velocidad de movimiento de circulos
         arg 7: medida de aplastamiento de las ondas
         arg 8: color de los circulos
         */
        cirLocos(100, 560, 820, 590, 45, 5, 20, 3);
    //system("PAUSE");
    closegraph();   
    return 0;
}
