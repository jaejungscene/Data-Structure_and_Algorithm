def solution(cards: list) -> int:
    two_group = [-1, -1]
    temp = 0
    
    for i in range(len(cards)):
        now_i = i
        group_cnt = 0
        while cards[now_i] != -1:
                temp = cards[now_i]-1
                cards[now_i] = -1
                now_i = temp
                group_cnt += 1
                
        if two_group[0] < two_group[1]:	temp = 0
        else:	temp = 1
        if group_cnt > two_group[temp]:	
            two_group[temp] = group_cnt
            
    return two_group[0] * two_group[1]