#ifndef FUNCIONESCLIENTES_H_INCLUDED
#define FUNCIONESCLIENTES_H_INCLUDED

#include <iostream>

using namespace std;

/// PROTOTIPOS FUNCIONES GLOBALES CLIENTE

int agregarRegistroCliente();
    Cliente cargarCliente();
    bool validarCliente(int nD);

bool modificarTelefonoCliente();
    int buscarIdCliente(int idC);

void mostrarClientes();
    void cargarArchivoEnVector(Cliente *obj, int cantReg);
    void mostrarVectorClientes(Cliente *obj, int cantReg);

void eliminarCliente();

bool mostrarClientePorId();

/// DEFINICIONES FUNCIONES GLOBALES CLIENTE

// 1 AGREGA REGISTROS CLIENTES  AL ARCHIVO Clientes.dat

int agregarRegistroCliente(){
    Cliente usuario;
    Archivo archi;
    Cuadro cuadroClienteCarga;
    cuadroClienteCarga.setCoor({26,17});
    cuadroClienteCarga.setalto(13);
    cuadroClienteCarga.setlargo(48);
    cuadroClienteCarga.dibujar();
    rlutil::showcursor();
    usuario = cargarCliente();
    rlutil::hidecursor();
    if(usuario.getEstado() == false){ // ERROR DNI O APERTURA DEL ARCHIVO
        return -1;
    }
    if(archi.grabarEnDisco(usuario)){ // GRABO EN DISCO
        gotoxy(42, 26);
        cout << "CLIENTE CARGADO";
        agregarCuentaCliente(usuario);
        return 0;
    }
    gotoxy(42, 26);
    cout << "FALLO AL GRABAR EN EL DISCO";
    return -2; // FALLO GRABAR EN DISCO
}

Cliente cargarCliente(){
    Cliente usuario;
    int nD;
    int idC;
    Archivo archi;
    gotoxy(40, 19);
    cout << "DNI CLIENTE: ";
    cin >> nD;
    if(validarCliente(nD) == true){
        gotoxy(32, 24);
        cout << "EL CLIENTE INGERSADO ESTA REGISTRADO";
        usuario.setEstado(false);
        return usuario;
    }
    idC = archi.contarRegistro(usuario); // ESTE SERIA PK AUTOINCREMENTAL DE CLIENTE
    if(idC == -1){
        gotoxy(38, 21);
        cout << "FALLO APERTURA DEL ARCHIVO";
        usuario.setEstado(false);
        return usuario;
    }
    idC++;
    usuario.Cargar(nD, idC);
    return usuario;
}

bool validarCliente(int nD){
    Cliente usuario;
    Archivo archi;
    int pos = 0;
    while(archi.leerDeDisco(pos, usuario)){
        if(nD == usuario.getDNI() && usuario.getEstado() == true){
            return usuario.getEstado();
        }
        pos++;
    }
    return false;
}

// 2 MODIFICA POR DNI LOS REGISTROS DE CLIENTES DEL ARCHIVO Clientes.dat

bool modificarTelefonoCliente(){
    Archivo archi;
    Cliente usuario;
    int idC, pos;
    char nT[40];
    Cuadro cuadroClienteModificar;
    cuadroClienteModificar.setCoor({26,17});
    cuadroClienteModificar.setalto(10);
    cuadroClienteModificar.setlargo(48);
    cuadroClienteModificar.dibujar();
    /// buscar el cliente a modificar telefono
    rlutil::showcursor();
    gotoxy(33, 19);
    cout << "ID CLIENTE A MODIFICAR TELEFONO: ";
    cin >> idC;
    // leer si existe el cliente
    pos = buscarIdCliente(idC);
    if(pos == -1){
        rlutil::hidecursor();
        gotoxy(31, 23);
        cout << "NO EXISTE EL ID DE CLIENTE EN EL ARCHIVO";
        return false;
    }
    archi.leerDeDisco(pos, usuario);
    // cambiar telefono del cliente
    gotoxy(32, 21);
    cout << "INGRESE EL NUEVO TELEFONO: ";
    cargarCadena(nT, 39);
    usuario.setTelefono(nT);
    // sobrescribir el registro
    rlutil::hidecursor();
    gotoxy(42, 24);
    cout << "CLIENTE MODIFICADO";
    return archi.modificarEnDisco(pos, usuario);
}

int buscarIdCliente(int idC){
    Archivo archi;
    Cliente usuario;
    int pos = 0;
    while(archi.leerDeDisco(pos, usuario)){
        if(idC == usuario.getIdCuenta()){
            if(usuario.getEstado()){
                return pos;
            }
        }
        pos++;
    }
    return -1;
}

// 3 MUESTRA LOS REGISTROS DE CLIENTES DEL ARCHIVO Clientes.dat

