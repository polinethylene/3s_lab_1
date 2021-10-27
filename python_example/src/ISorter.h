#ifndef INC_2S_LAB1_ISORTER_H
#define INC_2S_LAB1_ISORTER_H
//#include "Sequence.h"
template <class T> class Sequence;

template <class T> class ISorter{
public:
    ISorter(){};
    virtual void Sort(Sequence<T>& seq) = 0;
    virtual ~ISorter(){};
};

#endif //INC_2S_LAB1_ISORTER_H
