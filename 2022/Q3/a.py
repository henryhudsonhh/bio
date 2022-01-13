[s, ith] = [x for x in input().split(' ')]
ith = int(ith)

def getPossibleLetters(position):
  position = s.index(chr(position + 97))

  possible = [chr(position + 65)]
  for i in range(position - 1, -1, -1):
    if ord(s[i]) < ord(s[position]):
      possible.append(chr(i + 65))
    else:
      break

  return "".join(reversed(possible))

firstLetter = getPossibleLetters(0)

prefList = [firstLetter]

def solve(i):
  global ith
  if len(prefList) == len(s):
    return
  else:
    possibleLetters = getPossibleLetters(i)
    for k in range(len(possibleLetters)):
      totalCombs = 1
      for j in range(i + 1, len(s)):
        totalCombs *= len(getPossibleLetters(j))
      if totalCombs >= ith:
        prefList.append(possibleLetters[k])
        return solve(i + 1)
      else:
        ith -= totalCombs

solve(1)
print("".join(prefList))
