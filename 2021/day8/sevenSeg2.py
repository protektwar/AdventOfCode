

def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    wirings = readFile("input")
    sumDigits = 0
    for i, wiring in enumerate(wirings):
        wires, fourDigits = wiring.strip().split('|')
        print(f"{wires.split()} - {fourDigits.split()} []")
        digitsCount = 0
        digitsNumber = []
        # creating dictionary
        digit1 = [x for x in wires.split() if len(x) == 2][0]
        digit7 = [x for x in wires.split() if len(x) == 3][0]
        digit4 = [x for x in wires.split() if len(x) == 4][0]
        digit8 = [x for x in wires.split() if len(x) == 7][0]
        digits069 = [x for x in wires.split() if len(x) == 6]
        digits235 = [x for x in wires.split() if len(x) == 5]
#        print(f"{digit1}")
#        print(f"{digit4}")
#        print(f"{digit7}")
#        print(f"{digit8}")
#        print(f"{digits069}")
#        print(f"{digits235}")

        wireDigit1 = set(list(digit1))
        wireDigit7 = set(list(digit7))
        wireDigit4 = set(list(digit4))
        wireDigit8 = set(list(digit8))
   
        for wire in digits069:
            wireSet = set(list([x for x in wire]))
            segment = ('').join(map(str,wireDigit8 - wireSet))
#            print(f"wire: {wire} segment:{segment} in {digit1}")
            machted = True
            for char in segment:
                if not char in digit1:
                    machted = False
#                    print(f"False")
            if machted:
#                print(f"found 6")
                wireDigit6 = wireSet
                delete6 = wire
                
        digits09 = [x for x in digits069 if x != delete6]
        for wire in digits09:
            wireSet = set(list([x for x in wire]))
            segment = ('').join(map(str,wireDigit8 - wireSet))
#            print(f"wire: {wire} segment:{segment} in {digit4}")
            machted = True
            for char in segment:
                if not char in digit4:
                    machted = False
#                    print(f"False")
            if machted:
#                print(f"found 0")
                wireDigit0 = wireSet
                delete0 = wire

        digit9 = [x for x in digits09 if x != delete0][0]
        wireDigit9 = set(list(digit9))

        for wire in digits235:
            wireSet = set(list([x for x in wire]))
            segment = ('').join(map(str,wireDigit8 - wireSet))
#            print(f"wire: {wire} segment: {segment} in {digit4} wireSet: {wireSet}")
            matched = True
            for char in segment:
#                print(f"{char} in {digit4}")
                if not char in digit4:
                    matched = False
#                    print(f"False")
            if matched:
#                print(f"found 2")
                wireDigit2 = wireSet
                delete2 = wire

        digits35 = [x for x in digits235 if x != delete2]
        for wire in digits35:
            wireSet = set(list([x for x in wire]))
            #segment = ('').join(map(str,wireDigit8 - wireSet))
#            print(f"wire: {wire} segment: {segment} in {digit4} wireSet: {wireSet}")
            matched = True
            for char in digit1:
#                print(f"{char} in {digit1}")
                if not char in wire:
                    matched = False
#                    print(f"False")
            if matched:
#                print(f"found 3")
                wireDigit3 = wireSet
                delete3 = wire

        digit5 = [x for x in digits35 if x != delete3][0]
        wireDigit5 = set(list(digit5))

        wireDigitNumbers = [('').join(map(str,wireDigit0)), ('').join(map(str,wireDigit1)), \
                            ('').join(map(str,wireDigit2)), ('').join(map(str,wireDigit3)), \
                            ('').join(map(str,wireDigit4)), ('').join(map(str,wireDigit5)), \
                            ('').join(map(str,wireDigit6)), ('').join(map(str,wireDigit7)), \
                            ('').join(map(str,wireDigit8)), ('').join(map(str,wireDigit9))]
#        print(f"digit 0 {wireDigit0}")
#        print(f"digit 1 {wireDigit1}")
#        print(f"digit 2 {wireDigit2}")
#        print(f"digit 3 {wireDigit3}")
#        print(f"digit 4 {wireDigit4}")
#        print(f"digit 5 {wireDigit5}")
#        print(f"digit 6 {wireDigit6}")
#        print(f"digit 7 {wireDigit7}")
#        print(f"digit 8 {wireDigit8}")
#        print(f"digit 9 {wireDigit9}")

        print(f"{wireDigitNumbers}")
        #selecting numbers
        for digitOutput in fourDigits.split():
            for i, digit in enumerate(wireDigitNumbers):
                if len(digit) != len(digitOutput):
                    continue
                print(f"trying to find which number is {digitOutput} {digit} {i}")
                matched = True
                for char in list(digitOutput):
                    if digit.count(char) > 1 or digit.count(char) == 0:
#                    if not char in digit:
                        matched = False
#                        print("False break")
                        break
#                    print("True continue")
                if matched:
                    print(f"found {i}")
                    digitsNumber.append(i)
        print(f"{digitsNumber}")
        sumDigits += int(('').join(map(str,digitsNumber)))

    print(f"{sumDigits}")

