#include <iostream>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>
#define MAX 100
using namespace std;

typedef struct nod
{
    char inf;
    nod *st,*dr;
} ARB;
char e[MAX],efp[MAX];
int p[MAX],pfp[MAX];
ARB *rad;

void Creare(ARB* &c,int li,int ls,char epf[],int pfp[])
{
    int i, j, minim;
    minim=pfp[ls];
    i=ls;
    for(j=ls; j>=li; j--)
        if(pfp[j]<minim)
        {
            minim=pfp[j];
            i=j;
        }
    c=new ARB;
    c->inf=efp[i];
    if(li==ls)
        c->st=c->dr=0;
    else
    {
        Creare(c->st,li,i-1,efp,pfp);
        Creare(c->dr,i+1,ls,efp,pfp);
    }
}

char sir[256];
int n=0;

void Parcurgere(ARB *c)

{
    if(c)
    {
        sir[n]=c->inf;
        n++;

        Parcurgere(c->st);
        Parcurgere(c->dr);
    }

}

void deseneazaCerc(int x,int y, char s)
{

    circle(x,y,20);
    char sir[2];
    sir[0]=s;
    sir[1]='\0';
    outtextxy(x-3,y-6,sir);


}

void deseneazaPatrat(int x,int y, char s)
{
    rectangle(x-17,y-17,x+17,y+17);
    char sir[2];
    sir[0]=s;
    sir[1]='\0';
    outtextxy(x-3,y-6,sir);

}

void graf(int x,int y,int ok, char s[256])
{int coordx, coordy;
    char h=s[0];
    strcpy(s,s+1);
    if (ok==0 && strchr("+-*/",h))
    {
        deseneazaCerc(x-150,y+100,h);

        if (x!=750 && y!=0)
            line(x-h,y+h/2,x-200+h,y+100-h/2);
        if (x!=750 && y!=0)
            line(x-h,y+h/2,x+h,y+100-h/2);
        graf(x-100,y+100,0,s);
        graf(x-200,y+100,1,s);

    }
    else
    {
        if (ok==0 && strchr("0123456789",h))
        {
            deseneazaPatrat(x-100,y+100,h);
        }
        else if (ok==1 && strchr("+-*/",h))
        {
            deseneazaCerc(x+150,y+100,h);

            graf(x+200,y+100,0,s);
            graf(x+150,y+100,1,s);
        }
        else
        {
            if (x!=750 && y!=0)
            deseneazaPatrat(x+100,y+100,h);
        }
    }
}
int main()
{int x,y;
    char e[256];
    cin.get(e,256);
    int i,j=0;
    for(i=0; e[i]; i++)
        switch(e[i])
        {
        case ')':
            j-=10;
            break;
        case '(':
            j+=10;
            break;
        case '+':
        case '-':
            p[i]=j+1;
            break;
        case '*':
            p[i]=j+10;
            break;
        default:
            p[i]=1000;
        }
    j=-1;
    for(i=0; e[i]; i++)
        if(e[i]!=')'&&e[i]!='(')
        {
            j++;
            efp[j]=e[i];
            pfp[j]=p[i];
        }
    Creare(rad,0,j,efp,pfp);
    Parcurgere(rad);
    sir[n]='\0';

    initwindow(1400,700);
    graf(750,0,0,sir);
    outtextxy(50,100,"Lvl 0");
    outtextxy(50,200,"Lvl 1");
    outtextxy(50,300,"Lvl 2");
    outtextxy(50,400,"Lvl 3");
    outtextxy(50,500,"Lvl 4");
    outtextxy(50,600,"Lvl 5");
    getch();
    closegraph();
    return 0;
}
