# Scores 24/24 | 100%

def exec(s, c):
  r = s.copy()
  if c == 0:
    n = r.pop(0)
    r.insert(3, n)
  elif c == 1:
    n = r.pop(6)
    r.insert(3, n)
  elif c == 2:
    n = r.pop(3)
    r.insert(0, n)
  else:
    n = r.pop(3)
    r.insert(6, n)
  return r

s = [int(x) for x in input()]
target = [1,2,3,4,5,6,7]
layer = []
nextLayer = [s]
checked = set()

depth = -1
found = False

while not found:
  depth += 1

  layer = nextLayer.copy()
  nextLayer = []

  while len(layer) > 0:
    current = layer.pop(0)
    currentStr = "".join([str(x) for x in current])
    if currentStr in checked:
      pass
    else:
      if current == target:
        found = True
        layer = []
      else:
        checked.add(currentStr)
        for i in range(4):
          nextLayer.append(exec(current, i))

print(depth)
