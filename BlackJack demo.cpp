#include <iostream>
#include <algorithm> // Para usar random_shuffle (revolver)
#include <cstdlib>   // Para usar system() y srand()
#include <ctime>     // Para usar time() (que no se repita el mazo revuelto)
#include <limits>    // Para la validación de la variable opción (pending)
#include <vector>    // Para usar vector en lugar de arrays

#ifdef _WIN32
    #include <windows.h> // Para Windows
#endif

using namespace std;

class Pila {
    public:
        string ARREGLO[52];  // La pila tendrá 52 cartas (mazo completo)
        int top = -1;
        
        // Método para agregar un elemento
        void push(string n) {
            if (top != 51) {
                ARREGLO[++top] = n;
            } else {
                cout << "Tope alcanzado." << endl << endl;
            }
        }
        
        // Método para eliminar un elemento
        string pop() {
            string d;
            if (top != -1) {
                d = ARREGLO[top--];
            } else {
                d = "-1";  // Regresamos una cadena vacía si la pila está vacía
            }
            return d;
        }
        
        // Método para contar el número de elementos
        int count() {
            return top + 1;
        }

        // Método para ver el último elemento sin eliminarlo
        string peek() {
            string d;
            if (top != -1) {
                d = ARREGLO[top];
            } else {
                d = "-1";
            }
            return d;
        }

        // Método para verificar si la pila está vacía
        bool isEmpty() {
            return (top == -1);
        }

        // Método para verificar si la pila está llena
        bool isFull() {
            return (top == 51);
        }

        // Método para mostrar todas las cartas en la pila
        void MostrarTodo() {
            if (isEmpty()) {
                cout << "La pila está vacía." << endl;
                return;
            }
            for (int i = 0; i <= top; i++) {
                cout << ARREGLO[i] << endl;
            }
        }

        // Método para limpiar la pantalla según el sistema operativo
        void clearScreen() {
            #ifdef _WIN32
                system("cls"); // Comando para limpiar pantalla en Windows
            #else
                system("clear"); // Comando para limpiar pantalla en Unix (Linux/MacOS)
            #endif
        }
};

// Función para revolver el mazo
void revolver(Pila &mazo, string &mazoinicial, vector<string> &simbolos) {
    while (!mazo.isEmpty()) {
        mazo.pop();
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            string carta = simbolos[i] + " " + mazoinicial[j];  // Concatenar símbolo y número/letra
            mazo.push(carta);  // Añadir carta al mazo
        }
    }

    // Inicializar el generador de números aleatorios con una semilla basada en el tiempo
    srand(time(0));

    // Mezclar todo el mazo
    random_shuffle(mazo.ARREGLO, mazo.ARREGLO + 52);
}

void repartoInicial (Pila &mazo, Pila &crupier, Pila &Jugador) {
    Jugador.push(mazo.pop());
    crupier.push(mazo.pop());
    Jugador.push(mazo.pop());
    crupier.push(mazo.pop());
}

int main() {
    Pila crupier;
    Pila Jugador;
    Pila mazo;  
    string mazoinicial = "123456789JQKA";  // Las cartas numeradas y letras
    vector<string> simbolos = {"Diamantes", "Tréboles", "Corazones", "Picas"};  
    bool jugar = true;
    int opcion, levantarse = 2;
    
    while (jugar == true) {
        cout<< "       BLACKJACK"<<endl<<endl;
        cout<<"1. Jugar."<<endl;
        cout<<"2. Salir del juego."<<endl;
        cin>>opcion;
        switch(opcion) {
            case 1:
                
                while (levantarse == 2) {
                    revolver(mazo, mazoinicial, simbolos);
                    cout << mazo.peek() << endl;
                    cout << "prueba: " << endl;
                    cin >> levantarse;
                }
                break;
            case 2:
                jugar = false;
                break;
        }
    }

    /**
        Por hacer: las funciones de las reglas del black jack, valores de las cartas y la visualización de la mesa.
        reglas a implementar: 
            -El jugador gana si tiene mayor puntaje que el crupier y menos que 22.
            -El jugador gana con 5 cartas si la suma es menor a 22.
            -El dealer debe plantarse en 17.
            -Las apuestas se hacen antes de empezar a jugar. Excepción: doblar la apuesta.
            -El dealer mantiene una carta oculta hasta que sea su turno.
        Valores:
            -J,Q and K valen 11. A puede valer 1 u 11.
    **/
    return 0;
}


