

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    bingoNumbers = lines[0].strip().split(',')
    lines = lines[2:]
    cardCount = 0
    bingoCards = [[[{} for _ in range(5)] for _ in range(5)] for _ in range(100)]
    i = 0
    j = 0 
    for line in lines:
        if line == "\n":
            cardCount += 1
            i = 0
            j = 0 
        else:
            line = line.strip()
            j = 0
            for number in line.split():
#                print(f"{cardCount}-{i},{j} - {number}")
                bingoCards[cardCount][i][j] = {'value':int(number),'found':False}
                j += 1
            i += 1
#    print(bingoCards)
    return bingoNumbers, bingoCards

def checkIfBingoLineRow(cardNumber):
    for i in range(5):
        bingo = True
        for j in range(5):
            if not bingoCards[cardNumber][i][j]['found']:
                bingo = False
        if bingo:
            return bingo, i
    return bingo, -1

def checkIfBingoLineCol(cardNumber):
    for j in range(5):
        bingo = True
        for i in range(5):
            if not bingoCards[cardNumber][i][j]['found']:
                bingo = False
        if bingo:
            return bingo, j
    return bingo, -1

def printBingoCard(cardNumber):
    for i in range(5):
        for j in range(5):
            if bingoCards[cardNumber][i][j]['found']:
                print(f"!{bingoCards[cardNumber][i][j]['value']:2}", end = " ")
            else:
                print(f"{bingoCards[cardNumber][i][j]['value']:3}",end = " ")
        print()
    print ()


def sumNumberOnCardExpectBingo(cardNumber):
    sumCard = 0
    for i in range(5):
        for j in range(5):
            if not bingoCards[cardNumber][i][j]['found']:
                sumCard = sumCard + int(bingoCards[cardNumber][i][j]['value'])
    return sumCard

if __name__ == '__main__':
    bingoNumbers, bingoCards = readFile("input")
    for bingoNumber in bingoNumbers:
        bingoNumber = int(bingoNumber.strip())
#        printBingoCards(bingoCards)
        for cardNumber in range(len(bingoCards)):
#            print(bingoCards[cardNumber])
            print(f"BingoNumber: {bingoNumber} Card: {cardNumber}->")
            for i in range(5):
                for j in range(5):
#                    print(f"{bingoCards[cardNumber][i][j]} {bingoCards[cardNumber][i][j]['value']}", end = " ")
                    if bingoNumber == int(bingoCards[cardNumber][i][j]['value']):
#                        print(f"{cardNumber} - {i} {j} {bingoNumber} Found {bingoCards[cardNumber][i][j]['value']}")
                        bingoCards[cardNumber][i][j]['found'] = True
#                print()
            bingoRow, row =  checkIfBingoLineRow(cardNumber)
            bingoCol, col =  checkIfBingoLineCol(cardNumber)
            printBingoCard(cardNumber)
#            input()
#            printBingoCards(bingoCards)
            if bingoRow:
                print(f"Row {bingoRow} {bingoNumber} {row} {cardNumber}")
                break
    
            if bingoCol:
                print(f"Col {bingoCol} {bingoNumber} {col} {cardNumber}")
                break
            print("<-")
        if bingoRow or bingoCol:
            break
    sumNumbers = sumNumberOnCardExpectBingo(cardNumber)        
    print(f"{sumNumbers} * {bingoNumber} = {sumNumbers * bingoNumber}")
