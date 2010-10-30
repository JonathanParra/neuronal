#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NUM_ENTRADAS 2  //Cambiar este numero para cambiar las 
                        //entradas del perceptron
 
float entrada[NUM_ENTRADAS],
      pesos[NUM_ENTRADAS],
      salida;
int i;
 
using namespace std;
 
int main(){
  srand48(time(NULL)); //inicia el generador de numeros pseudoaleatorios
  for( i=0; i<NUM_ENTRADAS; i++ ){
  pesos[i]=drand48(); //se aplican valores aleatorios a las entradas
  }
  for( i=0; i<NUM_ENTRADAS; i++ ){
    cout<<"Entrada "<<i+1<<": ";
    cin>>entrada[i]; //se pide al usuario las entradas
  }
  salida=0.0;      //preventivamente se inicia la salida con 0
  for( i=0; i<NUM_ENTRADAS; i++ ){
    salida+=(entrada[i])*(pesos[i]);//se va a la salida la
  }                                     //suma de las entradas por los pesos
  salida=1/(1+exp(-1*salida));       //se aplica a la salida la funcion sigmoide
  cout<<"Salida: "<<salida<<endl;               //se imprime la salida
  cout<<"Pesos: "<<pesos[1]<<" "<<pesos[2]<<endl; //muestra los pesos usados
  return 0;
}