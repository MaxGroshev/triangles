import subprocess
import argparse
from   subprocess import Popen, PIPE, STDOUT

# -----------------------------------------------------------------------------------------

class TERMINAL_COLORS:
        PURPLE    = '\033[95m'
        OKBLUE    = '\033[94m'
        OKCYAN    = '\033[96m'
        OKGREEN   = '\033[92m'
        YELLOW    = '\033[33m'
        BLUE      = '\033[36m'
        GREEN     = '\033[32m'

        WARNING   = '\033[93m'
        ERROR     = '\033[91m'
        RED       = '\033[91m'
        DEFAULT   = '\033[0m'
        BOLD      = '\033[1m'
        UNDERLINE = '\033[4m'


test_data = {
    (3, -2.75, 3.17, 3,
        -2.22, 2.98, 0,
        3.34, -3.98, 0,
        0, 3, 0,
        3, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 1, 1,
        0, 1, 0)      : [1, 2, 3],
}

# -----------------------------------------------------------------------------------------

def check_output_data(num_of_test, stdout_data, correct_res):
    try:
        if stdout_data == correct_res:
            print(TERMINAL_COLORS.GREEN              + \
                    f"Test {num_of_test} IS PASSED:" + \
            TERMINAL_COLORS.DEFAULT
            )
        else:
            print(TERMINAL_COLORS.ERROR                + \
                    f"Test {num_of_test} IS FAILED:\n" + \
                    f"Prog output   = {stdout_data}\n" + \
                    f"Expected      = {correct_res}\n" + \
            TERMINAL_COLORS.DEFAULT
            )
    except:
        print(TERMINAL_COLORS.WARNING                   + \
            f"Test {num_of_test} fall. Prog output:\n'" + \
            stdout_data + "'"                           + \
            TERMINAL_COLORS.DEFAULT
            )

def run_triangles(name_of_testing_prog, test_case):
    pipe = Popen([name_of_testing_prog], stdout=PIPE, stdin=PIPE)

    input_str = str()
    for data in test_case:
        input_str += str(data) + " "

    # stdout_data = (pipe.communicate(input = bytes(input_str, "UTF-8")))
    # string_data = str(stdout_data[0].decode())
    # conver_output = string_data.split()
    # conver_output = [int(num) for num in conver_output]

    return 0 #conver_output


def run_test_data(test_data, name_of_testing_prog):
    num_of_trians = []

    for (test_case, i) in zip(test_data, range(len(test_data))):
        num_of_trians = run_triangles(name_of_testing_prog, test_case)
        check_output_data(i + 1, num_of_trians, test_data[test_case])

# -----------------------------------------------------------------------------------------

if __name__ == "__main__":
#     parser = argparse.ArgumentParser(prog = 'e2e_testing')#add help
#
#     args = parser.parse_args()

    run_test_data(test_data, "./build/triangles/trian")
