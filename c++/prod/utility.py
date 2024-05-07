def read_voltages(path):
    lines = []
    with open(path, 'r') as file_in:
        for line in file_in.readlines():
            lines.append(float(line.strip('\n')))
    return lines

def calcuate_v_in_value(ground_resistor_ohm, parallel_resistor_ohm):
    return (1024 * ground_resistor_ohm) / (ground_resistor_ohm + parallel_resistor_ohm)

def main():
    resistances = read_voltages('resistances.txt')
    v_ins = []
    for resistance in resistances:
        v_ins.append(round(calcuate_v_in_value(220, resistance)))

    print(v_ins)

    v_in_ranges = []
    i = 0
    for voltage in v_ins:
        v_in_ranges.append((voltage - (resistances[i] * .05), voltage, voltage + (resistances[i] * .05)))
        i += 1
    
    print(v_in_ranges)

if __name__ == '__main__':
    main()