def solution(numbers):
    answer = []
    for num in numbers:
        if num % 2 == 0:
            answer.append(num+1)
        else:
            binary = "0" + bin(num)[2:]
            idx = binary.rfind("0")
            binary = binary[:idx] + "1" + "0" + binary[idx+2:]
            answer.append(int(binary,2))
    
    return answer