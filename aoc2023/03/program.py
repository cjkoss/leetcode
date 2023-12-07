import os
import sys

def main() -> None:
    sum1 = 0
    sum2 = 0
    ord0 = ord('0')
    n_dot = ord('.') - ord0
    input_name = sys.argv[1]
    filename = os.path.join(os.path.dirname(__file__), input_name)
    empty = ''
    line1 = ''
    line2 = ''
    with open(filename) as file:
        for line in file:
            line3 = line.strip();
            if len(empty) == 0:
                empty = '.' * len(line3)
                line2 = empty
            else:
                sum1 += calc_line1(line1, line2, line3, ord0, n_dot)
            line1 = line2
            line2 = line3
    sum1 += calc_line1(line1, line2, empty, ord0, n_dot)
    print(sum1, sum2)

def calc_line1(line_before, line, line_after, ord0, n_dot) -> int:
    # print(line)
    result = 0
    num_buffer = 0
    reading_num = False
    adjacent_symbol = False
    for i in range(len(line)):
        ch = line[i]
        n = ord(ch) - ord0
        if n >= 0 and n <= 9:
            if not reading_num:
                reading_num = True
                adjacent_symbol = False
                num_buffer = 0
                if i > 0:
                    adjacent_symbol = has_adjacent_sybol(i-1, line_before, line, line_after, ord0, n_dot)  
            num_buffer = num_buffer * 10 + n
            if not adjacent_symbol:
                adjacent_symbol = has_adjacent_sybol(i, line_before, line, line_after, ord0, n_dot)
            continue
        if reading_num and num_buffer > 0:
            if not adjacent_symbol:
                adjacent_symbol = has_adjacent_sybol(i, line_before, line, line_after, ord0, n_dot)
            if adjacent_symbol:
                result += num_finished(num_buffer)
        reading_num = False
    if reading_num and num_buffer > 0 and adjacent_symbol:
        result += num_finished(num_buffer)
    return result

def num_finished(num):
    # print(num)
    return num

def has_adjacent_sybol(index, line_before, line, line_after, ord0, n_dot) -> bool:
    return not num_or_dot(line_before[index], ord0, n_dot) or not num_or_dot(line_after[index], ord0, n_dot) or not num_or_dot(line[index], ord0, n_dot)

def num_or_dot(ch, ord0, n_dot) -> bool:
    n = ord(ch) - ord0
    return n == n_dot or (n >= 0 and n <= 9)

if __name__ == "__main__":
    main()
