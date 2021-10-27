#ifndef LAB_2_ARRAYSEQ_H
#define LAB_2_ARRAYSEQ_H

#include <pybind11/pybind11.h>
#include <iostream>
#include "DynArray.h"
#include "Sequence.h"
#include "ISorter.h"

namespace py = pybind11;
using namespace std;

template <class T>
class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T> items;
public:
//    ArraySequence<T> &operator=(const Sequence<T> &sequence){
//        if (items!=NULL) {
//            delete this->items;
//        }
//        this->items = DynamicArray<T> (*sequence.items);
//        return *this;
//    }

    ArraySequence(){
        items = DynamicArray<T> ();
    }

    explicit ArraySequence(int length){
        if (length<=0){
            throw runtime_error("Incorrect length");
        }
        items = DynamicArray<T> (length);
    }

    ArraySequence(vector<T> got_items, int count){
        if (count<=0){
            throw runtime_error("Incorrect length");
        }
        if (got_items.size()==0){
            throw runtime_error("NULL items");
        }
        items = DynamicArray<T> (got_items, count);
    }

    ArraySequence(const ArraySequence <T> & list ){
        items = DynamicArray<T> (list.items);
    }


    T &Get(int index){
        return items.Get(index);
    }

    T &GetFirst(){
        return Get(0);
    }

    T &GetLast(){
        return Get(items.GetSize()-1);
    }

    int GetLength(){
        return items.GetSize();
    }

    void Set(int index, T value){
        items.Set(index,value);
    }

    void Append(T item){
        items.Resize(items.GetSize()+1);
        items.Set(items.GetSize()-1, item);
    }

    void Prepend(T item){
        items.Resize(items.GetSize()+1);
        for(int i=items.GetSize()-1; i>0; i--){
            items.Set(i,items.Get(i-1));
        }
        items.Set(0,item);
    }

    void InsertAt(T item, int index){
        items.Resize(items.GetSize()+1);
        for(int i=items.GetSize()-1; i>=index; i--){
            items.Set(i,items.Get(i-1));
        }
        items.Set(index,item);
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex){
        if (startIndex >= endIndex){
            throw runtime_error("Incorrect indexes");
        }
        ArraySequence<T> *new_list = new ArraySequence<T>();
        for(int i=startIndex; i<=endIndex; i++){
            new_list->Append(this->Get(i));
        }

        return new_list;
    }

    ArraySequence <T>* Concat(Sequence <T> *list){
        ArraySequence<T> *new_list = new ArraySequence<T>();
        for(int i=0; i<items.GetSize(); i++){
            new_list->Append(this->Get(i));
        }
        for(int i=0; i<list->GetLength(); i++){
            new_list->Append(list->Get(i));
        }

        return new_list;
    }

//    ArraySequence <T>* Concat(ArraySequence <T> *list){
//        ArraySequence<T> *new_list = new ArraySequence<T>();
//        for(int i=0; i<items.GetSize(); i++){
//            new_list->Append(this->Get(i));
//        }
//        for(int i=0; i<list->GetLength(); i++){
//            new_list->Append(list->Get(i));
//        }
//
//        return new_list;
//    }

    ArraySequence <T>* Map(T (f)(T )){
        ArraySequence<T> *new_list = new ArraySequence<T>();
        for(int i=0; i<items.GetSize(); i++){
            new_list->Append(f(this->Get(i)));
        }

        return new_list;
    }

    ArraySequence <T>* Where(bool (f)(T )){
        ArraySequence<T> *new_list = new ArraySequence<T>();
        for(int i=0; i<items.GetSize(); i++){
            if (f(this->Get(i))==true){
                new_list->Append(this->Get(i));
            }
        }

        return new_list;
    }

    T Reduce(T (f)(T, T), T c){
        T ans;
        T arg = c;
        for(int i=0; i<items.GetSize(); i++){
            ans = f(this->Get(i), arg);
            arg = ans;
        }
        return ans;
    }

    ArraySequence<T>* Sort(ISorter<T> &f) {
        ArraySequence<T>* newseq = new ArraySequence<T>(*this);
        f.Sort(*newseq);
        return newseq;
    }

    string SeqToString() {
        string s = "[";
        for (int i = 0; i < this->GetLength(); i++) {
            s = s + to_string(this->Get(i)) + ",";
        }
        s[s.length()-1] = ']';
        return s;
    }

    void Print(){
        items.Print();
    }
};

#endif //LAB_2_ARRAYSEQ_H
