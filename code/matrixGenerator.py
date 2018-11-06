
films = {}

filepath = '../dataSet/small/title.basics.tsv'
with open(filepath, 'r') as fp:
    line = fp.readline()
    while line:
        print("Line: {}".format(line.strip()))
        line = fp.readline()
