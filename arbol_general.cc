#include <iostream>
#include <string>

// Máximo número de hijos por nodo
const int MAX_HIJOS = 3;

// Estructura que almacena los datos de cada nodo
struct Datos {
    int id;
    std::string nombre;
};

// Estructura para los nodos del árbol general
struct Nodo {
    Datos dato;                   // Datos almacenados en el nodo
    Nodo* hijos[MAX_HIJOS];       // Arreglo de punteros a los hijos
    int num_hijos;                // Contador de hijos actuales

    // Constructor para inicializar el nodo
    Nodo(int id, std::string nombre) {
        dato.id = id;
        dato.nombre = nombre;
        num_hijos = 0;
        for (int i = 0; i < MAX_HIJOS; ++i) {
            hijos[i] = nullptr;
        }
    }
};

// Función para crear un nuevo nodo
Nodo* CrearNodo(int id, std::string nombre) {
    Nodo* nuevo_nodo = new Nodo(id, nombre);
    return nuevo_nodo;
}

// Función para agregar hijos a un nodo
void AgregarHijo(Nodo* padre, Nodo* hijo) {
    if (padre->num_hijos < MAX_HIJOS) {
        padre->hijos[padre->num_hijos] = hijo;
        padre->num_hijos++;
    } else {
        std::cout << "No se pueden agregar más hijos a este nodo (máximo " << MAX_HIJOS << " hijos)." << std::endl;
    }
}

// Función para recorrer el árbol en Preorden (Nodo -> Hijos)
void PreOrden(Nodo* raiz, int nivel = 0) {
    if (raiz != nullptr) {
        // Imprimir el nodo actual
        std::cout << std::string(nivel * 2, '-') << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;

        // Recorrer recursivamente los hijos
        for (int i = 0; i < raiz->num_hijos; ++i) {
            PreOrden(raiz->hijos[i], nivel + 1);
        }
    }
}

// Función para recorrer el árbol en Inorden (Izquierda -> Nodo -> Derecha)
void InOrden(Nodo* raiz, int nivel = 0) {
    if (raiz != nullptr) {
        // Recorrer el primer hijo (izquierda)
        if (raiz->num_hijos > 0) {
            InOrden(raiz->hijos[0], nivel + 1);
        }

        // Imprimir el nodo actual
        std::cout << std::string(nivel * 2, '-') << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;

        // Recorrer el resto de los hijos (derecha)
        for (int i = 1; i < raiz->num_hijos; ++i) {
            InOrden(raiz->hijos[i], nivel + 1);
        }
    }
}

// Función para recorrer el árbol en Postorden (Hijos -> Nodo)
void PostOrden(Nodo* raiz, int nivel = 0) {
    if (raiz != nullptr) {
        // Recorrer recursivamente los hijos
        for (int i = 0; i < raiz->num_hijos; ++i) {
            PostOrden(raiz->hijos[i], nivel + 1);
        }

        // Imprimir el nodo actual
        std::cout << std::string(nivel * 2, '-') << "ID: " << raiz->dato.id << ", Nombre: " << raiz->dato.nombre << std::endl;
    }
}

int main() {
    // Creación del nodo raíz
    int id_raiz;
    std::string nombre_raiz;

    std::cout << "Ingrese el ID del nodo raíz: ";
    std::cin >> id_raiz;
    std::cin.ignore();  // Limpiar el buffer del cin
    std::cout << "Ingrese el nombre del nodo raíz: ";
    std::getline(std::cin, nombre_raiz);

    Nodo* raiz = CrearNodo(id_raiz, nombre_raiz);

    // Crear hijos para el nodo raíz
    for (int i = 0; i < MAX_HIJOS; ++i) {
        int id_hijo;
        std::string nombre_hijo;

        std::cout << "\nIngrese el ID del hijo " << (i + 1) << " de la raíz: ";
        std::cin >> id_hijo;
        std::cin.ignore();
        std::cout << "Ingrese el nombre del hijo " << (i + 1) << " de la raíz: ";
        std::getline(std::cin, nombre_hijo);

        Nodo* hijo = CrearNodo(id_hijo, nombre_hijo);
        AgregarHijo(raiz, hijo);

        // Preguntar si se desea agregar hijos a este hijo
        char respuesta;
        std::cout << "¿Desea agregar hijos al nodo " << nombre_hijo << "? (s/n): ";
        std::cin >> respuesta;
        std::cin.ignore();

        if (respuesta == 's' || respuesta == 'S') {
            for (int j = 0; j < MAX_HIJOS; ++j) {
                int id_nieto;
                std::string nombre_nieto;

                std::cout << "Ingrese el ID del hijo " << (j + 1) << " de " << nombre_hijo << ": ";
                std::cin >> id_nieto;
                std::cin.ignore();
                std::cout << "Ingrese el nombre del hijo " << (j + 1) << " de " << nombre_hijo << ": ";
                std::getline(std::cin, nombre_nieto);

                Nodo* nieto = CrearNodo(id_nieto, nombre_nieto);
                AgregarHijo(hijo, nieto);
            }
        }
    }

    // Mostrar los recorridos
    std::cout << "\nRecorrido en Preorden:\n";
    PreOrden(raiz);

    std::cout << "\nRecorrido en Inorden:\n";
    InOrden(raiz);

    std::cout << "\nRecorrido en Postorden:\n";
    PostOrden(raiz);

    return 0;
}
