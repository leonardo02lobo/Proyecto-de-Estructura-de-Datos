/*
Integrantes del proyecto
Leonardo Jose Lobo Candelario V-31.489.733
Moises David Becerra Salamanca V-30.965.748
Luis Alfonso Omaña Colmenares V-31.180.408
*/
#include <iostream>
#include <windows.h>
#include <fstream> 
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "Usuario.h"
#include "Vehiculo.h"
#include "Chofer.h"
#include "Sector.h"
#include "Traslado.h"
#include "Estadisticas.h"
#include "Sectores.h"
#include "DatosGrafos.h"
#include "Grafo.h"

// Este metodo se crea para poder utilizar la funcion gotoxy
// La funcion gotoxy posiciona el cursor en la consola en las coordenadas especificadas (x, y).
 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 

using namespace std;

//portotipos de los metodos y creacion del archivo de texto
void Menu();
void MenuGestion();
void MenuServicios(); 
void MenuConductor();
void MenuUsuarios();
void GenerarGrafodesdeArchivo();
Sectores numeroSectores;
Cola* colaSectores = new Cola[numeroSectores.numSectores];
Cola** frente = new Cola*[numeroSectores.numSectores];
Cola** final = new Cola*[numeroSectores.numSectores];
Lista* lista = new Lista[numeroSectores.numSectores];

//funcion main encargada de la administracion del programa
//llama a la funcion meni para iniciar el flujo del programa 
int main(int argc, char** argv) {
	//llama al menu si todo salio bien 
	Menu();
	return 0;
}

//metodo encargado de la generar el menu con las opciones para poder gestionar a los usuarios o gestionar los servicios diarios
void Menu(){
	int opcion = 0;
	do{
		do{
			system("cls");
			fflush(stdin);
			gotoxy(40,1);
			cout<<"-------------------------------";
			gotoxy(40,2);
			cout<<"|    Bienvenidos a SPEEDCAR   |"<<endl;
			gotoxy(40,3);
			cout<<"-------------------------------";
			gotoxy(30,5);
			cout<<"Cual opcion quiere elegir"<<endl;
			gotoxy(30,7);
			cout<<"1. Gestion de Datos"<<endl;
			gotoxy(30,9);
			cout<<"2. Servicios Diarios"<<endl;
			gotoxy(30,11);
			cout<<"3. Salir "<<endl;
			gotoxy(30,13);
			cout<<"Ingrese la opcion: "<<endl;
			gotoxy(30,14);
			cin>>opcion;

			if(opcion < 1 || opcion > 3){
				gotoxy(40,16);
				cout<<"La opcion ingresa es invalida"<<endl;
				system("pause");
			}	
			system("cls");
		}while(opcion < 1 || opcion > 3);
		switch(opcion){
			case 1:
				MenuGestion();   
				break;
			case 2:
				MenuServicios();
				break;
			case 3:
				cout<<"Hasta luego"<<endl;
				break;
		}
	}while(opcion != 3);
}


//menu que se encarga de la gestion de los usuarios
//Se pidio el desarrollo de un peque?o CRUD para el archivo esta separado por funciones
void MenuGestion(){
	int opcion = 0;
	Usuario usuario;
	Vehiculo vehiculo;
	do{
		do{
			system("cls");
			fflush(stdin);
			gotoxy(40,1);
			cout<<"------------------------"<<endl;
			gotoxy(40,2);
			cout<<"|   Gestion de datos   |"<<endl;
			gotoxy(40,3);
			cout<<"------------------------"<<endl;
			gotoxy(30,5);
			cout<<"Cual opcion quiere elegir"<<endl;
			gotoxy(40,7);
			cout<<"1. Datos Usuarios"<<endl;
			gotoxy(40,9);
			cout<<"2. Datos Vehiculos"<<endl;
			gotoxy(40,11);
			cout<<"3. Salir"<<endl;
			gotoxy(30,13);
			cout<<"Ingrese la opcion: "<<endl;
			gotoxy(40,15);
			cin>>opcion;

			if(opcion < 1 || opcion > 3){
				gotoxy(40,17);
				cout<<"La opcion ingresa es invalida"<<endl;
				system("pause");	
			}
			system("cls");	
		}while(opcion < 1 || opcion > 3);
		switch(opcion){
			case 1:	
				MenuUsuarios();
				break;
				
			case 2:
				MenuConductor();
				break;
			
			case 3: 
				cout<<"Volver al Menu Anterior."<<endl;
				system("pause");
				break;
		}
	}while(opcion != 3);
}

