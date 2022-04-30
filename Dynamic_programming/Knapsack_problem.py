def print_arr(X):
  print()
  for i in range(len(X)):
    for j in range(len(X[0])):
      print(f'{X[i][j]:3}', end='')
    print()
  print()


########## initial setting ###########
W = 6  # capacity of knapsack
n = 5   # the number of items
v      = [5,  6, 18, 22, 28]  # value of items
weight = [1,  2,  5,  6,  7]     # weight of items
      ### 1   2   3   4   5 ###
OPT = [[ 0 for i in range(W+1) ] for j in range(n+1) ]


########## make OPT ##########
for i in range(1,n+1):
  for w in range(1, W+1):
    if weight[i-1] > w:
      OPT[i][w] = OPT[i-1][w]
    else:
      OPT[i][w] = max( OPT[i-1][w], OPT[i-1][w-weight[i-1]]+v[i-1] )
    # if OPT[i][w] >= max_value:
    #   max_value = OPT[i][w]
    #   max_w = w
    #   max_i = i

print_arr(OPT)

########## find index of items to maximize ##########
max_items_index = []
max_w = W
max_i = n

while max_i > 0:
  if OPT[max_i][max_w] != OPT[max_i-1][max_w]:
    max_items_index.insert(0,max_i)
    max_w = max_w - weight[max_i-1]
  max_i -= 1

print('indices used to maximizing value :',max_items_index)