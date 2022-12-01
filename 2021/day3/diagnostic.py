def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    gammas = [[] for _ in range(12)]
    binaries = readFile("input")
    for binary in binaries:
        binary = binary.strip()
        for i, bit in enumerate(binary):
            gammas[i].append(bit)
    gamma_rate = ""
    epsilon = ""
    for i in range(12):
        ones = gammas[i].count('1')
        zeros = gammas[i].count('0')
        print (f"{i:2} - 1:{ones} - 0:{zeros}")
        if ones > zeros:
            gamma_rate = gamma_rate + "1"
            epsilon = epsilon + "0"
        else:
            gamma_rate = gamma_rate + "0"
            epsilon = epsilon + "1"
    print("{:d}".format(int(f"0b{gamma_rate}",2)))
    print("{:d}".format(int(f"0b{epsilon}",2)))
    print(f"{int(f'0b{gamma_rate}',2) * int(f'0b{epsilon}',2)}")

    binaries_back = binaries
    gammas_back = gammas
    for i in range(12):
        ones = gammas[i].count('1')
        zeros = gammas[i].count('0')
        print(f"1 - {ones} 0 - {zeros}")
        binaries_temp = [] 
        if ones >= zeros :
            for idx, gamma in enumerate(gammas[i]):
                if gamma == "1":
                    print(f"more 1 on {i} - {binaries[idx].strip()}")
                    binaries_temp.append(binaries[idx].strip())
#            print(binaries_temp)
            gammas = [[] for _ in range(12)]
            for binary in binaries_temp:
                binary = binary.strip()
                for i, bit in enumerate(binary):
                    gammas[i].append(bit)
            binaries = binaries_temp
        else:
            for idx, gamma in enumerate(gammas[i]):
                if gamma == "0":
                    print(f"fewer 0 on {i} - {binaries[idx].strip()}")
                    binaries_temp.append(binaries[idx].strip())
#            print(binaries_temp)
            gammas = [[] for _ in range(12)]
            for binary in binaries_temp:
                binary = binary.strip()
                for i, bit in enumerate(binary):
                    gammas[i].append(bit)
            binaries = binaries_temp
    
    binaries = binaries_back
    gammas = gammas_back
    for i in range(12):
        print(gammas[i])
        ones = gammas[i].count('1')
        zeros = gammas[i].count('0')
        binaries_temp = [] 
        print(f"1 - {ones} 0 - {zeros}")
        if ones >= zeros :
            for idx, gamma in enumerate(gammas[i]):
                if gamma == "0":
                    print(f"fewer 0 on {i} - {binaries[idx].strip()}")
                    binaries_temp.append(binaries[idx].strip())
#            print(binaries_temp)
            gammas = [[] for _ in range(12)]
            for binary in binaries_temp:
                binary = binary.strip()
                for i, bit in enumerate(binary):
                    gammas[i].append(bit)
            binaries = binaries_temp
        else:
            for idx, gamma in enumerate(gammas[i]):
                if gamma == "1":
                    print(f"more 1 on {i} - {binaries[idx].strip()}")
                    binaries_temp.append(binaries[idx].strip())
#            print(binaries_temp)
            gammas = [[] for _ in range(12)]
            for binary in binaries_temp:
                binary = binary.strip()
                for i, bit in enumerate(binary):
                    gammas[i].append(bit)
            binaries = binaries_temp
#100110100010 | 111111111010
    o2 = int(f"0b100111101011",2) #100111101011 | 100110100010
    co2 = int(f"0b001011000101",2) #001011010100
    print(f"{o2 * co2}")
