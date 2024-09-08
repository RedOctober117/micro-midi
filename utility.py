def read_voltages(path):
    lines = []
    with open(path, 'r') as file_in:
        for line in file_in.readlines():
            lines.append(float(line.strip('\n')))
    return lines

def calcuate_v_in_value(ground_resistor_ohm, parallel_resistor_ohm):
    return (1024 * ground_resistor_ohm) / (ground_resistor_ohm + parallel_resistor_ohm)

def calculaite_v_bounds_error(v_ins, error):
    v_in_bounds = []
    i = 0
    for voltage in v_ins:
        v_in_bounds.append((int(voltage - (v_ins[i] * error)), int(voltage + (v_ins[i] * error))))
        i += 1
    return v_in_bounds

def write_ranges_error(ranges, path):
    with open(path, 'w') as main_file:
        main_file.write('#ifndef VINS_H\n#define VINS_H\n')
        i = 1
        for range in ranges:
            main_file.write(f'#define BUTTON_{i}_LOWER {range[0]}\n#define BUTTON_{i}_UPPER {range[1]}\n#define BUTTON_{i + 8}_LOWER {range[0]}\n#define BUTTON_{i + 8}_UPPER {range[1]}\n')        
            i += 1
        main_file.write('#endif')
    
def calculate_parallel_voltage(voltages):
    sum = 0
    for voltage in voltages:
        sum += voltage
    return (1 / (1 / sum))
        
def calculate_macros(v_ins, error=None):
    macros = dict()
    for base_voltage_index in range(len(v_ins)):
        macros[base_voltage_index] = list()
        for macro_voltage_index in range(len(v_ins)):
            if base_voltage_index != macro_voltage_index:
                macros[base_voltage_index].append(int(calcuate_v_in_value(220, calculate_parallel_voltage([v_ins[base_voltage_index], v_ins[macro_voltage_index]]))))
    
    return macros

    # for v_in in v_ins:
        
            
# def write_ranges_error_tuple(ranges, path):
#     with open(path, 'w') as main_file:
#         main_file.write('#ifndef VINS_H\n#define VINS_H\n')
#         i = 1
#         for range in ranges:
#             main_file.write(f'#define BUTTON_{i}_RANGE std::make_tuple({range[0]},{range[1]})\n#define BUTTON_{i + 8}_RANGE std::make_tuple({range[0]},{range[1]})\n')        
#             i += 1
#         main_file.write('#endif')

def write_ranges_exact(ranges, path):
    with open(path, 'w') as main_file:
        i = 1
        for range in ranges:
            main_file.write(f'#define BUTTON_{i} {range}\n#define BUTTON_{i + 8} {range}\n')        
            i += 1



def main():
    resistances = read_voltages('resistances.txt')
    v_ins = []
    for resistance in resistances:
        v_ins.append(round(calcuate_v_in_value(220, resistance)))
    macros = calculate_macros(resistances, .05)
    for key, item in macros.items():
        print(f'Button {key + 1}: {item}')
    write_ranges_error(calculaite_v_bounds_error(v_ins, .05), 'main/vins.hpp')

if __name__ == '__main__':
    main()
