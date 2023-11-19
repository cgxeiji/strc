import subprocess
import os
import json
import argparse

class StringConstant:
    def __init__(self, id, string, cpp):
        self.id = id
        self.string = string
        self.cpp = cpp

    def __str__(self):
        return "id: {}, string: {}, cpp: {}".format(self.id, self.string, self.cpp)

    def __repr__(self):
        return self.string

    def __eq__(self, other):
        return self.string == other.string

    def __hash__(self):
        return hash

# delete_definitions deletes the strc.cpp file and replaces it with an empty
# one
def delete_definitions(filename, lib_path):
    try:
        os.remove(filename)
    except OSError:
        pass

    print("Creating empty file: {}".format(filename))
    with open(filename, "w") as file:
        file.write("#include \"{}\"\n\n".format(lib_path))

# pre_make calls make and returns its output
def pre_make():
    # the call to make is expected to fail, but we only care about the output
    print("Precompiling without string definitions...")
    output = subprocess.run(["make", "-j"], shell=True, capture_output=True)
    output = output.stderr.decode("utf-8")
    return output

# clean_substring converts a string of escaped characters to a string
def clean_substring(substring):
    # split the string into individual components, and strip off extra
    # characters like single quotes
    escaped_chars = substring.replace("'", "").split(", ")
    escaped_chars.pop(0) # char

    # convert the bytes written as plain string to bytes
    byte_values = [bytes([int(char)]) for char in escaped_chars]

    # join the byte values and decode using UTF-8
    decoded_string = b''.join(byte_values).decode('utf-8')
    decoded_string

    return decoded_string

# parse_string_constant returns the lines of the output that contain the "strc"
# keyword
def parse_string_constant(output):
    query = "strc<"
    lines = []
    print("Searching for strc in output:")
    for line in output.splitlines():
        if query in line:
            lines.append(line)

    # extract the substring inside <>
    print("found substrings: (total {})".format(len(lines)))
    for i in range(len(lines)):
        lines[i] = lines[i].split("<")[3].split(">")[0]
        # delete (char)
        lines[i] = lines[i].replace("(char)", "")

    # keep only a unique list of substrings
    lines = list(dict.fromkeys(lines))
    print("keeping unique substrings: (total {})".format(len(lines)))
    #for line in lines:
        #print("    {}".format(line))

    # extract the string from each line
    to_strings = []
    print("unique strings:")
    for i in range(len(lines)):
        to_strings.append(clean_substring(lines[i]))
        print("    {}".format(to_strings[i]))

    # reshape each line into:
    # strc_id_t get_strc_id(strc<...>) { return ...; }
    print("creating definitions:")
    for i in range(len(lines)):
        lines[i] = "template</*\n    {}\n*/>\ncgx::strc_id_t cgx::get_strc_id<cgx::strc<{}>>() {{ return {}; }}".format(to_strings[i], lines[i], i)
    print("done")

    # create array of StringConstant objects
    string_constants = []
    print("creating StringConstant objects:")
    for i in range(len(to_strings)):
        string_constants.append(StringConstant(i, to_strings[i], lines[i]))
    print("done")

    return string_constants

# make_json takes an array of StringConstant objects and creates a json file
# with the given name
def make_json(filename, string_constants):
    print("Creating file: {}".format(filename))
    encoded = json.dumps(string_constants, default=lambda o: o.__dict__, indent=4)
    with open(filename, "w") as file:
        file.write(encoded)

# make_file creates a source file with the given name and writes the given
# lines to it
def make_file(filename, lines, lib_path):
    print("Creating file: {}".format(filename))
    with open(filename, "w") as file:
        file.write("#include \"{}\"\n\n".format(lib_path))
        for string in lines:
            file.write(string.cpp + "\n\n")

# post_make rebuilds the project after the strc.cpp file has been created
def post_make():
    print("Rebuilding project")
    output = subprocess.run(["make", "-j"], shell=True, check=True)

def main():
    # get the path to the library from the arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("lib_path", help="path to the strc library")
    args = parser.parse_args()
    lib_path = args.lib_path

    if not os.path.exists(lib_path):
        print("Error: path to the library does not exist")
        return

    delete_definitions("strc.cpp", lib_path)
    output = pre_make()
    string_constants = parse_string_constant(output)
    make_file("strc.cpp", string_constants, lib_path)
    post_make()
    make_json("strc.json", string_constants)
        

if __name__ == "__main__":
    main()

