#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Esta clase se encarga de almacenar los diferentes usuarios, obteniendo sus nombres, cédulas y direcciones.
class Usuario {
    private:
        int _cedula;
        string _nombre;
        string _direccion;

    public:
        // Constructor sin parámetros
        Usuario() {
            _cedula = 0;
            _nombre = "";
            _direccion = "";
        }

        // Constructor paramétrico que recibe los datos requeridos
        Usuario(int cedula, string nombre, string direccion) {
            this->_cedula = cedula;
            this->_nombre = nombre;
            this->_direccion = direccion;
        }

        //------------------METODOS SETTERS---------------------------------
        void setCedula(int cedula) {
            this->_cedula = cedula;
        }

        void setNombre(string nombre) {
            this->_nombre = nombre;
        }

        void setDireccion(string direccion) {
            this->_direccion = direccion;
        }

        //-----------------METODOS GETTERS-----------------------------------
        int getCedula() {
            return this->_cedula;
        }

        string getNombre() {
            return this->_nombre;
        }

        string getDireccion() {
            return this->_direccion;
        }

        // Este método devuelve un int y se encarga de contar la cantidad de usuarios almacenados 
        int DeterminarNumeroUsuarios() {
            ifstream archivo("Datos Usuarios.txt", ios::in);
            if (!archivo.is_open()) {
                cout << "--------------------------" << endl;
                cout << "Error al Abrir el Archivo." << endl;
                cout << "--------------------------" << endl;
            }
            int contador = 0;
            string linea = "";
            while (getline(archivo, linea)) {
                contador++;
            }
            return contador;
        }

        //------------------------CARGAR DATOS----------------------------------------
        // Método para agregar usuarios y escribir los datos en el archivo
        void AgregarUsuario() {
            ofstream archivo("Datos Usuarios.txt", ios::app);
            int usuariosActivos = DeterminarNumeroUsuarios();

            (!archivo.is_open()) ? cout << "Error al momento de escribir en el archivo" << endl : cout << endl;

            if (usuariosActivos > 10) {
                cout << "-----------------------------------------------------------------------------"<< endl;
                cout << "La Cantidad De Personas Excede El Máximo. Por Favor Eliminar Algunas Personas" << endl;
                cout << "-----------------------------------------------------------------------------"<< endl;
                return;
            }

            cout << "Usuarios Activos: " << usuariosActivos << endl;
            cout << "Agregar Usuario" << endl << endl;
            fflush(stdin);
            cout << "Ingrese su nombre: ";
            getline(cin, _nombre);
            fflush(stdin);
            cout << "Ingrese su cédula: ";
            cin >> _cedula;
            fflush(stdin);
            cout << "Ingrese su dirección: ";
            getline(cin, _direccion);

            archivo << _cedula << ":" << _nombre << ":" << _direccion << ":N_0" << "\n";
            archivo.close();
            cout << "Usuario Agregado con éxito" << endl;
        }

        //------------------------MODIFICAR DATOS------------------------------------
        // Método para modificar los datos en el archivo preguntando los datos a cambiar y accediendo a dichos datos
        void ModificarUsuario() {
            ifstream archivo("Datos Usuarios.txt", ios::in);
            ofstream temp("Temp.txt", ios::out);
            string linea;
            string cedulaBuscar;
            bool encontrado = false;
            string DatoViejo;
            string nuevo, lineaCambio;

            fflush(stdin);
            cout << "Ingrese la cédula para modificar los datos: ";
            cin >> cedulaBuscar;

            // Leer el archivo y buscar la cédula
            while (getline(archivo, linea)) {
                char* lineaChar = const_cast<char*>(linea.c_str());
                char* cedula = strtok(lineaChar, ":");
                if (cedula == cedulaBuscar) {
                    setCedula(atoi(cedula));
                    cout << "Datos encontrados" << endl << endl;
                    cout << "Cédula: " << getCedula() << endl;
                    setNombre(strtok(NULL, ":"));
                    cout << "Nombre: " << getNombre() << endl;
                    setDireccion(strtok(NULL, ":"));
                    cout << "Dirección: " << getDireccion() << endl;
                    encontrado = true;
                }
            }

            if (!encontrado) {
                cout << "Registro no encontrado." << endl;
                archivo.close();
                temp.close();
                return;
            }

            int opcion;
            cout << "\n¿Qué dato desea modificar?\n1. Cédula\n2. Nombre\n3. Dirección\nOpción: ";
            cin >> opcion;

            fflush(stdin);
            cout << "Ingrese el nuevo valor: ";
            cin >> nuevo;

            if (nuevo == "") {
                cout << "No puedes agregar un valor vacío a los datos. Por favor intentar más tarde" << endl;
                return;
            }

            if (opcion == 1) {
                DatoViejo = getCedula();
            } else if (opcion == 2) {
                DatoViejo = getNombre();
            } else if (opcion == 3) {
                DatoViejo = getDireccion();
            }

            archivo.clear();
            archivo.seekg(0);

            while (getline(archivo, lineaCambio)) {
                size_t posicion = lineaCambio.find(DatoViejo);
                if (posicion != string::npos) {
                    lineaCambio.replace(posicion, DatoViejo.length(), nuevo);
                }
                temp << lineaCambio << "\n";
            }

            archivo.close();
            temp.close();

            remove("Datos Usuarios.txt");
            rename("Temp.txt", "Datos Usuarios.txt");

            cout << (encontrado ? "Registro Modificado." : "Registro no encontrado.") << endl;
        }

