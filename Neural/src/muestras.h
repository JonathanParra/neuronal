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


#include <stdlib.h>
#include <stdio.h>

//Leer un archivo con los patrones de entrada y salida usados por la red
class patrones {
private:
    int N_patrones,  //Numero de muestras que se daran ( no se me ocurre otro modo de hacer el codigo seguro )
    in,
    out;
    double **Inputs, //Contenedores de los datos de la muestras
    **Outputs;
    char *archivo;
public:
    patrones(int a, int b, char *p) {
        in=a;       //Numero de entradas de la red
        out=b;      //Numero de salidas de la red;
        archivo=p;
    };
    ~patrones() {
        delete [] Inputs;   //Remueve las variables creadas en la construccion de la clase
        delete [] Outputs;
    }



    void Leer_Archivo( void ) {
        FILE *fw = fopen(archivo,"r");

        if (!fw) {
            perror(archivo);
            return;
        }

        fscanf(fw, "%d", &N_patrones);    //Lee del archivo cuantas muestras se usaran
        Crear_datos();                    //Crea las matrices para almacenar los patrones

        for ( int i=0; i<N_patrones; i++ ) {
            for ( int j = 0; j < in; j++ ) {      //Asigna a las matrices
                fscanf( fw, "%lf", &Inputs[j][i] ); //los datos de muestra de
            }                                     //entrada y salida.
            for ( int j = 0; j < out; j++ ) {     //Los almacena hasta que son
                fscanf( fw, "%lf", &Outputs[j][i] );//pedidos por otra funcion
            }
        }
    }

    void Asign_patrones( int n, double *p, double *s ) { //Esta funcion pasa cada array
        for ( int i=0; i<in; i++ ) {                      //de la matriz a array externos
            p[i]=Inputs[i][n];                                  //necesarios para el entrenamiento
        }                                                 //de la red
        for ( int i=0; i<out; i++ ) {
            s[i]=Outputs[i][n];
        }
    }

    void Crear_datos( void ) {                  //Crea las matrices
        Inputs=create_array( in, N_patrones );    //de las muestras de ingreso
        Outputs=create_array( out, N_patrones );  //de los objetivos
    }
    
    int N_muestras( void ){
      return N_patrones;
    }

    //Crear una matriz
    double **create_array( int Row, int Col )
    {
        double **array = new double*[Row];
        for ( int i = 0; i < Row; i++ )
            array[i] = new double[Col];
        return array;
    }
};
