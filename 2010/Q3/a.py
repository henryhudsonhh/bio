# Scores 23/23 | 100%

from copy import deepcopy

def pour(jugs, i1, i2):
  if jugs[i1] + jugs[i2] >= jugCaps[i2]:
    jugs[i1] -= jugCaps[i2] - jugs[i2]
    jugs[i2] = jugCaps[i2]
  else:
    jugs[i2] += jugs[i1]
    jugs[i1] = 0
  return jugs

def empty(jugs, i1):
  jugs[i1] = 0
  return jugs

def fill(jugs, i1):
  jugs[i1] = jugCaps[i1]
  return jugs

def check(jugs):
  return n in jugs

inp = input().split(' ')
j, n = int(inp[0]), int(inp[1])

jugCaps = [int(x) for x in input().split(' ')]
jugs = [0 for _ in range(j)]

seenStates = set()
found = False

depth = -1
nextLayer = [jugs]

while not found:
  depth += 1

  layer = deepcopy(nextLayer)
  nextLayer = []

  while len(layer) > 0:
    currentState = layer.pop(0)
    if tuple(currentState) not in seenStates:
      if check(currentState):
        found = True
        layer = []
      else:
        seenStates.add(tuple(currentState))

        for i in range(j):
          new = fill(currentState.copy(), i)
          if new != currentState:
            nextLayer.append(new)

          new = empty(currentState.copy(), i)
          if new != currentState:
            nextLayer.append(new)

          for k in range(j):  
            if i != k:
              new = pour(currentState.copy(), i, k)
              if new != currentState:
                nextLayer.append(new)

print(depth)