void mostrarClientes(){
    Archivo archi;
    Cliente usuario;
    int cant;
    Cliente *usuarioD;

    if((cant = archi.contarRegistro(usuario)) == 0){
        gotoxy(38, 20);
        cout << "NO HAY CLIENTES REGISTRADOS";
        return;
    }
    usuarioD = new Cliente[cant];
    if(usuarioD == NULL){
        gotoxy(38, 20);
        cout << "ERROR DE ASIGNACION DE MEMORIA" << endl;
        return;
    }
    cargarArchivoEnVector(usuarioD, cant);
    mostrarVectorClientes(usuarioD, cant);
    delete []usuarioD;
}

void cargarArchivoEnVector(Cliente *obj, int cantReg){
    Archivo archi;
    int i;
    for(i = 0; i < cantReg; i++){
        archi.leerDeDisco(i, obj[i]);
    }
}

void mostrarVectorClientes(Cliente *obj, int cantReg){
    Cuadro listaCliente;
    listaCliente.setCoor({20, 16});
    listaCliente.setlargo(60);
    listaCliente.setalto(40);
    listaCliente.dibujarLista();
    int i, posY = 0;
    gotoxy(27, 17);
    cout << "ID";
    gotoxy(37, 17);
    cout << "NOMBRE";
    gotoxy(54, 17);
    cout << "APELLIDO";
    gotoxy(68, 17);
    cout << "TELEFONO";
    for(i = 0; i < cantReg; i++){
        if(posY > 18){
            getch();
            posY = 0;
            while(posY <= 18){
                gotoxy(22, 19 + posY * 2);
                cout << "                            |                             ";
                posY++;
            }
            posY = 0;
        }
        if(obj[i].getEstado() == true){
            gotoxy(27, 19 + posY * 2);
            cout << obj[i].getIdCuenta();
            gotoxy(37, 19 + posY * 2);
            cout << obj[i].getNombre();
            gotoxy(54, 19 + posY * 2);
            cout << obj[i].getApellido();
            gotoxy(68, 19 + posY * 2);
            cout << obj[i].getTelefono();
            posY++;
        }
    }
}

// 4 ELIMINAR CLIENTE

void eliminarCliente(){
    Archivo archi;
    Cliente usuario;
    Cuadro cuadroClienteBorrar;
    cuadroClienteBorrar.setCoor({27,17});
    cuadroClienteBorrar.setalto(13);
    cuadroClienteBorrar.setlargo(46);
    cuadroClienteBorrar.dibujar();
    int idC, pos;
    /// buscar el cliente a eliminar
    rlutil::showcursor();
    gotoxy(38, 19);
    cout << "ID DEL CLIENTE A BORRAR: ";
    cin >> idC;
    /// leer si existe el registro
    rlutil::hidecursor();
    pos = buscarIdCliente(idC);
    if(pos == -1){
        gotoxy(30, 23);
        cout << "NO EXISTE EL ID DEL CLIENTE EN EL ARCHIVO";
        return;
    }
    archi.leerDeDisco(pos, usuario);
    /// Validar cuenta corriente deuda o no
    if(eliminarCuentaCliente(usuario.getIdCuenta()) == false){
        gotoxy(35, 23);
        cout << "NO SE PUEDE ELIMINAR, TIENE DEUDA";
        return;
    }
    /// cambiar el estado del campo
    usuario.setEstado(false);
    /// sobreescribir el registro
    archi.modificarEnDisco(pos, usuario);
    gotoxy(42, 22);
    cout << "CLIENTE BORRADO ";
    gotoxy(42, 25);
    cout << usuario.getNombre() << " " << usuario.getApellido();
}

// 5 MUESTRAR POR DNI LOS REGISTROS DE CLIENTES DEL ARCHIVO Clientes.dat

bool mostrarClientePorId(){
    Archivo archi;
    Cliente usuario;
    int idC, pos;
    Cuadro cuadroClienteMostarId;
    cuadroClienteMostarId.setCoor({27,17});
    cuadroClienteMostarId.setalto(12);
    cuadroClienteMostarId.setlargo(46);
    cuadroClienteMostarId.dibujar();
    /// buscar el cliente a mostrar
    rlutil::showcursor();
    gotoxy(36, 19);
    cout << "ID DEL CLIENTE A MOSTRAR: ";
    cin >> idC;
    /// leer si existe el cliente
    rlutil::hidecursor();
    pos = buscarIdCliente(idC);
    if(pos == -1){
        gotoxy(30, 23);
        cout << "NO EXISTE EL ID DE CLIENTE EN EL ARCHIVO";
        return false;
    }
    archi.leerDeDisco(pos, usuario);
    /// LISTAR EL CLIENTE FILTRADO
    usuario.Mostrar();
    return true;
}

#endif // FUNCIONESCLIENTES_H_INCLUDED
