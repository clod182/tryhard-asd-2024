#include "insieme.hpp"
#include <vector>
#include <iostream>

constexpr int hashsize = 8;
constexpr int hashaux = 5;

using namespace std;

// Struttura che rappresenta un nodo della lista concatenata
struct Elem {
    int info;       // Valore dell'elemento
    Elem* succ;     // Puntatore al nodo successivo
};

typedef Elem* PElem; // Puntatore a un nodo

// Implementazione interna della classe Insieme
struct Insieme::Impl {
    vector<PElem> content; // Vettore di liste concatenate (bucket della tabella hash)
    int numelementi;       // Numero totale di elementi nell'insieme
};

// Funzione hash che calcola il bucket in base al valore
int funHash(int val) {
    return val % hashsize; // Ritorna l'indice del bucket (val modulo hashsize)
}

/* Costruttore: crea un insieme vuoto */
Insieme::Insieme() {
    pimpl = new Impl;
    pimpl->numelementi = 0;
    for (size_t i = 0; i < hashsize; i++) {
        pimpl->content.push_back(nullptr); // Ogni bucket è inizialmente vuoto
    }
}

/* Costruttore di copia: crea un insieme copiando un altro */
Insieme::Insieme(const Insieme& set) {
    pimpl = new Impl;
    pimpl->numelementi = set.pimpl->numelementi; // Copia il numero di elementi

    for (size_t i = 0; i < hashsize; i++) {
        PElem elem = set.pimpl->content[i]; // Ottiene la lista del bucket corrente

        if (elem) { // Se esiste almeno un elemento
            PElem new_head = new Elem{elem->info, nullptr};
            pimpl->content.push_back(new_head); // Crea il nuovo nodo iniziale

            while (elem->succ) { // Copia i nodi successivi
                new_head->succ = new Elem{elem->succ->info, nullptr};
                new_head = new_head->succ;
                elem = elem->succ;
            }
        } else {
            pimpl->content.push_back(nullptr); // Il bucket è vuoto
        }
    }
}

/* Distruttore: libera tutta la memoria dinamica */
Insieme::~Insieme() {
    for (size_t i = 0; i < hashsize; i++) {
        PElem elem_to_delete = pimpl->content[i];

        // Cancella tutti i nodi della lista concatenata
        while (elem_to_delete) {
            PElem succ_to_delete = elem_to_delete->succ;
            delete elem_to_delete; // Dealloca il nodo corrente
            elem_to_delete = succ_to_delete;
        }
    }
    delete pimpl; // Dealloca la struttura Impl
}

/* Inserisce un elemento nell'insieme, se non già presente */
void Insieme::inserisci(int val) {
    if (!contiene(val)) { // Inserisce solo se l'elemento non è già presente
        int index = funHash(val); // Calcola il bucket
        PElem x = new Elem{val, pimpl->content[index]}; // Crea un nuovo nodo
        pimpl->content[index] = x; // Inserisce in testa alla lista
        pimpl->numelementi += 1; // Incrementa il numero di elementi
    }
}

/* Rimuove un elemento dall'insieme */
void Insieme::cancella(int val) {
    int index = funHash(val); // Calcola il bucket
    PElem elem = pimpl->content[index];
    PElem pred = nullptr; // Puntatore al nodo precedente
    bool found = false;

    // Cerca il nodo da eliminare
    while (elem && !found) {
        if (elem->info == val) {
            found = true; // Nodo trovato
        } else {
            pred = elem; // Avanza nella lista
            elem = elem->succ;
        }
    }

    if (found) {
        if (pred) {
            pred->succ = elem->succ; // Salta il nodo corrente
        } else {
            pimpl->content[index] = elem->succ; // Nodo in testa al bucket
        }
        delete elem; // Dealloca il nodo
        pimpl->numelementi--; // Decrementa il numero di elementi
    }
}

/* Restituisce il numero di elementi nell'insieme */
int Insieme::numElementi() const {
    return pimpl->numelementi;
}

