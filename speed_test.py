import os
from os import path
import json

generator_code_path = path.join("gen", "gen_test.cpp")
generator_path = path.join("gen", "gen_test.exe")

def gen_test(params):
    params = params.strip()
    if params.count(' ') < 2:
        return 0
    file_name = path.join("tests", params.replace(' ', '_') + '.txt')
    print("generating " + file_name, end=": ")

    if (os.system(generator_path + " " + params + " > " + file_name) != 0):
        print("failed")
        return 0
    print("succeed")
    return params.replace(' ', '_')

def gen_tests():
    if os.system("g++ -O2 -std=c++17 -o " + generator_path + " " + generator_code_path) != 0:
        print("Cannot compile generator " + generator_code_path)
        return []
    test_params = open(path.join("gen", "test_params.txt"), 'r').readlines()
    tests = []
    for params in test_params:
        test = gen_test(params)
        if test != 0:
            tests.append(test)
    return tests

def get_tests_list():
    tests = list(filter(lambda x: x.find('.txt') != -1, os.listdir('tests')))
    tests = list(map(lambda x: x[:-4], tests))
    if len(tests) == 0:
        tests = gen_tests()
    return tests

def run(test):
    test_path = path.join("tests", test + ".txt")
    id = os.system(".\\main.exe < " + test_path + " > run.json 2> run.err")
    if id == 0:
        rows = test
        with open("run.json", "r") as json_file:
            data = json.load(json_file)
            for algo in data:
                rows += "," + str(data[algo]["init"])
                rows += "," + str(data[algo]["query"])
                
        rows += "\n"
        with open("result.csv", "a") as result: result.write(rows)
    else:
        print("error")

def speed_test():
    tests = get_tests_list()
    if os.system("g++ -O2 -std=c++17 -o main.exe main.cpp") != 0:
        print("Cannot compile main.cpp")
        return
    with open("result.csv", "w") as f: f.close()
    for test in tests:
        run(test)
    if len(tests) > 0:
        result_first_line = "File test\\Algorithm"
        with open("run.json", "r") as json_file:
            data = json.load(json_file)
            for algo in data:
                result_first_line += "," + algo + ": initation time"
                result_first_line += "," + algo + ": answer query time"
        result_first_line += "\n"
        #prepend first line
        with open("result.csv", "r") as f: data = f.read()
        with open("result.csv", "w") as f: f.write(result_first_line + data)
        
speed_test()