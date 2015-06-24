#include <iostream>
//#include "C:\Users\Marco\Desktop\000 PORTADA\portada.h"
#include <cstdlib> 
#include "portada.h"
using namespace std;
/* á por \240 é por \202 í por \241 ó por \242 ú por \243 */



int main()
{
    
    int W = 920, H = 600;
    int t=100, l=400, imgH=70, imgW=71;//hélice
    int p[8], a=8, al=205, px=33, py=85; p[0]=l+px; p[1]=t+py; p[2]=l+a+px; p[3]=t+py; p[4]=l+a+px; p[5]=t+al+py; p[6]=l+px; p[7]=t+al+py;//soporte
    ///int le=0, to=0, ri=120, bo=400;//soporte
    int velocidad = 130;
    string ss;
    char *s = new char[0];	
    portada("Sistema mecánico eléctrico", "0.1");
    
    initwindow(W, H, "Animación");
    floodfill(15, 15, 15);//pongo pantalla en blanco    
    //pongo la batería
    ss = "sprite/BD.jpg";
    strcpy(s, ss.c_str());
    readimagefile(s, 365, 350, 160+365, 147+350);
    
    //pongo el soporte
    setfillstyle(SOLID_FILL, COLOR(126, 126, 126));
    fillpoly(4, p);
    setcolor(0);
    circle(l+35, t+34,53);
    
    while(!kbhit( ))
    {
        for(int i=0; i<12; i++)
        {   
            ss = "sprite/white.gif";
            strcpy(s, ss.c_str());
            readimagefile(s, l, t, imgW+l, imgH+t);
            ss = (i<10 ? "sprite/0" : "sprite/") + convertInt(i) + ".gif";
            strcpy(s, ss.c_str());
            readimagefile(s, l, t, imgW+l, imgH+t);
            //rectangle(le,to,ri,bo);
                     
            espera(velocidad);
        }
    }
    closegraph();   
    
    system("PAUSE");
    return 0;
}
