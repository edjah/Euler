from urllib.request import urlretrieve

with open('offline_problems.txt') as f:
    unsolved = [line.rstrip() for line in f]

base_url = "https://projecteuler.net/problem="
for num in unsolved:
    print('Downloading #{}'.format(num))
    urlretrieve(base_url + num, "unsolved/problem{}.html".format(num))

print('Done')
