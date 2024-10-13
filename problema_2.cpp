//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <iostream>
#include <vector>
using namespace std;

template <typename T1, typename T2>
struct key_value {
    T1 key = T1();
    T2 value = T2();
};

template <typename T1, typename T2>
class Hash_Table {
    int current_size;
    int element_count;
    key_value<T1, T2>* table;

public:
    Hash_Table(int initial_size) {
        table = new key_value<T1, T2>[initial_size];
        current_size = initial_size;
        element_count = 0;
    }

    int hash_function(const string& key) { //funcion hash para strings
        unsigned hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % current_size;
    }

    void insert(T1 key, T2 value) {
        int index = hash_function(key);
        while (table[index].key != T1() && table[index].key != key) {
            index = (index + 1) % current_size;
        }
        if (table[index].key == key) {
            table[index].value += value;
        } else {
            table[index].key = key;
            table[index].value = value;
            element_count++;
        }
    }

    T2* search(T1 key) {
        int index = hash_function(key);
        while (table[index].key != T1()) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            index = (index + 1) % current_size;
        }
        return nullptr;
    }

    key_value<T1, T2>* begin() { return &table[0]; } //para iterar
    key_value<T1, T2>* end() { return &table[current_size]; } //para iterar

    // ~Hash_Table() {
    //     delete[] table;
    // }
};

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
            return a.second < b.second;  // orden lexicografico
        }
        return a.first > b.first;  // mayor frecuencia primero
    }

public:
    Heap(string heapType) : type(heapType) {}

    void insert(T val) {
        elements.push_back(val);
        heapify_up(elements.size() - 1);
    }

    void pop() {
        if (elements.size() == 0) {
            cout << "Heap vacío" << endl;
            return;
        }

        swap(elements[0], elements[elements.size() - 1]);
        elements.pop_back();
        heapify_down(0);
    }

    T top() {
        if (elements.size() == 0) {
            // throw out_of_range("Heap vacio");
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
        Hash_Table<string, int> HT(words.size());

        for (const string& word : words) {
            int* freq = HT.search(word);
            if (freq) {
                (*freq)++;
            } else {
                HT.insert(word, 1);
            }
        }

        Heap<pair<int, string>> maxHeap("MAX_HEAP");

        for (auto it = HT.begin(); it != HT.end(); ++it) {
            if (it->key != "") {
                maxHeap.insert({it->value, it->key});
            }
        }

        vector<string> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }

        return result;
    }
};

