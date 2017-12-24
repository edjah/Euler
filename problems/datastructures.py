class HeapEmpty(Exception):
    pass

# min heap by default, but custom comparison functions are possible
class Heap:
    standard_cmp = lambda x, y: 1 if x < y else (-1 if x > y else 0)
    def __init__(self, array=[], compare=standard_cmp, kv_mode=False):
        self.compare = compare
        self.heap = [None, *array]
        self.kv_mode = kv_mode
        self._size = len(array)

        if self.kv_mode:
            self.indices = {}
        if len(array) > 0:
            for i in reversed(range(1, self._size//2 + 1)):
                self.heapify(i)
            if self.kv_mode:
                for i in range(1, len(self.heap)):
                    key = self.heap[i][1]
                    self.indices[key] = i

    def heapify(self, n):
        h = self.heap
        left, right = 2*n, 2*n + 1
        largest = n
        if left <= self._size and self.compare(h[left], h[n]) > 0:
            largest = left
        if right <= self._size and self.compare(h[right], h[largest]) > 0:
            largest = right

        if largest != n:
            h[largest], h[n] = h[n], h[largest]
            if self.kv_mode:
                self.indices[h[n][1]] = n
                self.indices[h[largest][1]] = largest
            self.heapify(largest)

    def peek(self):
        return self.heap[1]

    def pop(self):
        if self._size <= 0:
            raise HeapEmpty
        m = self.heap[1]
        self.heap[1] = self.heap[self._size]
        if self.kv_mode:
            del self.indices[m[1]]
        self._size -= 1
        self.heapify(1)
        return m

    def insert(self, n):
        h = self.heap
        if self.kv_mode and n[1] in self.indices:
            x = self.indices[n[1]]
            self.heap[x] = n
        else:
            self._size += 1
            if self._size >= len(h):
                h.append(n)
            else:
                h[self._size] = n
            if self.kv_mode:
                self.indices[n[1]] = self._size
            x = self._size
        while (x != 1 and self.compare(h[x//2], h[x]) < 0):
            h[x], h[x//2] = h[x//2], h[x]
            if self.kv_mode:
                self.indices[h[x][1]] = x
                self.indices[h[x//2][1]] = x // 2
            x //= 2

    def size(self):
        return self._size

class PriorityQueue:
    def __init__(self):
        self.heap = Heap(kv_mode=True)

    def pop(self):
        return self.heap.pop()

    def peek(self):
        return self.heap.peek()

    def size(self):
        return self.heap.size()

    def insert(self, k, v):
        self.heap.insert((v, k))

class Edge:
    def __init__(self, a, b, weight):
        self.a = a
        self.b = b
        self.weight = weight

    def other(self, x):
        if x == self.a:
            return self.b
        elif x == self.b:
            return self.a
        raise ValueError('Edge is not connected to vertex')

class Graph:
    def __init__(self, size, edges=[]):
        self._size = size
        self.adj = [[] for i in range(size)]
        for u, v, weight in edges:
            self.add_edge(u, v, weight)

    def size(self):
        return self._size

    def add_edge(self, u, v, weight):
        e = Edge(u, v, weight)
        self.adj[u].append(e)
        self.adj[v].append(e)

class UnionFind:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        u_root = self.find(u)
        v_root = self.find(v)

        if u_root == v_root:
            return

        if self.rank[u_root] < self.rank[v_root]:
            self.parent[u_root] = v_root
        elif self.rank[u_root] > self.rank[v_root]:
            self.parent[v_root] = u_root
        else:
            self.parent[u_root] = v_root
            self.rank[v_root] += 1

