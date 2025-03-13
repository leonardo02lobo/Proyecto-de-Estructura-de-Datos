#ifndef SECTOR_H
#define SECTOR_H

class Sector{
	private:
		string _id;
		string _nombreSector;
	public:
		Sector(){
			_id = "";
			_nombreSector = "";
		}
		Sector(string id,string nombreSector){
			this->_id = id;
			this->_nombreSector = nombreSector;
		}
		void setId(string id){
			this->_id = id;
		}
		void setNombreSector(string nombreSector){
			this->_nombreSector = nombreSector;
		}
		string getId(){
			return this->_id;
		}
		string getNombreSector(){
			return this->_nombreSector;
		}	
};
#endif