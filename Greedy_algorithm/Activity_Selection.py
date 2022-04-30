s = [0,1,2,4,1,5, 8, 9,11,13]
f = [0,3,5,7,8,9,10,11,14,16]

# k = current subproblem
# n = the number of activities
def Rec_Activity_Selector(s, f, k, n, result):
  m = k+1
  while m <= n and s[m] < f[k]:
    m = m+1
  if m <= n:
    result.append(m)
    Rec_Activity_Selector(s, f, m, n, result)
  else:
    return 

result = []
Rec_Activity_Selector(s, f, 0, len(s)-1, result)
print(result)