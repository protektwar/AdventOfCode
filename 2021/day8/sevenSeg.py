

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    wirings = readFile("input")
    digitsCount = 0
    for i, wiring in enumerate(wirings):
        wires, fourDigits = wiring.strip().split('|')
        for digitOutput in fourDigits.split():
            # 1 - len 2 | 4 - len 4 | 7 - len 3 | 8 - len 7
            if len(digitOutput) in [2, 3, 4, 7]:
                for matchingPattern in [wireSignalPattern 
                                        for wireSignalPattern in wires.split()
                                        if len(wireSignalPattern) == len(digitOutput)
                                        ]:
                    matched = True
                    for char in list(digitOutput):
                        if matchingPattern.count(char) > 1 or matchingPattern.count(char) == 0:
                            matched = False
                            break
                    if matched:
                        digitsCount += 1
    print(f"{digitsCount}")

