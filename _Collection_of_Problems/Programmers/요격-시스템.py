def solution(targets: list) -> int:
    targets.sort(key=lambda x: (x[0],x[1]))
    result = 0
    eMin = targets[0][1]
    
    for t in targets[1:]:
        if t[0] < eMin:
            eMin = min(eMin, t[1])
        else:
            eMin = t[1]
            result += 1
    
    return result + 1