int calcularPuntaje(const string cartas[], int numCartas) {
    int puntaje = 0;
    int ases = 0; // Contador de Ases

    for (int i = 0; i < numCartas; i++) {
        char valor = cartas[i][1]; // Obtener el valor de la carta
        if (valor >= '2' && valor <= '9') {
            puntaje += valor - '0'; // Convertir el carácter a entero
        } else if (valor == '1' || valor == 'J' || valor == 'Q' || valor == 'K') {
            puntaje += 10;
        } else if (valor == 'A') {
            puntaje += 11; // Contar el As como 11 inicialmente
            ases++; // Contar el número de Ases
        }
    }

    // Ajustar puntaje si hay Ases y se pasa de 21
    while (puntaje > 21 && ases > 0) {
        puntaje -= 10; // Cambiar un As de 11 a 1
        ases--;
    }

    return puntaje;
}

void mostrarPuntajes(string mesa[][10]) {
    int puntajeJugador = calcularPuntaje(mesa[0], 2); // Suponiendo que el jugador empieza con 2 cartas
    int puntajeCrupier = calcularPuntaje(mesa[1], 2); // Suponiendo que el crupier empieza con 2 cartas
    
    cout << "Puntaje del Jugador: " << puntajeJugador << endl;
    cout << "Puntaje del Crupier: " << puntajeCrupier << endl;
}
