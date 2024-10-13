//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

template<typename T>
class Heap {
    string type;
    vector<T> elements;

    void heapify_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (type == "MIN_HEAP") {
            if (left < elements.size() && compare(elements[left], elements[smallest])) {
                smallest = left;
            }
            if (right < elements.size() && compare(elements[right], elements[smallest])) {
                smallest = right;
            }
        }

        if (smallest != i) {
            swap(elements[i], elements[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2;

        if (i && compare(elements[i], elements[parent])) {
            swap(elements[i], elements[parent]);
            heapify_up(parent);
        }
    }

    bool compare(const T& a, const T& b) {
        if (a.first == b.first) {
            return a.second > b.second;  
        }
        return a.first < b.first;
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

        Heap<pair<int, string>> minHeap("MIN_HEAP");

        for (const auto& [word, freq] : frequencyMap) {
            minHeap.insert({freq, word});
            if (minHeap.size() > k) {
                minHeap.pop(); 
            }
        }

        vector<string> result;
        while (minHeap.size() > 0) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }

        reverse(result.begin(), result.end());

        return result;
    }
};
