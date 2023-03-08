def solution(enroll, referral, seller, amount):
    info = {}
    for i in range(len(enroll)):
        if referral[i] == "-":
            info[enroll[i]] = (i, None)
        else:
            info[enroll[i]] = (i, referral[i])

    answer = [0 for _ in range(len(enroll))]
    for i in range(len(seller)):
        parent = seller[i]
        while parent is not None:
            current = info[parent][0]
            distributed = int(amount[i] * 100 * 0.1)
            if distributed < 1:
                answer[current] += int(amount[i] * 100)
                break
            else:
                answer[current] += int(amount[i] * 100) - distributed
                amount[i] = amount[i] * 0.1
            parent = info[parent][1]
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


result = solution(enroll, referral, seller, amount)
print(result)