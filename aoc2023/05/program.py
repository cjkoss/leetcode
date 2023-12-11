import os
import sys


def main() -> None:
    sum1 = 0
    sum2 = 0
    input_name = sys.argv[1]
    read_seeds = True
    skip_header = True
    skip_name = False
    src1 = []
    src2 = {}
    convert = {}
    filename = os.path.join(os.path.dirname(__file__), input_name)
    with open(filename) as file:
        for line in file:
            l = line.strip()
            if len(l) > 0:
                if read_seeds:
                    # print(l.split(" "))
                    src1 = [int(n_str) for n_str in l.split(" ")[1:]]
                    i = 0
                    while i < len(src1):
                        src2[src1[i]] = src1[i + 1]
                        i += 2
                    print("seeds:", src1, src2)
                else:
                    if skip_name:
                        skip_name = False
                        continue
                    nums = [int(n_str) for n_str in l.split(" ")]
                    print(nums)
                    convert[nums[1]] = nums
                continue
            if not read_seeds:
                (src1, src2) = convert_src(src1, src2, convert)
            convert = {}
            read_seeds = False
            skip_name = True
    (src1, src2) = convert_src(src1, src2, convert)
    sum1 = min(src1)
    sum2 = min(src2.keys())
    print("result: ", sum1, sum2)


def convert_src(src1, src2, convert):  # -> (list, list):
    if len(convert) <= 0:
        return (src1, src2)
    # print("calc")
    src1.sort()
    src2_keys = list(src2.keys())
    src2_keys.sort()
    src2_result = {}
    i = 0
    j = 0
    j_start = src2_keys[j]
    j_len = src2[j_start]
    src1_len = len(src1)
    src2_len = len(src2_keys)
    keys = list(convert.keys())
    keys.sort()
    for k in keys:
        data = convert[k]
        # print("src", src[i], "conv", k)
        while i < src1_len and src1[i] < k:
            i += 1
            # print("src less", src[i])
        while i < src1_len and src1[i] >= k and src1[i] < k + data[2]:
            # print("src interval", src[i], k)
            src1[i] = src1[i] - k + data[0]
            i += 1
        print("line", k, j_start, j)
        while j < src2_len and j_start < k:
            if j_start + j_len - 1 < k:  # 1 (+1) < 2 (+3)
                print("jstart before full")
                src2_result[j_start] = j_len
                j += 1
                if j < src2_len:
                    j_start = src2_keys[j]
                    j_len = src2[j_start]
            else:  # (2, 3, 4, 5) 2 (+4) < 3 (+ 5) (3, 4, 5, 6, 7)
                print("jstart before part")
                src2_result[j_start] = k - j_start
                j_len = j_start + j_len - k
                j_start = k
        while j < src2_len and j_start >= k and j_start < k + data[2]:
            new_start = j_start - k + data[0]
            if j_start + j_len <= k + data[2]:  # 2 + 1 <= 1 + 2
                print("jstart after full")
                src2_result[new_start] = j_len
                j += 1
                if j < src2_len:
                    j_start = src2_keys[j]
                    j_len = src2[j_start]
            else:  # (2, 3, 4, 5) 2 + 4 > 1 + 3 (1, 2, 3)
                print("jstart after part")
                src2_result[new_start] = k + data[2] - j_start
                # append(2, 1 + 3 - 2) = (2, 3)
                j_len = j_start + j_len - k - data[2]  # 2
                j_start = k + data[2]  # 4 = (4, 5)
        if i >= src1_len and j >= src2_len:
            break
    while j < src2_len:
        src2_result[j_start] = j_len
        j += 1
        if j < src2_len:
            j_start = src2_keys[j]
            j_len = src2[j_start]

    print("calc", src2_result)
    return (src1, src2_result)


if __name__ == "__main__":
    main()
