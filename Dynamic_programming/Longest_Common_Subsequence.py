
####  simple recursive version  ####
def lcs(X, Y, m, n):
  if m==0 or n==0:
    return 0
  elif X[m]==Y[n]:
    return 1+ lcs(X, Y, m-1, n-1)
  else:
    return max(lcs(X, Y, m-1, n), lcs(X, Y, m, n-1))

str1 = " ABCDEF"
str2 = " GBCDFE"
x = lcs(str1, str2, 6, 6)
# print(x)    #3

str1 = " AXYT"
str2 = " AYZXT"
x = lcs(str1, str2, 4, 5)
# print(x)    #4


#######  bottom-up approach (dynamic programming)  #######
str1 = ' amputation' #" ABCDEF"
str2 = ' spanking' #" GBCDFE"

## **주의!**
## column을 나타내는 j는 str1, row를 나타내는 i는 str2 

## northwest = 0, west = 1, north = 2
b = [ [ 0 for y in range( len(str1) ) ]
             for x in range( len(str2) ) ] # for direction  **do not use index 0, start from index 1**
c = [ [ 0 for y in range( len(str1) ) ]
             for x in range( len(str2) ) ]  # for length size

def LCS_Length(X, Y):
  for i in range(1, len(str2)):
    for j in range(1, len(str1)):
      if str1[j] == str2[i]:
        c[i][j] = c[i-1][j-1] + 1
        b[i][j] = 0 #northwest
      elif c[i-1][j] >= c[i][j-1]:
        c[i][j] = c[i-1][j]
        b[i][j] = 2 #north
      else:
        c[i][j] = c[i][j-1]
        b[i][j] = 1 #west

def print_LCS(b, X, i, j):
  if i==0 or j==0:
    return
  elif b[i][j] == 0:  #b[i][j] is northwest
    print_LCS(b, X, i-1, j-1)
    print(f'  {X[j]}', end='')
  elif b[i][j] == 1:
    print_LCS(b, X, i, j-1)
  else:
    print_LCS(b, X, i-1, j)

def print_arr(X):
  for i in range(len(str2)):
    for j in range(len(str1)):
      print(f'{X[i][j]:3}', end='')
    print()
  print()


LCS_Length(str1, str2)
print('array c')
print_arr(c)
print('array b')
print_arr(b)
print_LCS(b, str1, len(str2)-1, len(str1)-1)
print()