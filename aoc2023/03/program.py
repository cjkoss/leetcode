import os
import sys


def main() -> None:
    sum1 = 0
    sum2 = 0
    ord0 = ord("0")
    n_dot = ord(".") - ord0
    input_name = sys.argv[1]
    filename = os.path.join(os.path.dirname(__file__), input_name)
    empty = ""
    line1 = ""
    line2 = ""
    with open(filename) as file:
        for line in file:
            line3 = line.strip()
            if len(empty) == 0:
                empty = "." * len(line3)
                line2 = empty
            else:
                sum1 += calc_line1(line1, line2, line3, ord0, n_dot)
                sum2 += calc_line2(line1, line2, line3, ord0)
            line1 = line2
            line2 = line3
    sum1 += calc_line1(line1, line2, empty, ord0, n_dot)
    sum2 += calc_line2(line1, line2, empty, ord0)
    print(sum1, sum2)


def calc_line2(line_before, line, line_after, ord0) -> int:
    result = 0
    for i in range(len(line)):
        ch = line[i]
        if ch == "*":
            nums = find_nums(line_before, line, line_after, i, ord0)
            nums_cnt = 0
            for j in range(3):
                for k in range(3):
                    nums_cnt += nums[j][k]
            if nums_cnt != 2:
                continue
            nums_multiply = 1
            lines = [line_before, line, line_after]
            for j in range(3):
                for k in range(3):
                    if nums[j][k] == 1:
                        nums_multiply *= read_num(lines[j], i + k - 1, ord0)
            result += nums_multiply
    return result


def read_num(line, index, ord0) -> int:
    num = ord(line[index]) - ord0
    tens = 1
    for i in range(index - 1, -1, -1):
        n = ord(line[i]) - ord0
        if n < 0 or n > 9:
            break
        tens *= 10
        num += tens * n
    for i in range(index + 1, len(line)):
        n = ord(line[i]) - ord0
        if n < 0 or n > 9:
            break
        num = num * 10 + n
    # print(num)
    return num


def find_nums(line_before, line, line_after, index, ord0) -> list:
    nums = []
    nums.append(line_nums(line_before, index, ord0))
    n0 = is_num(line, index - 1, ord0)
    n2 = is_num(line, index + 1, ord0)
    nums.append([n0, 0, n2])
    nums.append(line_nums(line_after, index, ord0))
    return nums


def line_nums(line, index, ord0) -> list:
    nums = [0, 0, 0]
    nums[1] = is_num(line, index, ord0)
    if nums[1] == 1:
        return nums
    nums[0] = is_num(line, index - 1, ord0)
    nums[2] = is_num(line, index + 1, ord0)
    return nums


def is_num(line, index, ord0) -> int:
    if index >= len(line) or index < 0:
        return 0
    n = ord(line[index]) - ord0
    if n >= 0 and n <= 9:
        return 1
    return 0


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
                    adjacent_symbol = has_adjacent_sybol(
                        i - 1, line_before, line, line_after, ord0, n_dot
                    )
            num_buffer = num_buffer * 10 + n
            if not adjacent_symbol:
                adjacent_symbol = has_adjacent_sybol(
                    i, line_before, line, line_after, ord0, n_dot
                )
            continue
        if reading_num and num_buffer > 0:
            if not adjacent_symbol:
                adjacent_symbol = has_adjacent_sybol(
                    i, line_before, line, line_after, ord0, n_dot
                )
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
    return (
        not num_or_dot(line_before[index], ord0, n_dot)
        or not num_or_dot(line_after[index], ord0, n_dot)
        or not num_or_dot(line[index], ord0, n_dot)
    )


def num_or_dot(ch, ord0, n_dot) -> bool:
    n = ord(ch) - ord0
    return n == n_dot or (n >= 0 and n <= 9)


if __name__ == "__main__":
    main()
