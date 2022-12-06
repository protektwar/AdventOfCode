
file_ = open("input")
lines = file_.readlines()

sumOverlap = 0
for line in lines:
    line = line.strip('\n')
    firstPart, secondPart = line.split(',')
    print(f"--->{line}\n")
    f1 = int(firstPart.split('-')[0])
    f2 = int(firstPart.split('-')[1])
    s1 = int(secondPart.split('-')[0])
    s2 = int(secondPart.split('-')[1])
    if ((f1 <= s1) and (s2 <= f2)) or \
       ((s1 <= f1) and (f2 <= s2)) or \
       ((f1 <= s1) and (s1 <= f1)) or \
       ((f1 <= s2) and (s2 <= f2)) or \
       ((s1 <= f1) and (f1 <= s2)) or \
       ((s1 <= f2) and (f2 <= s2)):
        sumOverlap += 1

print(f"In how many assignment pairs do the ranges overlap? {sumOverlap}")
