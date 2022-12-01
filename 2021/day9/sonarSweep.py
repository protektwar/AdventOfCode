

def readFile(filename):
    file1 = open(filename, 'r')
    lines = file1.readlines()
    return lines

if __name__ == '__main__':
    depths = readFile("input")
    initial = True
    prev_depth = 0
    measurments = 0
    for depth in depths:
        depth = depth.strip()
        if initial:
            initial = False
            prev_depth = depth
            print(f"{depth} (N/A - no previous measurement)")
        else:
            if (int(depth)-int(prev_depth)) > 0:
                measurments = measurments + 1
                print(f"{depth}-{prev_depth} increased")
            else:
                print(f"{depth}-{prev_depth} decreased")
        prev_depth = depth
    print(f"{measurments}")
