
def Binary_Search(A, low, high, key):
  mid = (low + high)//2
  if high <= low:
    return (False, None)
  elif A[mid] == key:
    return (True, mid)
  elif A[mid] > key:
    return Binary_Search(A, low, mid-1, key)
  else:
    return Binary_Search(A, mid+1, high, key)


A = [1,3,5,7,9,11,12,13,14,17,18,20]

num = 432
(bool, index) = Binary_Search(A, 0, len(A)-1, num)
if bool :
  print(f'{A[index]} is in {index}th')
else:
  print(f"there isn't number ({num})")

# for i in range(1):
#   (bool, index) = Binary_Search(A, 0, len(A)-1, i)
#   if bool:
#     print(f'{A[index]} is in {index}th')
#   else:
#     print(f"there isn't number ({i})")
