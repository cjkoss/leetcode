import os
import sys


def main() -> None:
    sum1 = 0
    sum2 = 0
    ord0 = ord("0")
    wins_max = 10
    line_multipliers = [1] * wins_max
    multiplier_index = 0
    input_name = sys.argv[1]
    filename = os.path.join(os.path.dirname(__file__), input_name)
    with open(filename) as file:
        for line in file:
            l = line.strip() + " "
            n = calc_line1(l, ord0)
            if n > 0:
                sum1 += pow(2, n - 1)
            m = line_multipliers[multiplier_index]
            sum2 += m
            print(m, n)
            line_multipliers[multiplier_index] = 1
            multiplier_index = (multiplier_index + 1) % wins_max
            for i in range(n):
                ind = (multiplier_index + i) % wins_max
                line_multipliers[ind] += m
    print(sum1, sum2)


def calc_line1(line, ord0) -> int:
    result = 0
    num_buffer = 0
    reading_num = False
    skip_until_col = True
    win_nums = set()
    read_win_nums = True
    for i in range(len(line)):
        ch = line[i]
        if skip_until_col:
            if ch == ":":
                skip_until_col = False
            continue
        n = ord(ch) - ord0
        if n >= 0 and n <= 9:
            if not reading_num:
                reading_num = True
                num_buffer = 0
            num_buffer = num_buffer * 10 + n
        else:
            if reading_num:
                reading_num = False
                # print(num_buffer)
                if read_win_nums:
                    win_nums.add(num_buffer)
                else:
                    if num_buffer in win_nums:
                        result += 1
            if ch == "|":
                read_win_nums = False
    return result


if __name__ == "__main__":
    main()
