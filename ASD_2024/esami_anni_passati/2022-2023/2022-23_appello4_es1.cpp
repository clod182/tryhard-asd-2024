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
è maggiore di una costante k fornita in input. 
Il prototipo della procedura è:
void set_fruitful(PTNode r, int k)

b. Valutare la complessità della procedura, indicando eventuali relazioni di ricorrenza e
mostrando la loro risoluzione.

*/

/*#region utilities functions*/
struct TNode{
    int key;
    bool fruitful;
    TNode* left;
    TNode* center;
    TNode* right;

    TNode(int k) : key(k), fruitful(false), left(nullptr), center(nullptr), right(nullptr) {}
};
typedef TNode* PTNode;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
int elabCycle(PTNode r, int k){
    if(r == nullptr) return 0;

    int sumL = elabCycle(r->left, k);
    int sumC = elabCycle(r->center, k);
    int sumR = elabCycle(r->right, k);
    if(sumL > k && sumC > k && sumR > k){
        r->fruitful = true;
    }
    return r->key + sumL + sumC + sumR;
}
void set_fruitful(PTNode r, int k){
    elabCycle(r, k);
}


//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
//----------------------------------------------------------------------------------------------------------------------------------------
// FUNZIONI DI UTILITÀ PER I TEST

// Stampa l'albero con informazioni dettagliate
void printTree(PTNode r, int level = 0, string prefix = "Root: ") {
    if (r == nullptr) return;
    
    cout << string(level * 4, ' ') << prefix 
         << "key=" << r->key << ", fruitful=" << (r->fruitful ? "true" : "false") << endl;
    
    if (r->left || r->center || r->right) {
        printTree(r->left, level + 1, "L--- ");
        printTree(r->center, level + 1, "C--- ");
        printTree(r->right, level + 1, "R--- ");
    }
}

// Calcola la somma di un sottoalbero
int calculateSum(PTNode r) {
    if (r == nullptr) return 0;
    return r->key + calculateSum(r->left) + calculateSum(r->center) + calculateSum(r->right);
}

// Verifica manualmente se un nodo dovrebbe essere fruitful
bool shouldBeFruitful(PTNode r, int k) {
    if (r == nullptr) return false;
    
    int sumL = calculateSum(r->left);
    int sumC = calculateSum(r->center);
    int sumR = calculateSum(r->right);
    
    return (sumL > k) && (sumC > k) && (sumR > k);
}

// Verifica la correttezza dell'algoritmo
bool verifyCorrectness(PTNode r, int k) {
    if (r == nullptr) return true;
    
    bool expected = shouldBeFruitful(r, k);
    if (r->fruitful != expected) {
        cout << "ERRORE: Nodo con key=" << r->key 
             << " dovrebbe essere " << (expected ? "fruitful" : "non-fruitful")
             << " ma è " << (r->fruitful ? "fruitful" : "non-fruitful") << endl;
        return false;
    }
    
    return verifyCorrectness(r->left, k) && 
           verifyCorrectness(r->center, k) && 
           verifyCorrectness(r->right, k);
}

// Conta nodi fruitful
int countFruitful(PTNode r) {
    if (r == nullptr) return 0;
    return (r->fruitful ? 1 : 0) + 
           countFruitful(r->left) + 
           countFruitful(r->center) + 
           countFruitful(r->right);
}

//----------------------------------------------------------------------------------------------------------------------------------------
// COSTRUZIONE ALBERI DI TEST

// Test 1: Albero semplice a 2 livelli
PTNode createTest1() {
    PTNode root = new TNode(10);
    root->left = new TNode(5);
    root->center = new TNode(15);
    root->right = new TNode(8);
    return root;
}

// Test 2: Albero più profondo
PTNode createTest2() {
    PTNode root = new TNode(20);
    
    // Livello 1
    root->left = new TNode(10);
    root->center = new TNode(30);
    root->right = new TNode(15);
    
    // Livello 2 - figli di left
    root->left->left = new TNode(2);
    root->left->center = new TNode(3);
    root->left->right = new TNode(4);
    
    // Livello 2 - figli di center
    root->center->left = new TNode(12);
    root->center->center = new TNode(8);
    root->center->right = new TNode(5);
    
    // Livello 2 - figli di right
    root->right->left = new TNode(6);
    root->right->center = new TNode(7);
    root->right->right = new TNode(1);
    
    return root;
}

