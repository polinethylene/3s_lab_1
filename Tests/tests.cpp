#include <gtest/gtest.h>
#include "../python_example/src/ArraySeq.h"
#include "../python_example/src/LinkedListSeq.h"
#include "../python_example/src/Complex.h"
#include "../python_example/src/Sort.h"

TEST(Array_and_List, Create) {
    DynamicArray<int> array = DynamicArray<int>(10);
    int arr[7] = {1,2,3,4,5,6,7};
    DynamicArray<int> array_2 = DynamicArray<int>(arr, 4);
    ASSERT_EQ (10, array.GetSize());
    ASSERT_EQ (0, array.Get(3));
    ASSERT_ANY_THROW(array.Get(11));
    array.Set(3,12);
    ASSERT_EQ (12, array.Get(3));
    DynamicArray<int> array_3 = DynamicArray<int>(array_2);
    ASSERT_ANY_THROW(array.Resize(-1));
    array.Resize(11);
    ASSERT_EQ (0, array.Get(10));
    ASSERT_EQ (3, array_3.Get(2));

    LinkedList<int> list = LinkedList<int>(arr,5);
    cout << list.Get(2) << endl;
    ASSERT_EQ (1, list.GetFirst());
    ASSERT_EQ (5, list.GetLast());
    list.Append(2);
    list.Prepend(1);
    ASSERT_EQ (1, list.Get(0));
    ASSERT_EQ (2, list.GetLast());
    list.InsertAt(6,4);
    ASSERT_EQ (6, list.Get(4));
    ASSERT_EQ (8, list.GetLength());
}

TEST(Sequence, Create) {
    ArraySequence<int> array = ArraySequence<int>();
    ASSERT_EQ(0, array.GetLength());
    ASSERT_ANY_THROW(array.GetFirst());

    float arr[7] = {1.0,2,-3,4,53.6,6,7.19};
    ArraySequence<float> array_2 = ArraySequence<float>(10);
    ArraySequence<float> array_3 = ArraySequence<float>(arr, 7);
    ASSERT_EQ (10, array_2.GetLength());
    ASSERT_EQ (0, array_2.Get(3));
    ASSERT_ANY_THROW(array.Get(11));
    array.Set(3,12);
    ASSERT_FLOAT_EQ (-3, array_3.Get(2));
    ASSERT_FLOAT_EQ (12, array.Get(3));

    array_3.InsertAt(3.4,4);
    array_3.Prepend(0);
    array_3.Append(1.45);

    ASSERT_FLOAT_EQ (0, array_3.Get(0));
    ASSERT_FLOAT_EQ (53.6, array_3.Get(6));
    ASSERT_FLOAT_EQ (1.45, array_3.GetLast());

    ArraySequence<Complex> list = ArraySequence<Complex>();
    ASSERT_EQ(0, list.GetLength());
    ASSERT_ANY_THROW(list.GetFirst());

    Complex *arr2 = new Complex[4]();
    arr2[0] = Complex(2,3);
    arr2[1] = Complex(-1,2.3);
    arr2[2] = Complex(0,23);
    arr2[3] = Complex(7.8,-3);
    LinkedListSequence<Complex> list_2 = LinkedListSequence<Complex>(12);
    LinkedListSequence<Complex> list_3 = LinkedListSequence<Complex>(arr2, 4);

    ASSERT_EQ (12, list_2.GetLength());
    ASSERT_EQ (Complex(0,0), list_2.Get(3));

    ASSERT_ANY_THROW(list.Get(11));
    list_3.Set(3,Complex(12,3));

    ASSERT_EQ (Complex(0,23), list_3.Get(2));
    ASSERT_EQ (Complex(12,3), list_3.Get(3));
    list_3.InsertAt(Complex(12,2),3);
    list_3.Prepend(Complex(-3,1));
    list_3.Append(Complex(0,0));

    ASSERT_EQ (Complex(-3,1), list_3.Get(0));
    ASSERT_EQ (Complex(12,3), list_3.Get(5));
    ASSERT_EQ (Complex(0,0), list_3.GetLast());
}

TEST(LinkedListSequence_Sort, Sort)
{
    int items[5] = {1,4,3,2,5};
    float items2[5] = {0.1,4.4,2.3,7.2,6.5};
    string items3[5] = {"aabb","ccbb", "bbaa","ddee","wwqq"};

    LinkedListSequence<int> int_l_seq = LinkedListSequence<int>(items,5);
    LinkedListSequence<float> float_l_seq = LinkedListSequence<float>(items2,5);
    LinkedListSequence<string> string_l_seq = LinkedListSequence<string>(items3,5);

    Sequence<int> *sorted_seq_int = (int_l_seq.Sort(ShellSort<int>()));
    Sequence<int> *sorted_seq_int_2 = (int_l_seq.Sort(QuickSort<int>()));
    Sequence<float> *sorted_seq_float = (float_l_seq.Sort(ShellSort<float>()));
    Sequence<float> *sorted_seq_float_2 = (float_l_seq.Sort(QuickSort<float>()));
    Sequence<string> *sorted_seq_string = (string_l_seq.Sort(ShellSort<string>()));
    Sequence<string> *sorted_seq_string_2 = (string_l_seq.Sort(QuickSort<string>()));

    ASSERT_EQ (4, sorted_seq_int->Get(3));
    ASSERT_EQ (3, sorted_seq_int_2->Get(2));
    ASSERT_FLOAT_EQ (6.5, sorted_seq_float->Get(3));
    ASSERT_FLOAT_EQ (4.4, sorted_seq_float_2->Get(2));
    ASSERT_EQ ("aabb", sorted_seq_string->Get(0));
    ASSERT_EQ ("ccbb", sorted_seq_string_2->Get(2));
}

TEST(ArraySequence_Sort, Sort)
{
    int items[5] = {1,4,3,2,5};
    float items2[5] = {0.1,4.4,2.3,7.2,6.5};
    string items3[5] = {"aabb","ccbb", "bbaa","ddee","wwqq"};

    ArraySequence<int> int_seq = ArraySequence<int>(items,5);
    ArraySequence<float> float_seq = ArraySequence<float>(items2,5);
    ArraySequence<string> string_seq = ArraySequence<string>(items3,5);

    Sequence<int> *sorted_seq_int = (int_seq.Sort(ShellSort<int>()));
    Sequence<int> *sorted_seq_int_2 = (int_seq.Sort(QuickSort<int>()));
    Sequence<float> *sorted_seq_float = (float_seq.Sort(ShellSort<float>()));
    Sequence<float> *sorted_seq_float_2 = (float_seq.Sort(QuickSort<float>()));
    Sequence<string> *sorted_seq_string = (string_seq.Sort(ShellSort<string>()));
    Sequence<string> *sorted_seq_string_2 = (string_seq.Sort(QuickSort<string>()));

    ASSERT_EQ (4, sorted_seq_int->Get(3));
    ASSERT_EQ (3, sorted_seq_int_2->Get(2));
    ASSERT_FLOAT_EQ (6.5, sorted_seq_float->Get(3));
    ASSERT_FLOAT_EQ (4.4, sorted_seq_float_2->Get(2));
    ASSERT_EQ ("aabb", sorted_seq_string->Get(0));
    ASSERT_EQ ("ccbb", sorted_seq_string_2->Get(2));
}
