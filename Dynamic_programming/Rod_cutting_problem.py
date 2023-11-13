# i = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  # index
p = [0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30] # each index's price
r = [ 0 for i in range(len(p)) ] # optimal revenue = maximum revenue to get
s = [ 0 for i in range(len(p)) ] # value of first piece size(i=index) to be selected as optimal solution

opt = [ 0 for _ in range(len(p)) ]
mark = [ 0 for _ in range(len(p)) ]

for n in range(1, len(opt)):
  temp = -10000
  for k in range(1, n+1):
    # print(k, n-k, p[k], opt[n-k])
    if temp < p[k]+opt[n-k]:
      temp = p[k]+opt[n-k]
      mark[n] = n-k
  opt[n] = temp

def search(n: int, used: list) -> None:
  if n == 0:
    return 0
  used.append(n-mark[n])
  search(mark[n], used)

n = 2
used = []
print("opt:", opt)
print("mark:", mark)
search(n, used)
print("used:", used)
print()
      

########  recursive version  ##############################################
def recursive_CUT_ROD(p, n):
  if n==0:
    return 0
  else:
    q = -10000 # -infinite
    for i in range(n, 0, -1):
      q = max(q, p[i] + recursive_CUT_ROD(p, n-i))
    return q
##########################################################################

for n in range(1, len(r)):
  r[n] = recursive_CUT_ROD(p, n)
print("recursive:", r)
print()


#############  dynamic programming version ( bottom up )  ###############
def bottom_up_CUT_ROD(p):
  r = [ 0 for i in range(len(p)) ] # optimal revenue = maximum revenue to get
  s = [ 0 for i in range(len(p)) ] # value of first piece size(i=index) to be selected as optimal solution
  for n in range(1, len(p)):
    q = -10000
    for i in range(1,n+1):
      if q < p[i]+r[n-i]:
        q = p[i]+r[n-i]
        s[n] = i
    r[n] = q
  return r, s
#########################################################################

def find_pieces(i, s):
  info = [s[i]]
  i = i - s[i]
  while i > 0:
    info.insert(0, s[i])
    i = i - s[i]
  return info


r, s = bottom_up_CUT_ROD(p)
print("dynamic r:",r)
print("dynamic s:",s)
print()

index = 8
info = find_pieces(index, s)
print(index,'-> r =',r[index])