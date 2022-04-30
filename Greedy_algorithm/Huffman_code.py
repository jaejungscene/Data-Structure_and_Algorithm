class Node:
    def __init__(self):
        self.freq = None
        self.left = None
        self.right = None

    @property
    def getfreq(self):
        return self.freq

    @property
    def getLeft(self):
        return self.left
    
    @property
    def getRight(self):
        return self.right

    def setfreq(self, value):
        self.freq = value

    def setLeft(self, node):
        self.left = node

    def setRright(self, node):
        self.right = node

    # def __str__(self):
    #   # return "asdf"
    #   return "({}, {})".format(self.char, self.freq)


class Leaf:
    # init() : constructor
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq

    @property
    def getchar(self):
        return self.char

    @property
    def getfreq(self):
        return self.freq

    def __str__(self):
      # return "asdf"
      return "({}, {})".format(self.char, self.freq)

#####################################################

# 7주차 algorithm 강의노트 31 page에서 확인할 수 있다.
# C = [ None, Leaf('f',5), Leaf('e',9), Leaf('c',12), Leaf('b',13), Leaf('d',16), Leaf('a',45) ] # case 1
# C = [ None, Leaf('z',2), Leaf('k',7), Leaf('m',24), Leaf('c',32), Leaf('u',37), Leaf('d',42), Leaf('l',42), Leaf('e',120) ] # case 2
C = [ None, Leaf('f',5), Leaf('e',9), Leaf('c',12), Leaf('b',13), Leaf('a',45) ] # case 3

C[0] = len(C)-1


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
      if Q[current*2+1].getfreq >= Q[current*2].getfreq:
        tmp = current*2
      else:
        tmp = current*2+1
    if Q[current].getfreq > Q[tmp].getfreq:
      swap(Q, current, tmp)
    else:
      break
    current = tmp
  return rtr_value  
  
def build_huffman_tree(C):
  for i in range(C[0]-1):
    z = Node()
    x = extract_min(C)
    y = extract_min(C)
    z.setfreq(x.getfreq + y.getfreq)
    z.setLeft(x)
    z.setRright(y)
    insert(C, z)
  return extract_min(C)

p = 0
def find_print_code(Now, code): # preorder travel and print code
  global p
  if isinstance(Now, Node):
    code[p] = 0
    p += 1
    find_print_code(Now.getLeft, code)
    code[p] = 1
    p += 1
    find_print_code(Now.getRight, code)
  else:
    print( '(%c, %2d) :'%(Now.getchar, Now.getfreq), code[:p] )
  p -= 1


code = [None,None,None,None,None,None,None,None,None,None]
root = build_huffman_tree(C)
find_print_code(root, code)