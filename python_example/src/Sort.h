#ifndef INC_2S_LAB1_SORT_H
#define INC_2S_LAB1_SORT_H
#include "Sequence.h"
#include "ISorter.h"

template<class T>
void swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class T>
class ShellSort : public ISorter<T>{
public:
    ShellSort()=default;

    void Sort(Sequence<T>& seq) {
        for (int gap = seq.GetLength()/2; gap > 0; gap /= 2) {
            for (int i = gap; i < seq.GetLength(); i += 1) {
                T temp = seq.Get(i);
                int j;
                for (j = i; j >= gap && this->cmp(seq.Get(j-gap), temp); j -= gap)
                    seq.Get(j) = seq.Get(j-gap);

                seq.Get(j) = temp;
            }
        }
    }
    virtual ~ShellSort(){};
};

template <class T>
class QuickSort : public ISorter<T>{
public:
    QuickSort()=default;

    int partition (Sequence<T>& seq, int low, int high) {
        T pivot = seq.Get(high);
        int i = (low - 1);

        for (int j = low; j <= high- 1; j++)
        {
            if (seq.Get(j) <= pivot)
            {
                i++;
                swap(seq.Get(i), seq.Get(j));
            }
        }
        swap(seq.Get(i+1), seq.Get(high));
        return (i + 1);
    }

    void quickSort(Sequence<T>& seq, int low, int high) {
        if (low < high)
        {
            int pi = partition(seq, low, high);

            quickSort(seq, low, pi - 1);
            quickSort(seq, pi + 1, high);
        }
    }

    void Sort(Sequence<T>& seq) {
        quickSort(seq, 0, seq.GetLength() - 1);
    }

    virtual ~QuickSort(){};
};

#endif //INC_2S_LAB1_SORT_H
