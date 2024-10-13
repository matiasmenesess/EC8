//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <vector>
#include <iostream>
using namespace std;

struct Elemento {
    int val;
    int fila;
    int columna;
};

class Heap {
    vector<Elemento> heap;
    void heapify_down(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap.size() && heap[left].val < heap[smallest].val) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].val < heap[smallest].val) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2;
        if (i && heap[i].val < heap[parent].val) {
            swap(heap[i], heap[parent]);
            heapify_up(parent);
        }
    }

public:
    void insert(Elemento node) {
        heap.push_back(node);
        heapify_up(heap.size() - 1);
    }

    Elemento top() {
        if (heap.size() == 0) {
//            cout << "Heap vacio" << endl;
        }
        Elemento raiz = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);

        return raiz;
    }

    bool empty() const {
        return heap.size() == 0;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        Heap heap;
        for (int i = 0; i < matrix.size(); i++) {
            Elemento el;
            el.val = matrix[i][0];
            el.fila = i;
            el.columna = 0;
            heap.insert(el);
        }

        Elemento element;
        for (int i = 0; i < k; i++) {
            element = heap.top();
            if (element.columna + 1 < matrix.size()) {
                Elemento nuevoElemento;
                nuevoElemento.val = matrix[element.fila][element.columna + 1];
                nuevoElemento.fila = element.fila;
                nuevoElemento.columna = element.columna + 1;
                heap.insert(nuevoElemento);
            }
        }

        return element.val;
    }
};

