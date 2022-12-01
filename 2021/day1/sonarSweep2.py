import sys

def readFile(filename):
    file1 = open(filename, 'r')
    lines = file1.readlines()
    return lines

if __name__ == '__main__':
    depths = readFile("input")
    initial = True
    prev_depth = 0
    measurments = []
    #create new thee-measurment sliding windows
    for i in range(len(depths)-2):
        sum_meas = int(depths[i].strip()) + int(depths[i+1].strip()) + int(depths[i+2].strip())
        print(f"{depths[i].strip()} + {depths[i+1].strip()} + {depths[i+2].strip()} = {sum_meas}")
        measurments.append(sum_meas)
    initial = True
    prev_meas = 0
    measurment = 0
    for meas in measurments:
        if initial:
            initial = False
            prev_meas = meas
            print(f"{meas} (N/A - no previous measurement)")
        else:
            if (int(meas)-int(prev_meas)) > 0:
                measurment += 1
                print(f"{meas}-{prev_meas} (increased)")
            else:
                if (int(meas)-int(prev_meas)) == 0:
                    print(f"{meas}-{prev_meas} (no change)")
                else:
                    print(f"{meas}-{prev_meas} (decreased)")
        prev_meas = meas 
    print(f"{measurment}")

