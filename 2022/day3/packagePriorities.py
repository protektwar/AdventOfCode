
file_ = open("input")
lines = file_.readlines()

sumPriorities = 0
for elfNumber, line in enumerate(lines):
    line = line.strip('\n')
    firstC = set(list(line[:len(line)//2]))
    secondC = set(list(line[len(line)//2:]))
    commonItem = ('').join(firstC.intersection(secondC))
    print(f"{line} {commonItem} {firstC}-{secondC}")
    if ord(commonItem[0]) > 96: #small letters
        sumPriorities += ord(commonItem[0]) - ord('a') + 1
    else:
        sumPriorities += ord(commonItem[0]) - ord('A') + 1 + 26
    print(f"{sumPriorities}")

print(f"{sumPriorities}")
