# Scores 24/24 | 100%

def getLargestNumBelow(n):
  fib1, fib2, fib3 = 0, 1, 1
  if n <= 1:
      return n
  while (fib3 <= n):
      fib1, fib2 = fib2, fib3
      fib3 = fib1 + fib2
  return fib2

def solve(n):
  nums = []

  while n:
    num = getLargestNumBelow(n)
    nums.append(str(num))
    n -= num
    
  res = " ".join(nums)
  return res

print(solve(int(input())))
