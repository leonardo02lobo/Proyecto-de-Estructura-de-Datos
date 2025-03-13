#ifndef CHOFER_H
#define CHOFER_H
#include<cstring>

using namespace std;

class Chofer{

	private:
	
		int _cedula;
		string _nombreConductor;
	public:

		Chofer(){
			_cedula = 0;
			_nombreConductor = "";
		}
		
		Chofer(string nombreConductor,int cedula){
			_cedula = cedula;
			_nombreConductor = nombreConductor;
		}

		void setNombreConductor(string nombreConductor){
			_nombreConductor = nombreConductor;
		}
		void setCedula(int cedula){
			_cedula = cedula;
		}

		string getNombreConductor(){
			return _nombreConductor;
		}

		int getCedula(){
			return _cedula;
		}
};
#endif

