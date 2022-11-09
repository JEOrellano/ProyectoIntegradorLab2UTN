#include "Servicio.h"
#include "Archivo.h"
#include <iostream>
#include <cstdio>

using namespace std;

Servicio::Servicio(){
    codigo = 0;
    precio = 1;
    strcpy(descripcion, "SIN DATO");
    estado = false;
}

bool Servicio::cargar(int var){
    int pre;
    codigo = var;
    gotoxy (38, 18);
    cout << "DESCRIPCION: ";
    gotoxy (43, 20);
    cout << "PRECIO: ";
    gotoxy(51,18);
    cargarCadena(descripcion,29);
    if(validarCadena(descripcion)==false){
        rlutil::hidecursor();
        gotoxy (29, 22);
        cout << "ERROR, INGRESAR SOLO CARACTERES ALFABETICOS";
        return false;
    }
    gotoxy(51,20);
    cin >> pre;
    if(setPrecio(pre)==false){
        gotoxy (35, 22);
        rlutil::hidecursor();
        cout << "EL PRECIO NO PUEDE SER NEGATIVO" << endl;
        return false;
    }
    estado = true;
    return true;
}

bool Servicio::mostrar(int var){
    if(estado==true){
        gotoxy(32,21+var);
        cout << codigo << endl;
        gotoxy(44,21+var);
        cout << descripcion << endl;
        gotoxy(63,21+var);
        cout << precio << endl;
        return true;
    }
    return false;
}

/// SETS

void Servicio::setCodigo(int var){codigo = var;}
bool Servicio::setPrecio(float var){
    if(var>0){
        precio = var;
        return true;
    }
    return false;
}
void Servicio::setDescripcion(const char *V){strcpy(descripcion,V);}
void Servicio::setEstado(bool ban){estado = ban;}

/// GETS

int Servicio::getCodigo(){return codigo;}
float Servicio::getPrecio(){return precio;}
const char *Servicio::getDescripcion(){return descripcion;}
bool Servicio::getEstado(){return estado;}
