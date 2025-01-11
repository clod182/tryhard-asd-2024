
#include "insieme.hpp"
#include <vector>
#include <iostream>

constexpr int hashsize = 8;
constexpr int hashaux = 5;

using namespace std;

// Funzione di hash che calcola l'indice usando doppio hashing
int funHash(int val, int i){
    // Prima parte della funzione hash (h1), modulo hashsize.
    // La seconda parte (h2) è calcolata come (1 + 2 * (val % (hashsize - 3))).
    // La posizione finale dipende da i, che cresce ad ogni tentativo di collisione.
    return (val % hashsize + i * (1 + 2 * (val % (hashaux)))) % hashsize;
}

// Struttura che rappresenta un singolo elemento dell'insieme (un intero)
struct Elem{
    int info;  // Il valore memorizzato nell'elemento
};

typedef Elem *PElem;  // Definisce PElem come un puntatore a Elem

// Struttura che implementa l'insieme con una tabella hash
struct Insieme::Impl{
    vector<PElem> content;  // Vettore che contiene i puntatori agli elementi
    int numelementi;        // Numero di elementi nell'insieme
    PElem DEL;              // Puntatore speciale che indica una posizione eliminata
    /*
    Il puntatore DEL non solo consente di mantenere le informazioni sui "buchi" creati durante le cancellazioni, 
    ma permette anche al sistema di riutilizzare correttamente le posizioni in caso di collisioni, 
    senza rischiare di interrompere il probing o di perdere il percorso di ricerca degli altri elementi che erano stati precedentemente inseriti.
    */

    // Funzione per inserire un elemento nell'insieme senza controllare se è già presente, controllando la disponibilità della posizione
    void inseriscisenzaCheck(int val){
        int index, i;
        bool ok = false;
        i = 0;  // Variabile di controllo per il numero di tentativi (collisionsi)
        
        do{
            // Calcola l'indice usando la funzione di hash e il numero di tentativi
            index = funHash(val, i);
            
            // Se la posizione è vuota o marcata come eliminata, inseriamo l'elemento
            if (content[index] == nullptr || content[index] == DEL) {
                content[index] = new Elem{val};  // Crea un nuovo elemento e lo inserisce
                numelementi += 1;                // Incrementa il numero di elementi
                ok = true;                        // Operazione riuscita
            }
            else
                i++;  // Incrementa i per il prossimo tentativo (gestione collisioni)
        } while(i < hashsize && !ok);  // Continua finché ci sono tentativi disponibili e l'elemento non è stato inserito
        
        // Se l'insieme è pieno e non siamo riusciti a inserire, stampa un messaggio
        if (!ok)
            cout << "Set pieno\n";
    }
};

// Costruttore che crea un insieme vuoto
Insieme::Insieme(){
    pimpl = new Impl;  // Crea una nuova implementazione interna
    pimpl->numelementi = 0;  // Inizializza il numero di elementi a 0
    pimpl->DEL = new Elem;  // Crea un oggetto speciale per segnare le posizioni eliminate
    
    // Inizializza la tabella hash con nullptr
    for (size_t i = 0; i < hashsize; i++)
        pimpl->content.push_back(nullptr);
}

// Costruttore di copia che crea un nuovo insieme copiando gli elementi di un altro insieme
Insieme::Insieme(const Insieme& set) {
    pimpl = new Impl;  // Crea una nuova implementazione interna
    pimpl->numelementi = set.pimpl->numelementi;  // Copia il numero di elementi
    pimpl->DEL = new Elem;  // Crea un nuovo oggetto speciale per l'eliminazione
    
    // Inizializza la tabella hash vuota
    for (size_t i = 0; i < hashsize; i++)
        pimpl->content.push_back(nullptr);
    
    // Copia gli elementi dall'insieme originale
    for (size_t i = 0; i < hashsize; i++){
        PElem curr_elem = set.pimpl->content[i];
        // Se l'elemento non è nullo o marcato come eliminato, lo inserisce nell'insieme
        if (curr_elem != nullptr && curr_elem != set.pimpl->DEL)
            this->pimpl->inseriscisenzaCheck(curr_elem->info);
    }
}

