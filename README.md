## Tema 2 - Wordle - Joc de ghicit cuvinte din 5 litere

### Descriere Generala
  Proiectul abordeaza un joc in linia de comanda unde utilizatorul trebuie sa ghiceasca un cuvant secret format
din 5 litere. Cuvintele sunt validate pe baza unor reguli, iar utilizatorul primeste feedback dupa fiecare 
incercare, cu privire la pozitiile literelor.

### Cum se joaca ?
1. La inceputul jocului, se genereaza automat un cuvant secret de 5 litere dintr-un dictionar care se afla in 
fisierul tastatura.txt.
2. Utilizatorul are 6 incercari pentru a ghici acest cuvant, iar scorul maxim pe care il poate obtine este 120.
3. Dupa fiecare incercare:
   - daca cuvantul introdus nu este valid (nu are 5 litere, contine caractere invalide sau nu exista in dictionar)
     utilizatorul va primi o eroare si va putea incerca din nou.
   - daca este valid, va primi feedback in stilul wordle-ului original, spre exemplu, cu verde vor fi afisate literele
   aflate pe pozitiile lor, cu galben literele care se regasesc in cuvant, dar care nu sunt pe pozitia lor
   corecta, iar cu gri, literele care nu se afla in cuvant.
4. Jocul se termina fie cand cuvantul este ghicit in limita a celor 6 incercari, fie cand se epuizeaza toate 
incercarile.

### Reguli de validare a cuvintelor :
1. Cuvantul trebuie sa aiba exact 5 litere. (LengthValidator)
2. Cuvantul trebuie sa contina doar litere ale alfabetului englez. (AlphabetValidator)
3. Cuvintele trebuie sa se regaseasca intr-un dictionar valid, adica cel din fisierul "tastatura.txt". (DictionaryValidator)


#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [ ] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level

### Indeplinire cerinte:
- **Clase mostenite**:
  - 'WordValidator' = clasa abstracta de baza ce cuprinde validatorii cuvantului introdus de catre utilizator.
    - Derivate : 'LengthValidator' = valideaza lungimea cuvantului ( lungimea trebuie sa fie egala cu 5).
                                   = ca si date membru, avem requiredLength = lungimea necesara si defaultLength care este un atribut static ce reprezinta lungimea 'default' cu care este initializat obiectul de tip LengthValidator.
                 'AlphabetValidator' = valideaza caracterele cuvantului (caracterele trebuie sa fie litere ale alfabetului englez a-z sau A-Z).
                 'DictionaryValidator' = verifica daca cuvantul introdus de utilizator se afla in dictionarul limbii romane ( care este definit in fisierul tastatura.txt).
                                       = ca si data membru, avem un vector 'dictionar' in care sunt stocate cuvintele din dictionarul jocului.
  - 'FeedbackStrategy' = clasa abstracta de baza care cuprinde strategia de feedback, si anume, modalitatea de afisare a corectitudinii inputului introdus de utilizator.
                 'ClassicFeedback' = clasa derivata care se foloseste pentru feedback-ul in linia de comanda. Mai exact, literele colorate cu verde sunt la locul potrivit, literele 
                                     colorate cu galben se afla in cuvant, dar nu pe pozitia corespunzatoare, iar literele gri nu se regasesc in cuvant.
                                   = regasim aici doua functii: toLowerCase() care este statica si transforma literele in litere mici, precum si functia getFeedback() care ofera utilizatorului feedback-ul vizual al cuvantului 
                                     introdus prin colorarea literelor in functie de regulile specificate mai sus.
- **Functii virtuale**
  - 'validate() este functie pur virtuala in 'WordValidator', redefinita in fiecare derivata si este apelata 
    polimorfic in main() printr-un 'std::vector<std::unique_ptr<WordValidator>>'.
  - functia getFeedback() este functie pur virtuala in 'FeedbackStrategy', redefinita in derivata ClassicFeedback
    si cuprinde logica feedback-ului oferit utilizatorului la fiecare input introdus.
  - am implementat in clasa de baza (WordValidator) o functie non-virtuala functiePrintare() care apeleaza metoda virtuala pura printDetails() ce permite utilizarea
  polimorfismului. se poate apela functiePrintare() pe un pointer la WordValidator, iar printDetails() va fi rezolvata corect în funcție de tipul obiectului derivat 
  (ex: LengthValidator, DictionaryValidator, etc.).

