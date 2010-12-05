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


#ifndef BACKPROP_H
#define BACKPROP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>



//Declaracion de la clase "RedNeuronal" que realiza todo el calculo de la red MLP ( multilayer perceptron )
class RedNeuronal
{
public:
    RedNeuronal();
    ~RedNeuronal();

    void CreateRed(void);
    void TrainRed(void);
    void TestRed(void);
    void Train(void);

    void RandomPesos(void);
    void RandomBias(void);
    void ZeroDeltaPesos(void);
    void SaveNet(char*);
    void RestoreNet(char*);

    double *Input_nudo;
    double *Output_nudo;
    double *Target;

    double Error;     //error total en la red
    double Epsilon;   //error minimo requerido
    double Alpha;     //momemto
    double Eta;       //taza de aprendizaje

    int input_num;    //numero de elementos de ingreso
    int output_num;   //elementos en la capa oculta
    int hidden_num;   //elementos en la capa de salida
    int target_num;   //numero de objetivos ( aunque si generalmente son en
    //la misma cantidad de los elementos de salida, uno nunca sabe... )

private:

    double *Hidden_nudo;


    double *HBias;
    double *OBias;

    double **InputPeso;
    double **HiddenPeso;

    double *Delta;
    double *HDelta;
    double *DPeso;
    double *DPeso_;

    void FeedForward(void);
    void ComputeError(void);
    void Backpropagate(void);

    double Sigmoid( double num );

    double Err;

};



double **create_array( int Row, int Col );
double Random( int High, int Low );




#endif
