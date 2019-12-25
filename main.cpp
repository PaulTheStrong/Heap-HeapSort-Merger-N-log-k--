#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template<typename T>
class Heap {
private:
	vector<T> tree;
	int heapSize;
public:
	Heap() :heapSize(0) {
		this->tree.resize(1);
	}
	Heap(const vector<T>& vec) :heapSize(vec.size()) {
		this->tree.resize(1);
		for (int i = 0; i < vec.size(); i++)
			this->tree.push_back(vec[i]);
		build_heap();
	}

	int left(int i) {
		return i * 2;
	}

	int right(int i) {
		return i * 2 + 1;
	}

	int parent(int i) {
		return i / 2;
	}

	void heapify(int i) {
		int l = left(i);
		int r = right(i);
		int largest = 0;
		if (l <= this->heapSize && this->tree[l] > this->tree[i])
			largest = l;
		else
			largest = i;
		if (r <= this->heapSize && this->tree[r] > this->tree[largest])
			largest = r;
		if (largest != i) {
			swap(this->tree[i], this->tree[largest]);
			heapify(largest);
		}
	}

	void build_heap() {
		for (int i = heapSize / 2; i > 0; i--) {
			heapify(i);
		}
	}

	vector<T> heap_sort() {
		int t = heapSize;
		vector<T> ret(heapSize);
		for (int i = heapSize; i >= 2; i--) {
			swap(this->tree[i], this->tree[1]);
			heapSize--;
			heapify(1);
		}

	}

	void insert(T key) {
		int i = ++this->heapSize;
		if (heapSize < this->tree.size())
			this->tree[i] = key;
		else
			this->tree.push_back(key);
		while (i > 1 && this->tree[parent(i)] < key) {
			this->tree[i] = this->tree[parent(i)];
			i = parent(i);
		}
		this->tree[i] = key;
	}

	T extractMax() {
		if (this->heapSize == 0)
			exit(0);
		T max = this->tree[1];
		this->tree[1] = this->tree[heapSize--];
		heapify(1);
		return max;
	}

	void increaseKey(int i, int key) {
		if (i > 0 && i <= this->heapSize && key > this->tree[i]) {
			while (i > 1 && key > this->tree[parent(i)]) {
				this->tree[i] = this->tree[parent(i)];
				i = parent(i);
			}
			this->tree[i] = key;
		}
	}

	void del(int i) {
		if (i <= this->heapSize) {
			this->tree[i] = this->tree[heapSize--];
			heapify(i);
		}
	}

	void print() {
		cout << "{ ";
		for (int i = 1; i < heapSize; i++) {
			cout << this->tree[i] << ", ";
		}
		if (heapSize > 0)
			cout << this->tree[heapSize];
		cout << " }\n";
	}
};

void enterTesetMode() {
	Heap<int> heap;
	string cmd = "";
	while (cmd != "q") {
		cout << "q : exit,  ins : insert, inc : increase, ext : extract, p : print, del : delete \n";
		cin >> cmd;
		if (cmd == "ins") {
			int num;
			cout << "Your Number : ";
			cin >> num;
			heap.insert(num);
			heap.print();
		}
		else if (cmd == "ext") {
			cout << "Number extracted : " << heap.extractMax() << '\n';
			heap.print();
		}
		else if (cmd == "inc") {
			int i, k;
			cout << "Index : ";
			cin >> i;
			cout << "Key : ";
			cin >> k;
			heap.increaseKey(i, k);
			heap.print();
		}
		else if (cmd == "del") {
			int i;
			cout << "Index : ";
			cin >> i;
			heap.del(i);
			heap.print();
		}
			else if (cmd == "p") {
			heap.print();
		}
	}
}

template <typename T>
vector<T> merge(vector<vector<T> >& values) {
	vector<T> ret;
	vector<int> sizes(values.size());
	Heap<pair<T, int> > merger;
	int all = 0;
	for (int i = 0; i < sizes.size(); i++)
	{
		sizes[i] = 1;
		all += values[i].size();
		merger.insert({ values[i][values[i].size() - 1], i });
	}

	while (all != 0) {
		pair<T, int> elem = merger.extractMax();
		int row = elem.second;
		if (sizes[row] < values[row].size()) {
			merger.insert({values[row][values[row].size() - ++sizes[row]] , row });
		}
		all--;
		ret.push_back(elem.first);
	}
	return ret;
}


int main() {
	//enterTesetMode();

	vector<vector<int>> list = {	{ 1, 5, 9, 15, 20 },
									{ 3, 4, 10, 16, 17},
									{ 6, 7, 8, 11, 12 } };
	vector<int> merged = merge(list);
	for (int n : merged)
		cout << n << ' ';
	cin.get();
	system("pause");
}