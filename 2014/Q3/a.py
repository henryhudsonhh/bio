# Scores 25/25 | 100%

letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

def numberOfPasswordsWithLength(l, b, dp):
  if l <= 1:
    return l
  if f"{l} {b}" in dp:
    return dp[f"{l} {b}"]

  num = sum(numberOfPasswordsWithLength(l - 1, i, dp) for i in range(b + 1, 36))
  dp[f"{l} {b}"] = num

  return num

def getLengthAndPrevious():
  c = 0
  prev = 0
  for l in range(36):
    for begin in range(36):
      c += numberOfPasswordsWithLength(l + 1, begin, dp)
      if c >= n:
        return [l + 1, prev]
    prev = c

n = int(input())
s = ""

dp = dict()

res = getLengthAndPrevious()
length, previous = res[0], res[1]
prevChar = -1

n -= previous

for i in range(length, 0, -1):
  c = 0
  for j in range(prevChar + 1, 36):
    c += numberOfPasswordsWithLength(i, j, dp)

    if c >= n:
      s += letters[j]
      prevChar = j
      break

  n -= c - numberOfPasswordsWithLength(i, prevChar, dp)

print(s)
