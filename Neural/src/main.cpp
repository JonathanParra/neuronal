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


#include <iostream>
#include "funciones.h"


using namespace std;

int c=0; //simple variable para el control del loop

int main( int argc, char *argv[])
{
    //Presentacion
    cout<<"******************************************************************************"<<endl;
    cout<<"<NEURAL>  Copyright (C) 2010  Sauruxum"<<endl;
    cout<<"    This program comes with ABSOLUTELY NO WARRANTY."<<endl;
    cout<<"    This is free software, and you are welcome to redistribute it"<<endl;
    cout<<"    under certain conditions; type `show c' for details."<<endl;
    cout<<"******************************************************************************"<<endl;
    cout<<" ____________               "<<endl;
    cout<<"< neural >                  "<<endl;
    cout<<" ------------               "<<endl;
    cout<<"           ,__,             "<<endl;
    cout<<"           (oo)____         "<<endl;
    cout<<"           (__)    )\       "<<endl;
    cout<<"              ||--|| *      "<<endl; 
    cout<<""<<endl;
    cout<<"Aplicacion para el entrenamiento y uso de una red"<<endl;
    cout<<"neuronal basada en el algoritmo back propagation"<<endl;
    cout<<""<<endl;
    cout<<"******************************************************************************"<<endl;
    cout<<""<<endl;
    //Menu de inicio
    while(c!=1){
    c=menu();
    }
}


