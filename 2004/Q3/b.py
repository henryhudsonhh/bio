# Scores 5/5 | 100%

d = {
  ".-": "a", "-...": "b", "-.-.": "c",
  "-..": "d", ".": "e", "..-.": "f", "--.": "g",
  "....": "h", "..": "i", ".---": "j", "-.-": "k",
  ".-..": "l", "--": "m", "-.": "n", "---": "o",
  ".--.": "p", "--.-": "q", ".-.": "r", "...": "s",
  "-": "t", "..-": "u", "...-": "v", ".--": "w",
  "-..-": "x", "-.--": "y", "--..": "z"
}

c = {}

for i in d.keys():
  c[d[i]] = i


def getNextSubStrings(fullString):
  return [fullString[:i+1] for i in range(min(4,len(fullString)))]

def isLetter(morseCode):
  return morseCode in d.keys()

def constructTree(code, letters):
  global ct


  if len(code) == 0:
    ct += 1
  else:
    nxt = getNextSubStrings(code)
    for newCode in nxt:
      if isLetter(newCode):
        constructTree(code[len(newCode):], letters + d[newCode])

ct = 0

constructTree("-----", "")

print(ct)

ct = 0

constructTree("-..-----.", "")

print(ct)
