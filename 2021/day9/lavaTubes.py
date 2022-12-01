import sys
#n = 5 
#m = 10 
n = 100
m = 100

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

def isValid(i, j, smokeFlowMatrixMins):
    if (i >= 0 and i < n and j >= 0 and j < m):
        if str(smokeFlowMatrixMins[i][j]) == ' ':
            print("isValid true")
            return True 
    print("isValid false")
    return False 

def printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix):
     for i in range(n):
         print(f"{('').join(map(str,smokeFlowMatrixMins[i]))} {('').join(map(str,smokeFlowsMatrix[i]))}")

def findMin(i, j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move):
    for k in range(4):
        print(f"findMin x_move[{k}] = {x_move[k]}")
        print(f"findMin y_move[{k}] = {y_move[k]}")
        next_i = i + x_move[k]
        next_j = j + y_move[k]
        print(f"findMin before isValid {smokeFlowsMatrix[i][j]} i:{i} j:{j} next_i:{next_i} next_j:{next_j}")
        if isValid(next_i, next_j, smokeFlowMatrixMins):# and isValid(i, j, smokeFlowMatrixMins):
            print(f"findMin isValid i:{i} j:{j} next_i:{next_i} next_j:{next_j}")
            print(f"findMin sFM[{i}][{j}]:{smokeFlowsMatrix[i][j]} >= sFM[{next_i}][{next_j}]:{smokeFlowsMatrix[next_i][next_j]}?")
            if smokeFlowsMatrix[i][j] >= smokeFlowsMatrix[next_i][next_j]:
                print(f"findMin {smokeFlowsMatrix[i][j]} >= {smokeFlowsMatrix[next_i][next_j]}")
                smokeFlowMatrixMins[i][j] = smokeFlowsMatrix[i][j]
#                smokeFlowMatrixMins[next_i][next_j] = smokeFlowsMatrix[next_i][next_j]
                print(f"findMin smokeFlowMatrixMins[{next_i}][{next_j}]:  {smokeFlowsMatrix[next_i][next_j]}")
                print(f"findMin before findMin next Call")
                printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix)
                if findMin(next_i, next_j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move):
                    printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix)
                    return True
            else:
                print(f"findMin {smokeFlowsMatrix[i][j]} < {smokeFlowsMatrix[next_i][next_j]}")
                smokeFlowMatrixMins[i][j] = ' '#smokeFlowsMatrix[i][j] 
                smokeFlowMatrixMins[next_i][next_j] = smokeFlowsMatrix[next_i][next_j]
                print(f"findMin smokeFlowMatrixMins[{next_i}][{next_j}]:  {smokeFlowsMatrix[next_i][next_j]}")
                print(f"findMin before findMin next Call")
                printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix)
                if findMin(next_i, next_j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move):
                    printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix)
                    return True
                
            printMinMatrix(smokeFlowMatrixMins, smokeFlowsMatrix)
#        input()
    print(f"findMin False exit")
    return False

if __name__ == '__main__':
#    smokeFlows = readFile("input.demo")
    smokeFlows = readFile("input")
#                   [i-1][j]
#          [i][j-1] [i][j] [i][j+1]
#                   [i+1][j]
           #   W   N   E   S
    x_move = [-1,  0,  1,  0]
    y_move = [ 0, -1,  0,  1]
    smokeFlowsMatrix = [ [] for _ in range(n)]
    smokeFlowMatrixMins = [ [' ' for _ in range(m)] for _ in range(n)]
    for i,smokeFlow in enumerate(smokeFlows):
        smokeFlowsMatrix[i] = [int(x) for x in smokeFlow.strip()]
#        print(f"{smokeFlowsMatrix[i]}")
#    input() 
    for i in range(n):
        for j in range(m):
            print(f"----{i}-{j}---->>>")
            findMin(i, j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move)
            print(f"<<<-{i}-{j}-------")
#        print(f"{('').join(map(str,smokeFlowMatrixMins[i]))}")
    sum = 0
    for i in range(n):
        for j in range(m):
            if smokeFlowsMatrix[i][j] != smokeFlowMatrixMins[i][j]:
                sum += smokeFlowsMatrix[i][j] + 1
    print(f"sum of risk levels: {sum}")
                
     