// Distruttore che libera la memoria degli elementi e dell'oggetto DEL
Insieme::~Insieme(){
    // Libera la memoria per ogni elemento nella tabella hash
    for (size_t i = 0; i < hashsize; i++)
        if (pimpl->content[i] != nullptr && pimpl->content[i] != pimpl->DEL)
            delete pimpl->content[i];
    delete pimpl->DEL;  // Libera l'oggetto speciale DEL
    delete pimpl;       // Libera l'oggetto Impl
}

// Funzione che inserisce un valore nell'insieme solo se non è già presente
void Insieme::inserisci(int val){
    // Se il valore non è già presente nell'insieme, lo inserisce
    if(!contiene(val)) {
        this->pimpl->inseriscisenzaCheck(val);
    }
}

// Funzione che rimuove un valore dall'insieme
void Insieme::cancella(int val){
    int index, i;
    bool ok;
    i = 0;
    ok = false;
    
    do{
        // Calcola l'indice utilizzando il doppio hash
        index = funHash(val, i);
        
        // Se troviamo l'elemento, lo segniamo come eliminato (DEL)
        if (pimpl->content[index] != nullptr && pimpl->content[index] != pimpl->DEL && pimpl->content[index]->info == val)
            ok = true;  // Elemento trovato
        else
            i++;  // Continua a cercare con i nuovi tentativi
        
    } while(i < hashsize && !ok && pimpl->content[index] != nullptr);
    
    // Se l'elemento è stato trovato, lo rimuove
    if (ok) {
        PElem elem = pimpl->content[index];
        pimpl->content[index] = pimpl->DEL;  // Segna la posizione come "eliminata"
        delete elem;  // Libera la memoria dell'elemento
        pimpl->numelementi -= 1;  // Decrementa il numero di elementi
    }
}

// Funzione che restituisce il numero di elementi nell'insieme
int Insieme::numElementi() const {
    return pimpl->numelementi;  // Restituisce il numero di elementi
}

// Funzione che verifica se un valore è presente nell'insieme
bool Insieme::contiene(int val) const {
    int index, i;
    bool ok;
    i = 0;
    ok = false;
    
    do{
        // Calcola l'indice con doppio hashing
        index = funHash(val, i);
        
        // Se l'elemento è presente, restituisce true
        if (pimpl->content[index] != nullptr && pimpl->content[index] != pimpl->DEL && pimpl->content[index]->info == val)
            ok = true;
        else
            i++;  // Prova con un altro tentativo
        
    } while(i < hashsize && !ok && pimpl->content[index] != nullptr);
    
    return ok;  // Restituisce true se trovato, false altrimenti
}

// Funzione che restituisce l'unione di due insiemi
Insieme Insieme::unione(const Insieme& I_2) const {
    Insieme insieme_unione(*this);  // Crea una copia dell'insieme corrente
    
    // Aggiunge gli elementi dell'altro insieme
    for(int i = 0; i < I_2.pimpl->content.size(); i++) {
        PElem e = I_2.pimpl->content[i];
        // Se l'elemento non è nullo e non è già presente nell'insieme, lo inserisce
        if(e != nullptr && e != I_2.pimpl->DEL && !(contiene(e->info))) {
            insieme_unione.pimpl->inseriscisenzaCheck(e->info);
        }
    }
    return insieme_unione;  // Restituisce l'unione dei due insiemi
}

// Funzione che restituisce l'intersezione di due insiemi
Insieme Insieme::intersezione(const Insieme& I_2) const {
    Insieme insieme_intersez;  // Crea un nuovo insieme per l'intersezione
    
    // Aggiunge gli elementi che sono comuni a entrambi gli insiemi
    for(int i = 0; i < hashsize; i++) {
        PElem e = pimpl->content[i];
        if(e != nullptr && e != pimpl->DEL && I_2.contiene(e->info)) {
            insieme_intersez.pimpl->inseriscisenzaCheck(e->info);
        }
    }
    return insieme_intersez;  // Restituisce l'intersezione
}

