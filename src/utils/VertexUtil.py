import sys

def main():
    model_path: str = sys.argv[1]
    csv_path: str = sys.argv[0]

    model_file = load_file(model_path)
    parse_obj_file(model_file)

def load_file(path: str):
    file = open(path, "r")
    return file

def parse_obj_file(file_object):
    lines = file_object.readlines()

    vertex_list = []
    index_list = []

    for line in lines:
       
        line_type = line[0]

        if line_type == 'f':
            int_list = line.strip().split(" ")
            int_list.remove('')
            for index in int_list[2:]:
                index_list.append(index)
        elif line_type == 'v' and line[1] != 'n' :
            float_list = line.strip().split(" ")
            vertex_list.append(float_list[2])
            vertex_list.append(float_list[4])
            vertex_list.append(float_list[6])

    print(vertex_list)
    print(index_list)
    return

def parse_csv():
    pass

def compare_csv():
    pass

if __name__ == '__main__':
    sys.exit(main())