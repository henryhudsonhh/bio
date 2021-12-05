# Scores 24/24 | 100%

from itertools import cycle

class Cell:
  def __init__(self, clock):
    self.clock = clock
  
  def updateClock(self):
    self.clock += 1

grid = {
  repr([0,0]): Cell(0)
}

cRow = 0
cCol = 0

inp = input().split(" ")
disappear = int(inp[0])
trail = [repr([0,0])]
ins = inp[1]
n = int(inp[2])

rowDirs = [-1, 0, 1, 0]
colDirs = [0, 1, 0, -1]
dirPtr = 0
cycleIns = cycle(list(ins))

fRow = rowDirs[dirPtr]
fCol = colDirs[dirPtr]

def nextIns():
  return next(cycleIns)

def updateTrail():
  if len(trail) == disappear:
    grid[trail[0]].clock = -1
    trail.pop(0)
  for coord in trail:
    grid[coord].updateClock()

stopFlag = False

for i in range(n):
  instruction = nextIns()

  if instruction == "R":
    dirPtr = (dirPtr + 1) % 4
  elif instruction == "L":
    dirPtr = (dirPtr - 1) % 4

  fRow = rowDirs[dirPtr]
  fCol = colDirs[dirPtr]

  whileFlag = False

  if repr([cCol + fCol, cRow + fRow]) in grid:
    count = 0
    occupiedFlag = False

    if grid[repr([cCol + fCol, cRow + fRow])].clock != -1:
      occupiedFlag = True

    while occupiedFlag:
      whileFlag = True
      if count == 4:
        stopFlag = True
        break
      dirPtr = (dirPtr + 1) % 4
      fRow = rowDirs[dirPtr]
      fCol = colDirs[dirPtr]

      coord = repr([cCol + fCol, cRow + fRow])

      if coord not in grid or grid[coord].clock == -1:
        occupiedFlag = False
        cCol += fCol
        cRow += fRow

      count += 1
  
  if not whileFlag:
    cCol += fCol
    cRow += fRow

  
  updateTrail()
  grid[repr([cCol, cRow])] = Cell(0)
  trail.append(repr([cCol, cRow]))
  
  if stopFlag:
    break

print('(' + str(cCol) + ', ' + str(cRow * -1) + ')')
