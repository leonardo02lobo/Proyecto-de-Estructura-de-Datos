// MenuGestion.h
#ifndef MENUGESTION_H
#define MENUGESTION_H

#include <iostream>
#include "Vehiculo.h"
#include "Usuario.h"

void MenuConductor();
void MenuUsuarios();

class MenuGestion {
public:
    static void mostrarMenuGestion() {
        	int opcion = 0;
	Usuario usuario;
	Vehiculo vehiculo;
	do{
		do{
			system("cls");
			fflush(stdin);
		
			cout<<"------------------------"<<endl;
		
			cout<<"|   Gestion de datos   |"<<endl;
		
			cout<<"------------------------"<<endl;
		
			cout<<"\nCual opcion quiere elegir"<<endl;
		
			cout<<"1. Datos Usuarios"<<endl;
		
			cout<<"2. Datos Vehiculos"<<endl;
		
			cout<<"3. Salir"<<endl;
		
			cout<<"Ingrese la opcion: "<<endl;
			
			cin>>opcion;

			if(opcion < 1 || opcion > 3){
			
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
    
    //Este metodo se encarga del CRUD del usuario
static void MenuUsuarios(){
	int opcion;
	Usuario usuario;
	do{
		do{		
			system("cls");
			fflush(stdin);
			
			cout<<"-----------------------";
			
			cout<<"|   Modificar datos   |";
		
			cout<<"---------------------- ";
		
			cout<<"\n1. Agregar Usuario"<<endl;
		
			cout<<"2. Modificar Usuario"<<endl;
		
			cout<<"3. Consultar Usuario"<<endl;
		
			cout<<"4. Eliminar Usuario"<<endl;
		
			cout<<"5. Salir"<<endl;
		
			cout<<"Ingrese la opcion: "<<endl;
		
			cin>>opcion;
			
			if(opcion < 1 || opcion > 5){
			
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
static void MenuConductor(){
	int opcion;
	Sectores sectores;
	Vehiculo vehiculo;
	
	do{
		do{		
			system("cls");
			fflush(stdin);
		
			cout<<"-----------------------";
		
			cout<<"|   Modificar datos   |";
		
			cout<<"---------------------- ";
		
			cout<<"\n1. Agregar Conductor"<<endl;
		
			cout<<"2. Modificar Conductor"<<endl;
		
			cout<<"3. Consultar Conductor"<<endl;
		
			cout<<"4. Eliminar Conductor"<<endl;
		
			cout<<"5. Salir"<<endl;
		
			cout<<"Ingrese la opcion: "<<endl;
		
			cin>>opcion;
			
			if(opcion < 1 || opcion > 5){
		
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
};



#endif // MENUGESTION_H