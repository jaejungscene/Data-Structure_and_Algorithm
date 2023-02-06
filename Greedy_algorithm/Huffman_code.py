import sys                                                            
sys.path.append("/Users/jaejungscene/Projects/DataStructure_and_Algorithm")
from Tree.min_heap import insert, extract_min;

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
# C = [ None, Leaf('f',5), Leaf('e',9), Leaf('c',12), Leaf('b',13), Leaf('a',45) ] # case 3
C = [ None, Leaf('o',3), Leaf('a',8), Leaf('i',10), Leaf('t',12), Leaf('e',24), Leaf('s',33), Leaf('u',57) ] # case 4

C[0] = len(C)-1
  
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

def preorder(root):
  if isinstance(root, Node):
    print(root.getfreq,' ', end='')
    preorder(root.getLeft)
    preorder(root.getRight)
  else:
    print('(',root.getchar,root.getfreq,') ', end='')

code = [None,None,None,None,None,None,None,None,None,None,None]
root = build_huffman_tree(C)
preorder(root)
print()
find_print_code(root, code)