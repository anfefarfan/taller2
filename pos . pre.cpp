#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string.h>
#define max 50

using namespace std;

struct nodo {
       char palabra;
       struct nodo *sgte;
       };

typedef struct nodo *Ptrpila;
typedef struct nodo *Tlista;


void push(Ptrpila &,char);
char pop(Ptrpila &);
void agregar_atras(Tlista &,char);
void destruir(Ptrpila &);
int  prioridad_infija(char );
int  prioridad_pila(char );
void imprimir( Tlista &);
void balanceoSimbolos( Ptrpila &, char []);


  int main(void)
    {   Ptrpila p=NULL;
        Ptrpila M=NULL;
        Tlista lista=NULL;
        char cad[max], c,x;
        int tam;


        do{
           cout<<"ingrese expresion infija:";
           gets(cad);
              if(M!=NULL)
                 destruir(M);
           balanceoSimbolos(M,cad);
           }while(M!=NULL);

        tam=strlen(cad);
        for(int i=0;i<tam;i++)
        {
            if((cad[i]>=49&&cad[i]<=57)||(cad[i]>=97&&cad[i]<=122))
                agregar_atras(lista,cad[i]);
            if(cad[i]=='+'||cad[i]=='-'||cad[i]=='*'||cad[i]=='/'||cad[i]=='('||cad[i]=='^')
            {   if(p==NULL)
                    push(p,cad[i]);
                else
                {
                    if(prioridad_infija(cad[i])>prioridad_pila(p->palabra))
                        push(p,cad[i]);
                    else
                    {   if(prioridad_infija(cad[i])==prioridad_pila(p->palabra))
                          {
                            c=pop(p);
                            agregar_atras(lista,c);
                            push(p,cad[i]);
                          }
                        else
                          {
                            c=pop(p);
                            agregar_atras(lista,c);
                          }
                    }
                }
            }
            if(cad[i]==')')
               {
                while(p->palabra!='('&&p!=NULL)
                   {
                       c=pop(p);
                       agregar_atras(lista,c);
                    }
                if(p->palabra=='(')
                        c=pop(p);
                }
        }
        while(p!=NULL)
            {
                c=pop(p);
                agregar_atras(lista,c);
            }

        imprimir(lista);
        system("pause");
        return 0;
    }


void push(Ptrpila &p,char a)
{
    Ptrpila q=new struct nodo;
    q->palabra=a;
    q->sgte=p;
    p=q;
 }

char pop(Ptrpila &p)
{
    int n;
    Ptrpila aux;

    n=p->palabra;
    aux=p;
    p=p->sgte;
    delete(aux);
    return n;

}

void agregar_atras(Tlista &lista,char a)
{
    Tlista t, q = new(struct nodo);

    q->palabra  = a;
    q->sgte = NULL;

    if(lista==NULL)
      {
        lista = q;
      }
    else
      {
        t = lista;
        while(t->sgte!=NULL)
        {
            t = t->sgte;
        }
        t->sgte = q;
      }

}

void destruir(Ptrpila &M)
{    Ptrpila aux;

     if(M !=NULL)
     {
         while(M!=NULL)
         {
             aux=M;
             M=M->sgte;
             delete(aux);
         }

      }
}

int prioridad_infija(char a)
{
    if(a=='^')
        return 4;
    if( a=='*')
        return 2;
    if( a=='/')
        return 2;
    if( a=='+')
        return 1;
    if( a=='-')
        return 1;
    if(a=='(')
        return 5;
}


int prioridad_pila(char a)
{
    if(a=='^')
        return 3;
    if( a=='*')
        return 2;
    if( a=='/')
        return 2;
    if( a=='+')
        return 1;
    if( a=='-')
        return 1;
    if(a=='(')
        return 0;
}

void imprimir( Tlista &lista)
{
    Ptrpila aux;
    aux=lista;

    if(lista!=NULL)
     {    cout<<"\t\nLa expresion posfija es:\n\n";
          while(aux!=NULL)
          {    cout<<aux->palabra;
               aux = aux->sgte;
          }
      }
      cout<<endl<<endl;
}


void balanceoSimbolos( Ptrpila &p, char cad[])
{
     Ptrpila aux;
     int i = 0;

     while( cad[i] != '\0')
     {
            if( cad[i]=='(' || cad[i]=='[' || cad[i]=='{' )
            {
                 push( p, cad[i] );
            }
            else if( cad[i]==')' || cad[i]==']' || cad[i]=='}' )
            {
                 aux = p;

                 if(aux!=NULL)
                 {
                      if( cad[i]==')' )
                      {
                           if( aux->palabra == '(')
                              pop( p );
                      }
                      else if( cad[i]==']' )
                      {
                           if( aux->palabra == '[')
                              pop( p );
                      }
                      else if( cad[i]=='}' )
                      {
                           if( aux->palabra == '{')
                              pop( p );
                      }
                 }
                 else
                     push( p, cad[i] );
            }
            i++;
     }
}
