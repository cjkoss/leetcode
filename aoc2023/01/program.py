import os

def main() -> None:
  sum1 = 0
  sum2 = 0
  ord0 = ord('0')
  nums = {
    'o' : {'one': 1},
    't' : {'two': 2, 'three': 3},
    'f' : {'four': 4, 'five': 5},
    's' : {'six': 6, 'seven': 7},
    'e' : {'eight': 8},
    'n' : {'nine': 9 },
  }
  filename = os.path.join(os.path.dirname(__file__), "input")
  with open(filename) as file:
    for line in file:
      sum1 += calc_line1(line, ord0)
      sum2 += calc_line2(line, ord0, nums)
  print(sum1, sum2)

def calc_line1(line, ord0) -> int:
  l = len(line)
  for i in range(l):
    n1 = ord(line[i]) - ord0;
    if n1 >= 0 and n1 <= 9:
      for j in range(l-1, i-1, -1):
        n2 = ord(line[j]) - ord0
        if n2 >= 0 and n2 <= 9:
          return 10 * n1 + n2
  raise Exception(f"could not found digits1 in {line}")
  return 0

def calc_line2(line, ord0, nums) -> int:
  l = len(line)
  for i in range(l):
    n1 = get_digit(line, i, ord0, nums)
    if n1 >= 0:
      for j in range(l-1, i-1, -1):
        n2 = get_digit(line, j, ord0, nums) 
        if n2 >= 0:
          return 10 * n1 + n2
  raise Exception(f"could not found digits2 in {line}")
  return 0

def get_digit(line, index, ord0, nums) -> int:
  ch = line[index]
  n = ord(ch) - ord0
  if n >= 0 and n <= 9:
    return n
  if ch in nums:
    ch_nums = nums[ch]
    for key in ch_nums.keys():
      sub_line = line[index:index+len(key)]
      if sub_line == key:
        # print(line, sub_line, index)
        # raise Exception() 
        return ch_nums[key]
  return -1

if __name__ == '__main__':
  main()

