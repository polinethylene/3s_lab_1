import matplotlib.pyplot as plt
import datetime
import numpy as np
import PySequence

def compareArraySeq(x):
    y_shell = list()
    y_quick = list()
    my_formatter = "{0:.5f}"
    for el in x:
        items = np.random.random_integers(-10000, 10000, el)
        seq = PySequence.ArraySequence_int(items, el)
        a = datetime.datetime.now()
        sorted_seq = seq.Sort(PySequence.ShellSort_int())
        b = datetime.datetime.now()
        sorted_seq_2 = seq.Sort(PySequence.QuickSort_int())
        c = datetime.datetime.now()
        y_shell.append(float(my_formatter.format((b - a).total_seconds() * 1000)))
        y_quick.append(float(my_formatter.format((c - b).total_seconds() * 1000)))
    plt.xlabel('Array length')
    plt.ylabel('Time in ms')
    plt.plot(x, y_shell, 'r', label='shellsort')
    print("ShellSort time:", y_shell)
    plt.plot(x, y_quick, 'b', label='quicksort')
    print("QuickSort time:", y_quick)
    plt.legend()
    figname = 'Array'
    xmin, xmax = 0, x[-1]+50
    ymin, ymax = 0, y_shell[-1]
    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)
    plt.savefig(figname)
    plt.clf()

def compareListSeq(x):
    y_shell = list()
    y_quick = list()
    my_formatter = "{0:.5f}"
    for el in x:
        items = np.random.random_integers(-10000, 10000, el)
        seq = PySequence.LinkedListSequence_int(items, el)
        a = datetime.datetime.now()
        sorted_seq = seq.Sort(PySequence.ShellSort_int())
        b = datetime.datetime.now()
        sorted_seq_2 = seq.Sort(PySequence.QuickSort_int())
        c = datetime.datetime.now()
        y_shell.append(float(my_formatter.format((b - a).total_seconds() * 1000)))
        y_quick.append(float(my_formatter.format((c - b).total_seconds() * 1000)))
    plt.xlabel('Array length')
    plt.ylabel('Time in ms')
    plt.plot(x, y_shell, 'r', label='shellsort')
    print("ShellSort time:", y_shell)
    plt.plot(x, y_quick, 'b', label='quicksort')
    print("QuickSort time:", y_quick)
    plt.legend()
    figname = 'LinkedList'
    xmin, xmax = 0, x[-1]+50
    ymin, ymax = 0, y_shell[-1]
    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)
    plt.savefig(figname)
    plt.clf()

if __name__ == "__main__":
    x = list([50,100,150,200,250,300,350,400,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200])
    compareArraySeq(x)
    compareListSeq(x)