def init_filesystem(fs_desc, dir_name, lines):
    fs_desc[dir_name] = { ".size": 0 }

    while lines:
        line = lines.pop(0).strip()
        tokens = line.split()
        if tokens[0] == "$" and tokens[1] == "cd" and tokens[2] == "..":
            return fs_desc[dir_name][".size"]
        elif tokens[0] == "$" and tokens[1] == "cd":
            dir_size = init_filesystem(fs_desc[dir_name], tokens[2], lines)
            fs_desc[dir_name][".size"] = fs_desc[dir_name][".size"] + dir_size
        elif tokens[0] == "dir":
            fs_desc[dir_name][tokens[1]] = { ".size": 0 }
        elif tokens[0].isdigit():
            fs_desc[dir_name][tokens[1]] = int(tokens[0])
            fs_desc[dir_name][".size"] = fs_desc[dir_name][".size"] + int(tokens[0])

    return fs_desc[dir_name][".size"]


def filter_by_max_size(fs_desc, max_size):
    acc_size = 0

    for value in fs_desc.values():
        if type(value) is dict:
            if value[".size"] < max_size:
                acc_size += value[".size"] + filter_by_max_size(value, max_size)
            else:
                acc_size += filter_by_max_size(value, max_size)

    return acc_size

input_file = open('input.txt', 'r')
lines = input_file.readlines()
first_line = lines.pop(0).strip()

fs_desc = {}
init_filesystem(fs_desc, "/", lines)
print("acc size: ", filter_by_max_size(fs_desc, 100000))
