

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines[0]

if __name__ == '__main__':
    initialState = [int(x) for x in readFile("input").strip().split(',')]
    dayCount = 1
    counter = len(initialState) 
#    for day in range(80):
    for day in range(256):
        counter += initialState.count(0)
#        print(f"{day} - {initialState.count(0)}")
        for i in range(len(initialState)):
            if initialState[i] == 0:
                initialState[i] = 6
                initialState.append(8)
                continue
            initialState[i] -= 1
            
    print(f"{len(initialState)} {counter}")

