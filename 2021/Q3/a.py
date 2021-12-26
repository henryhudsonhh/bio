# Scores 24/24 | 100%

def add(window):
  for i in range(len(warehouse)):
    if warehouse[i] not in window:
      window += warehouse[i]
      return window
  return window

def swap(window):
  window = list(window)
  window[0], window[1] = window[1], window[0]
  return "".join(window)

def rotate(window):
  window = list(window)
  window.append(window.pop(0))
  return "".join(window)

order = input()
warehouse = "".join(sorted(order))

correct = False
depth = -1
nextLayer = [""]

seen = set()

while not correct:
  depth += 1

  layer = nextLayer.copy()
  nextLayer = []

  while len(layer) > 0:
    current = layer.pop(0)
    if current == order:
      correct = True
      layer = []
    if current not in seen:
      seen.add(current)
      if depth <= 1:
        nextLayer.append(add(current))
      else:
        nextLayer.append(add(current))
        nextLayer.append(swap(current))
        nextLayer.append(rotate(current))

print(depth)
