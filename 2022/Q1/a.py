# Scores 24/24 | 100%

def getLetter(a, b):
  a, b = ord(a) - 64, ord(b) - 64
  join = (a - b)
  if join < 1:
    join += 26
  return chr(join + 64)

s = list(input())

for i in range(len(s) - 1, 0, -1):
  s[i] = getLetter(s[i], s[i - 1])

print("".join(s))
