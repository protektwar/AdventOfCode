

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines[0]

if __name__ == '__main__':
    initialState = [int(x) for x in readFile("input").strip().split(',')]
    fishStates = [0 for _ in range(9)]
    
    for i in range(9):
        fishStates[i] = initialState.count(i)


    print(f"{fishStates}")
    for day in range(256):
        print(f"{day} {fishStates}")
        updateFishStates = [0 for _ in range(9)]
        for i in range(9):
            if i == 0:
                updateFishStates[6] += fishStates[i]
                updateFishStates[8] += fishStates[i]
            else:
                updateFishStates[i-1] +=fishStates[i]
        fishStates = updateFishStates.copy()
        print(f"!{day} {fishStates}")
        print(f"?{day} {updateFishStates}")

    print(f"{fishStates}")
    print(f"{sum(fishStates)}")


            