// Funzione che restituisce la differenza tra due insiemi
Insieme Insieme::differenza(const Insieme& I_2) const {
    Insieme insieme_diff;  // Crea un nuovo insieme per la differenza
    
    // Aggiunge gli elementi che sono nell'insieme corrente ma non nell'altro
    for(int i = 0; i < hashsize; i++) {
        PElem e = pimpl->content[i];
        if(e != nullptr && e != pimpl->DEL && !I_2.contiene(e->info)) {
            insieme_diff.pimpl->inseriscisenzaCheck(e->info);
        }
    }
    return insieme_diff;  // Restituisce la differenza
}

// Funzione che stampa gli elementi dell'insieme
void Insieme::stampa() const {
    cout << "{ ";
    // Stampa ogni elemento, escludendo quelli che sono nulli o eliminati
    for (size_t i = 0; i < hashsize; i++)
        if (pimpl->content[i] != nullptr && pimpl->content[i] != pimpl->DEL)
            cout << pimpl->content[i]->info << " ";
    cout << "}" << endl;
}

int main() {
    // Creazione di due insiemi
    Insieme s1;
    Insieme s2;

    // Inserimento di elementi nel primo insieme
    cout << "Inserimento nel primo insieme:" << endl;
    s1.inserisci(10);
    s1.inserisci(20);
    s1.inserisci(30);
    s1.inserisci(40);
    s1.stampa();  // Stampa l'insieme s1

    // Inserimento di elementi nel secondo insieme
    cout << "Inserimento nel secondo insieme:" << endl;
    s2.inserisci(30);
    s2.inserisci(40);
    s2.inserisci(50);
    s2.inserisci(60);
    s2.stampa();  // Stampa l'insieme s2

    // Verifica la presenza di un elemento nell'insieme
    cout << "Verifica se 20 è presente in s1: " << (s1.contiene(20) ? "Sì" : "No") << endl;
    cout << "Verifica se 50 è presente in s1: " << (s1.contiene(50) ? "Sì" : "No") << endl;

    // Unione di due insiemi
    cout << "Unione tra s1 e s2:" << endl;
    Insieme unione_insiemi = s1.unione(s2);
    unione_insiemi.stampa();  // Stampa l'insieme risultante dall'unione

    // Intersezione di due insiemi
    cout << "Intersezione tra s1 e s2:" << endl;
    Insieme intersezione_insiemi = s1.intersezione(s2);
    intersezione_insiemi.stampa();  // Stampa l'insieme risultante dall'intersezione

    // Differenza di due insiemi
    cout << "Differenza tra s1 e s2 (s1 - s2):" << endl;
    Insieme differenza_insiemi = s1.differenza(s2);
    differenza_insiemi.stampa();  // Stampa l'insieme risultante dalla differenza

    // Rimozione di un elemento da un insieme
    cout << "Rimozione di 20 da s1:" << endl;
    s1.cancella(20);
    s1.stampa();  // Stampa l'insieme s1 dopo la rimozione di 20

    // Rimozione di un elemento non presente
    cout << "Rimozione di 100 da s1 (elemento non presente):" << endl;
    s1.cancella(100);  // Non succede nulla, perché 100 non è presente
    s1.stampa();  // Stampa l'insieme s1 dopo il tentativo di rimozione

    // Numero di elementi in s1
    cout << "Numero di elementi in s1: " << s1.numElementi() << endl;
    cout << "Numero di elementi in s2: " << s2.numElementi() << endl;

    // Creazione di un nuovo insieme tramite copia
    cout << "Creazione di un nuovo insieme copia di s1:" << endl;
    Insieme s1_copy(s1);
    s1_copy.stampa();  // Stampa l'insieme copia di s1

    return 0;
}