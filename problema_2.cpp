//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template<typename T>
class Heap {
    string type;
    vector<T> elements;

    void heapify_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (type == "MAX_HEAP") {
            if (left < elements.size() && Comparar(elements[left], elements[largest])) {
                largest = left;
            }
            if (right < elements.size() && Comparar(elements[right], elements[largest])) {
                largest = right;
            }
        }

        if (largest != i) {
            swap(elements[i], elements[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2;

        if (i && Comparar(elements[i], elements[parent])) {
            swap(elements[i], elements[parent]);
            heapify_up(parent);
        }
    }

    bool Comparar(const T& a, const T& b) {
        if (a.first == b.first) {
            return a.second < b.second;  // lexicographical order
        }
        return a.first > b.first;  // higher frequency comes first
    }

public:
    Heap(string heapType) : type(heapType) {}

    void insert(T val) {
        elements.push_back(val);
        heapify_up(elements.size() - 1);
    }

    void pop() {
        if (elements.size() == 0) {
            cout << "Heap vacio" << endl;
            return;
        }

        swap(elements[0], elements[elements.size() - 1]);
        elements.pop_back();
        heapify_down(0);
    }

    T top() {
        if (elements.size() == 0) {
            throw out_of_range("Heap is empty");
        }
        return elements[0];
    }

    int size() {
        return elements.size();
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> frequencyMap;
        for (const string& word : words) {
            frequencyMap[word]++;
        }

        Heap<pair<int, string>> maxHeap("MAX_HEAP");

        for (const auto& [word, freq] : frequencyMap) {
            maxHeap.insert({freq, word});
        }

        vector<string> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }

        return result;
    }
};
