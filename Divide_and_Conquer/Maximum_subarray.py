INT_MIN = -2147483648


def Find_Crossing_subarray(A, low, mid, high):
  max_left = mid
  left_sum = INT_MIN
  sum = 0
  for i in range(mid, low-1, -1):
    sum = sum + A[i]
    if sum > left_sum:
      left_sum = sum
      max_left = i

  max_right = mid+1
  right_sum = INT_MIN
  sum = 0
  for i in range(mid+1, high+1, 1):
    sum = sum + A[i]
    if sum > right_sum:
      right_sum = sum
      max_right = i
  
  return (max_left, max_right, left_sum+right_sum)


def Find_Maximum_subarray(A, low, high):
  if high == low:
    return (low, high, A[low])
  else:
    mid = (int((low+high)/2))  # e.g.) 2~4  -->  2+{(4-2)/2} = 3  -->  (low+high)/2
    (left_low, left_high, left_sum) = \
      Find_Maximum_subarray(A, low, mid)
    (right_low, right_high, right_sum) = \
      Find_Maximum_subarray(A, mid+1, high)
    (cross_low, cross_high, cross_sum) = \
      Find_Crossing_subarray(A, low, mid, high)
  
  if left_sum >= right_sum and left_sum >= cross_sum:
    return (left_low, left_high, left_sum)
  elif right_sum >= left_sum and right_sum >= cross_sum:
    return (right_low, right_high, right_sum)
  else:
    return (cross_low, cross_high, cross_sum)


A = [None, -2,1,-3,4,-1,2,1,-5,4]
print(f"Array = {A}")  
(i, j, sum) = Find_Maximum_subarray(A, 1, len(A)-1)
print(f"sum = {sum}")
print(f"Max_Subarray = {A[i:j+1]}")
print()

A = [None, -2,-3,4,-1,-2,1,5,-3]
print(f"Array = {A}")  
(i, j, sum) = Find_Maximum_subarray(A, 1, len(A)-1)
print(f"sum = {sum}")
print(f"Max_Subarray = {A[i:j+1]}")
print()