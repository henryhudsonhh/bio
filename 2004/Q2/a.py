# Scores 26/26 | 100%

from copy import deepcopy

board = [['X'] * 9]
for i in range(1, 7):
  board.append(['X'])
  for j in range(1, 8):
    board[i].append('-')
  board[i].append('X')
board.append(['X'] * 9)

player = True
players = {True: '*', False: 'o'}

drow, dcol = [-1, -1, -1, 0, 1, 1, 1, 0], [-1, 0, 1, 1, 1, 0, -1, -1]

def play(board, col):
  for i in range(6, 0, -1):
    if board[i][col] == "-":
      board[i][col] = players[player]
      break
  return board

def printBoard():
  for i in range(1, 7):
    for j in range(1, 8):
      print(board[i][j], end="")
    print()

def boardIsFull():
  for i in range(1, 7):
    for j in range(1, 8):
      if board[i][j] == '-':
        return False
  return True

def checkResult(board):
  seen = set()

  if boardIsFull():
    return "Draw"

  for i in range(1, 7):
    for j in range(1, 8):
      if (i, j) not in seen:
        seen.add((i, j))
        current = board[i][j]
        if current != '-':
          for k in range(8):
            checkRow, checkCol = i, j
            posCounter = 0
            invalid = ['X', '-', '*']
            if current == "*":
              invalid = ['X', '-', 'o']
            positions = []
            changeRow, changeCol = drow[k], dcol[k]
            while board[checkRow][checkCol] not in invalid and posCounter < 4:
              posCounter += 1
              checkRow += changeRow
              checkCol += changeCol
              positions.append((checkRow, checkCol))
            if posCounter == 4:
              if current == "*":
                return "Player 1 wins"
              else:
                return "Player 2 wins"
  return None

def nextMove():
  global player, board
  strat2Flag = False

  for i in range(1, 7):
    bCopy = deepcopy(board)
    bCopy = play(bCopy, i)
    res = checkResult(bCopy)
    if res == "Player 1 wins" and player:
      return i
    elif res == "Player 2 wins" and not player:
      return i
    else:
      strat2Flag = True

  if strat2Flag:
    player = not player
    for i in range(1, 7):
      bCopy = deepcopy(board)
      bCopy = play(bCopy, i)
      res = checkResult(bCopy)
      if res != "Draw" and res != None:
        player = not player
        return i

  if strat2Flag:    
    player = not player
    for i in range(1, 8):
      if board[1][i] == '-':
        return i

_ = input()
startMoves = [int(x) for x in input().split(' ')]
finished = False

for move in startMoves:
  board = play(board, move)
  player = not player

printBoard()

instruction = input()

while not finished:

  if instruction == "n":
    col = nextMove()
    board = play(board, col)
    if checkResult(board) == None:
      printBoard()
      instruction = input()
  else:
    instruction = "nr"
    col = nextMove()
    board = play(board, col)

  res = checkResult(board)
  if res != None:
    printBoard()
    if res != None:
      print(res)
      finished = True

  player = not player