- **Constructori virtuali (clone)**
  - fiecare validator implementeaza un clone() care returneaza un 'std::unique_ptr<WordValidator>'
  - am folosit in main() la linia `validators.emplace_back(dict->clone());` pentru a adauga DictionaryValidator in vectorul de unique_ptr validators, 
  iar nevoia de clonare vine de la faptul ca nu putem muta un unique_ptr.

- **Pointerii la clasa de bază vor fi atribute ale altei clase, nu doar niște pointeri/referințe în main** :
  - in cadrul clasei Game, am utilizat un vector de unique_ptr<WordValidator> care stocheaza obiecte de tipuri derivate din WordValidator. Astfel, acesti pointeri
  - sunt atribute ale clasei Game.

- **Apel constructor de baza**
  - derivatele apeleaza constructorul de baza WordValidator cu parametri comuni

- **Pointer de baza cu functie virtuala**
  - in clasa Game, folosesc un `std::vector<std::unique_ptr<WordValidator>>` pentru a stoca validatorii si a apela  functia virtuala `validate()`.

- **`dynamic_cast`**:
  - in functia `printValidatorTypes()` din clasa `Game`, folosesc `dynamic_cast` pentru a realiza downcasting din clasa de baza `WordValidator` catre clasele derivate. Acest mecanism imi permite sa identific dinamic tipul fiecarui validator,
  stocat in vectorul validators, astfel incat sa pot afisa pe ecran utilizatorului regulile specifice fiecarui validator.
  - de asemenea, pentru clasa Game, am implementat:
    - constructori de copiere
    - operatorul copy and swap =  este folosit in functia `play()` din `Game` pentru a oferi utilizatorului sanse noi de a ghici cuvantul, ca si runde bonus.
                               =  in momentul in care utilizatorul a ramas fara sanse de a ghici cuvantul, este intrebat daca doreste sa mai incerce, iar in caz afirmativ, 
                                  prin operatorul copy and swap, se creeaza o copie a jocului curent, permitand utilizatorului sa joace in continuare fara a crea o instanta complet noua de joc.
 
- **Smart pointers**:
  - `std::unique_ptr` este folosit pentru gestionarea dinamica a validatorilor.

- **Exceptii**:
  - clasa `ValidatorExceptions` derivă din `std::exception`.
    - derivatele AlphabetValidatorException, LengthValidatorException, DictionaryValidatorException sunt prinse in 
    functia Game::play(), caz in care se poate reintroduce inputul mai departe de catre utilizator.
    - metoda `what()` este suprascrisa pentru a returna un mesaj personalizat de eroare, care poate fi afisat cu std::cerr << e.what(); 
  - in main avem cele trei exceptii:
    - throw ValidatorExceptions("Cuvantul din dictionar nu are 5 litere!" + cuvantAles) = exceptie care are loc in cazul in care se genereaza un cuvant din dictionar cu lungime < 5.
    - throw ValidatorExceptions("Lista de validatori este goala. Nu putemm continua jocul") = exceptie care are loc in cazul in care dictionarul este gol.
    - throw EmptyDictionaryException("Fisierul " + filename + " nu contine cuvinte valide.") = care este prinsa in main la generarea dictionarului din fisierul `tastatura.txt` cand fisierul nu poate fi deschis.

- **functii si atribute `static`**:
  - Ex: `WordChecker::isValidChar()` este funcție `static`, Game::score() este functie 'static',
  - Game::printRemainingAttempts() este functie 'static'.
  - size_t LengthValidator::defaultLength = 5 este atribut 'static'.

- **STL**:
  - `std::vector`, `std::string`, `std::ifstream`, `std::random`, `std::unordered_set`, `std::memory`, `std::algorithm`,
  - `std::unordered_map`, `std::random`

- **`const`**:
  - Metodele `validate()`, `clone()` si altele sunt declarate `const`.
  - Parametrii transmiși prin `const &` unde este cazul.

- **Nivel înalt, fără getters/setters inutile**:
  - functiile de validare si feedback sunt centralizate si nu expun datele interne inutil.


#### Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.




## Bibliografie

- https://github.com/mcmarius/poo/tree/master/tema-2
- https://cplusplus.com/reference/algorithm//
- https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
- https://www.youtube.com/watch?v=L14j5RZO0ok
- https://www.youtube.com/watch?v=UOB7-B2MfwA&t=303s
- https://www.listedecuvinte.com/cuvinte5literepagina4.htm - folosit pentru preluarea cuvintelor.
- https://wordly.org/ - jocul original dupa care m-am inspirat.