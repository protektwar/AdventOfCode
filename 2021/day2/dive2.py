def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    commands = readFile("input")
    forward = 0
    depth = 0
    aim = 0
    for command in commands:
        command = command.strip()
        direction, units = command.split()
        match direction:
            case "forward":
                forward = forward + int(units)
                depth = depth + aim * int(units)
            case "up":            
                 aim= aim - int(units)
            case "down":
                aim = aim + int(units)
    print(f"{forward} * {depth} = {forward * depth}")
