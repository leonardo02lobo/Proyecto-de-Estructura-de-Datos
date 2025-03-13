#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Usuario
{
private:
    int _cedula;
    string _nombre;
    string _direccion;

public:
    Usuario()
    {
        _cedula = 0;
        _nombre = "";
        _direccion = "";
    }

    Usuario(int cedula, string nombre, string direccion)
    {
        this->_cedula = cedula;
        this->_nombre = nombre;
        this->_direccion = direccion;
    }

    void setCedula(int cedula)
    {
        this->_cedula = cedula;
    }

    void setNombre(string nombre)
    {
        this->_nombre = nombre;
    }

    void setDireccion(string direccion)
    {
        this->_direccion = direccion;
    }

    int getCedula()
    {
        return this->_cedula;
    }

    string getNombre()
    {
        return this->_nombre;
    }

    string getDireccion()
    {
        return this->_direccion;
    }

    int DeterminarNumeroUsuarios()
    {
        ifstream archivo("Datos Usuarios.txt", ios::in);
        if (!archivo.is_open())
        {
            cout << "--------------------------" << endl;
            cout << "Error al Abrir el Archivo." << endl;
            cout << "--------------------------" << endl;
            return 0;
        }
        int contador = 0;
        string linea = "";
        while (getline(archivo, linea))
        {
            contador++;
        }
        return contador;
    }

    void AgregarUsuario()
    {
        ofstream archivo("Datos Usuarios.txt", ios::app);
        int usuariosActivos = DeterminarNumeroUsuarios();

        (!archivo.is_open()) ? cout << "Error al momento de escribir en el archivo" << endl : cout << endl;

        if (usuariosActivos > 10)
        {
            cout << "-----------------------------------------------------------------------------" << endl;
            cout << "La Cantidad De Personas Excede El Maximo. Por Favor Eliminar Algunas Personas" << endl;
            cout << "-----------------------------------------------------------------------------" << endl;
            return;
        }

        cout << "Numero de Usuarios Almacenados: " << usuariosActivos << endl;
        cout << "Agregar Usuario" << endl
             << endl;
        fflush(stdin);
        cout << "Ingrese su nombre: ";
        getline(cin, _nombre);
        fflush(stdin);
        cout << "Ingrese su cedula: ";
        cin >> _cedula;
        fflush(stdin);
        cout << "Ingrese su direccion: ";
        getline(cin, _direccion);

        archivo << _cedula << ":" << _nombre << ":" << _direccion << ":N_0" << "\n";
        archivo.close();
        cout << "Usuario Agregado con exito" << endl;
    }

    void ModificarUsuario()
    {
        ifstream archivo("Datos Usuarios.txt", ios::in);
        ofstream temp("Temp.txt", ios::out);

        string cedulaBuscar;
        string DatoViejo;
        string nuevo, lineaCambio;
        bool encontrado = false;
        fflush(stdin);
        cout << "Ingrese la cedula para modificar los datos: ";
        cin >> cedulaBuscar;

        Usuario usuario = separarDatos(archivo, cedulaBuscar, encontrado);

        if (!encontrado)
        {
            cout << "Registro no encontrado." << endl;
            archivo.close();
            temp.close();
            return;
        }

        int opcion;
        cout << "\nQue dato desea modificar?\n1. Cedula\n2. Nombre\n3. Direccion\nOpcion: ";
        cin >> opcion;

        fflush(stdin);
        cout << "Ingrese el nuevo valor: ";
        cin >> nuevo;

        if (nuevo == "")
        {
            cout << "No puedes agregar un valor vacio a los datos. Por favor intentar mas tarde" << endl;
            return;
        }

        if (opcion == 1)
        {
            DatoViejo = usuario.getCedula();
        }
        else if (opcion == 2)
        {
            DatoViejo = usuario.getNombre();
        }
        else if (opcion == 3)
        {
            DatoViejo = usuario.getDireccion();
        }

        archivo.clear();
        archivo.seekg(0);

        while (getline(archivo, lineaCambio))
        {
            size_t posicion = lineaCambio.find(DatoViejo);
            if (posicion != string::npos)
            {
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

    void ConsultarUsuario()
    {
        string cedulaBuscada;
        string linea;
        ifstream archivo("Datos Usuarios.txt", ios::in);
        bool band = false;

        fflush(stdin);
        cout << "Digite la Cedula a Buscar: ";
        getline(cin, cedulaBuscada);

        separarDatos(archivo, cedulaBuscada, band);

        if (!band)
        {
            cout << "No se ha encontrado ningun usuario con esa cedula. Por favor intentar mas tarde" << endl;
        }
    }

    void EliminarUsuario()
    {
        string cedulaBuscada;
        string linea;
        fstream archivo("Datos Usuarios.txt", ios::in);
        ofstream temp("temp.txt", ios::out);
        bool encontrado = false;

        fflush(stdin);
        cout << "Digite la Cedula a Buscar: ";
        getline(cin, cedulaBuscada);

        while (getline(archivo, linea))
        {
            char *lineaChar = const_cast<char *>(linea.c_str());
            char *cedula = strtok(lineaChar, ":");

            if (cedulaBuscada != cedula)
            {
                temp << linea << "\n";
            }
            else
            {
                encontrado = true;
            }
        }

        archivo.close();
        temp.close();

        remove("Datos Usuarios.txt");
        rename("temp.txt", "Datos Usuarios.txt");

        cout << (encontrado ? "Registro eliminado." : "Registro no encontrado.") << endl;
    }

    void actualizarUsoApp(string cedula)
    {
        fstream archivo("Datos Usuarios.txt", ios::in);
        fstream temp("temp.txt", ios::out);
        string linea;
        string cedulaOri, NombreOri, DireccionOri, NVeces, NVecesFinal = "N_0";
        bool band = false;

        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            getline(ss, cedulaOri, ':');
            getline(ss, NombreOri, ':');
            getline(ss, DireccionOri, ':');
            getline(ss, NVeces, ':');

            if (cedula == cedulaOri)
            {
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

private:
    Usuario separarDatos(ifstream &archivo, string cedulaBuscar, bool &encontrado)
    {
        string linea;
        string cedulaOri, NombreOri, DireccionOri, NVeces;
        Usuario usuario;

        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            getline(ss, cedulaOri, ':');
            getline(ss, NombreOri, ':');
            getline(ss, DireccionOri, ':');
            usuario.setCedula(atoi(cedulaOri.c_str()));
            usuario.setNombre(NombreOri);
            usuario.setDireccion(DireccionOri);

            if (cedulaOri == cedulaBuscar)
            {
                cout << "Datos encontrados" << endl
                     << endl;
                cout << "Cedula: " << getCedula() << endl;
                cout << "Nombre: " << getNombre() << endl;
                cout << "Direccion: " << getDireccion() << endl;
                encontrado = true;
                return usuario;
            }
        }
        return usuario;
    }
};
#endif