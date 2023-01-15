# Scores 23/23 | 100%

letters = [*input()]

pentominoes = {
  'F': [[0, 1], [0, 2], [1, 0], [1, 1], [2, 1]],
  'G': [[0, 0], [0, 1], [1, 1], [1, 2], [2, 1]],
  'I': [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]],
  'L': [[0, 0], [1, 0], [2, 0], [3, 0], [3, 1]],
  'J': [[0, 1], [1, 1], [2, 1], [3, 1], [3, 0]],
  'N': [[0, 1], [1, 0], [1, 1], [2, 0], [3, 0]],
  'M': [[0, 0], [1, 0], [1, 1], [2, 1], [3, 1]],
  'P': [[0, 0], [0, 1], [1, 0], [1, 1], [2, 0]],
  'Q': [[0, 0], [0, 1], [1, 0], [1, 1], [2, 1]],
  'T': [[0, 0], [0, 1], [0, 2], [1, 1], [2, 1]],
  'U': [[0, 0], [0, 2], [1, 0], [1, 1], [1, 2]],
  'V': [[0, 0], [1, 0], [2, 0], [2, 1], [2, 2]],
  'W': [[0, 0], [1, 0], [1, 1], [2, 1], [2, 2]],
  'X': [[0, 1], [1, 0], [1, 1], [1, 2], [2, 1]],
  'Z': [[0, 0], [0, 1], [1, 1], [2, 1], [2, 2]],
  'S': [[0, 2], [0, 1], [1, 1], [2, 1], [2, 0]],
  'Y': [[0, 1], [1, 0], [1, 1], [2, 1], [3, 1]],
  'A': [[0, 0], [1, 0], [1, 1], [2, 0], [3, 0]]
}

maxI, maxJ = 15, 15

def countOnes(board):
  count = 0
  for i in range(maxI):
    for j in range(maxJ):
      if board[i][j]:
        count += 1
  return count

row, col = 0, 1

def cleanBoard(board):
  for i in range(maxI):
    for j in range(maxJ):
      if board[i][j] != 1:
        board[i][j] = 0
  return board

def drawBoardWithPentomino1(anchor_1, pentomino_1):
  board = [[0 for j in range(maxJ)] for i in range(maxI)]
  for i in range(5):
    coord = [
      anchor_1[row] + pentomino_1[i][row], anchor_1[col] + pentomino_1[i][col]
    ]
    board[coord[row]][coord[col]] = 1
  return board

def drawBoard(board):
  for i in range(maxI):
    for j in range(maxJ):
      print(board[i][j], end="")
    print()

def getBoundingBox(board):
  boundedBoard = []

  topRow, bottomRow, leftCol, rightCol = 0, 0, 0, 0
  for i in range(len(board)):
    if 1 in board[i]:
      topRow = i
      break
  for i in range(len(board) - 1, -1, -1):
    if 1 in board[i]:
      bottomRow = i
      break
  boardT = list(zip(*board))
  for i in range(len(boardT)):
    if 1 in boardT[i]:
      leftCol = i
      break
  for i in range(len(boardT) - 1, -1, -1):
    if 1 in boardT[i]:
      rightCol = i
      break

  boundedBoard = board[topRow:bottomRow + 1]
  boundedBoard = list(zip(*boundedBoard))[leftCol:rightCol + 1]
  return boundedBoard

def solve(letters):
  anchor_1 = [5, 5]
  pentomino_1 = pentominoes[letters[0]]

  board = drawBoardWithPentomino1(anchor_1, pentomino_1)

  anchor_spaces = []
  for i in range(1, maxI - 1):
    for j in range(1, maxJ - 1):
      if board[i][j] == 0:
        if board[i - 1][j] == 1 or board[i + 1][j] == 1 or board[i][
            j - 1] == 1 or board[i][j + 1] == 1:
          anchor_spaces.append([i, j])
          board[i][j] = 'x'

  anchor_2 = []
  pentomino_2 = pentominoes[letters[1]]
  seen = []

  total = 0

  while len(anchor_spaces):  # for each outside space
    anchor_2 = anchor_spaces.pop(0)
    for i in range(5):  # for each anchor on p2
      square_anchor = pentomino_2[i]
      for j in range(5):  # for each point on p2
        relative_coord = pentomino_2[j]
        coord = [
          anchor_2[row] + (relative_coord[row] - square_anchor[row]),
          anchor_2[col] + (relative_coord[col] - square_anchor[col])
        ]
        board[coord[row]][coord[col]] = 1
      board = cleanBoard(board)
      boundedBoard = getBoundingBox(board)
      if countOnes(board) == 10 and boundedBoard not in seen:
        total += 1
        seen.append(boundedBoard)
      board = drawBoardWithPentomino1(anchor_1, pentomino_1)

  return total

print(solve([*letters]))