// Test 3: Albero con valori negativi
PTNode createTest3() {
    PTNode root = new TNode(0);
    root->left = new TNode(-5);
    root->center = new TNode(10);
    root->right = new TNode(-3);
    
    root->left->left = new TNode(-1);
    root->left->center = new TNode(-2);
    root->left->right = new TNode(-1);
    
    return root;
}

// Test 4: Albero sbilanciato
PTNode createTest4() {
    PTNode root = new TNode(100);
    root->left = new TNode(50);
    root->center = new TNode(25);
    // right è nullptr
    
    root->left->center = new TNode(10);
    root->left->center->left = new TNode(5);
    root->left->center->center = new TNode(3);
    root->left->center->right = new TNode(2);
    
    return root;
}

// Test 5: Albero con un solo nodo
PTNode createTest5() {
    return new TNode(42);
}

//----------------------------------------------------------------------------------------------------------------------------------------
// FUNZIONE PRINCIPALE DI TEST

void runTest(PTNode tree, int k, const string& testName) {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST: " << testName << " (k = " << k << ")" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\nAlbero PRIMA dell'elaborazione:" << endl;
    printTree(tree);
    
    // Calcola somme dei sottoalberi per la radice
    if (tree != nullptr) {
        cout << "\nSomme dei sottoalberi della radice:" << endl;
        cout << "- Sottoalbero sinistro: " << calculateSum(tree->left) << endl;
        cout << "- Sottoalbero centrale: " << calculateSum(tree->center) << endl;
        cout << "- Sottoalbero destro: " << calculateSum(tree->right) << endl;
        cout << "- Somma totale albero: " << calculateSum(tree) << endl;
    }
    
    // Esegui l'algoritmo
    set_fruitful(tree, k);
    
    cout << "\nAlbero DOPO l'elaborazione:" << endl;
    printTree(tree);
    
    // Verifica correttezza
    bool isCorrect = verifyCorrectness(tree, k);
    int fruitfulCount = countFruitful(tree);
    
    cout << "\nRisultati:" << endl;
    cout << "- Nodi fruitful: " << fruitfulCount << endl;
    cout << "- Test " << (isCorrect ? "PASSATO ✓" : "FALLITO ✗") << endl;
}

//----------------------------------------------------------------------------------------------------------------------------------------
// MAIN

int main() {
    cout << "Testing della funzione set_fruitful per alberi ternari" << endl;
    cout << "=====================================================" << endl;
    
    // Test 1: Caso base semplice
    runTest(createTest1(), 5, "Albero semplice - k medio");
    
    // Test 2: Stesso albero con k più basso
    runTest(createTest1(), 2, "Albero semplice - k basso");
    
    // Test 3: Stesso albero con k molto alto
    runTest(createTest1(), 50, "Albero semplice - k alto");
    
    // Test 4: Albero più complesso
    runTest(createTest2(), 10, "Albero complesso - k medio");
    
    // Test 5: Albero complesso con k basso
    runTest(createTest2(), 5, "Albero complesso - k basso");
    
    // Test 6: Albero con valori negativi
    runTest(createTest3(), -10, "Albero con negativi - k negativo");
    
    // Test 7: Albero sbilanciato
    runTest(createTest4(), 15, "Albero sbilanciato");
    
    // Test 8: Singolo nodo
    runTest(createTest5(), 0, "Singolo nodo");
    
    // Test 9: Albero vuoto
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST: Albero vuoto" << endl;
    cout << string(60, '=') << endl;
    PTNode emptyTree = nullptr;
    set_fruitful(emptyTree, 10);
    cout << "Test albero vuoto completato senza errori ✓" << endl;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "TUTTI I TEST COMPLETATI!" << endl;
    cout << string(60, '=') << endl;
    
    return 0;
}