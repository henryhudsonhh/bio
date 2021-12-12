# Scores 24/24 | 100%

from copy import deepcopy

odeck = []
shuffleints = [int(x) for x in input().split(" ")]

suits = ["C", "H", "S", "D"]
values = ["A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"]

def validMove(p1, p2, i1, i2):
  if p1[0] == p2[0] or p1[1] == p2[1]:
    if abs(i1 - i2) == 1:
        return True
    elif abs(i1 - i2) == 3:
        return True
  return False

def move(deck, i1, i2):
  for i in range(len(deck[i1]) - 1, -1, -1):
    deck[i2].insert(0, deck[i1][i])
  deck.remove(deck[i1])

def rotate(l):
  return l[1:] + l[:1]

def shuffle(deck):
  d = deck.copy()
  shuffleddeck = []
  c = 0
  while len(d) != 0:
    num = shuffleints[c]

    for i in range(1, num):
      d = rotate(d)

    shuffleddeck.append(d[0])
    d.pop(0)

    c += 1
    c %= 6
  return shuffleddeck


def s1():
  flag = True
  while flag:
    flag = False
    for i in range(len(deck) - 1, 0, -1):
      if validMove(deck[i][0], deck[i - 1][0], i, i - 1):
        move(deck, i, i - 1)
        flag = True
        break
      elif i >= 3:
        if validMove(deck[i][0], deck[i - 3][0], i, i - 3):
          move(deck, i, i - 3)
          flag = True
          break
    if len(deck) == 1:
      flag = False

def s2():
  flag = True
  while flag:
    moves = []
    for i in range(len(deck) - 1, 0, -1):
      if validMove(deck[i][0], deck[i - 1][0], i, i - 1):
        moves.append([len(deck[i]) + len(deck[i - 1]), i, i - 1])
      if i >= 3:
        if validMove(deck[i][0], deck[i - 3][0], i, i - 3):
          moves.append([len(deck[i]) + len(deck[i - 3]), i, i - 3])
    mx = 0
    mxMove = []
    
    for i in range(len(moves)):
      if moves[i][0] > mx:
        mx = moves[i][0]
        mxMove = moves[i]
    if len(moves) == 0:
      flag = False
    else:
      move(deck, mxMove[1], mxMove[2])

def possibleMoves(deck):
  n = 0
  for i in range(len(deck) - 1, 0, -1):
    if validMove(deck[i][0], deck[i - 1][0], i, i - 1):
      n += 1
    if i >= 3:
      if validMove(deck[i][0], deck[i - 3][0], i, i - 3):
        n += 1
  return n

def s3():
  flag = True
  while flag:
    moves, mx = 0, -1
    maxmove = []
    for i in range(len(deck) - 1, 0, -1):
      moves = 0
      if validMove(deck[i][0], deck[i - 1][0], i, i - 1):
        newdeck = deepcopy(deck)
        move(newdeck, i, i - 1)
        moves += possibleMoves(newdeck)

        if moves > mx:
          mx = moves
          maxmove = [i, i - 1]
      moves = 0
      if i >= 3:
        if validMove(deck[i][0], deck[i - 3][0], i, i - 3):
          newdeck = deepcopy(deck)
          move(newdeck, i, i - 3)
          moves += possibleMoves(newdeck)
          if moves > mx:
            mx = moves
            maxmove = [i, i - 3]
    if mx == -1:
      flag = False
    else:
      move(deck, maxmove[0], maxmove[1])

for suit in range(4):
  for val in range(13):
    card = values[val] + suits[suit]
    odeck.append([card])

odeck = shuffle(odeck)

print(odeck[0][0], odeck[len(odeck) - 1][0])

deck = deepcopy(odeck)
s1()
print(len(deck), deck[0][0])

deck = deepcopy(odeck)
s2()
print(len(deck), deck[0][0])

deck = deepcopy(odeck)
s3()
print(len(deck), deck[0][0])
