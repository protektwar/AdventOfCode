def readFile(filename):
    file = open(filename, 'r')
    lines = file.readlines()
    return lines

if __name__ == '__main__':
    commands = readFile("input")
    forward = 0
    depth = 0
    for command in commands:
        command = command.strip()
        direction, units = command.split()
        match direction:
            case "forward":
                forward = forward + int(units)
            case "up":            
                depth = depth - int(units)
            case "down":
                depth = depth + int(units)
    print(f"{forward} * {depth} = {forward * depth}")
