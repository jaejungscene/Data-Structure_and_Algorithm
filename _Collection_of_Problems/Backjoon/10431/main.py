import sys

def get_input():
    P = int(sys.stdin.readline().rstrip())
    all_test_cases = []
    for _ in range(P):
        one_line = sys.stdin.readline().rstrip().split(" ")[1:]
        one_line = list(map(int, one_line))
        all_test_cases.append(one_line)
    return P, all_test_cases

def find_insertion_point(line, now_std_height):
    for i in range(len(line)):
        if line[i] > now_std_height:
            return i
    return -1

def cal_student_back(test_case):
    line = []
    total_steps = 0
    for now_std_height in test_case:
        insertion_point = find_insertion_point(line, now_std_height)
        if insertion_point != -1:
            line.insert(insertion_point, now_std_height)
            total_steps += len(line) - 1 - insertion_point
        else:
            line.append(now_std_height)
    return total_steps

if __name__ == "__main__":
    P, all_test_cases = get_input()
    result_str = ""
    results = []
    for i in range(P):
        now_result_str = cal_student_back(all_test_cases[i])
        results.append(f"{i+1} {now_result_str}")
    print("\n".join(results))
    