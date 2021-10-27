#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <iostream>
#include "ArraySeq.h"
#include "LinkedListSeq.h"
#include "Sort.h"

namespace py = pybind11;
using namespace std;

template<typename T>
void declare_array(py::module &m, const string &typestr) {
    using Class = ArraySequence<T>;
    std::string pyclass_name = std::string("ArraySequence") + "_" + typestr;
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::dynamic_attr())
            .def(py::init<>())
            .def(py::init<int>())
            .def(py::init<vector<T>, int>())
            .def(py::init<const Class &>())
            .def("Get",      &Class::Get)
            .def("GetFirst",     &Class::GetFirst)
            .def("GetLast",    &Class::GetLast)
            .def("GetLength",      &Class::GetLength)
            .def("Set",     &Class::Set)
            .def("Append",    &Class::Append)
            .def("Prepend",      &Class::Prepend)
            .def("InsertAt",     &Class::InsertAt)
            .def("GetSubsequence",    &Class::GetSubsequence)
            .def("Concat",      &Class::Concat)
            .def("Map",    &Class::Map)
            .def("Where",      &Class::Where)
            .def("Reduce",    &Class::Reduce)
            .def("Sort",      &Class::Sort)
            .def("Print",     &Class::Print);
}


template<typename T>
void declare_list(py::module &m, const string &typestr) {
    using Class = LinkedListSequence<T>;
    string pyclass_name = string("LinkedListSequence") + "_" + typestr;
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::dynamic_attr())
            .def(py::init<>())
            .def(py::init<int>())
            .def(py::init<vector<T>, int>())
            .def("Get",      &Class::Get)
            .def("GetFirst",     &Class::GetFirst)
            .def("GetLast",    &Class::GetLast)
            .def("GetLength",      &Class::GetLength)
            .def("Set",     &Class::Set)
            .def("Append",    &Class::Append)
            .def("Prepend",      &Class::Prepend)
            .def("InsertAt",     &Class::InsertAt)
            .def("GetSubsequence",    &Class::GetSubsequence)
            .def("Concat",      &Class::Concat)
            .def("Map",    &Class::Map)
            .def("Where",      &Class::Where)
            .def("Reduce",    &Class::Reduce)
            .def("Sort",      &Class::Sort)
            .def("Print",     &Class::Print);
}

template<class T>
class PyVirtualClass : public ISorter<T>{
        public:
            using ISorter<T>::ISorter;

            void Sort(Sequence<T>& seq) override {
                PYBIND11_OVERRIDE_PURE(
                    void,
                    ISorter<T>,
                    Sort,
                    seq
                    );
            }

    };

template <typename T>
void declare_sort(py::module &m, const string& typestr1)
{
    string pyclass_name = string("ISorter") + "_" + typestr1;
    py::class_<ISorter <T>, PyVirtualClass<T>>(m,pyclass_name.c_str(),py::module_local())
        .def(py::init<>())
<<<<<<< Updated upstream
=======
        .def(py::init<std::function<bool(T,T)>>())
>>>>>>> Stashed changes
        .def("Sort", &ISorter <T>::Sort);

    string pyshell_name = string("ShellSort") + "_" + typestr1;
    py::class_<ShellSort<T>, ISorter<T>>(m, pyshell_name.c_str())
        .def(py::init<>())
<<<<<<< Updated upstream
=======
        .def(py::init<std::function<bool(T,T)>>())
>>>>>>> Stashed changes
        .def("Sort", &ShellSort <T>::Sort);

    string pyquick_name = string("QuickSort") + "_" + typestr1;
    py::class_<QuickSort<T>, ISorter<T>>(m, pyquick_name.c_str())
        .def(py::init<>())
<<<<<<< Updated upstream
=======
        .def(py::init<std::function<bool(T,T)>>())
>>>>>>> Stashed changes
        .def("Sort", &QuickSort <T>::Sort);
};

PYBIND11_MODULE(PySequence, m) {
    declare_array<int>(m, "int");
    declare_array<float>(m, "float");
    declare_array<string>(m, "string");
    declare_list<int>(m, "int");
    declare_list<float>(m, "float");
    declare_list<string>(m, "string");
    declare_sort<int>(m, "int");
    declare_sort<float>(m, "float");
    declare_sort<string>(m, "string");
}