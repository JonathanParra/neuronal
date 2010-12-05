/*Copyright (C) 2010  Sauruxum

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/


#include <time.h>
#include <iostream>
#include "red.h"
#include "muestras.h"
#include "funciones.h"

double A_error,        //Variable de error local para el entrenamiento
       S_error,        //Suma total del error, focalizado para detener el entrenamiento
       *l,             //Array que contiene los patrones de entrada de forma temporal
       *d;             //Array que ontiene los patrones de salida de forma temporal
int he, muestras, i, j; 
int inp, hid, outp;    //Varibles que definen la cantidad de elementos en cada capa
char f[32], g[32];     //Cadenas para os nombres de los archivos requeridos
int m;                 //Coje el valor para elegir la funcion del menu
bool op, comp=false;   //Variables de uso en el error de entrenamiento y el comparador respectivamente

using namespace std;

//Funcion del menu que da la opcion de entrenar una red, teniendo a la mano los patrones necesarios
void Entrenar_red ( void )
{
    cout<<"Ingresar el numero de elementos de entrada"<<endl;
    cin>>inp;
    cout<<"Ingresar el numero de elementos de la capa oculta"<<endl;
    cin>>hid;
    cout<<"Ingresar el numero de elementos de salida"<<endl;
    cin>>outp;
    cout<<"Ingresar el archivo de patrones"<<endl;
    cin.width (31);
    cin>>f;
    cout<<"Ingresar el archivo donde desea guardar los datos de la red"<<endl;
    cin.width (31);
    cin>>g;
    srand ( time ( NULL ) );
    RedNeuronal BPN;          //Nueva clase del tipo RedNeuronal

    BPN.input_num = inp;      //Se especifica el numero de elementos de entrada
    BPN.output_num = outp;    //el numero de elementos en la capa de salida
    BPN.hidden_num = hid;     //el numero de elementos en la capa oculta
    BPN.target_num = outp;    //y el numero de objetivos ( coindice casi siempre con las salidas )
    BPN.CreateRed();          //Crea la red para ser entrenada
    l=new double [BPN.input_num];
    d=new double [BPN.output_num];
    patrones Patr ( BPN.input_num, BPN.output_num, f );   //Crea la clase que contendra el archivo de patrones
    Patr.Leer_Archivo();                                  //Lee el archivo de patrones
    muestras=Patr.N_muestras();                           //Da a la variable auxiliar la cantidad de patrones usados

    //Los siguientes valores podeis cambiarlos antes de compilacion, estos son valores optimales en casos generales
    BPN.Epsilon = 0.01f; //Minimo error ( usado solo para debug )
    BPN.Eta = 0.5f;      //Taza de entrenamiento
    BPN.Alpha = 0.3f;    //Momento
    S_error=1000;        //Auxiliar, sirve para detener el entrenamiento cuando baja de un minimo de error
    op=true;
    
    //Comienza el entrenamiento de la red
    for ( i=0; S_error>0.01; i++ )
    {
        //ejecuta el loop hasta un limite ( para evitar loops infinitos que con mala suerte suceden )
        if (i==100000){           //lo que no significa que no sea posible el entrenamiento, es cosa de los rand()
	  cout<<"Fallido: normalmente los entrenamientos no superan las 60000 epocas..."<<endl;
	  op=false;                                                                       
	  break;
	  break;
	}
	//Pasa 1 a 1 los patrones de entrada y salida y entrena la red
        for ( he=0; he<muestras; he++ )
        {
            Patr.Asign_patrones ( he, l, d );
            for ( j=0; j<BPN.input_num; j++ )
            {
                BPN.Input_nudo[j]=l[j];
            }
            for ( j=0; j<BPN.output_num; j++ )
            {
                BPN.Target[j]=d[j];
            }
            BPN.TestRed();
            for ( j=0; j<BPN.input_num; j++ )
            {
                cout <<BPN.Input_nudo[j]<<" ";
            }
            cout<<" ---> ";
            for ( j=0; j<BPN.output_num; j++ )
            {
                cout<< BPN.Output_nudo[j]<<" ";
            }
            cout<<endl;
            for ( j=0; j<BPN.output_num; j++ )
            {
                A_error+= ( BPN.Target[j]-BPN.Output_nudo[j] ) * ( BPN.Target[j]-BPN.Output_nudo[j] );
            }
            BPN.TrainRed();
        }
        //Calcula el error en la red en una cierta epoca
        S_error=sqrt ( ( A_error ) * ( A_error ) );
        A_error=0;
    }

    if (op==true) BPN.SaveNet(g);      //eso mismo, guarda la red al archivo
    cout<<f<<endl;
    cout<<"Entrenamiento de la red realizado en "<<i<<" epocas"<<endl;
}

//Esta funcion del menu coje el archivo donde se guardo la red y la utiliza para simularla
void Usar_red(void){
  RedNeuronal BPN;
  cout<<"Ingresar el nombre del archivo que contiene los datos de la red"<<endl;
  cin.width (31);
  cin>>f;
  BPN.RestoreNet(f);      //Recupera la red del archivo dado
  cout<<"Ingresar los valores de entrada a la red:"<<endl;
  for(i=0; i<BPN.input_num; i++){                  //
    cout<<"Entrada "<<(i+1)<<endl;                 //A este punto el programa pide los datos
    cin>>BPN.Input_nudo[i];                        //de ingreso hasta llenar el buffer de entrada
    cout<<endl;
  } 
  BPN.TestRed();                                   //Da salidas a la red
  cout<<"Salidas:"<<endl;
  for(int i=0; i<BPN.output_num; i++){        
    cout<<Comparador(BPN.Output_nudo[i])<<endl;    //Ennumera las salidas de la red
  }                                                //La salida puede ser continua o discreta 
}                                                  //segun lo que se elige en el menu principal


//Muestra el menu...
int menu(void) {
    cout<<""<<endl;
    //Menu de inicio
    cout<<"Menu"<<endl;
    cout<<"1. Usar una red entrenada"<<endl;
    cout<<"2. Entrenar una nueva red"<<endl;
    cout<<"3. Activar/desactivar el comparador en salida"<<endl;
    cout<<"4. Salir"<<endl;
    cin>>m;
    cout<<endl;
    //Segun la entrada entrega una funcion...
    if (m==1) Usar_red();
    if (m==2) Entrenar_red();
    if (m==3) Set_comparador();
    if (m==4)return 1;
    else return 0;
}

//El comparador. Por cada llamada de la funcion alterna la salida entre continua ( de 0 a 1 ) o discreta ( o 0 o 1 )
void Set_comparador( void ) {
    if (comp==false) {
        comp=true;
        cout<<"Comparador activado"<<endl;
    }
    else {
        comp=false;
        cout<<"Comparador desactivado"<<endl;
    }
}

//Esta funcion realiza la accion de dar la salida, segun la eleccion en el menu
double Comparador( double a ) {
    if (comp==true) {
        if (a<0.5) return 0;
        if (a>=0.5) return 1;
    }
    else return a;
}