# Scores 25/25 | 100%

n = int(input())

table = dict()

machine = ["0" for _ in range(7)]
pos = 3
state = "1"

for i in range(n):
  instructions = input().split(' ')
  table[f"{i + 1}0"] = instructions[0]
  table[f"{i + 1}1"] = instructions[1]

m = int(input())

it = 0

for i in range(m):
  it += 1
  current = machine[pos]

  ins = table[state + current]
  machine[pos] = ins[0]
  if ins[1] == "R":
    pos += 1
    if len(machine) - pos < 4:
      machine.append("0")
  else:
    if pos == 3:
      machine.insert(0, "0")
    else:
      pos -= 1

  state = ins[2]

  if state == "0":
    break

print("".join(machine[pos - 3:pos + 4]))
print(it)
