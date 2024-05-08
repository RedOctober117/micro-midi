def read_voltages(path):
    lines = []
    with open(path, 'r') as file_in:
        for line in file_in.readlines():
            lines.append(float(line.strip('\n')))
    return lines

def calcuate_v_in_value(ground_resistor_ohm, parallel_resistor_ohm):
    return (1024 * ground_resistor_ohm) / (ground_resistor_ohm + parallel_resistor_ohm)

def calculaite_v_bounds(v_ins, error):
    v_in_bounds = []
    i = 0
    for voltage in v_ins:
        v_in_bounds.append((voltage - (v_ins[i] * error), voltage + (v_ins[i] * error)))
        i += 1
    return v_in_bounds

def write_ranges(ranges, path):
    with open(path, 'w') as main_file:
        i = 1
        for range in ranges:
            main_file.write(f'#define BUTTON_{i}_LOWER {range[0]}\n#define BUTTON_{i}_UPPER {range[1]}\n#define BUTTON_{i + 8}_LOWER {range[0]}\n#define BUTTON_{i + 8}_UPPER {range[1]}\n')        
            i += 1


def main():
    resistances = read_voltages('resistances.txt')
    v_ins = []
    for resistance in resistances:
        v_ins.append(round(calcuate_v_in_value(220, resistance)))

    bounds = calculaite_v_bounds(v_ins, .05)
    write_ranges(bounds, 'main/vins.h')


if __name__ == '__main__':
    main()