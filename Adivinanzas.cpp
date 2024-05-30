#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;
using namespace sf;

int main() {
    // Inicializar la semilla del generador de números aleatorios
    srand(static_cast<unsigned int>(std::time(nullptr)));
    int numero_secreto = std::rand() % 100 + 1;
    int intento;
    int numero_de_intentos = 0;

    // Crear la ventana
    RenderWindow window(VideoMode(800, 600), "Juego de Adivinanza de Numeros");

    // Configurar la fuente y el texto
    Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        return -1;
    }

    Text promptText("Adivina un numero entre 1 y 100:", font, 24);
    promptText.setPosition(20, 20);
    
    
    //Lo que pone el usuario
    Text inputText("", font, 24);
    inputText.setPosition(20, 60);

    //Mensaje para cuando el usuario pone el numero
    Text feedbackText("", font, 24);
    feedbackText.setPosition(20, 100);

    string input;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
            	//Verificamos si hemos insertado un número si lo hemos hecho se actualiza el texto en pantalla
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    input += static_cast<char>(event.text.unicode);
                    inputText.setString(input);
                //Si el usuario usa \b es decir borra un caracter lo actualizamos, es decir lo quitamos de input    
                } else if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                    inputText.setString(input);
                //Si pulsa enter pues se ejecuta la adivinanza    
                } else if (event.text.unicode == '\r' && !input.empty()) {
                    intento = stoi(input);
                    numero_de_intentos++;
                    if (intento > numero_secreto) {
                        feedbackText.setString("Demasiado alto. Intenta nuevamente.");
                    } else if (intento < numero_secreto) {
                        feedbackText.setString("Demasiado bajo. Intenta nuevamente.");
                    } else {
                        stringstream ss;
                        ss << "¡Felicidades! Adivinaste el numero en " << numero_de_intentos << " intentos.";
                        feedbackText.setString(ss.str());
                    }
                    input.clear();
                    inputText.setString("");
                }
            }
        }

        window.clear();
        window.draw(promptText);
        window.draw(inputText);
        window.draw(feedbackText);
        window.display();
    }

    return 0;
}

