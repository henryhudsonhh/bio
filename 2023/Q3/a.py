# Scores 23/23 | 100%

from copy import deepcopy

start = [[int(x) for x in ipt] for ipt in input().split(' ')]
end = [[int(x) for x in ipt] for ipt in input().split(' ')]

def move(state, from_stack, to_stack):
  if state[to_stack] != [0]:
    state[to_stack].append(state[from_stack].pop())
  else:
    state[to_stack] = [state[from_stack].pop()]
  if state[from_stack] == []:
    state[from_stack] = [0]
  return state

def getNeighbours(state):
  res = []
  for i in range(4):
    if state[i][-1] != 0:
      for j in range(4):
        if i != j:
          res.append(move(deepcopy(state), i, j))
  return res
          
notFound = True
seen = []
seen.append(start)
depth = -1
newlayer = [start]

while notFound:
  depth += 1
  layer = newlayer.copy()
  newlayer = []

  while(len(layer)):
    current = layer.pop(0)
    if current == end:
      notFound = False
      break
      
    neighbours = getNeighbours(current)
    for node in neighbours:
      if node not in seen:
        newlayer.append(node)
        seen.append(node)

print(depth)
