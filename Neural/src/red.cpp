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


#include "red.h"

//Constructor
RedNeuronal::RedNeuronal()
{
    Error = 0;
    Input_nudo = 0;
    Hidden_nudo = 0;
    Output_nudo = 0;
    Target = 0;
    HBias = 0;
    OBias = 0;
    Delta = 0;
    HDelta = 0;
    DPeso = 0;
    DPeso_= 0;
    InputPeso = 0;
    HiddenPeso = 0;
}

//Destructor
RedNeuronal::~RedNeuronal()
{
    delete [] Input_nudo;
    delete [] Hidden_nudo;
    delete [] Output_nudo;
    delete [] Target;

    delete [] HBias;
    delete [] OBias;

    delete [] Delta;
    delete [] HDelta;

    delete [] DPeso;
    delete [] DPeso_;

    delete [] InputPeso;
    delete [] HiddenPeso;
}

//Se crea el espacio para las variables usadas en la red con los datos
//del constructor. Tambien se inician algunas variables
void RedNeuronal::CreateRed(void)
{
    Input_nudo = new double[input_num];
    Hidden_nudo = new double[hidden_num];

    Output_nudo = new double[output_num];
    Target = new double[target_num];

    HBias = new double[hidden_num];
    OBias = new double[output_num];

    Delta = new double[output_num];
    HDelta = new double[hidden_num];

    DPeso = new double[output_num];
    DPeso_ = new double[hidden_num];

    InputPeso = create_array( input_num, hidden_num );
    HiddenPeso = create_array( hidden_num, output_num );

    RandomPesos();
    ZeroDeltaPesos();

    RandomBias();
}

//Inicializa los pesos con valores aleatorios
void RedNeuronal::RandomPesos(void)
{
    int i,j;

    for ( i = 0; i < input_num; i++ ) {
        for ( j = 0; j < hidden_num; j++ ) {
            InputPeso[i][j] = Random( 1, -1 );
        }
    }

    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < output_num; j++ ) {
            HiddenPeso[i][j] = Random( 1, -1 );
        }
    }
}

//Los bias tambien son iniciados con valores aleatorios
void RedNeuronal::RandomBias(void)
{
    int i = 0;

    for ( ; i < output_num; i++ ) {
        OBias[i] = Random( 1, 0 );
    }

    for ( i = 0; i < hidden_num; i++ ) {
        HBias[i] = Random( 1, 0 );
    }
}

//Inicia las variables de actualizacion de los pesos sinapticos
void RedNeuronal::ZeroDeltaPesos(void)
{
    int i = 0;

    for ( ; i < output_num; i++ ) {
        DPeso[i] = 0;
    }

    for ( i = 0; i < hidden_num; i++ ) {
        DPeso_[i] = 0;
    }
}

//guarda las variables necesarias en un archivo, asi son recuperadas posteriormente
void RedNeuronal::SaveNet(char *p)
{
    FILE *fw = fopen(p, "w");

    if (!fw) {
        perror(p);
        return;
    }

    int i,j;

    fprintf( fw, "%d\n", input_num );
    fprintf( fw, "%d\n", hidden_num );
    fprintf( fw, "%d\n", output_num );
    fprintf( fw, "%d\n", target_num );

    //guarda el momento
    fprintf( fw, "%lf\n", Alpha );
    //guarda la constante "taza de aprendizaje"
    fprintf( fw, "%lf", Eta );
    fprintf( fw, "\n" );
    //guarda los valores de los bias de la capa oculta-salida
    for ( i = 0; i < output_num; i++ ) {
        fprintf( fw, "%lf  ", OBias[i] );
    }

    fprintf( fw, "\n\n" );

    //y los bias de la capa de ingreso-oculta
    for ( i = 0; i < hidden_num; i++ ) {
        fprintf( fw, "%lf  ", HBias[i] );
    }

    fprintf( fw, "\n\n" );

    //guarda los pesos sinapticos
    for ( i = 0; i < input_num; i++ ) {
        for ( j = 0; j < hidden_num; j++ ) {
            fprintf( fw, "%lf  ", InputPeso[i][j] );
        }
    }

    fprintf( fw, "\n\n\n" );

    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < output_num; j++ ) {
            fprintf( fw, "%lf  ", HiddenPeso[i][j] );
        }
    }

    fprintf( fw, "\n\n" );

    for ( i = 0; i < output_num; i++ ) {
        fprintf( fw, "%lf  ", DPeso[i] );
    }

    fprintf( fw, "\n\n" );

    for ( i = 0; i < hidden_num; i++ ) {
        fprintf( fw, "%lf  ", DPeso_[i] );
    }

    fflush(fw);
    fclose(fw);
}

