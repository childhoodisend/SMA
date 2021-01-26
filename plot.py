from matplotlib import pylab


def importdata(filaname: str):
    data = []
    with open(filaname) as f:
        for line in f:
            data.append([float(x) for x in line.split()])
    return data


datatest = importdata("data/test.txt")


def plot(filename: str, position: int):
    data = importdata(filename)

    pylab.subplot(2, 3, position)
    pylab.plot([i for i in range(20)], data[:20], [i for i in range(20)], datatest[:20])
    pylab.title(filename)


for i in range(2, 8):
    plot("data/data" + str(2 ** i) + "d.txt", i - 1)
pylab.show()
for i in range(2, 8):
    plot("data/data" + str(2 ** i) + "f.txt", i - 1)
pylab.show()