//Este metodo se encarga del menu de los servicios del codigo y sus funcionalidades
void MenuServicios(){
	int opcion = 0;
	Sectores sectores;
	Vehiculo vehiculo;
	Traslado traslado(colaSectores,frente,final,lista); 
	do{
		do{
			system("cls");
			fflush(stdin);
			gotoxy(40,1);
			cout<<"-------------------------";
			gotoxy(40,2);
			cout<<"|   Servicios diarios   |";
			gotoxy(40,3);
			cout<<"------------------------";
			gotoxy(30,5);
			cout<<"Elije una opcion"<<endl;
			gotoxy(30,7);
			cout<<"1. Actualizar Ubicacion Vehiculo"<<endl;
			gotoxy(30,9);
			cout<<"2. Solicitar Traslado"<<endl;
			gotoxy(30,11);
			cout<<"3. Finalizar Traslado"<<endl;
			gotoxy(30,13);
			cout<<"4. Imprimir Reporte"<<endl;
			gotoxy(30,15);
			cout<<"5. Generar Grafo de Sectores"<<endl;
			gotoxy(30,17);
			cout<<"6. Salir"<<endl;
			gotoxy(30,19);
			cout<<"Ingrese la opcion: "<<endl;
			gotoxy(30,21);
			cin>>opcion;

			if(opcion < 1 || opcion > 5){
				gotoxy(40,21);
				cout<<"La opcion ingresa es invalida"<<endl;
				system("pause");	
			}	
			system("cls");
		}while(opcion < 1 || opcion > 5);
		switch(opcion){
			case 1:{
				int id = vehiculo.ActualizarUbicacionVehiculo();
				traslado.RevisarCola(id);
				traslado.RevisarLista(id);
				break;
			}    
			case 2: 
			    traslado.solicitar(sectores);
                break;
			case 3:
				{
					string placa;
					cout << "Ingrese la placa del vehiculo para finalizar el traslado: ";
					cin >> placa;
					traslado.finalizarTraslado(placa); 
				}
				break;
			case 4:{
					Estadisticas e;
					e.generarReporte();
					
					cout<<"Estadisticas Hechas. El archivo se encuentra en la raiz del proyecto."<<endl;
				break;
			}	
			case 5:
				GenerarGrafodesdeArchivo();
				break;
			case 6:
				cout<<"Volver al Menu Anterior."<<endl;
				break;
		}
		system("pause");
	}while(opcion != 5);
}

//Este metodo se encarga del CRUD del usuario
void MenuUsuarios(){
	int opcion;
	Usuario usuario;
	do{
		do{		
			system("cls");
			fflush(stdin);
			gotoxy(40,1);
			cout<<"-----------------------";
			gotoxy(40,2);
			cout<<"|   Modificar datos   |";
			gotoxy(40,3);
			cout<<"---------------------- ";
			gotoxy(40,5);
			cout<<"1. Agregar Usuario"<<endl;
			gotoxy(40,7);
			cout<<"2. Modificar Usuario"<<endl;
			gotoxy(40,9);
			cout<<"3. Consultar Usuario"<<endl;
			gotoxy(40,11);
			cout<<"4. Eliminar Usuario"<<endl;
			gotoxy(40,13);
			cout<<"5. Salir"<<endl;
			gotoxy(30,15);
			cout<<"Ingrese la opcion: "<<endl;
			gotoxy(40,17);
			cin>>opcion;
			
			if(opcion < 1 || opcion > 5){
				gotoxy(40,19);
				cout<<"La opcion ingresa es invalida"<<endl;
				system("pause");	
			}
			system("cls");
		}while(opcion < 1 || opcion > 5);
		
		switch(opcion){
			case 1:
				usuario.AgregarUsuario();
				break;
			case 2:
				usuario.ModificarUsuario();
				break;
			case 3:
				usuario.ConsultarUsuario();
				break;
			case 4:
				usuario.EliminarUsuario();
				break;
			case 5:
				cout<<"Volver al Menu Anterior."<<endl;
				break;
		}
		system("pause");
	}while(opcion != 5);
}

