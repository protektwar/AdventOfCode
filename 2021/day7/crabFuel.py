import sys

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines[0]

if __name__ == '__main__':
    #markov chains???
    horPos = [int(x) for x in readFile("input").strip().split(',')]
    print(f"{horPos}")
    fuelConsumption = 0
    totalFuelMin = 9223372036854775807 
    for i in range(len(horPos)):
        totalFuel = 0
        for j in range(len(horPos)):
            fuelAct = abs(horPos[i] - horPos[j])
            totalFuel += fuelAct
        if totalFuelMin > totalFuel:
            totalFuelMin = totalFuel
            

    print(f"{totalFuelMin}")
