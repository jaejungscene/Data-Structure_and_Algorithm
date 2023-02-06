# def build_min_heap(C):

def swap(Q, a, b):
  tmp = Q[a]
  Q[a] = Q[b]
  Q[b] = tmp

def insert(Q, z):
  Q[0] += 1
  Q[Q[0]] = z
  current = Q[0]
  while True:
    if current == 1:
      break
    if Q[current].getfreq < Q[current//2].getfreq:
      swap(Q, current, current//2)
      current = current//2
    else:
      break

def extract_min(Q):
  rtr_value = Q[1]
  Q[1] = Q[Q[0]]
  Q[Q[0]] = None
  Q[0] -= 1
  current = 1
  while True:
    if current*2 > Q[0]:
      break
    if current*2 == Q[0]:
      tmp = current*2
    else:
      if Q[current*2+1].getfreq > Q[current*2].getfreq: # (> or >=)로 값 바뀜
        tmp = current*2
      else:
        tmp = current*2+1

    if Q[current].getfreq >= Q[tmp].getfreq: # ( >= or > )로 값 바뀜 
      swap(Q, current, tmp)
    else:
      break
    current = tmp
  return rtr_value  