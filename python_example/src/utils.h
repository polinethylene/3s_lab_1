#ifndef INC_2S_LAB1_UTILS_H
#define INC_2S_LAB1_UTILS_H
#include <iostream>
#include <ctime>
#include "Sequence.h"
#include "ArraySeq.h"
#include "LinkedListSeq.h"
#include "Complex.h"
#include "Sort.h"

using namespace std;

int dialog(int n);
ArraySequence<int> get_seq_randint(int length);
ArraySequence<float> get_seq_randfloat(int length);
ArraySequence<Complex> get_seq_randcomplex(int length);
ArraySequence<string> get_seq_randstring(int length);

LinkedListSequence<int> get_listseq_randint(int length);
LinkedListSequence<float> get_listseq_randfloat(int length);
LinkedListSequence<Complex> get_listseq_randcomplex(int length);
LinkedListSequence<string> get_listseq_randstring(int length);

template<class T>
bool decrease(T a, T b) {
    return a<b;
}

template<class T>
T *get_items(int length) {
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    T *items = new T[length]();
    cout << "Input sequence:" << endl;
    T value;
    for (int i = 0; i < length; i++) {
        cin >> value;
        items[i] = value;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return items;
}

template<class T>
ArraySequence<T> getSequence(int length) {
    T *items = get_items<T>(length);
    ArraySequence<T> seq = ArraySequence<T>(items, length);
    delete[] items;
    return seq;
}

template<class T>
LinkedListSequence<T> getListSequence(int length) {
    T *items = get_items<T>(length);
    LinkedListSequence<T> seq = LinkedListSequence<T>(items, length);
    delete[] items;
    return seq;
}

template<class T>
void menu(Sequence<T>& seq) {
    Sequence<T> *sorted_seq;
    Sequence<T> *sorted_seq_2;
    int sort;
    int action;

    clock_t start_time;
    clock_t end_time;
    double search_time;

    cout << "Choose action:\n 0 - sort\n 1 - compare sorts" << endl;
    action = dialog(2);
    if (action == 0) {
        cout << "Input sort type:\n 0 - shell\n 1 - quick" << endl;
        sort = dialog(2);
        switch (sort) {
            case 0:
                sorted_seq = (seq.Sort(ShellSort<T>()));
                break;
            case 1:
                sorted_seq = (seq.Sort(QuickSort<T>()));
                break;
            default:
                cout << "There is no such sort type" << endl;
                break;
        }
    } else if (action == 1) {
        start_time =  clock();
        sorted_seq = seq.Sort(ShellSort<T>());
        end_time = clock();
        search_time = (end_time - start_time)/(double) CLOCKS_PER_SEC;
        cout << "ShellSort time: " << search_time * 1000000 << " nanoseconds" << endl;

        start_time =  clock();
        sorted_seq = seq.Sort(QuickSort<T>());
        end_time = clock();
        search_time = (end_time - start_time)/(double) CLOCKS_PER_SEC;
        cout << "QuickSort time: " << search_time * 1000000 << " nanoseconds" << endl;

        start_time =  clock();
        sorted_seq_2 = sorted_seq->Sort(ShellSort<T>());
        end_time = clock();
        search_time = (end_time - start_time)/(double) CLOCKS_PER_SEC;
        cout << "ShellSort time for sorted sequence: " << search_time * 1000000 << " nanoseconds" << endl;

        start_time =  clock();
        sorted_seq_2 = sorted_seq->Sort(QuickSort<T>());
        end_time = clock();
        search_time = (end_time - start_time)/(double) CLOCKS_PER_SEC;
        cout << "QuickSort time for sorted sequence: " << search_time * 1000000 << " nanoseconds" << endl;
    }
}

#endif //INC_2S_LAB1_UTILS_H
