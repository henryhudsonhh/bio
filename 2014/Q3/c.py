# Scores 3/3 | 100%

def numberOfPasswordsWithLength(l, b, dp):
  if l <= 1:
    return l
  if f"{l} {b}" in dp:
    return dp[f"{l} {b}"]

  num = sum(numberOfPasswordsWithLength(l - 1, i, dp) for i in range(b + 1, 36))
  dp[f"{l} {b}"] = num

  return num

dp = dict()

total = 0

for i in range(37):
  for j in range(36):
    total += numberOfPasswordsWithLength(i, j, dp)

print(total)
