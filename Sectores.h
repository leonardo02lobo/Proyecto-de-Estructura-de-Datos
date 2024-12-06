#ifndef SECTORES_H
#define SECTORES_H
#include "Sector.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

/**
 * Clase que representa una coleccion de sectores.
 * Contiene los diferentes sectores con sus identificadores
 * y un metodo para asignar un sector de manera aleatoria.
 */
class Sectores{
	public:
    vector<string> sectores;       ///< Lista de nombres de sectores.
    vector<string> idSectores;     ///< Lista de identificadores de sectores.
    int numSectores;               ///< Numero total de sectores.
	    
	    /**
     * Constructor por defecto.
     * Inicializa la lista de sectores y sus identificadores.
     */
	    
	    Sectores(){
	    	sectores.push_back("Barrio Obrero");
	    	sectores.push_back("Pirineos");
	    	sectores.push_back("Centro");
	    	sectores.push_back("La Concordia");
	    	sectores.push_back("Los Chaguaramos");
	    	sectores.push_back("San Juan");
	    	sectores.push_back("El Cementerio");
	    	sectores.push_back("La Castra");
	    	sectores.push_back("La Popa");
	    	sectores.push_back("Las Acacias");
	    	sectores.push_back("El Estadio");
	    	sectores.push_back("La Florida");
	    	sectores.push_back("Santa Teresa");
	    	sectores.push_back("El Reloj");
	    	
	    	idSectores.push_back("ID1");
	    	idSectores.push_back("ID2");
	    	idSectores.push_back("ID3");
	    	idSectores.push_back("ID4");
	    	idSectores.push_back("ID5");
	    	idSectores.push_back("ID6");
	    	idSectores.push_back("ID7");
	    	idSectores.push_back("ID8");
	    	idSectores.push_back("ID9");
	    	idSectores.push_back("ID10");
	    	idSectores.push_back("ID11");
	    	idSectores.push_back("ID12");
	    	idSectores.push_back("ID13");
	    	idSectores.push_back("ID14");
	    	
			numSectores = sectores.size();
		}
		
		/**
     * Asigna un sector aleatorio a un objeto de tipo Sector.
     * @param sector Puntero al objeto Sector al que se le asignara un nombre y ID.
     */
    void DistribuirSectores(Sector* sector) {

        if (numSectores == 0) {
            return;

        }

        int random = rand() % numSectores;
        
        // Asigno el sector y su ID
        sector->setNombreSector(sectores[random]);
        sector->setId(idSectores[random]);

        // Eliminar el sector y su ID asignados
        sectores.erase(sectores.begin() + random);
        idSectores.erase(idSectores.begin() + random);
        numSectores--; 
    }
    
    string DevolverSector(string id){
    	string nuevoSector;
    	for(int i = 0; i < idSectores.size();i++){
    		if(id == idSectores[i]){
    			nuevoSector = sectores[i];
    			break;
			}
		}
		return nuevoSector;
	}
};
#endif


