#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

class Pila {
public:
    string ARREGLO[52];
    int top = -1;

    void push(string n) {
        if (top != 51) {
            ARREGLO[++top] = n;
        } else {
            cout << "Tope alcanzado." << endl << endl;
        }
    }

    string pop() {
        string d;
        if (top != -1) {
            d = ARREGLO[top--];
        } else {
            d = "-1";
        }
        return d;
    }

    int count() {
        return top + 1;
    }

    string peek() {
        return (top != -1) ? ARREGLO[top] : "-1";
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == 51);
    }
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int solicitarOpcion(const string& mensaje, int min, int max) {
    int opcion;
    while (true) {
        cout << mensaje;
        cin >> opcion;
        if (cin.fail() || opcion < min || opcion > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            cout << "Opción inválida. Por favor, ingrese un número entre ";
            cout << min << " y " << max << "." << endl << endl;
        } else {
            return opcion;
        }
    }
}

void revolver(Pila &mazo, string &mazoinicial, vector<string> &simbolos) {
    while (!mazo.isEmpty()) {
        mazo.pop();
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            string carta = simbolos[i] + " " + mazoinicial[j];
            mazo.push(carta);
        }
    }

    srand(time(0));
    random_shuffle(mazo.ARREGLO, mazo.ARREGLO + 52);
}

void repartoInicial(Pila &mazo, vector<string> &jugador, vector<string> &crupier) {
    jugador.push_back(mazo.pop());
    jugador.push_back(mazo.pop());
    crupier.push_back(mazo.pop());
    crupier.push_back(mazo.pop());
}

int calcularPuntaje(vector<string> &mano) {
    int puntaje = 0, ases = 0;
    for (string carta : mano) {
        char valor = carta[carta.size() - 1];
        if (valor >= '2' && valor <= '9') {
            puntaje += valor - '0';
        } else if (valor == '1' || valor == 'J' || valor == 'Q' || valor == 'K') {
            puntaje += 10;
        } else if (valor == 'A') {
            ases++;
            puntaje += 11;
        }
    }
    while (puntaje > 21 && ases > 0) {
        puntaje -= 10;
        ases--;
    }
    return puntaje;
}

void turnoDealer(Pila &mazo, vector<string> &crupier) {
    while (calcularPuntaje(crupier) <= 16) {
        crupier.push_back(mazo.pop());
    }
}

void mostrarMano(vector<string> &mano, string nombre, bool mostrarTodas = true) {
    cout << nombre << ": ";
    for (size_t i = 0; i < mano.size(); i++) {
        if (!mostrarTodas && i == 1) {
            cout << "Carta oculta ";
        } else {
            if (mano[i].back() == '1') {
                cout << mano[i] << "0   ";  
            } else {
                cout << mano[i] << "   ";
            }
        }
    }
    cout << endl << endl;
}

int main() {
    Pila mazo;
    string mazoinicial = "123456789JQKA";
    vector<string> simbolos = {"Diamantes", "Tréboles", "Corazones", "Picas"};
    bool jugar = true;
    int dinero = 1000;
    int apuesta;

    while (jugar) {
        cout << "       BLACKJACK\n\n";
        cout << "Dinero actual: $" << dinero << endl;

        int opcion = solicitarOpcion("1. Jugar.\n2. Salir del juego. ", 1, 2);
        cout<<endl;
        if (opcion == 2) {
            jugar = false;
            break;
        }

        clearScreen();
        revolver(mazo, mazoinicial, simbolos);

        vector<string> jugador, crupier;
        repartoInicial(mazo, jugador, crupier);

        cout << "Ingrese su apuesta: ";
        cin >> apuesta;
        if (apuesta > dinero || apuesta <= 0) {
            cout << "Apuesta inválida.\n";
            continue;
        }

        bool turnoJugador = true;
        while (turnoJugador) {
            
            mostrarMano(crupier, "Crupier", false);
            mostrarMano(jugador, "Jugador");

            int puntajeJugador = calcularPuntaje(jugador);
            cout << "Puntaje del Jugador: " << puntajeJugador << endl << endl;

            if (puntajeJugador > 21) {
                cout << "Te pasaste de 21. Pierdes la apuesta.\n";
                dinero -= apuesta;
                turnoJugador = false;
                break;
            }

            cout << "1. Pedir carta.\n2. Terminar turno.\n3. Doblar (aumentar la apuesta y recibir solo una carta).\n";
            int eleccion;
            cin >> eleccion;

            if (cin.fail() || eleccion < 1 || eleccion > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opción inválida. Por favor, intente de nuevo.\n";
                continue; // Repite la iteración, mostrando nuevamente las manos.
            }

            if (eleccion == 1) { // Pedir carta
                jugador.push_back(mazo.pop());
            } else if (eleccion == 2) { // Terminar turno
                turnoJugador = false;
            } else if (eleccion == 3) { // Doblar
                // Verificar si el jugador tiene suficiente dinero para duplicar la apuesta
                if (apuesta * 2 <= dinero) {
                    apuesta *= 2; // Doblar la apuesta
                    jugador.push_back(mazo.pop()); // Recibir una carta
                    cout << "Has doblado tu apuesta a $" << apuesta << ".\n";
                    turnoJugador = false; // Terminar el turno
                } else {
                    clearScreen();
                    cout << "No tienes suficiente dinero para doblar tu apuesta. Tu apuesta es de $" << apuesta << " y necesitas otros $" << apuesta << " para hacerlo.\n";
                    continue; // Repite la iteración, mostrando nuevamente las manos.
                }
            }
        }

        if (calcularPuntaje(jugador) <= 21) {
            turnoDealer(mazo, crupier);
            mostrarMano(crupier, "Crupier");

            int puntajeJugador = calcularPuntaje(jugador);
            int puntajeCrupier = calcularPuntaje(crupier);

            cout << "Puntaje del Crupier: " << puntajeCrupier << endl;
            if (puntajeCrupier > 21 || puntajeJugador > puntajeCrupier) {
                cout << endl << endl << "¡Ganaste! Ganas $" << apuesta << ".\n";
                dinero += apuesta;
            } else if (puntajeJugador < puntajeCrupier) {
                cout << endl << endl << "Perdiste. Pierdes $" << apuesta << ".\n";
                dinero -= apuesta;
            } else {
                cout << endl << endl << "Empate. Recuperas tu apuesta.\n";
            }
        }

        if (dinero <= 0) {
            clearScreen();
            cout << "Te quedaste sin dinero. Fin del juego.\n";
            jugar = false;
        }
    }

    return 0;
}
