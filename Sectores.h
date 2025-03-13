#ifndef SECTORES_H
#define SECTORES_H
#include "Sector.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Sectores{
	public:
    vector<string> sectores;
    vector<string> idSectores;
    int numSectores;              
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
    void DistribuirSectores(Sector* sector) {

        if (numSectores == 0) {
            return;

        }

        int random = rand() % numSectores;
        
        sector->setNombreSector(sectores[random]);
        sector->setId(idSectores[random]);

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