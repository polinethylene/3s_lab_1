# This Python file uses the following encoding: utf-8
import sys
import random
import PySequence
import re
import numpy as np
from PySide6 import QtCore, QtWidgets, QtGui
from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QHBoxLayout, QWidget
import string
import datetime

ALPHABET = np.array(list(string.ascii_lowercase + string.ascii_uppercase))

def toString(seq):
    s = "["
    for i in range(seq.GetLength()):
        s = s + str(seq.Get(i)) + ", "
    s = s[:-2]
    s += "]"
    return s

def decreasingCompare(a,b):
    return a > b

def increasingCompare(a,b):
    return a < b

class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.emptyLabel = QtWidgets.QLabel("")

        self.seqBox = QtWidgets.QComboBox()
        self.seqBox.addItem("ListSequence")
        self.seqBox.addItem("ArraySequence")
        self.comBox = QtWidgets.QComboBox()
        self.comBox.addItem("increasing")
        self.comBox.addItem("decreasing")
        self.typeBox = QtWidgets.QComboBox()
        self.typeBox.addItem("int")
        self.typeBox.addItem("float")
        self.typeBox.addItem("string")
        self.sortBox = QtWidgets.QComboBox()
        self.sortBox.addItem("QuickSort")
        self.sortBox.addItem("ShellSort")

        self.lengthLineEdit = QtWidgets.QLineEdit()
        self.lengthLineEdit.setPlaceholderText("length")

        self.genButton = QtWidgets.QPushButton("Generate")
        self.sortButton = QtWidgets.QPushButton("Sort")
        self.comButton = QtWidgets.QPushButton("Compare")

        self.layout = QtWidgets.QVBoxLayout(self)
        self.layout.addWidget(self.emptyLabel)
        self.layout.addWidget(self.seqBox)
        self.layout.addWidget(self.typeBox)
        self.layout.addWidget(self.lengthLineEdit)
        self.layout.addWidget(self.sortBox)
        self.layout.addWidget(self.comBox)
        self.layout.addWidget(self.genButton)
        self.layout.addWidget(self.sortButton)
        self.layout.addWidget(self.comButton)
        self.layout.addStretch()
        self.layout.maximumWidth = 14


class InputWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.inputLabel = QtWidgets.QLabel("Input")

        self.inputTextEdit = QtWidgets.QTextEdit()
        self.inputTextEdit.setObjectName('display')

        self.layout = QtWidgets.QVBoxLayout(self)
        self.layout.addWidget(self.inputLabel)
        self.layout.addWidget(self.inputTextEdit)
        self.layout.addStretch()

        policy = self.sizePolicy()
        policy.setVerticalStretch(2)
        self.setSizePolicy(policy)


class OutputWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.outputLabel = QtWidgets.QLabel("Output")

        self.inputTextEdit = QtWidgets.QTextEdit()
        self.inputTextEdit.setObjectName('display')
        self.inputTextEdit.setReadOnly(True)

        self.layout = QtWidgets.QVBoxLayout(self)
        self.layout.addWidget(self.outputLabel)
        self.layout.addWidget(self.inputTextEdit)
        self.layout.addStretch()

        policy = self.sizePolicy()
        policy.setVerticalStretch(2)
        self.setSizePolicy(policy)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Lab 1")

        layout = QHBoxLayout()

        self.utilsWidget = MyWidget()
        self.inputWidget = InputWidget()
        self.outputWidget = OutputWidget()
        layout.addWidget(self.utilsWidget,0)
        layout.addWidget(self.inputWidget,2)
        layout.addWidget(self.outputWidget,2)

        widget = QWidget()
        widget.setLayout(layout)

        self.setCentralWidget(widget)

        self.items = [0, 1]
        self.utilsWidget.genButton.clicked.connect(self.genMagic)
        self.utilsWidget.sortButton.clicked.connect(self.sortMagic)
        self.utilsWidget.comButton.clicked.connect(self.compareMagic)

    def genMagic(self):
        length = int(self.utilsWidget.lengthLineEdit.text())
        if length:
            if str(self.utilsWidget.typeBox.currentText()) == "int":
                items = np.random.random_integers(-10000, 10000, length)
            elif str(self.utilsWidget.typeBox.currentText()) == "float":
                items = np.random.uniform(-10000, 10000, length)
            else:
                items = [''.join(random.choice(ALPHABET) for _ in range(5)) for i in range(length)]
            self.items = list(items)
            line = ''.join(str(self.items))
            msg = re.sub("\'", "",line)
            self.inputWidget.inputTextEdit.setPlainText(msg)

    def sortMagic(self):
        text = self.inputWidget.inputTextEdit.toPlainText()
        text_clear = re.sub("[^\w\.\s\-]", "",text)
        compare = increasingCompare if str(self.utilsWidget.comBox.currentText()) == "increasing" else decreasingCompare
        if str(self.utilsWidget.typeBox.currentText()) == "int":
            data = np.fromstring(text_clear, dtype=int, sep=' ')
            self.items = list(data)
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_int(self.items, len(self.items))
                sort_type = PySequence.ShellSort_int(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_int(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)
            else:
                seq = PySequence.LinkedListSequence_int(self.items, len(self.items))
                sort_type = PySequence.ShellSort_int(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_int(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)
        elif str(self.utilsWidget.typeBox.currentText()) == "float":
            data = np.fromstring(text_clear, dtype=float, sep=' ')
            self.items = list(data)
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_float(self.items, len(self.items))
                sort_type = PySequence.ShellSort_float(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_float(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)
            else:
                seq = PySequence.LinkedListSequence_float(self.items, len(self.items))
                sort_type = PySequence.ShellSort_float(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_float(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)
        else:
            self.items = text_clear.split(' ')
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_string(self.items, len(self.items))
                sort_type = PySequence.ShellSort_string(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_string(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)
            else:
                seq = PySequence.LinkedListSequence_string(self.items, len(self.items))
                sort_type = PySequence.ShellSort_string(compare) if str(self.utilsWidget.sortBox.currentText()) == "ShellSort" \
                    else PySequence.QuickSort_string(compare)
                sorted_seq = seq.Sort(sort_type)
                text_edit = toString(sorted_seq)

        self.outputWidget.inputTextEdit.setPlainText(text_edit)

    def compareMagic(self):
        my_formatter = "{0:.5f}"
        text = self.inputWidget.inputTextEdit.toPlainText()
        text_clear = re.sub("[^\w\.\s\-]", "", text)
        if str(self.utilsWidget.typeBox.currentText()) == "int":
            data = np.fromstring(text_clear, dtype=int, sep=' ')
            self.items = list(data)
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_int(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_int())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_int())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                      " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"
                # text_edit = toString(sorted_seq)
                # text_edit_2 = toString(sorted_seq_2)
            else:
                seq = PySequence.LinkedListSequence_int(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_int())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_int())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                      " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"
        elif str(self.utilsWidget.typeBox.currentText()) == "float":
            data = np.fromstring(text_clear, dtype=float, sep=' ')
            self.items = list(data)
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_float(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_float())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_float())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                      " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"
            else:
                seq = PySequence.LinkedListSequence_float(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_float())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_float())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                      " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"
        else:
            self.items = text_clear.split(' ')
            if str(self.utilsWidget.seqBox.currentText()) == "ArraySequence":
                seq = PySequence.ArraySequence_string(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_string())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_string())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                    " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"
            else:
                seq = PySequence.LinkedListSequence_string(self.items, len(self.items))
                a = datetime.datetime.now()
                sorted_seq = seq.Sort(PySequence.ShellSort_string())
                b = datetime.datetime.now()
                sorted_seq_2 = seq.Sort(PySequence.QuickSort_string())
                c = datetime.datetime.now()
                msg = "ShellSort time: " + str(my_formatter.format((b - a).total_seconds() * 1000)) + \
                      " ms\nQuickSort time: " + str(my_formatter.format((c - b).total_seconds() * 1000)) + "ms"

        self.outputWidget.inputTextEdit.setPlainText(msg)

if __name__ == "__main__":
    app = QApplication([])

    with open("style.qss", "r") as f:
            _style = f.read()
            app.setStyleSheet(_style)

    window = MainWindow()
    window.resize(900, 600)
    window.show()

    sys.exit(app.exec())
