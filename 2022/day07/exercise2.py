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


def filter_by_min_size(fs_desc, min_size):
    min_value = fs_desc[".size"]

    for value in fs_desc.values():
        if type(value) is dict:
            if value[".size"] > min_size:
                min_value_from_children = filter_by_min_size(value, min_size)
                if min_value_from_children < min_value:
                    min_value = min_value_from_children

    return min_value

input_file = open('input.txt', 'r')
lines = input_file.readlines()
first_line = lines.pop(0).strip()

fs_desc = {}
init_filesystem(fs_desc, "/", lines)

total_filesystem_used_space = fs_desc["/"][".size"]
total_filesystem_unused_space = 70000000 - total_filesystem_used_space
need_to_free = 30000000 - total_filesystem_unused_space
print("Bytes to free: ", filter_by_min_size(fs_desc["/"], need_to_free))
