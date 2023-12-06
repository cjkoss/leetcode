import os


def main() -> None:
    sum1 = 0
    sum2 = 0
    filename = os.path.join(os.path.dirname(__file__), "input")
    with open(filename) as file:
        for line in file:
            sum1 += calc_line1(line.strip())
            sum2 += calc_line2(line.strip())
    print(sum1, sum2)


def calc_line2(line) -> int:
    (_, game_data) = line.split(": ")
    sets = game_data.split("; ")
    max_red = 0
    max_green = 0
    max_blue = 0
    for s in sets:
        colors = s.split(", ")
        for c in colors:
            (num, color) = c.split(" ")
            n = int(num)
            if color == "red":
                if n > max_red:
                    max_red = n
            elif color == "green":
                if n > max_green:
                    max_green = n
            elif color == "blue":
                if n > max_blue:
                    max_blue = n
    return max_red * max_green * max_blue


def calc_line1(line) -> int:
    (game_name, game_data) = line.split(": ")
    sets = game_data.split("; ")
    for s in sets:
        colors = s.split(", ")
        for c in colors:
            (num, color) = c.split(" ")
            if color == "red":
                if int(num) > 12:
                    return 0
            elif color == "green":
                if int(num) > 13:
                    return 0
            elif color == "blue":
                if int(num) > 14:
                    return 0
    (_, game_num) = game_name.split(" ")
    return int(game_num)


if __name__ == "__main__":
    main()
