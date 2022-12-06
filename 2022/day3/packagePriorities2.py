
file_ = open("input")
lines = file_.readlines()

sumPriorities = 0
for elfNumber, line in enumerate(lines):
    line = line.strip('\n')
    if (elfNumber % 3) == 0:
        firstElf = set(list(line))
    elif (elfNumber % 3) == 1:
        secondElf = set(list(line))
    elif (elfNumber % 3) == 2:
        thirdElf = set(list(line))
        commonItem = ('').join(firstElf.intersection(secondElf,thirdElf))
        print(f"{commonItem}")
        if ord(commonItem[0]) > 96: #small letters
            sumPriorities += ord(commonItem[0]) - ord('a') + 1
        else:
            sumPriorities += ord(commonItem[0]) - ord('A') + 1 + 26
        print(f"{sumPriorities}")

print(f"{sumPriorities}")
