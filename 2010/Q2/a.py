# Scores 24/24 | 100%

grid = [
  ["x"] * 13,
  ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"], 
  ["x"] + [1] * 4 + [int(x) for x in input().split(" ")] + [1] * 4 + ["x"], 
  ["x"] + [1] * 4 + [int(x) for x in input().split(" ")] + [1] * 4 + ["x"], 
  ["x"] + [1] * 4 + [int(x) for x in input().split(" ")] + [1] * 4 + ["x"], 
  ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"], ["x"] + [1] * 11 + ["x"],
  ["x"] * 13,
]

def printGridFromPos(row, col):
  print(f"{grid[row - 1][col - 1]}{grid[row - 1][col]}{grid[row - 1][col + 1]}\n{grid[row][col - 1]}{grid[row][col]}{grid[row][col + 1]}\n{grid[row + 1][col - 1]}{grid[row + 1][col]}{grid[row + 1][col + 1]}")

def rotateDie():
  if header == UP:
    die[0], die[1], die[2], die[3], die[4], die[5] = die[3], die[0], die[1], die[2], die[4], die[5]
  elif header == RIGHT:
    die[0], die[1], die[2], die[3], die[4], die[5] = die[4], die[1], die[5], die[3], die[2], die[0]
  elif header == DOWN:
    die[0], die[1], die[2], die[3], die[4], die[5] = die[1], die[2], die[3], die[0], die[4], die[5]
  else:
    die[0], die[1], die[2], die[3], die[4], die[5] = die[5], die[1], die[4], die[3], die[0], die[2]

def moveDie():
  global header, row, col
  h = (die[0] + grid[row][col])
  if h > 6:
    h -= 6
  grid[row][col] = h
  
  if h == 2:
    header += 1
    if header > 4:
      header = 1
  elif h == 5:
    header -= 1
    if header < 1:
      header = 4
  elif h != 1 and h != 6:
    header += 2
    if header > 4:
      header -= 4
  
  d = dirc[header]

  row += d[0]
  col += d[1]

  if grid[row][col] == "x":
    if d[1] == 1:
      col = 1
    elif d[1] == -1:
      col = 11
    elif d[0] == 1:
      row = 1
    else:
      row = 11
  
  rotateDie()

n = int(input())

UP, RIGHT, DOWN, LEFT = 1, 2, 3, 4

dirc = {
  UP: [-1, 0],
  RIGHT: [0, 1],
  DOWN: [1, 0],
  LEFT: [0, -1]
}

header = UP

row, col = 6, 6

die = [1, 2, 6, 5, 3, 4]

while n > 0:
  for i in range(n):
    moveDie()
  
  printGridFromPos(row, col)

  n = int(input())
