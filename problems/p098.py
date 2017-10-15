from time import perf_counter
start = perf_counter()

with open('p098_words.txt', 'r') as f:
    words = eval(f.readline())

anagrams = []
for i in range(len(words) - 1):
    for j in range(i + 1, len(words)):
        if sorted(words[i]) == sorted(words[j]):
            anagrams.append((words[i], words[j]))

def is_square(n):
    k = n ** 0.5
    return k == int(k)

def test_square_anagram(pair):
    a, b = pair
    seen = set()
    unique_chars = ''.join(c for c in a if not (c in seen or seen.add(c)))
    unique = len(unique_chars)
    ans = None
    def digit_sub(repl, n, digits):
        nonlocal ans
        if n <= 0:
            x, y = a, b
            for i in range(unique):
                c = str(repl[i])
                x = x.replace(unique_chars[i], c)
                y = y.replace(unique_chars[i], c)
            if x[0] != '0' and y[0] != '0':
                q, w = int(x), int(y)
                if is_square(q) and is_square(w):
                    if ans == None:
                        ans = max(q, w)
                    else:
                        ans = max(ans, q, w)
            return
        for d in digits:
            new_digits = [i for i in digits if i != d]
            digit_sub(repl + (d,), n - 1, new_digits)

    digit_sub((), unique, range(10))
    return ans


ans = (0, ('', ''))
for pair in anagrams:
    x = test_square_anagram(pair)
    if x is not None:
        if x > ans[0]:
            ans = (x, pair)

print('Solution:', ans[0], ans[1])

end = perf_counter()
print(end - start, 'seconds to run')
