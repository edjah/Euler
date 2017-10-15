from time import perf_counter
start = perf_counter()

triangles = []
with open('p102_triangles.txt') as f:
    for line in f:
        tri = map(int, line.split(','))
        triangles.append(tri)

def area(x1, y1, x2, y2, x3, y3):
   return abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2

def tri_contains_origin(x1, y1, x2, y2, x3, y3):
   A  = area(x1, y1, x2, y2, x3, y3)
   A1 = area(0, 0, x2, y2, x3, y3)
   A2 = area(x1, y1, 0, 0, x3, y3)
   A3 = area(x1, y1, x2, y2, 0, 0)
   return A == A1 + A2 + A3

sol = 0
for tri in triangles:
    sol += tri_contains_origin(*tri)

print('Solution:', sol)

end = perf_counter()
print(end - start, 'seconds to run')
