#ifndef DATOSGRAFOSH
#define DATOSGRAFOSH

using namespace std;

class DatosGrafos {
	private:
		int ID_Sector_Llegada;
		int ID_Sector_Destino;
		float Distancia;
	public:
		DatosGrafos(){
			
		}
		DatosGrafos(int ID_Sector_Llegada,int ID_sector_Destino,float distancia){
			this->ID_Sector_Llegada = ID_Sector_Llegada;
			this->ID_Sector_Destino = ID_sector_Destino;
			this->Distancia = distancia;
		}
		
		int getIDSectorLlegada(){
			return ID_Sector_Llegada;
		}
		
		int getIDSectorDestino(){
			return ID_Sector_Destino;
		}
		
		int getDistancia(){
			return Distancia;
		}
};

#endif
