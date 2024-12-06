#ifndef SECTOR_H
#define SECTOR_H

/**
 * Clase que representa un sector en el sistema de transporte.
 * Contiene el ID y el nombre del sector.
 */
class Sector{
	private:
		string _id;
		string _nombreSector;
	public:
		
		/**
	    * Constructor sin par?metros.
	    * Inicializa el ID y el nombre del sector como cadenas vac?as.
	    */
		Sector(){
			_id = "";
			_nombreSector = "";
		}
		/**
	    * Constructor parametrico.
	    * @param id Identificador del sector.
	    * @param nombreSector Nombre del sector.
	    */
		Sector(string id,string nombreSector){
			this->_id = id;
			this->_nombreSector = nombreSector;
		}
		//------------------METODOS SETTERS---------------------------------
		/**
	    * Establece el ID del sector.
	    * @param id Nuevo ID del sector.
	    */
		void setId(string id){
			this->_id = id;
		/**
	    * Establece el nombre del sector.
	    * @param nombreSector Nuevo nombre del sector.
	    */
		}
		void setNombreSector(string nombreSector){
			this->_nombreSector = nombreSector;
		}
		//-----------------METODOS GETTERS-----------------------------------
		/**
	    * Obtiene el ID del sector.
	    * @return ID del sector.
	    */
		string getId(){
			return this->_id;
		}
		/**
	    * Obtiene el nombre del sector.
	    * @return Nombre del sector.
	    */
		string getNombreSector(){
			return this->_nombreSector;
		}
		
		
};
#endif


