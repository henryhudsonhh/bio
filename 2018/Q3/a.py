# Scores 24/24 | 100%

l = int(input())
root = input()

path = ""

smallest = {"null": 0}

def swap(root, i, j):
  ls = list(root)
  ls[i], ls[j] = ls[j], ls[i]
  return "".join(ls)

def getTransformations(root):
  original = root
  newCodes = set()
  for i in range(0, len(root) - 2):
    if (root[i + 2] > root[i + 1] and root[i + 2] < root[i]) or (root[i + 2] < root[i + 1] and root[i + 2] > root[i]):
      root = swap(root, i, i + 1)
      newCodes.add(root)
      root = original
  for i in range(1, len(root) - 1):
    if (root[i - 1] < root[i] and root[i - 1] > root[i + 1]) or (root[i - 1] > root[i] and root[i - 1] < root[i + 1]):
      root = swap(root, i, i + 1)
      newCodes.add(root)
      root = original
  return newCodes

def constructGraph(depth, root, path):
  transformations = getTransformations(root)

  for t in transformations:
    if(t in smallest.keys() and depth < smallest[t]) or not t in smallest.keys():
      newPath = [path[i:i+l] for i in range(0, len(path), l)]
      if t not in newPath:
        smallest[t] = depth

        newPath.append(t)
        constructGraph(depth + 1, t, "".join(newPath))


constructGraph(1, root, root)

t = max(smallest.values())

print(t)

# Second Solution, scores 24/24 | 100%

n = int(input())
num = input()

def swapString(s, i1, i2):
  s = list(s)
  s[i1], s[i2] = s[i2], s[i1]
  return "".join(s)

graph = dict()

def getNeighbours(s):
  res = set()
  for i in range(len(s) - 1):
    if 0 < i < len(s) - 2:
      [a, b, c, d] = [int(x) for x in s[i-1:i+3]]
      if b < a < c or b < d < c or b > a > c or b > d > c:
        res.add(swapString(s, i, i+1))
    elif i == 0:
      [a, b, c] = [int(x) for x in s[i:i+3]]
      if a < c < b or a > c > b:
        res.add(swapString(s, i, i+1))
    else:
      [a, b, c] = [int(x) for x in s[i-1:i+2]]
      if c < a < b or c > a > b:
        res.add(swapString(s, i, i+1))
  return list(res)
  
foundNew = True
seen = set()
seen.add(num)
graph[num] = 0
depth = 0
newlayer = [num]

while foundNew:
    depth += 1
    layer = newlayer.copy()
    newlayer = []

    foundNew = False
    while len(layer):
      current = layer.pop(0)
      neighbours = getNeighbours(current)
      for node in neighbours:
        if node not in seen:
          newlayer.append(node)
          seen.add(node)
          foundNew = True
          graph[node] = depth

print(max(graph.values()))
