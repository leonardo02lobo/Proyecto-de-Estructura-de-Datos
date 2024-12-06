#ifndef CHOFER_H
#define CHOFER_H
#include<cstring>

using namespace std;

//Esta clase contiene unicamente el nombre del condcutor del vehiculo
class Chofer{
	private:
		int _cedula;
		string _nombreConductor;
	public:
		//constructor sin parametro
		Chofer(){
			_cedula = 0;
			_nombreConductor = "";
		}
		//constructor parametrico
		Chofer(string nombreConductor,int cedula){
			_cedula = cedula;
			_nombreConductor = nombreConductor;
		}
		//-----------------METODO SETTER---------------------------
		void setNombreConductor(string nombreConductor){
			_nombreConductor = nombreConductor;
		}
		void setCedula(int cedula){
			_cedula = cedula;
		}
		//----------------METODO GETTER----------------------------
		string getNombreConductor(){
			return _nombreConductor;
		}
		int getCedula(){
			return _cedula;
		}
};
#endif