//Este metodo se encarga del CRUD del conductor
void MenuConductor(){
	int opcion;
	Sectores sectores;
	Vehiculo vehiculo;
	
	do{
		do{		
			system("cls");
			fflush(stdin);
			gotoxy(40,1);
			cout<<"-----------------------";
			gotoxy(40,2);
			cout<<"|   Modificar datos   |";
			gotoxy(40,3);
			cout<<"---------------------- ";
			gotoxy(40,5);
			cout<<"1. Agregar Conductor"<<endl;
			gotoxy(40,7);
			cout<<"2. Modificar Conductor"<<endl;
			gotoxy(40,9);
			cout<<"3. Consultar Conductor"<<endl;
			gotoxy(40,11);
			cout<<"4. Eliminar Conductor"<<endl;
			gotoxy(40,13);
			cout<<"5. Salir"<<endl;
			gotoxy(30,15);
			cout<<"Ingrese la opcion: "<<endl;
			gotoxy(40,17);
			cin>>opcion;
			
			if(opcion < 1 || opcion > 5){
				gotoxy(40,19);
				cout<<"La opcion ingresa es invalida"<<endl;
				system("pause");	
			}
			system("cls");
		}while(opcion < 1 || opcion > 5);
		
		switch(opcion){
			case 1:
				vehiculo.AgregarVehiculo(sectores);
				break;
			case 2:
				vehiculo.ModificarVehiculo();
				break;
			case 3:
				vehiculo.ConsultarVehiculo();
				break;
			case 4:
				vehiculo.EliminarVehiculo();
				break;
			case 5:
				cout<<"Volver al Menu Anterior."<<endl;
				break;
		}
		system("pause");
	}while(opcion != 5);
}

void GenerarGrafodesdeArchivo(){
	string nombreDelArchivo = "Grafo.txt";
	ifstream file(nombreDelArchivo.c_str());
	
	if(!file.is_open()){
		cout<<"no se pudo abrir el archivo 'Grafo.txt'"<<endl;
		return;
	}
	
	int maxSectores = 0;
	vector<DatosGrafos> hijos;
	
	string linea;
	while(getline(file,linea)){
		int sectorLlegada,sectorDestino;
		float distancia;
		char coma;
		stringstream ss(linea);
		
		ss >> sectorLlegada >>coma >> sectorDestino >> coma >> distancia;
		
		
		maxSectores = max(maxSectores,max(sectorLlegada,sectorDestino));
		
		DatosGrafos datos(sectorLlegada,sectorDestino,distancia);
		hijos.push_back(datos);
	}
	file.close();
	
	int N = maxSectores + 1;
	int** adyacenciaMatriz = new int*[N];
	for(int i = 0; i < N; i++){
		adyacenciaMatriz[i] = new int[N];
		for(int j = 0; j < N; j++){
			adyacenciaMatriz[i][j] = 0;
		}
	}
	
	// Rellenar la matriz con las distancias
	for (int i = 0; i < hijos.size(); ++i) {
	    int sector1 = hijos[i].getIDSectorLlegada();
	    int sector2 = hijos[i].getIDSectorDestino();
	    int distancia = hijos[i].getDistancia();
	
	    adyacenciaMatriz[sector1][sector2] = distancia;
	    adyacenciaMatriz[sector2][sector1] = distancia;  // Grafo no dirigido
	}
	// Mostrar la matriz de adyacencia
    cout << "Matriz de adyacencia:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << adyacenciaMatriz[i][j] << " ";
        }
        cout << endl;
    }

    // Liberar la memoria
    for (int i = 0; i < N; ++i) {
        delete[] adyacenciaMatriz[i];
    }
    delete[] adyacenciaMatriz;
}
