#include "LengthValidator.h"
#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "ClassicFeedback.h"
#include "FeedbackStrategy.h"
#include "Game.h"
#include "DictionaryValidator.h"
#include <iostream>
#include "ValidatorExceptions.h"
#include "WordleFactory.h"
/* Zagan Claudiu Gabriel - Grupa 133.

Modificari TEMA 3 :

1. CLASA TEMPLATE:
       - Am transformat clasa AlphabetValidator intr-o clasa template:
         AlphabetValidator<T>, unde T este o colectie de caractere permise
         (in cazul nostru, std::unordered_set<char>).
       - Clasa permite acum validarea pe baza unui set personalizat de caractere.
       - Am adaugat si o functie membru care verifica daca un caracter este permis,
         precum si operatorul << pentru afisare.

    2. SINGLETON:
       - Clasa Game a fost modificata pentru a respecta design pattern-ul Singleton.
       - Acum exista o singura instanta a jocului, accesibila prin Game::getInstance().
       - Constructorul Game este privat, iar instanta este gestionata static.

    3. FACTORY METHOD:
       - Am adaugat clasa WordleFactory, care construieste si returneaza
         o instanta completa de Game pregatita pentru rulare.
       - Aceasta fabrica automat validatori, incarca un cuvant random
         din dictionar si configureaza jocul cu un numar standard de incercari.
       - Factory-ul simplifica foarte mult codul din main() si permite
         testarea rapida sau rularea directa a jocului.
*/




int main()
{
    try
    {
        Game& joc = WordleFactory::createDefaultGame();
        // Folosit pentru a arata utilizatorului Regulile in functie de care trebuie alese cuvintele.
        joc.printValidatorTypes();
        // Rulam jocul
        joc.play();
    }
    catch (const ValidatorExceptions& e) { // upcasting
        std::cerr << "Exceptie prinsa in main: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Alta exceptie: " << e.what() << std::endl;
    }
    return 0;
}
