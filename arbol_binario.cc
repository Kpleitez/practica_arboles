#include <iostream>
#include <string>

// Estructura que almacena los datos de cada nodo
struct Datos {
    int id;
    std::string nombre;
};

// Estructura para los nodos del árbol
struct Nodo {
    Datos dato;        // Datos almacenados en el nodo
    Nodo* izquierda;   // Puntero al hijo izquierdo
    Nodo* derecha;     // Puntero al hijo derecho
};

// Función para insertar un nodo en el árbol
Nodo* Insertar(Nodo* raiz, Datos nuevo_dato) {
    if (raiz == nullptr) {
        Nodo* nuevo_nodo = new Nodo();
        nuevo_nodo->dato = nuevo_dato;
        nuevo_nodo->izquierda = nullptr;
        nuevo_nodo->derecha = nullptr;
        return nuevo_nodo;
    }

    if (nuevo_dato.id < raiz->dato.id) {
        raiz->izquierda = Insertar(raiz->izquierda, nuevo_dato);
    } else {
        raiz->derecha = Insertar(raiz->derecha, nuevo_dato);
    }

    return raiz;
}

// Función para buscar un nodo en el árbol
bool Buscar(Nodo* raiz, int id) {
    if (raiz == nullptr) {
        return false;
    }

    if (raiz->dato.id == id) {
        return true;
    }

    if (id < raiz->dato.id) {
        return Buscar(raiz->izquierda, id);
    } else {
        return Buscar(raiz->derecha, id);
    }
}

// Funciones para los recorridos del árbol
void InOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        InOrden(raiz->izquierda);
        std::cout << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;
        InOrden(raiz->derecha);
    }
}

void PreOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        std::cout << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;
        PreOrden(raiz->izquierda);
        PreOrden(raiz->derecha);
    }
}

void PostOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        PostOrden(raiz->izquierda);
        PostOrden(raiz->derecha);
        std::cout << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;
    }
}

// Función para eliminar un nodo del árbol
Nodo* EncontrarMin(Nodo* nodo) {
    while (nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

Nodo* Eliminar(Nodo* raiz, int id) {
    if (raiz == nullptr) {
        return raiz;
    }

    if (id < raiz->dato.id) {
        raiz->izquierda = Eliminar(raiz->izquierda, id);
    } else if (id > raiz->dato.id) {
        raiz->derecha = Eliminar(raiz->derecha, id);
    } else {
        if (raiz->izquierda == nullptr && raiz->derecha == nullptr) {
            delete raiz;
            raiz = nullptr;
        } else if (raiz->izquierda == nullptr) {
            Nodo* temp = raiz;
            raiz = raiz->derecha;
            delete temp;
        } else if (raiz->derecha == nullptr) {
            Nodo* temp = raiz;
            raiz = raiz->izquierda;
            delete temp;
        } else {
            Nodo* temp = EncontrarMin(raiz->derecha);
            raiz->dato = temp->dato;
            raiz->derecha = Eliminar(raiz->derecha, temp->dato.id);
        }
    }
    return raiz;
}

// Programa principal
int main() {
    Nodo* raiz = nullptr;
    int numNodos;

    std::cout << "¿Cuántos nodos deseas insertar en el árbol? ";
    std::cin >> numNodos;

    // Solicitar al usuario que ingrese los datos de cada nodo
    for (int i = 0; i < numNodos; i++) {
        Datos d;
        std::cout << "Ingrese el ID del nodo " << (i + 1) << ": ";
        std::cin >> d.id;
        std::cin.ignore();  // Ignorar el salto de línea después del ID
        std::cout << "Ingrese el nombre asociado al nodo " << (i + 1) << ": ";
        std::getline(std::cin, d.nombre);

        raiz = Insertar(raiz, d);
    }

    // Mostrar los recorridos del árbol
    std::cout << "\nRecorrido Inorden:" << std::endl;
    InOrden(raiz);

    std::cout << "\nRecorrido Preorden:" << std::endl;
    PreOrden(raiz);

    std::cout << "\nRecorrido Postorden:" << std::endl;
    PostOrden(raiz);

    // Buscar un nodo
    int idBuscar;
    std::cout << "\nIngrese el ID del nodo que desea buscar: ";
    std::cin >> idBuscar;

    if (Buscar(raiz, idBuscar)) {
        std::cout << "El nodo con ID " << idBuscar << " fue encontrado." << std::endl;
    } else {
        std::cout << "El nodo con ID " << idBuscar << " no fue encontrado." << std::endl;
    }

    // Eliminar un nodo
    int idEliminar;
    std::cout << "\nIngrese el ID del nodo que desea eliminar: ";
    std::cin >> idEliminar;

    raiz = Eliminar(raiz, idEliminar);

    std::cout << "\nRecorrido Inorden después de eliminar el nodo con ID " << idEliminar << ":" << std::endl;
    InOrden(raiz);

    return 0;
}

