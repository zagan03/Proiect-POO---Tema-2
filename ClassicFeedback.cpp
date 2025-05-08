#include "ClassicFeedback.h"
#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>



std::string ClassicFeedback::toLowerCase(const std::string& word)
{
    std::string result = word;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    // std::transform(start, end, destination_start, function);
    return result;
}

// Coloreaza literele in consola - functie statica
static void printColoredChar(char ch, WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // primesti acces la consola
    SetConsoleTextAttribute(hConsole, color);
    std::cout << ch;
    Sleep(500); // efect de animatie;
    SetConsoleTextAttribute(hConsole, 7); // reset la culoarea default (gri deschis)
}


// Functie care reda feedbackul utilizatorului asupra inputului sau
// Aceasta functie se ocupa si de cazul in care un utilizator a introdus aceeasi litera intr-un cuvant, colorand litera
// de atatea ori de cate apare in cuvant.


std::string ClassicFeedback::getFeedback(const std::string &input, const std::string &answer) const
{

    std::unordered_map<char,int> Aparitii;
    for (char ch : answer)
        {
        Aparitii[ch]++; // vector de frecventa
        }

    for (unsigned int i = 0; i < input.size(); i++)
        {
        if (input[i] == answer[i] && Aparitii[input[i]] > 0)
        {
            printColoredChar(input[i], FOREGROUND_GREEN | FOREGROUND_INTENSITY); // verde
            Aparitii[input[i]]--;
        }
        else if (answer.find(input[i]) != std::string::npos && Aparitii[input[i]] > 0)
        {
            printColoredChar(input[i], FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // galben
            Aparitii[input[i]]--;
        }
        else
        {
            printColoredChar(input[i], FOREGROUND_INTENSITY); // gri
        }
    }
    std::cout << '\n';
    return "";
}
// stocam numarul de aparitii al unei litere si dupa ne folosim de el ca sa stim cate litere
// din acel fel poate avea cuvantul colorate cu galben/verde