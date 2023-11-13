def solution(sequence: list) -> int:
    # 1 부터 연속펄스 부분 수열을 곱한값 찾기 prefix sum 만들기 
    # maxV - minV 
    # 각각의 리스트에서 max()
    prefixS = [0]
    for i in range(len(sequence)):
        pulse = 1 if i%2 ==0  else -1
        prefixS.append(prefixS[-1]+pulse*sequence[i])

    #print(prefixS, max(prefixS), min(prefixS))
    return (max(prefixS) - min(prefixS))