
#include <iostream>
#include <vector>
using namespace std;

// ---------------------- Linked List ----------------------
struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() { head = nullptr; }

    void insert(int val) {
        Node* newNode = new Node{val, nullptr};
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        if (!temp) {
            cout << "List is empty!" << endl;
            return;
        }
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void remove(int val) {
        if (!head) return;
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != val) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* del = temp->next;
            temp->next = temp->next->next;
            delete del;
        }
    }
};

// ---------------------- Merge Sort ----------------------
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ---------------------- Quick Sort ----------------------
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------------------- Binary Search ----------------------
int binarySearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ---------------------- Main Menu ----------------------
int main() {
    LinkedList list;
    vector<int> arr;
    bool isArraySorted = false; 
    int choice, val;

    do {
        cout << endl << "===== MENU =====" << endl;
        cout << "1. Insert into Linked List" << endl;
        cout << "2. Delete from Linked List" << endl;
        cout << "3. Display Linked List" << endl;
        cout << "4. Input Array" << endl;
        cout << "5. Display Array" << endl;
        cout << "6. Merge Sort Array" << endl;
        cout << "7. Quick Sort Array" << endl;
        cout << "8. Binary Search in Array" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: "; cin >> val;
            list.insert(val);
            break;
        case 2:
            cout << "Enter value to delete: "; cin >> val;
            list.remove(val);
            break;
        case 3:
            list.display();
            break;
        case 4:
            arr.clear();
            cout << "Enter size of array: ";
            int n; cin >> n;
            cout << "Enter elements:" << endl;
            for (int i = 0; i < n; i++) {
                cin >> val;
                arr.push_back(val);
            }
            isArraySorted = false; 
            break;
        case 5:
            if (arr.empty()) cout << "Array is empty!" << endl;
            else {
                for (int x : arr) cout << x << " ";
                cout << endl;
            }
            break;
        case 6:
            if (!arr.empty()) {
                mergeSort(arr, 0, arr.size() - 1);
                isArraySorted = true;
                cout << "Array sorted using Merge Sort." << endl;
            } else cout << "Array empty!" << endl;
            break;
        case 7:
            if (!arr.empty()) {
                quickSort(arr, 0, arr.size() - 1);
                isArraySorted = true; 
                cout << "Array sorted using Quick Sort." << endl;
            } else cout << "Array empty!" << endl;
            break;
        case 8:
            if (arr.empty()) {
                cout << "Array is empty!" << endl;
            } else if (!isArraySorted) { 
                cout << "Warning: Array is not sorted. Please sort it first using option 6 or 7." << endl;
            } else {
                cout << "Enter value to search: "; cin >> val;
                int idx = binarySearch(arr, val);
                if (idx != -1) cout << "Value found at index " << idx << endl;
                else cout << "Value not found!" << endl;
            }
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
