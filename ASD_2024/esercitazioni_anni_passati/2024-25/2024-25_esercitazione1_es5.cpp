#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue> // Usata solo nel main per testing

using namespace std;

/* TESTO
ESERCIZIO 5
Un videogioco prevede che il proprio avatar venga paracadutato su una mappa. 
La mappa è divisa in celle a cui è associato un numero indicante l’altitudine.
Un giocatore furbo deve far atterrare il proprio avatar in una cella con un’altitudine
superiore o uguale a quella delle celle adiacenti per non essere svantaggiato. 
Infatti, il giocatore furbo deve poter attaccare dall’alto i giocatori atterrati su celle 
con altitudine più bassa o almeno deve poter fronteggiare gli altri giocatori ad armi pari, 
cioè a pari altitudine. 

Tuttavia, il giocatore deve decidere in fretta dove far atterrare il proprio avatar, 
in quanto aprire il paracadute troppo tardi causerà la morte del proprio avatar e la perdita della partita ancora prima di iniziarla. 
Supponi di essere il giocatore e di rappresentare la mappa nella tua mente come una matrice quadrata n x n di
numeri positivi, mentre le locazioni esterne alla mappa sono rappresentate con un numero negativo. 
Sviluppa un algoritmo divide et impera EFFICIENTE per trovare le coordinate di una cella che non fornisca uno svantaggio una volta atterrato. 
Lo spazio aggiuntivo utilizzabile è O(1).

Il prototipo della procedura è:
void findGoodCell(const vector<vector<int>>& map, int columns, int& index row, int& index column)
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function------------------------
int checkGoodCell(const std::vector<std::vector<int>>& map, int columns, int index_row, int index_column) {
    cout << "checkGoodCell on " << index_row << ", " << index_column << "\n";
    // Determiniamo il numero di righe
    int rows = map.size();
    
    // Valore della cella corrente
    int currentVal = map[index_row][index_column];
    
    // Definiamo i possibili offset per accedere alle celle adiacenti
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            // Ignoriamo la cella stessa
            if (dr == 0 && dc == 0)
                continue;
            
            int neighborRow = index_row + dr;
            int neighborCol = index_column + dc;
            
            // Controllo dei limiti per evitare accessi fuori dall'array
            if (neighborRow < 0 || neighborRow >= rows || neighborCol < 0 || neighborCol >= columns)
                continue; // Se il vicino non esiste, lo saltiamo
            
            int neighborVal = map[neighborRow][neighborCol];
            
            // Qui puoi inserire il criterio di "good" che preferisci.
            // Nell'esempio si richiede che ogni vicino abbia un valore <= currentVal.
            if (neighborVal > currentVal) {
                return neighborCol;
            }
        }
    }
    // Se nessun vicino viola la condizione, restituiamo true
    return -1;
}

//------------------------main function------------------------
void findGoodCellHelper(const vector<vector<int>>& map, int columns, int &index_row, int &index_column) {
    // L'idea classica prevede di selezionare la colonna centrale,
    // individuare il massimo in quella colonna e confrontarlo con i vicini laterali.
    // Se è una "good cell" (cioè, l'altitudine è maggiore o uguale a quella delle celle adiacenti),
    // In caso contrario, si applica ricorsivamente l'algoritmo su una metà (sinistra o destra) della mappa.
    // Ricorda:
    // - La mappa ha dimensioni columns x columns
    // - Le locazioni al di fuori della mappa si considerano con altitudine negativa.
    // - Utilizza spazio aggiuntivo O(1).

    if (index_row>columns || index_column>columns && index_row<0 && index_column<0){
        return;
    }

    int curMax    = map[0][index_column];
    int curMaxInd = 0;
    for (int i = 1; i < columns; ++i) {
        if (map[i][index_column] > curMax) {
            curMax    = map[i][index_column];
            curMaxInd = i;
        }
    }
    index_row = curMaxInd;
    
    int cellTestResult = checkGoodCell(map, columns, index_row, index_column);
    if(cellTestResult == -1){
        return;
    }
    else{
        index_column = cellTestResult;
        findGoodCellHelper(map, columns, index_row, index_column);
    }

}

void findGoodCell(const vector<vector<int>>& map, int columns, int &index_row, int &index_column) {
    index_column = columns / 2;
    index_row = 0;

    findGoodCellHelper(map, columns, index_row, index_column);
}

int main() {
    // Esempio di mappa
    // Rappresentazione: la mappa è una matrice quadrata di altitudini positive.
    // Per le celle fuori mappa, si considera come se avessero altitudine negativa (per garantire "sicurezza")
    // Nell'esempio, useremo una mappa 4x4.
    vector<vector<int>> map = {
        {10,  8, 10, 10},
        {14, 13, 12, 11},
        {15,  9, 11, 21},
        {16, 17, 19, 20}
    };
    int n = map.size(); // dimensione della mappa (n x n)
    
    int foundRow = -1, foundCol = -1;
    
    // Chiamata alla funzione findGoodCell
    findGoodCell(map, n, foundRow, foundCol);
    
    // Stampa del risultato
    if (foundRow >= 0 && foundCol >= 0) {
        cout << "Buona cella trovata in (" << foundRow << ", " << foundCol << ") con altitudine " << map[foundRow][foundCol] << endl;
    } else {
        cout << "Nessuna buona cella trovata." << endl;
    }
    
    // Aggiungi ulteriori test se necessario
    
    return 0;
}