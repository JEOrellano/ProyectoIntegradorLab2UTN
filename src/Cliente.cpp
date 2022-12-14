#include "Cliente.h"
#include <iostream>
using namespace std;

Cliente::Cliente()
{
    DNI = 0;
    strcpy(nombre, "SIN DATO");
    strcpy(apellido, "SIN DATO");
    strcpy(telefono, "SIN DATO");
    strcpy(email, "SIN DATO");
    idCuenta = 0;
    estado = false;
}

/// CARGAR
bool Cliente::Cargar(int nD, int idC){
    if(!setDNI(nD)){
        rlutil::hidecursor();
        gotoxy(37, 22);
        cout << " El DNI DEBE SER POSITIVO" << endl;
        gotoxy(34, 24);
        cout << " DEBE TENER COMO MINIMO 7 DIGITOS" << endl;
        return false;
    }
    gotoxy(40, 21);
    cout << "NOMBRE: ";
    gotoxy(40, 22);
    cout << "APELLIDO: ";
    gotoxy(40, 23);
    cout << "TELEFONO: ";
    gotoxy(40, 24);
    cout << "EMAIL: ";
    gotoxy(48, 21);
    rlutil::showcursor();
    cargarCadena(nombre, 29);
    if(validarCadena(nombre)==false){
        gotoxy (29, 27);
        cout << "ERROR, INGRESAR SOLO CARACTERES ALFABETICOS";
        return false;
    }
    setNombre(nombre);
    gotoxy(50, 22);
    cargarCadena(apellido, 29);
    if(validarCadena(apellido)==false){
        gotoxy (29, 27);
        cout << "ERROR, INGRESAR SOLO CARACTERES ALFABETICOS";
        return false;
    }
    setApellido(apellido);
    gotoxy(50, 23);
    cargarCadena(telefono, 39);
    setTelefono(telefono);
    gotoxy(47, 24);
    cargarCadena(email, 39);
    if(!setEmail(email)){
        rlutil::hidecursor();
        gotoxy(38, 26);
        cout << "EL EMAIL DEBE TENER . Y @" << endl;
        return false;
    }
    setEmail(email);
    rlutil::hidecursor();
    setIdCuenta(idC);

    estado = 1;
    setEstado(estado);
    return true;
}

void Cliente::Mostrar()
{
    if(estado){
        gotoxy(42, 21);
        cout << "DNI: " << DNI;
        gotoxy(42, 22);
        cout << "NOMBRE: " << nombre;
        gotoxy(42, 23);
        cout << "APELLIDO: " << apellido;
        gotoxy(42, 24);
        cout << "TELEFONO: " << telefono;
        gotoxy(42, 25);
        cout << "EMAIL: " << email;
        gotoxy(42, 26);
        cout << "ID CUENTA: " << idCuenta;
    }
}

/// SETS
bool Cliente::setDNI(int nD){
    if(nD > 1000000){
        DNI = nD;
        return true;
    }
    return false;
}
void Cliente::setNombre(const char *nom){strcpy(nombre, nom);}
void Cliente::setApellido(const char *ape){strcpy(apellido, ape);}
void Cliente::setTelefono(const char *tel){strcpy(telefono, tel);}
bool Cliente::setEmail(const char *e){
    int contPunto = 0, i;
    bool contArroba = false;
    for(i = 0; i < strlen(e); i++){
        if(e[i] == '.'){
            contPunto++;
        }
        if(e[i] == '@'){
            contArroba = true;
        }
    }
    if(contPunto == 0){
        return false;
    }
    else{
        if(contArroba == true){
            strcpy(email, e);
            return true;

        }
    }
    return false;
}
void Cliente::setIdCuenta(int idC){idCuenta = idC;}
void Cliente::setEstado(bool e){estado = e;}

/// GETS
int Cliente::getDNI(){return DNI;}
const char *Cliente::getNombre(){return nombre;}
const char *Cliente::getApellido(){return apellido;}
const char *Cliente::getTelefono(){return telefono;}
const char *Cliente::getEmail(){return email;}
int Cliente::getIdCuenta(){return idCuenta;}
bool Cliente::getEstado(){return estado;}
