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