//recupera los datos guardados en el archivo "net.dat"
void RedNeuronal::RestoreNet(char *p)
{
    FILE *fw = fopen(p, "r");

    if (!fw) {
        perror(p);
        return;
    }

    int i,j;

    fscanf( fw, "%d", &input_num );
    fscanf( fw, "%d", &hidden_num );
    fscanf( fw, "%d", &output_num );
    fscanf( fw, "%d", &target_num );

    CreateRed();

    //recupera el momento
    fscanf( fw, "%lf\n\n", &Alpha );
    //recupera la taza de aprendizaje
    fscanf( fw, "%lf", &Eta );
    //recupera los bias
    for ( i = 0; i < output_num; i++ ) {
        fscanf( fw, "%lf", &OBias[i] );
    }
    for ( i = 0; i < hidden_num; i++ ) {
        fscanf( fw, "%lf", &HBias[i] );
    }

    for ( i = 0; i < input_num; i++ ) {
        for ( j = 0; j < hidden_num; j++ ) {
            fscanf( fw, "%lf", &InputPeso[i][j] );
        }
    }

    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < output_num; j++ ) {
            fscanf( fw, "%lf", &HiddenPeso[i][j] );
        }
    }

    for ( i = 0; i < output_num; i++ ) {
        fscanf( fw, "%lf  ", &DPeso[i] );
    }

    for ( i = 0; i < hidden_num; i++ ) {
        fscanf( fw, "%lf  ", &DPeso_[i] );
    }

    fclose(fw);
}

//la funcion de transferencia para la red es la funcion sigmoide
double RedNeuronal::Sigmoid( double num )
{
    return (double)(1/(1+exp(-num)));
}

//retroalimenta la red, para conseguir las salidas
void RedNeuronal::FeedForward(void)
{
    // variables para los contadores
    int i, j;
    // variable auxiliar para guardar el resultado de la suma de los pesos por las entradas
    double synapse_sum = 0.0f;

    //retroalimenta la capa oculta
    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < input_num; j++ ) {
            synapse_sum += InputPeso[j][i]*Input_nudo[j];
        }
        Hidden_nudo[i] = Sigmoid( synapse_sum + HBias[i]);

        //se reinicia el valor de la variable auxiliar para el siguiente loop
        synapse_sum = 0.0f;
    }

    //retroalimenta la capa de salida
    for ( i = 0; i < output_num; i++ ) {
        for ( j = 0; j < hidden_num; j++ ) {
            synapse_sum += HiddenPeso[j][i]*Hidden_nudo[j];
        }
        Output_nudo[i] = Sigmoid( synapse_sum + OBias[i] );

        //reinicio de la variable auxiliar
        synapse_sum = 0.0f;
    }
}

//calculo del error cometido durante el entrenamiento
void RedNeuronal::ComputeError(void)
{
    //contadores
    int i, j;
    // ajuste del error a 0
    Error = 0;

    //Variable auxiliar para tener el valor del error
    double error_sum = 0.0f;

    //calculo del error a la capa de salida
    for ( i = 0; i < output_num; i++ ) {
        Err = ( Target[i] - Output_nudo[i] );
        Delta[i] = ( 1 - Output_nudo[i] )*Output_nudo[i] * Err;
        Error += 0.5f * Err * Err;
    }

    //calculo del error a la capa oculta
    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < output_num; j++ ) {
            error_sum += Delta[j]*HiddenPeso[i][j];
        }
        HDelta[i] = ( 1 - Hidden_nudo[i] )*Hidden_nudo[i] * error_sum;
        //reinicio de la variable auxiliar
        error_sum = 0.0f;
    }
}

//retropropaga el error
void RedNeuronal::Backpropagate(void)
{
    int  i, j;
    //retropropagacion del error en la capa de salida salida
    for ( i = 0; i < hidden_num; i++ ) {
        for ( j = 0; j < output_num; j++ ) {
            HiddenPeso[i][j] += Eta*Delta[j]*Hidden_nudo[i] + Alpha * DPeso[j];
            DPeso[j] = Eta*Delta[j]*Hidden_nudo[i];
        }
    }

    //retropropagacion del error a la capa oculta
    for ( i = 0; i < input_num; i++ ) {
        for ( j = 0; j < hidden_num; j++ ) {
            InputPeso[i][j] += Eta*HDelta[j]*Input_nudo[i] + Alpha * DPeso_[j];
            DPeso_[j] = Eta*HDelta[j]*Input_nudo[i];
        }
    }

    //retropropagacion del error al bias de las salidas
    for ( i = 0; i < output_num; i++ ) {
        OBias[i] += Eta*Delta[i];
    }

    //retropropagacion del error al bias de la capa oculta
    for ( i = 0; i < hidden_num; i++ ) {
        HBias[i] += Eta*HDelta[i];
    }
}

//Entrena la red con los patrones de entrada y los patrones de salida
//en modo de obtener como respuesta los patrones de salida
void RedNeuronal::TrainRed(void)
{
    FeedForward();
    ComputeError();
    Backpropagate();
}


//solo debug
void RedNeuronal::Train()
{
    Error = RAND_MAX;
    int epoch = 0;
    while ( Error > Epsilon ) {
        TrainRed();
        epoch++;
        printf( "epoch = %d\n", epoch );
    }
}

//Prueba el funcionamiento de la red
void RedNeuronal::TestRed(void)
{
    FeedForward();
}

//Crear una matriz de valores "double"
double **create_array( int Row, int Col )
{
    double **array = new double*[Row];
    for ( int i = 0; i < Row; i++ )
        array[i] = new double[Col];
    return array;
}

//Generador de numeros aleatorios, desde un minimo a un maximo
double Random( int High, int Low )
{
    //se usa la funcion time(NULL) para no tener siempre la misma secuencia de aleatorios
    srand( ( unsigned int )time( NULL ) );
    //retorna el numero aleatorio
    return ( (double)rand()/RAND_MAX) * (High - Low) + Low;
}

