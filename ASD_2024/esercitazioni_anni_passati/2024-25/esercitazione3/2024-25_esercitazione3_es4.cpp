#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 4
Fornire un’implementazione per il tipo di dato Dizionario il cui insieme di operazioni è specificato nel file dizionario.hpp, utilizzando una tabella Hash con concatenamento.

Deve essere completato il file implHashChainingDaComp.cpp.
Per ciascuna operazione specificare la complessit`a (caso pessimo e caso medio) e completare il tipo Elem in modo da rendere le operazioni il più efficienti possibili. 
Si crei un dizionario e si devono eseguire le seguenti operazioni:

1. inserimento della sequenza di chiavi: 42, 16, 7, 85
2. cancellazione: 42
3. ricerca: 85
4. inserimento: 29

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
const int hashsize = 10; // Dimensione della tabella hash (fissa)

// Struttura dell'elemento contenente la coppia chiave-valore
struct Elem {
    int key;    // chiave
    int info;   // valore associato
    Elem* next; // puntatore al prossimo nella lista
    Elem* prev; // puntatore al precedente
};

typedef Elem* PElem;

class Dizionario {
public:
    Dizionario();               // Costruttore
    ~Dizionario();              // Distruttore
    void inserisci(int k, int val);  // Inserimento di una coppia (chiave, valore)
    void cancella(PElem e);          // Cancellazione dell'elemento puntato
    PElem cerca(int k);              // Ricerca per chiave
    int numChiavi();                 // Numero totale di chiavi presenti
    int leggiChiave(PElem e);        // Restituisce la chiave di un elemento
    int leggiInfo(PElem e);          // Restituisce il valore associato
    void stampa();                   // Stampa il contenuto del dizionario

private:
    struct Impl {
        vector<PElem> contentVect; // Vettore di liste per la tabella hash
        int numchiavi;         // Conteggio delle chiavi presenti
    };

    Impl* pimpl; // Puntatore all'implementazione (pimpl idiom)
};

// Funzione di hash semplice (modulo)
int funHash(int val) {
    return val % hashsize;
}

// Costruttore: inizializza la tabella con liste vuote
Dizionario::Dizionario() {
    pimpl = new Impl;
    pimpl->numchiavi = 0;
    for (int i = 0; i < hashsize; i++)
        pimpl->contentVect.push_back(nullptr);
}

// Funzione ricorsiva di cancellazione della lista
void cancellaLista(PElem l) {
    if (l) {
        cancellaLista(l->next);
        delete l;
    }
}

// Distruttore: libera tutta la memoria allocata
Dizionario::~Dizionario() {
    for (int i = 0; i < hashsize; i++)
        cancellaLista(pimpl->contentVect[i]);
    delete pimpl;
}

// Inserimento di una nuova coppia (key, val) nella tabella hash
void Dizionario::inserisci(int k, int val) {
    int index = funHash(k); // Calcola l'indice nella tabella
    PElem nuovo = new Elem{k, val, nullptr, nullptr}; // Crea nuovo elemento
    // Inserisce in testa alla lista della posizione index
    nuovo->next = pimpl->contentVect[index];
    if (pimpl->contentVect[index])
        pimpl->contentVect[index]->prev = nuovo;
    pimpl->contentVect[index] = nuovo;
    pimpl->numchiavi++;
}

// Cancellazione di un elemento dalla lista corrispondente alla sua chiave
void Dizionario::cancella(PElem x) {
    PElem succ = x->next;
    if (x->prev)
        x->prev->next = succ; // Collegamento del precedente
    else
        pimpl->contentVect[funHash(x->key)] = succ; // x era in testa
    if (succ)
        succ->prev = x->prev;
    delete x;
    pimpl->numchiavi--;
}

// Ricerca di un elemento tramite la chiave
PElem Dizionario::cerca(int k) {
    PElem iter = pimpl->contentVect[funHash(k)];
    while (iter && iter->key != k)
        iter = iter->next;
    return iter; // nullptr se non trovato
}

// Restituisce il numero di chiavi presenti
int Dizionario::numChiavi() {
    return pimpl->numchiavi;
}

// Restituisce la chiave di un elemento
int Dizionario::leggiChiave(PElem x) {
    return x->key;
}

// Restituisce il valore associato di un elemento
int Dizionario::leggiInfo(PElem x) {
    return x->info;
}

// Stampa completa della tabella hash
void Dizionario::stampa() {
    for (int i = 0; i < hashsize; i++) {
        if (pimpl->contentVect[i] == nullptr)
            cout << "tab[" << i << "] = vuoto\n";
        else {
            cout << "tab[" << i << "] = ";
            PElem iter = pimpl->contentVect[i];
            while (iter) {
                cout << "(" << iter->key << "," << iter->info << ")\t";
                iter = iter->next;
            }
            cout << endl;
        }
    }
}

// Funzione di test con operazioni principali
/*int main() {
    Dizionario dict;

    // Inserimenti
    dict.inserisci(42, 1);
    dict.inserisci(16, 2);
    dict.inserisci(7, 3);
    dict.inserisci(85, 4);

    // Stampa dopo inserimento
    cout << "Dizionario dopo inserimenti:\n";
    dict.stampa();

    // Cancellazione
    PElem elem = dict.cerca(42);
    if (elem) {
        dict.cancella(elem);
        cout << "\nDizionario dopo cancellazione della chiave 42:\n";
        dict.stampa();
    }

    // Ricerca
    elem = dict.cerca(85);
    if (elem)
        cout << "\nElemento con chiave 85 trovato: valore = " << dict.leggiInfo(elem) << endl;
    else
        cout << "\nElemento con chiave 85 non trovato" << endl;

    return 0;
}*/

int main() {
    Dizionario dict;

    // Lista di coppie chiave-info da inserire (simulate tante entries)
    vector<pair<int, int>> entries = {
        {42, 100}, {15, 200}, {27, 300}, {33, 400}, {87, 500},
        {56, 600}, {18, 700}, {94, 800}, {65, 900}, {74, 1000},
        {23, 1100}, {11, 1200}, {8, 1300}, {17, 1400}, {99, 1500},
        {3, 1600}, {28, 1700}, {31, 1800}, {47, 1900}, {63, 2000},
        {77, 2100}, {91, 2200}, {44, 2300}, {39, 2400}, {72, 2500},
        {86, 2600}, {29, 2700}, {20, 2800}, {36, 2900}, {58, 3000}
    };

    // Inserimento delle chiavi
    cout << "Inserimento di 30 chiavi nel dizionario...\n";
    for (const auto& [key, info] : entries) {
        dict.inserisci(key, info);
    }

    cout << "\n--- Dizionario dopo tutti gli inserimenti ---\n";
    dict.stampa();

    // Ricerca di alcune chiavi esistenti
    cout << "\n--- Ricerche di chiavi esistenti ---\n";
    vector<int> chiaviDaCercare = {42, 74, 91, 3, 86};
    for (int k : chiaviDaCercare) {
        PElem found = dict.cerca(k);
        if (found)
            cout << "Trovata chiave " << k << " con valore: " << dict.leggiInfo(found) << "\n";
        else
            cout << "Chiave " << k << " non trovata (errore!).\n";
    }

    // Ricerca di chiavi NON presenti
    cout << "\n--- Ricerche di chiavi NON presenti ---\n";
    vector<int> chiaviAssenti = {100, 50, 0, 13, 89};
    for (int k : chiaviAssenti) {
        PElem found = dict.cerca(k);
        if (found)
            cout << "Errore: chiave " << k << " trovata, ma non dovrebbe esistere.\n";
        else
            cout << "Chiave " << k << " correttamente non trovata.\n";
    }

    // Cancellazione di alcune chiavi
    cout << "\n--- Cancellazione di chiavi ---\n";
    vector<int> daCancellare = {42, 18, 99, 58, 3, 100};  // include una non esistente (100)
    for (int k : daCancellare) {
        PElem found = dict.cerca(k);
        if (found) {
            dict.cancella(found);
            cout << "Cancellata chiave " << k << ".\n";
        } else {
            cout << "Chiave " << k << " non presente, impossibile cancellare.\n";
        }
    }

    // Stampa finale dello stato del dizionario
    cout << "\n--- Dizionario dopo cancellazioni ---\n";
    dict.stampa();

    // Numero di chiavi rimanenti
    cout << "\nNumero di chiavi nel dizionario dopo tutte le operazioni: " << dict.numChiavi() << "\n";

    return 0;
}
