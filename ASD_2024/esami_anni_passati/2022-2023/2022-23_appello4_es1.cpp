#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO4
Si consideri un albero ternario completo in cui ogni nodo ha i seguenti campi: (i) key chiave intera,
(ii) fruitful valore booleano, (iii) left puntatore al figlio sinistro, (iv) center puntatore al
figlio centrale, (v) right puntatore al figlio destro.

a. Si scriva una procedura efficiente in C++ che assegni True al campo fruitful del
nodo se e solo se la somma delle chiavi dei nodi di ciascuno dei sottoalberi radicati nei figli
è maggiore di una costante k fornita in input. Il prototipo della procedura è:
void set_fruitful(PTNode r, int k)

b. Valutare la complessità della procedura, indicando eventuali relazioni di ricorrenza e
mostrando la loro risoluzione.

*/

/*#region utilities functions*/
struct TNode{
    int key;
    bool fruitfull;
    TNode* left;
    TNode* right;
};
typedef TNode* PTNode;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
void set_fruitful(PTNode r, int k){
    
}


//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
int main() {
    return 0;
}
