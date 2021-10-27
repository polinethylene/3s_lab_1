#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int dialog(int n) {
    int choice;
    cin >> choice;
    while(choice < 0 || choice >= n) {
        cout << "Wrong input." << endl;
        cin >> choice;
    }
    return choice;
}

ArraySequence<int> get_seq_randint(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    int *items = new int[length]();
    int value;
    for (int i = 0; i < length; i++) {
        value = rand() % 20000 - 10000;
        items[i] = value;
    }
    ArraySequence<int> seq = ArraySequence<int>(items, length);
    delete[] items;
    return seq;
}

ArraySequence<float> get_seq_randfloat(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    float *items = new float[length]();
    float value;
    float LO = -10000, HI = 10000;
    for (int i = 0; i < length; i++) {
        value = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        items[i] = value;
    }
    ArraySequence<float> seq = ArraySequence<float>(items, length);
    delete[] items;
    return seq;
}

ArraySequence<Complex> get_seq_randcomplex(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    Complex *items = new Complex[length]();
    float re,im;
    float LO = -100000, HI = 100000;
    for (int i = 0; i < length; i++) {
        re = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        im = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        items[i] = Complex(re,im);
    }
    ArraySequence<Complex> seq = ArraySequence<Complex>(items, length);
    delete[] items;
    return seq;
}

ArraySequence<string> get_seq_randstring(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    string *items = new string[length]();
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    int len = 4;

    for (int j = 0; j < length; ++j) {
        string tmp;
        tmp.reserve(len);

        for (int i = 0; i < len; ++i)
            tmp += alphanum[rand() % (sizeof(alphanum) - 1)];

        items[j] = tmp;
    }

    ArraySequence<string> seq = ArraySequence<string>(items, length);
    delete[] items;
    return seq;
}

LinkedListSequence<int> get_listseq_randint(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    int *items = new int[length]();
    int value;
    for (int i = 0; i < length; i++) {
        value = rand() % 20000 - 10000;
        items[i] = value;
    }
    LinkedListSequence<int> seq = LinkedListSequence<int>(items, length);
    delete[] items;
    return seq;
}

LinkedListSequence<float> get_listseq_randfloat(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    float *items = new float[length]();
    float value;
    float LO = -10000, HI = 10000;
    for (int i = 0; i < length; i++) {
        value = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        items[i] = value;
    }
    LinkedListSequence<float> seq = LinkedListSequence<float>(items, length);
    delete[] items;
    return seq;
}

LinkedListSequence<Complex> get_listseq_randcomplex(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    Complex *items = new Complex[length]();
    float re,im;
    float LO = -100000, HI = 100000;
    for (int i = 0; i < length; i++) {
        re = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        im = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        items[i] = Complex(re,im);
    }
    LinkedListSequence<Complex> seq = LinkedListSequence<Complex>(items, length);
    delete[] items;
    return seq;
}

LinkedListSequence<string> get_listseq_randstring(int length) {
    srand (static_cast <unsigned> (time(0)));
    if (length <= 0) {
        throw runtime_error("Incorrect length");
    }
    string *items = new string[length]();
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    int len = 4;

    for (int j = 0; j < length; ++j) {
        string tmp;
        tmp.reserve(len);

        for (int i = 0; i < len; ++i)
            tmp += alphanum[rand() % (sizeof(alphanum) - 1)];

        items[j] = tmp;
    }

    LinkedListSequence<string> seq = LinkedListSequence<string>(items, length);
    delete[] items;
    return seq;
}