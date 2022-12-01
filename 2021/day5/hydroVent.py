

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    hydroVents = readFile("input")
    maxX = 0
    maxY = 0
    linePoints = [[[] for _ in range(4)] for _ in range(500)]
    lineNumber = 0 
    for hydroVent in hydroVents:
        x1y1,x2y2 = hydroVent.split(" -> ")
        x1,y1 = x1y1.split(",")
        x2,y2 = x2y2.split(",")
        x1 = int(x1.strip())
        y1 = int(y1.strip())
        x2 = int(x2.strip())
        y2 = int(y2.strip())
        if maxX < x1:
            maxX = x1
        if maxX < x2:
            maxX = x2
        if maxY < y1:
            maxY = y1
        if maxY < y2:
            maxY = y2
        print(f"{x1},{y1} -> {x2},{y2}")
        linePoints[lineNumber][0] = x1
        linePoints[lineNumber][1] = y1
        linePoints[lineNumber][2] = x2
        linePoints[lineNumber][3] = y2
        lineNumber += 1
    print(f"{linePoints}")

    hydroVentMap = [[0 for _ in range(maxY+1)] for _ in range(maxX+1)]
    print(f"{hydroVentMap}")
    print(f"{maxX} {maxY}")
    for line in range(len(linePoints)):
        if linePoints[line][0] == linePoints[line][2]: # horizontal line
            x = linePoints[line][0]
            if linePoints[line][3] > linePoints[line][1]:
                y1 = linePoints[line][1]
                y2 = linePoints[line][3]
            else: 
                y1 = linePoints[line][3]
                y2 = linePoints[line][1]
            for y in range(y1,y2+1):
#                print(f"({x} {y})", end=" ")
                hydroVentMap[x][y] += 1

        if linePoints[line][1] == linePoints[line][3]: # vertical line
            y = linePoints[line][1]
            if linePoints[line][2] > linePoints[line][0]:
                x1 = linePoints[line][0]
                x2 = linePoints[line][2]
            else: 
                x1 = linePoints[line][2]
                x2 = linePoints[line][0]
            for x in range(x1,x2+1):
#                print(f"({x} {y})", end=" ")
                hydroVentMap[x][y] += 1
    #print(f"{hydroVentMap}")
    ventCount = 0
    for x in range(maxX+1):
        prevVent = 0
        for y in range(maxY+1):
            if hydroVentMap[x][y] > 1:
                if preVent != hydroVentMap[x][y] or preVent == hydroVentMap[x][y]:
                    print(f"{x},{y} {preVent} - {hydroVentMap[x][y]}")
                    ventCount += 1
            preVent = hydroVentMap[x][y]
                
    print(f"{ventCount}")
