#ifndef INC_2S_LAB1_ISORTER_H
#define INC_2S_LAB1_ISORTER_H

template <class T> class Sequence;

template <class T> class ISorter{
protected:
//    bool (*cmp)(T,T);
    const std::function<bool(T,T)> cmp;
public:
//    ISorter(bool (*cmp)(T,T)) : cmp(cmp){};
    ISorter(const std::function<bool(T,T)> cmp) : cmp(cmp){};
    ISorter() : ISorter([](T a, T b) -> bool {return a>b;}){};
    virtual void Sort(Sequence<T>& seq) = 0;
    virtual ~ISorter(){};
};

#endif //INC_2S_LAB1_ISORTER_H