        //------------------------CONSULTAR DATOS-------------------------------------
        // Método que muestra en consola los datos del usuario
        void ConsultarUsuario() {
            string cedulaBuscada;
            string linea;
            fstream archivo("Datos Usuarios.txt", ios::in);
            bool band = false;

            fflush(stdin);
            cout << "Digite la Cédula a Buscar: ";
            getline(cin, cedulaBuscada);

            while (getline(archivo, linea)) {
                char* lineaChar = const_cast<char*>(linea.c_str());
                char* cedula = strtok(lineaChar, ":");
                if (cedula == cedulaBuscada) {
                    cout << "Datos del Usuario" << endl;
                    cout << "Nombre: " << strtok(NULL, ":") << endl;
                    cout << "Cédula: " << cedula << endl;
                    cout << "Dirección: " << strtok(NULL, ":") << endl;
                    band = true;
                    break;
                }
            }

            if (!band) {
                cout << "No se ha encontrado ningún usuario con esa cédula. Por favor intentar más tarde" << endl;
            }
        }

        //------------------------ELIMINAR DATOS--------------------------------------
        void EliminarUsuario() {
            string cedulaBuscada;
            string linea;
            fstream archivo("Datos Usuarios.txt", ios::in);
            ofstream temp("temp.txt", ios::out);
            bool encontrado = false;

            fflush(stdin);
            cout << "Digite la Cédula a Buscar: ";
            getline(cin, cedulaBuscada);

            while (getline(archivo, linea)) {
                char* lineaChar = const_cast<char*>(linea.c_str());
                char* cedula = strtok(lineaChar, ":");

                if (cedulaBuscada != cedula) {
                    temp << linea << "\n";
                } else {
                    encontrado = true;
                }
            }

            archivo.close();
            temp.close();

            remove("Datos Usuarios.txt");
            rename("temp.txt", "Datos Usuarios.txt");

            cout << (encontrado ? "Registro eliminado." : "Registro no encontrado.") << endl;
        }

        //-----------------------ACTUALIZAR USO DE LA APLICACIÓN-----------------------
        void actualizarUsoApp(string cedula) {
            fstream archivo("Datos Usuarios.txt", ios::in);
            fstream temp("temp.txt", ios::out);
            string linea;
            string cedulaOri, NombreOri, DireccionOri, NVeces, NVecesFinal = "N_0";
            bool band = false;

            while (getline(archivo, linea)) {
                stringstream ss(linea);
                getline(ss, cedulaOri, ':');
                getline(ss, NombreOri, ':');
                getline(ss, DireccionOri, ':');
                getline(ss, NVeces, ':');

                if (cedula == cedulaOri) {
                    stringstream ss2(NVeces);
                    string token;
                    getline(ss2, token, '_');
                    string numero;
                    getline(ss2, numero, '_');

                    int numeroVeces = atoi(numero.c_str());
                    numeroVeces++;

                    ostringstream oss;
                    oss << "N_" << numeroVeces;
                    NVecesFinal = oss.str();

                    band = true;
                    linea.replace(linea.find(NVeces), NVeces.length(), NVecesFinal);
                }

                temp << linea << endl;
            }

            archivo.close();
            temp.close();

            remove("Datos Usuarios.txt");
            rename("temp.txt", "Datos Usuarios.txt");

            cout << (band ? "Este Usuario ha usado la aplicacion con exito." : "El Usuario no se ha encontrado.") << endl;
        }
};
#endif

