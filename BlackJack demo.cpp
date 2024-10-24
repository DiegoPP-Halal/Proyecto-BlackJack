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

void repartoInicial (Pila &mazo, string mesa[][10]) {
    mesa[0][0]=mazo.pop();
    mesa[1][0]=mazo.pop();
    mesa[0][1]=mazo.pop();
    mesa[1][1]=mazo.pop();
}
// Función para mostrar la mano de un jugador
void mostrarMano(string jugador[], int numCartas, const string &nombreJugador) {
    cout << nombreJugador << " tiene: ";
    for (int i = 0; i < numCartas; i++) {
        cout << jugador[i] << " ";
    }
    cout << endl;
}

// Función para calcular el puntaje de las cartas
int calcularPuntaje(string jugador[], int numCartas) {
    int puntaje = 0;
    int ases = 0; // Contador de Ases

    for (int i = 0; i < numCartas; i++) {
        string carta = jugador[i];
        char valor = carta[carta.size() - 1]; // Obtener el último carácter para saber el valor

        // Cartas numéricas
        if (valor >= '2' && valor <= '9') {
            puntaje += valor - '0'; // Convertir carácter numérico a entero
        }
        // Cartas 10, J, Q, K valen 10
        else if (valor == '1' || valor == 'J' || valor == 'Q' || valor == 'K') {
            puntaje += 10;
        }
        // As
        else if (valor == 'A') {
            ases++;
            puntaje += 11; // El As inicialmente vale 11
        }
    }

    // Si hay Ases y el puntaje es mayor a 21, restar 10 por cada As hasta que no se pase de 21
    while (puntaje > 21 && ases > 0) {
        puntaje -= 10;
        ases--;
    }

    return puntaje;
}

int main() {
    string mesa[2][10]; //fila 1 es para el jugador, la fila 2 para el crupier.
    Pila mazo;  
    string mazoinicial = "123456789JQKA";  // Las cartas numeradas y letras
    vector<string> simbolos = {"Diamantes", "Tréboles", "Corazones", "Picas"};  
    bool jugar = true;
    int opcion, partida = 2, turno = 0, conteo_pedir = 0;
    
    while (jugar == true) {
        cout<< "       BLACKJACK"<<endl<<endl;
        cout<<"1. Jugar."<<endl;
        cout<<"2. Salir del juego."<<endl;
        cin>>opcion;
        switch(opcion) {
            case 1:
                
                while (partida == 2) {
                    mazo.clearScreen();
                    revolver(mazo, mazoinicial, simbolos);
                    repartoInicial(mazo, mesa);
                    while (turno == 0){
                        cout<<"         Crupier"<<endl;
                        cout<<  mesa[1][0]<<"  ";
                        if (conteo_pedir == 0){
                            cout<<" Carta oculta."<<endl;
                        }
                        else{
                            cout<<mesa[1][1]<<endl;
                        }
                        cout<<"         Jugador"<<endl;
                        cout<<  mesa[0][0]<<"  "<<mesa[0][1]<<endl<<endl;
                        
                        // Mostrar puntaje de los jugadores 
                        string jugador[2] = {mesa[0][0], mesa[0][1]};
                        string crupier[2] = {mesa[1][0], mesa[1][1]};  //Problema: Al incrementar las cartas no se puede almacenar en los vectores jugador y crupier.

                        int puntajeJugador = calcularPuntaje(jugador, 2);
                        int puntajeCrupier = calcularPuntaje(crupier, 2);

                        cout << "Puntaje del Jugador: " << puntajeJugador << endl;
                        cout << "Puntaje del Crupier (visible): " << calcularPuntaje(crupier, 1) << endl << endl;
                        
                        cout<<"1. Pedir carta."<<endl;
                        cout<<"2. Doblar apuesta. "<<endl;
                        cout<<"3. Terminar turno. "<<endl;
                        cin>>turno;
                    }
                    
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

