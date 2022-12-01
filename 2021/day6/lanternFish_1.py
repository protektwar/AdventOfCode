

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines[0]

if __name__ == '__main__':
    initialState = [int(x) for x in readFile("input").strip().split(',')]
    dayCount = 1
    counter = 0 
    for i in range(len(initialState)):
        counter += (((6 * 80) - initialState[i]) * (80 / initialState[i]))
        print(f"{initialState[i]} {counter} {(6-initialState[i])*80} {80/initialState[i]}")
            
            
    print(f"{counter}")

