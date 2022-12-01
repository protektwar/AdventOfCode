

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    wirings = readFile("input")
    digitsCount = 0
    for i, wiring in enumerate(wirings):
        print("---------------------->>>>>>>>>>>>>>>>>>>>>>")
        wires, fourDigits = wiring.strip().split('|')
        print(f"line: {i} {wireSignalPatterns} - {fourDigitOutputs}")
        for digitOutput in fourDigits.split():
            # 1 - len 2 | 4 - len 4 | 7 - len 3 | 8 - len 7
            if len(digitOuput) in [2, 3, 4, 7]:
                print(f"digitOutput: {digitOutput} lenth: {len(digitOutput)}")
                matchingPatterns = [wireSignalPattern 
                                    for wireSignalPattern in wires.split() 
                                    if len(wireSignalPattern) == len(digitOutput)
                                   ]
                print(f"matchingPatterns: {matchingPatterns}")
                for matchingPattern in matchingPatterns:
                    matched = True
                    for char in list(digitOutput):
                        print(f"matchingPattern: {matchingPattern} {char}")
                        if matchingPattern.count(char) > 1 or matchingPattern.count(char) == 0:
                            matched = False
                            print("False break")
                            break
                        print("True continue")
                    if matched:
                        digitsCount += 1
                        print (f"matchingPattern: {matchingPattern} TotalDigitCount: {digitsCount}")
        print("---------------------->>>>>>>>>>>>>>>>>>>>>>")
    print(f"{digitsCount}")

