def solution(k, room_number):
    answer = []
    rdict = {}
    for num in room_number:
        idx = num
        visit = {idx}
        while idx in rdict:
            idx = rdict[idx]
            visit.add(idx)
        for room in visit:
            rdict[room] = idx+1
        answer.append(idx)
    return answer

k =10
room_number = [1,3,4,1,3,1]
print(solution(k, room_number))