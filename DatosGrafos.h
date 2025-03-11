
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

// metodos auxiliares
void DatosGrafos::mostrarVehiculosDisponibles() {
    for (const auto &vehiculo : listaVehiculos) {
        if (vehiculo.disponible) {
            cout << "ID: " << vehiculo.id << ", Sector: " << vehiculo.sector << endl;
        }
    }
}

int DatosGrafos::obtenerSectorVehiculo(int idVehiculo) {
    for (const auto &vehiculo : listaVehiculos) {
        if (vehiculo.id == idVehiculo) {
            return vehiculo.sector;
        }
    }
    return -1; // No encontrado
}

void DatosGrafos::actualizarUbicacionVehiculo(int idVehiculo, int nuevoSector) {
    for (auto &vehiculo : listaVehiculos) {
        if (vehiculo.id == idVehiculo) {
            vehiculo.sector = nuevoSector;
            break;
        }
    }
}


#endif
