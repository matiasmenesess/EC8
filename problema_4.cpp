//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso
#include <vector>
using namespace std;
struct Node {
    int value;
    int row;
    int col;
};
class Heap {
    vector<Node> heap;
    void heapify_down(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap.size() && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }
    void heapify_up(int i) {
        int parent = (i - 1) / 2;
        if (i && heap[i].value < heap[parent].value) {
            swap(heap[i], heap[parent]);
            heapify_up(parent);
        }
    }
public:
    void insert(Node node) {
        heap.push_back(node);
        heapify_up(heap.size() - 1);
    }
    Node extract_min() {
        if (heap.size() == 0) {
            cout<<"Heap vacio";
        }
        Node root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);

        return root;
    }
    bool empty() const {
        return heap.size() == 0;
    }
};
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        Heap heap1;
        for (int i = 0; i < n; i++) {
            heap1.insert({matrix[i][0], i, 0});
        }
        Node element;
        for (int i = 0; i < k; i++) {
            element = heap1.extract_min();
            if (element.col + 1 < n) {
                heap1.insert({matrix[element.row][element.col + 1], element.row, element.col + 1});
            }
        }
        return element.value;
    }
};
