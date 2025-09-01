#ifndef _LEXICO
#define _LEXICO

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
using namespace std;

class TipoSimbolo {
public:
    enum {
        ERROR = -1,
        IDENTIFICADOR = 0,
        ENTERO = 1,
        REAL = 2,
        CADENA = 3,
        TIPO = 4,         // int, float, void
        OPSUMA = 5,       // + -
        OPMUL = 6,        // * /
        OPRELAC = 7,      // < <= > >=
        OPOR = 8,         // ||
        OPAND = 9,        // &&
        OPNOT = 10,       // !
        OPIGUALDAD = 11,  // == !=
        PTCOMA = 12,      // ;
        COMA = 13,        // ,
        PARIZQ = 14,      // (
        PARDER = 15,      // )
        LLAVEIZQ = 16,    // {
        LLAVEDER = 17,    // }
        IGUAL = 18,       // =
        IF = 19,
        WHILE = 20,
        RETURN = 21,
        ELSE = 22,
        FIN = 23          // $
    };
};

class Lexico {
private:
    string fuente;
    int ind;
    bool continua;
    char c;
    int estado;

    char sigCaracter();
    void sigEstado(int estado);
    void aceptacion(int t);
    bool esLetra(char c);
    bool esDigito(char c);
    bool esEspacio(char c);
    void retroceso();

public:
    string simbolo;
    int tipo;

    Lexico(string fuente);
    Lexico();

    void entrada(string fuente);
    string tipoAcad(int tipo);
    int sigSimbolo();
    bool terminado();
};

#endif

