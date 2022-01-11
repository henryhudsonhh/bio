class Hexagon:
  def __init__(self, row, col, val):
    self.row, self.col = row, col
    self.sides = list("XXXXXX")
    self.val = val
    self.owned = -1

edge_match = {0: 3, 1: 4, 2: 5, 3: 0, 4: 1, 5: 2}

grid = []

locs = [[0, 0], [4, 4]]
dirs = [0, 5]
[r, b] = [int(x) for x in input().split(' ')]

ct = 0
for i in range(5):
  row = []
  for j in range(5):
    ct += 1
    row.append(Hexagon(i, j, ct))
  grid.append(row)

def updateOwnership(hexagon):
  global grid
  s = grid[hexagon[0]][hexagon[1]].sides
  rc, bc = 0, 0
  for i in range(6):
    if s[i] == "R":
      rc += 1
    elif s[i] == "B":
      bc += 1
  if rc > bc:
    grid[hexagon[0]][hexagon[1]].owned = "R"
  elif bc > rc:
    grid[hexagon[0]][hexagon[1]].owned = "B"
  else:
    grid[hexagon[0]][hexagon[1]].owned = -1

def valToCoords(val):
  return [(val - 1) // 5, (val - 1) % 5]

def updateLoc(loc, c):
  global grid
  val = grid[loc[0]][loc[1]].val - 1
  val += c
  val %= 25

  loc = valToCoords(val + 1)
  return loc

def updateDirs():
  global dirs
  dirs[0] += 1
  dirs[0] %= 5
    
  dirs[1] -= 1
  if dirs[1] < 0:
    dirs[1] = 4

def updateNeighbour(loc, side, c):
  global grid
  addupper, addlower, minusupper, minuslower = 5, 4, 6, 5
  if loc[0] % 2 != 0:
    addupper, addlower, minusupper, minuslower = 6, 5, 5, 4
  if side == 1:
    grid[loc[0]][loc[1] + 1].sides[4] = c
    updateOwnership([loc[0], loc[1] + 1])
  elif side == 4:
    grid[loc[0]][loc[1] - 1].sides[1] = c
    updateOwnership([loc[0], loc[1] - 1])
  elif side == 0:
    val = grid[loc[0]][loc[1]].val - minuslower
    grid[valToCoords(val)[0]][valToCoords(val)[1]].sides[3] = c
    updateOwnership([valToCoords(val)[0], valToCoords(val)[1]])
  elif side == 2:
    val = grid[loc[0]][loc[1]].val + addupper
    grid[valToCoords(val)[0]][valToCoords(val)[1]].sides[5] = c
    updateOwnership([valToCoords(val)[0], valToCoords(val)[1]])
  elif side == 3:
    val = grid[loc[0]][loc[1]].val + addlower
    grid[valToCoords(val)[0]][valToCoords(val)[1]].sides[0] = c
    updateOwnership([valToCoords(val)[0], valToCoords(val)[1]])
  elif side == 5:
    val = grid[loc[0]][loc[1]].val - minusupper
    grid[valToCoords(val)[0]][valToCoords(val)[1]].sides[2] = c
    updateOwnership([valToCoords(val)[0], valToCoords(val)[1]])
  
def findAndUpdateNeighbour(loc, side, c):
  if loc[0] == 0:
    if side == 0 or side == 5:
      return
  elif loc[0] == 4:
    if side == 2 or side == 3:
      return
  if loc[1] == 0:
    if loc[0] % 2 != 0:
      if side == 4:
        return
    else:
      if side in [3,4,5]:
        return
  if loc[1] == 4:
    if loc[0] % 2 == 0:
      if side == 1:
        return
    else:
      if side in [0,1,2]:
        return

  updateNeighbour(loc, side, c)

def getNeighbours(loc):
  ns = ["" for i in range(6)]
  addupper, addlower, minusupper, minuslower = 5, 4, 6, 5
  if loc[0] % 2 != 0:
    addupper, addlower, minusupper, minuslower = 6, 5, 5, 4
  if loc[0] != 0 and not (loc[1] == 4 and loc[0] % 2 != 0):
    nVal = grid[loc[0]][loc[1]].val - minuslower
    ns[0] = valToCoords(nVal)
  else:
    ns[0] = ""
  if loc[1] != 4:
    ns[1] = [loc[0], loc[1] + 1]
  else:
    ns[1] = ""
  if loc[0] != 4:
    if not (loc[1] == 4 and loc[0] % 2 != 0):
      nVal = grid[loc[0]][loc[1]].val + addupper
      ns[2] = (valToCoords(nVal))
    else:
      ns[2] = ""
    if not (loc[1] == 0 and loc[0] % 2 == 0):
      nVal = grid[loc[0]][loc[1]].val + addlower
      ns[3] = (valToCoords(nVal))
    else:
      ns[3] = ""
  else:
    ns[2] = ""
    ns[3] = ""
  if loc[1] != 0:
    ns[4] = [loc[0], loc[1] - 1]
  else:
    ns[4] = ""
  if loc[0] != 0 and not (loc[1] == 0 and loc[0] % 2 == 0):
    nVal = grid[loc[0]][loc[1]].val - minusupper
    ns[5] = (valToCoords(nVal))
  else:
    ns[5] = ("")
  return ns

def skirmish():
  global grid, locs, dirs
  grid[locs[0][0]][locs[0][1]].sides[dirs[0]] = "R"
  findAndUpdateNeighbour(locs[0], dirs[0], "R")
  updateOwnership(locs[0])
  locs[0] = updateLoc(locs[0], r)
  
  grid[locs[1][0]][locs[1][1]].sides[dirs[1]] = "B"
  findAndUpdateNeighbour(locs[1], dirs[1], "B")
  updateOwnership(locs[1])
  locs[1] = updateLoc(locs[1], b)

  updateDirs()

def gainAndRemoved(l, loc):
  res = []
  nbs = getNeighbours(loc)
  curr = grid[loc[0]][loc[1]].sides.copy()
  for n in range(len(nbs)):
    gain, removed = 0, 0
    if nbs[n] != "":
      sds = grid[nbs[n][0]][nbs[n][1]].sides.copy()
      if sds[edge_match[n]] == "X" and curr[n] == "X":
        if l == "R":
          if sds.count("R") + 1 > sds.count("B") and sds.count("R") == sds.count("B"):
            gain += 1
          elif sds.count("R") + 1 == sds.count("B"):
            removed += 1
          if curr.count("R") + 1 > curr.count("B") and curr.count("R") == curr.count("B"):
            gain += 1
          elif curr.count("R") + 1 == curr.count("B"):
            removed += 1
        else:
          if sds.count("R") < sds.count("B") + 1 and sds.count("R") == sds.count("B"):
            gain += 1
          elif sds.count("R") == sds.count("B") + 1:
            removed += 1
          if curr.count("R") < curr.count("B") + 1 and curr.count("R") == curr.count("B"):
            gain += 1
          elif curr.count("R") == curr.count("B") + 1:
            removed += 1
        res.append([gain, removed, grid[loc[0]][loc[1]].val, n, loc[0], loc[1]])
  
  return res

def preferredEdge(l):
  main = []
  for i in range(5):
    for j in range(5):
      edges = gainAndRemoved(l, [i, j])
      if i == 0 and j == 1:
        edges = gainAndRemoved(l, [i, j])
      for z in range(len(edges)):
        main.append(edges[z])
  
  main = sorted(main, key=lambda x:x[0])
  if len(main) == 0:
    quit("Invalid Entry")
  mostGains = [main[-1]]
  for i in range(len(main) - 2, -1, -1):
    if main[i][0] == main[i + 1][0]:
      mostGains.append(main[i])
    else:
      break

  if len(mostGains) > 1:
    mostGains = sorted(mostGains, key=lambda x:x[1])
    mostRemoved = [mostGains[-1]]
    for i in range(len(mostGains) - 2, -1, -1):
      if mostGains[i][1] == mostGains[i + 1][1]:
        mostRemoved.append(mostGains[i])
      else:
        break

    if len(mostRemoved) > 1: 
      if l == "R":
        mostRemoved = list(reversed(sorted(mostRemoved, key=lambda x:x[2])))
      else:
        mostRemoved = sorted(mostRemoved, key=lambda x:x[2])
      bestHexNum = [mostRemoved[-1]]
      for i in range(len(mostRemoved) - 2, -1, -1):
        if mostRemoved[i][2] == mostRemoved[i + 1][2]:
          bestHexNum.append(mostRemoved[i])
        else:
          break

      if len(bestHexNum) > 1:
        if l == "R":
          bestHexNum = list(reversed(sorted(bestHexNum, key=lambda x:x[3])))
        else:
          bestHexNum = sorted(bestHexNum, key=lambda x:x[3])
        pr = bestHexNum[-1]
      else:
        pr = bestHexNum[0]
    else:
      pr = mostRemoved[0]
  else:
    pr = mostGains[0]

  return pr

def feud():
  global grid, locs, dirs
  edge = preferredEdge("R")
  grid[edge[4]][edge[5]].sides[edge[3]] = "R"
  updateOwnership([edge[4], edge[5]])
  findAndUpdateNeighbour([edge[4], edge[5]], edge[3], "R")

  edge = preferredEdge("B")
  grid[edge[4]][edge[5]].sides[edge[3]] = "B"
  updateOwnership([edge[4], edge[5]])
  findAndUpdateNeighbour([edge[4], edge[5]], edge[3], "B")
[s, f] = [int(x) for x in input().split(' ')]

for i in range(s):
  skirmish()
for i in range(f):
  feud()

rcount, bcount = 0, 0
for i in range(5):
  for j in range(5):
    if grid[i][j].owned == "R":
      rcount += 1
    elif grid[i][j].owned == "B":
      bcount += 1
print(rcount)
print(bcount)
