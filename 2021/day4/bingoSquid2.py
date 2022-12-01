

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
    bingoCardsWin =[ False for _ in range(100)]
    itIsLast = False
    lastCard = 0
    for bingoNumber in bingoNumbers:
        bingoNumber = int(bingoNumber.strip())
        for cardNumber in range(len(bingoCards)):
            print(f"Card: {cardNumber} | {bingoCardsWin.count(True)} out of {len(bingoCardsWin)} won\n")
            print(f"BingoNumber: {bingoNumber} Card: {cardNumber}->")
            if bingoCardsWin[cardNumber]:
                print("continue <-")
                continue
            for i in range(5):
                for j in range(5):
                    if bingoNumber == int(bingoCards[cardNumber][i][j]['value']):
                        bingoCards[cardNumber][i][j]['found'] = True
            bingoRow, row =  checkIfBingoLineRow(cardNumber)
            bingoCol, col =  checkIfBingoLineCol(cardNumber)
            printBingoCard(cardNumber)
            if bingoRow:
                bingoCardsWin[cardNumber] = True
                print(f"Card: {cardNumber} | {bingoCardsWin.count(True)} out of {len(bingoCardsWin)} won\n")
                print(f"Row | bingoRow: {bingoRow} *{bingoNumber}* {row} Card: {cardNumber}")
                if bingoCardsWin.count(False) == 0:
                    itIsLast = True
                    lastCard = cardNumber
    
            if bingoCol:
                bingoCardsWin[cardNumber] = True
                print(f"Card: {cardNumber} | {bingoCardsWin.count(True)} out of {len(bingoCardsWin)} won\n")
                print(f"Col | bingoCol: {bingoCol} *{bingoNumber}* {col} Card: {cardNumber}")
                if bingoCardsWin.count(False) == 0:
                    itIsLast = True
                    lastCard = cardNumber
            print("<-")
        if itIsLast:
            break
    
    sumNumbers = sumNumberOnCardExpectBingo(lastCard)        
    print(f"{sumNumbers} * {bingoNumber} = {sumNumbers * bingoNumber}")
