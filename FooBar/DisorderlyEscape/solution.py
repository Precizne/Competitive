from collections import Counter

def gcd(a, b):
    if(b == 0):
        return a
    return gcd(b, a % b)

factorial = list()
def gen_factorial(n):
    factorial.append(1)
    for i in range(1, n):
        factorial.append(i * factorial[-1])

def cycles(p, n):
    c = factorial[n]
    for i, j in Counter(p).items():
        c //= (i ** j) * factorial[j]
    return c

def partitions(n, i = 1):
    yield [n]
    for i in range(i, n // 2 + 1):
        for p in partitions(n - i, i):
            yield [i] + p

def solution(w, h, s):
    gen_factorial(100)
    ans = 0
    for part_w in partitions(w):
        for part_h in partitions(h):
            val = cycles(part_w, w) * cycles(part_h, h)
            ans += val * (s ** sum([sum([gcd(i, j) for i in part_w]) for j in part_h]))
    return str(ans // (factorial[w] * factorial[h]))


print(solution(2, 2, 2))
print(solution(2, 3, 4))
