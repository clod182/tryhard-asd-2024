#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO2

Sia A un vettore di interi positivi di lunghezza n. Si consideri il problema di disporre gli elementi in A in modo che
il valore assoluto della differenza tra due elementi adiacenti decresca scorrendo il vettore da sinistra verso destra.
Formalmente, per ogni i ∈ [1, n − 2] dovrà valere che |A[i] – A[i+1]| ≥ |A[i+1]−A[i+2]|

a. Quali elementi di A dovranno essere spostati in A[1] e A[2] per rispettare la condizione sopra presentata?

b. Si scriva in c++ una procedura efficiente per risolvere il problema descritto. Valutare e
giustificare la complessità della procedura proposta.

c. Si scriva in c++ una procedura efficiente per risolvere il problema descritto nel caso in cui la
differenza tra il massimo e il minimo di A sia inferiore a n. Valutare e giustificare la complessità della
procedura proposta.

/*#region utilities functions*/
// Funzione ausiliaria per il merge
void merge(vector<int>& arr, int left, int mid, int right) {
    // Calcola le dimensioni dei due sottoarray
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crea array temporanei
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    
    // Copia i dati negli array temporanei
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    // Merge dei due array temporanei nell'array originale
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copia gli elementi rimanenti di leftArr, se ce ne sono
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copia gli elementi rimanenti di rightArr, se ce ne sono
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Funzione ricorsiva per il mergesort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Trova il punto medio per dividere l'array in due metà
        int mid = left + (right - left) / 2;
        
        // Ordina ricorsivamente la prima e la seconda metà
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge delle due metà ordinate
        merge(arr, left, mid, right);
    }
}
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
//DOMANDA 1 **************************************************************
// O(n log n)
vector<int> orderByModule(vector<int> vect){
    if(vect.size() <= 1){
        return vect;
    }
    int dim = vect.size();

    vector<int> ret(dim);

    mergeSort(vect, 0, dim-1);

    int i = 0, j = dim-1, place = 0;
    while(i <= j){
        ret[place] = vect[i];
        ret[place + 1] = vect[j];

        i++;
        j--;
        place +=2;
    }    

    return ret;
}

//DOMANDA 2 **************************************************************
//n FISSO, counting sort ci porta a O(n)
vector<int> orderByModuleWithN(vector<int> vect){
    int dim = vect.size();
    vector<int> ret(dim);

    int maxVal = vect[0];
    int minVal = vect[0];

    // Trova minimo e massimo

    for (int i = 1; i < dim; ++i) {
        if (vect[i] < minVal) minVal = vect[i];
        if (vect[i] > maxVal) maxVal = vect[i];
    }

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);
 
    // Conta le occorrenze
    for (int i = 0; i < dim; ++i) {
        count[vect[i] - minVal]++;
    }

    //  L'accumulo (per la stabilità) in questo caso non serve
    /*for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }*/


    // Ricostruisci array ordinato
    vector<int> sorted;
    for (int i = 0; i < range; ++i) {
        while (count[i]--) {
            sorted.push_back(i + minVal);
        }
    }

    // Ricostruisci in modo zig-zag
    int i = 0, j = dim - 1;
    int pos = 0;
    while (i <= j) {
        ret[pos++] = sorted[i++];
        if (i <= j)
            ret[pos++] = sorted[j--];
    }

    return ret;
}

//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
// Utility: stampa un vettore
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

// Utility: verifica la proprietà richiesta
bool checkProperty(const vector<int>& A) {
    int n = A.size();
    for (int i = 0; i <= n - 3; ++i) {
        int diff1 = abs(A[i] - A[i+1]);
        int diff2 = abs(A[i+1] - A[i+2]);
        if (diff1 < diff2) return false;
    }
    return true;
}

int main() {
    vector<vector<int>> testCases = {
        {1, 3, 5, 9, 12},
        {10, 1, 2, 9, 3, 4},
        {100, 50, 10, 1},
        {5, 5, 5, 5},             // tutti uguali
        {1, 1000, 2, 999},        // grandi differenze alternate
        {7},                     // un solo elemento
        {8, 3}                   // due elementi
    };

    int testNum = 1;
    for (auto& test : testCases) {
        cout << "Test " << testNum++ << " - Original: ";
        printVector(test);

        //vector<int> result = orderByModule(test);
        vector<int> result = orderByModuleWithN(test);
        cout << "          Ordered : ";
        printVector(result);

        if (result.size() >= 3) {
            cout << "          Property satisfied? "
                 << (checkProperty(result) ? "YES" : "NO") << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }

    return 0;
}