
file_ = open("input")
lines = file_.readlines()

sumAssignment = 0
for line in lines:
    line = line.strip('\n')
    firstPart, secondPart = line.split(',')
    print(f"--->{line}\n")
    if ((int(firstPart.split('-')[0]) <= int(secondPart.split('-')[0])) and (int(secondPart.split('-')[1]) <= int(firstPart.split('-')[1]))) or\
       ((int(secondPart.split('-')[0]) <= int(firstPart.split('-')[0])) and (int(firstPart.split('-')[1]) <= int(secondPart.split('-')[1]))):
        sumAssignment += 1
        print(f"Found\n")

print(f"In how many assignment pairs does one range fully contain the other? {sumAssignment}")
