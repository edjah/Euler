from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

prime_set = set(read_primes(10 ** 6))


def compute_n(layer, idx):
    if layer == 0:
        return 1

    layer_start = 3*layer*layer - 3*layer + 2
    layer_size = 6 * layer
    return layer_start + (idx % layer_size)


def PD(layer, idx):
    adj_tiles = [
        (layer + 1, idx + idx // layer + 1),
        (layer + 1, idx + idx // layer),
        (layer - 1, idx - idx // layer),
        (layer, idx + 1),
        (layer, idx - 1),
    ]

    if idx % layer == 0:
        adj_tiles += [(layer + 1, idx + idx // layer - 1)]
    else:
        adj_tiles += [(layer - 1, idx - idx // layer - 1)]

    count = 0
    n = compute_n(layer, idx)
    for adj_layer, adj_idx in adj_tiles:
        other = compute_n(adj_layer, adj_idx)
        count += abs(other - n) in prime_set
    return count


# pd3 tiles are only ever the first or the last tiles in a layer
pd3_tiles = [1]
layer = 1
while len(pd3_tiles) < 2000:
    for idx in (0, 6 * layer - 1):
        if PD(layer, idx) == 3:
            pd3_tiles.append(compute_n(layer, idx))

    layer += 1

print('Solution:', pd3_tiles[1999])
end_time()
