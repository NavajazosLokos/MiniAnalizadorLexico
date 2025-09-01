#include "lexico.h"

Lexico::Lexico(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico() {
    ind = 0;
}

string Lexico::tipoAcad(int tipo) {
    switch(tipo) {
        case TipoSimbolo::IDENTIFICADOR: return "identificador";
        case TipoSimbolo::ENTERO: return "entero";
        case TipoSimbolo::REAL: return "real";
        case TipoSimbolo::CADENA: return "cadena";
        case TipoSimbolo::TIPO: return "tipo";
        case TipoSimbolo::OPSUMA: return "opSuma";
        case TipoSimbolo::OPMUL: return "opMul";
        case TipoSimbolo::OPRELAC: return "opRelac";
        case TipoSimbolo::OPOR: return "opOr";
        case TipoSimbolo::OPAND: return "opAnd";
        case TipoSimbolo::OPNOT: return "opNot";
        case TipoSimbolo::OPIGUALDAD: return "opIgualdad";
        case TipoSimbolo::PTCOMA: return ";";
        case TipoSimbolo::COMA: return ",";
        case TipoSimbolo::PARIZQ: return "(";
        case TipoSimbolo::PARDER: return ")";
        case TipoSimbolo::LLAVEIZQ: return "{";
        case TipoSimbolo::LLAVEDER: return "}";
        case TipoSimbolo::IGUAL: return "=";
        case TipoSimbolo::IF: return "if";
        case TipoSimbolo::WHILE: return "while";
        case TipoSimbolo::RETURN: return "return";
        case TipoSimbolo::ELSE: return "else";
        case TipoSimbolo::FIN: return "$";
        default: return "Error";
    }
}

void Lexico::entrada(string fuente) {
    ind = 0;
    this->fuente = fuente;
}

char Lexico::sigCaracter() {
    if (terminado()) return '$';
    return fuente[ind++];
}

bool Lexico::terminado() {
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c) {
    return isalpha(c) || c == '_';
}

bool Lexico::esDigito(char c) {
    return isdigit(c);
}

bool Lexico::esEspacio(char c) {
    return c == ' ' || c == '\t';
}

void Lexico::retroceso() {
    if (c != '$') ind--;
    continua = false;
}

void Lexico::sigEstado(int estado) {
    this->estado = estado;
    simbolo += c;
}

void Lexico::aceptacion(int t) {
    tipo = t;
    sigEstado(0); // solo para agregar el carácter al simbolo
    continua = false;
}

// Diccionario de palabras reservadas
unordered_map<string,int> palabrasReservadas = {
    {"if", TipoSimbolo::IF},
    {"while", TipoSimbolo::WHILE},
    {"return", TipoSimbolo::RETURN},
    {"else", TipoSimbolo::ELSE},
    {"int", TipoSimbolo::TIPO},
    {"float", TipoSimbolo::TIPO},
    {"void", TipoSimbolo::TIPO}
};

int Lexico::sigSimbolo() {
    simbolo = "";
    estado = 0;
    continua = true;

    while(continua) {
        c = sigCaracter();

        switch(estado) {
            case 0:
                if(esEspacio(c)) break;
                else if(c == '+' || c == '-') aceptacion(TipoSimbolo::OPSUMA);
                else if(c == '*' || c == '/') aceptacion(TipoSimbolo::OPMUL);
                else if(c == ';') aceptacion(TipoSimbolo::PTCOMA);
                else if(c == ',') aceptacion(TipoSimbolo::COMA);
                else if(c == '(') aceptacion(TipoSimbolo::PARIZQ);
                else if(c == ')') aceptacion(TipoSimbolo::PARDER);
                else if(c == '{') aceptacion(TipoSimbolo::LLAVEIZQ);
                else if(c == '}') aceptacion(TipoSimbolo::LLAVEDER);
                else if(c == '=') {
                    char next = sigCaracter();
                    if(next == '=') { simbolo += next; aceptacion(TipoSimbolo::OPIGUALDAD); } 
                    else { retroceso(); aceptacion(TipoSimbolo::IGUAL); }
                }
                else if(c == '!') {
                    char next = sigCaracter();
                    if(next == '=') { simbolo += next; aceptacion(TipoSimbolo::OPIGUALDAD); } 
                    else { aceptacion(TipoSimbolo::OPNOT); }
                }
                else if(c == '<' || c == '>') {
                    char next = sigCaracter();
                    if(next == '=') { simbolo += next; aceptacion(TipoSimbolo::OPRELAC); }
                    else { retroceso(); aceptacion(TipoSimbolo::OPRELAC); }
                }
                else if(c == '&') {
                    char next = sigCaracter();
                    if(next == '&') { simbolo += next; aceptacion(TipoSimbolo::OPAND); }
                }
                else if(c == '|') {
                    char next = sigCaracter();
                    if(next == '|') { simbolo += next; aceptacion(TipoSimbolo::OPOR); }
                }
                else if(esLetra(c)) {
                    sigEstado(0);
                    while(esLetra(c) || esDigito(c)) { 
                        c = sigCaracter();
                        if(!esLetra(c) && !esDigito(c)) { retroceso(); break; }
                        simbolo += c;
                    }
                    if(palabrasReservadas.find(simbolo) != palabrasReservadas.end())
                        tipo = palabrasReservadas[simbolo];
                    else
                        tipo = TipoSimbolo::IDENTIFICADOR;
                    continua = false;
                }
                else if(esDigito(c)) {
                    sigEstado(0);
                    tipo = TipoSimbolo::ENTERO;
                    simbolo += c;
                    bool esReal = false;
                    while(true) {
                        c = sigCaracter();
                        if(esDigito(c)) { simbolo += c; }
                        else if(c == '.' && !esReal) { simbolo += c; esReal = true; tipo = TipoSimbolo::REAL; }
                        else { retroceso(); break; }
                    }
                    continua = false;
                }
                else if(c == '$') { aceptacion(TipoSimbolo::FIN); }
                else { tipo = TipoSimbolo::ERROR; continua = false; }
                break;
        }
    }
    return tipo;
}