/* Verifica se un elemento è presente nell'insieme */
bool Insieme::contiene(int val) const {
    int index = funHash(val); // Calcola il bucket
    PElem elem = pimpl->content[index];

    while (elem) { // Scorre la lista
        if (elem->info == val) {
            return true; // Elemento trovato
        }
        elem = elem->succ; // Avanza nella lista
    }
    return false; // Elemento non trovato
}

/* Restituisce un nuovo insieme che rappresenta l'unione con un altro insieme */
Insieme Insieme::unione(const Insieme& I_2) const {
    Insieme insieme_unione(*this); // Copia il primo insieme

    for (size_t i = 0; i < hashsize; i++) {
        PElem elem = I_2.pimpl->content[i];
        while (elem) { // Scorre i nodi del secondo insieme
            if (!insieme_unione.contiene(elem->info)) {
                insieme_unione.inserisci(elem->info); // Aggiunge solo elementi nuovi
            }
            elem = elem->succ;
        }
    }
    return insieme_unione;
}

/* Restituisce un nuovo insieme che rappresenta l'intersezione */
Insieme Insieme::intersezione(const Insieme& I_2) const {
    Insieme insieme_intersez;

    for (size_t i = 0; i < hashsize; i++) {
        PElem elem = pimpl->content[i];
        while (elem) { // Scorre i nodi del primo insieme
            if (I_2.contiene(elem->info)) {
                insieme_intersez.inserisci(elem->info); // Aggiunge solo gli elementi comuni
            }
            elem = elem->succ;
        }
    }
    return insieme_intersez;
}

/* Restituisce un nuovo insieme che rappresenta la differenza */
Insieme Insieme::differenza(const Insieme& I_2) const {
    Insieme insieme_diff;

    for (size_t i = 0; i < hashsize; i++) {
        PElem elem = pimpl->content[i];
        while (elem) { // Scorre i nodi del primo insieme
            if (!I_2.contiene(elem->info)) {
                insieme_diff.inserisci(elem->info); // Aggiunge solo elementi non presenti nel secondo insieme
            }
            elem = elem->succ;
        }
    }
    return insieme_diff;
}

/* Stampa il contenuto dell'insieme */
void Insieme::stampa() const {
    cout << "{ ";
    for (size_t i = 0; i < hashsize; i++) {
        PElem elem = pimpl->content[i];
        while (elem) {
            cout << elem->info << " "; // Stampa ogni elemento
            elem = elem->succ;
        }
    }
    cout << "}" << endl;
}

int main() {
    // Creazione di due insiemi vuoti
    Insieme insieme1;
    Insieme insieme2;

    // Inserimento di elementi in insieme1
    insieme1.inserisci(10);
    insieme1.inserisci(20);
    insieme1.inserisci(30);

    cout << "Insieme 1 dopo inserimenti: ";
    insieme1.stampa();

    // Inserimento di elementi in insieme2
    insieme2.inserisci(20);
    insieme2.inserisci(40);
    insieme2.inserisci(50);

    cout << "Insieme 2 dopo inserimenti: ";
    insieme2.stampa();

    // Test del metodo contiene()
    cout << "Insieme 1 contiene 20? " << (insieme1.contiene(20) ? "Sì" : "No") << endl;
    cout << "Insieme 2 contiene 30? " << (insieme2.contiene(30) ? "Sì" : "No") << endl;

    // Rimozione di un elemento da insieme1
    insieme1.cancella(20);
    cout << "Insieme 1 dopo rimozione di 20: ";
    insieme1.stampa();

    // Unione degli insiemi
    Insieme unione = insieme1.unione(insieme2);
    cout << "Unione di Insieme 1 e Insieme 2: ";
    unione.stampa();

    // Intersezione degli insiemi
    Insieme intersezione = insieme1.intersezione(insieme2);
    cout << "Intersezione di Insieme 1 e Insieme 2: ";
    intersezione.stampa();

    // Differenza tra Insieme 1 e Insieme 2
    Insieme differenza = insieme1.differenza(insieme2);
    cout << "Differenza (Insieme 1 - Insieme 2): ";
    differenza.stampa();

    // Numero di elementi
    cout << "Numero di elementi in Insieme 1: " << insieme1.numElementi() << endl;
    cout << "Numero di elementi in Insieme 2: " << insieme2.numElementi() << endl;

    return 0;
}