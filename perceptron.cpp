#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define EPOCA 200  //Numero de iteraciones del entrenamiento
#define K 0.2f     //Taza de aprendizaje


float TrainNetwork( float x0, float x1, float target );//Funcion para entrenar el perceptron
float RunNetwork( float x0, float x1 );                //Funcion que entrega las salidas
float sigmoide( float s );                             //Funcion sigmoide
void pesos_init(void);                                 //Inicia los pesos aleatoriamente


float Pesos[2];    // pesos sinapticos
float bias = 1.0f; //El bias lo ajustamos al valor 1

int main()
{
  int i = 0;
  
  pesos_init();
  
  while( i < EPOCA ) // Entrenando la funcion logica AND
  {
    i++;
    
    //Se pasan los patrones para la funcion AND
    cout << "Salida" << endl;
    cout << "1, 1 = " << TrainNetwork( 1, 1, 1 ) << endl;
    cout << "1, 0 = " << TrainNetwork( 1, 0, 0 ) << endl;
    cout << "0, 1 = " << TrainNetwork( 0, 1, 0 ) << endl;
    cout << "0, 0 = " << TrainNetwork( 0, 0, 0 ) << endl;
    
    cout << "\n";
    
    //Se muestran los pesos a cada epoca
    cout << "Peso[0] = " << Pesos[0] << endl;
    cout << "Peso[1] = " << Pesos[1] << endl;
    
    cout << "\nbias = " << bias << endl;
    
    cout << "\n\n" << "epoca = " << i << endl;
    
  }
  
  //Se hace la prueba para ver el estado del entrenamiento
  cout << "Verificar los resultados:" << endl;
  cout << "1, 1 = " << RunNetwork( 1, 1 ) << endl;
  cout << "1, 0 = " << RunNetwork( 1, 0 ) << endl;
  cout << "0, 1 = " << RunNetwork( 0, 1 ) << endl;
  cout << "0, 0 = " << RunNetwork( 0, 0 ) << endl;
  
  cout << "\n";
  
  //Se muestran los pesos finales
  cout << "Peso[0] = " << Pesos[0] << endl;
  cout << "Peso[1] = " << Pesos[1] << endl;
  
  //Esto es el bias*W
  cout << "\nbias = " << bias << endl;
  
  cout << "\n\n" << "epoca = " << i << endl;
  return 0;
}

float TrainNetwork( float x0, float x1, float target )
{
  float net = 0;
  float out = 0;
  float delta[2];  //Es la variacion de los pesos sinapticos
  float Error;
  
  net = Pesos[0]*x0 + Pesos[1]*x1-bias;
  net = sigmoide( net );
  
  Error = target - net;
  
  bias -= K*Error;  //Como el bias es siempre 1, pongo que 
                    //el bias incluye ya su peso sinaptico
  
  delta[0] = K*Error * x0;  //la variacion de los pesos sinapticos corresponde 
  delta[1] = K*Error * x1;  //al error cometido, por la entrada correspondiente
  
  Pesos[0] += delta[0];  //Se ajustan los nuevos valores
  Pesos[1] += delta[1];  //de los pesos sinapticos
  
  out=net;
  return out;
}

float RunNetwork( float x0, float x1 )
{
  float net = 0;
  float out = 0;
  
  net = Pesos[0]*x0 + Pesos[1]*x1-bias;
  net=sigmoide( net );
  
  out=net;
  return out;
}


void pesos_init(void)
{
  for( int i = 0; i < 2; i++ )
  {
    Pesos[i] = (float)rand()/RAND_MAX;
  }
}

float sigmoide( float s ){
  return (1/(1+exp(-1*s)));
}
