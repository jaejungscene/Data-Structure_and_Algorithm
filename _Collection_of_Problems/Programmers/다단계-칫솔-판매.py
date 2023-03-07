def solution(enroll, referral, seller, amount):
    parentList = []
    i, j = 0, 0
    for i in range(len(referral)):
        if referral[i] == "-":
            parentList.append(None)
        else:
            for j in range(i):
                if enroll[j] == referral[i]:
                    parentList.append(j)

    answer = [0 for _ in range(len(enroll))] 
    for i in range(len(seller)):
        for j in range(len(enroll)):
            if enroll[j] == seller[i]:
                break
        
        while j is not None:
            distributed = int(amount[i] * 100 * 0.1)
            if distributed < 1:
                answer[j] += int(amount[i] * 100)
                break
            else:
                answer[j] += int(amount[i] * 100) - distributed
                amount[i] = amount[i] * 0.1
            j = parentList[j]
    
    return answer



### Test Case 1 ###
enroll = ["john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"]
referral = ["-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"]
seller = ["young", "john", "tod", "emily", "mary"]
amount = [12, 4, 2, 5, 10]
# result = [360, 958, 108, 0, 450, 18, 180, 1080]


### Test Case 2 ###
enroll = ["john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"]
referral = ["-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"]
seller = ["sam", "emily", "jaimie", "edward"]
amount = [2, 3, 5, 4]
# result = [0, 110, 378, 180, 270, 450, 0, 0]


answer = solution(enroll, referral, seller, amount)
print(answer)