from lib.utility import start_time, end_time
start_time()


def M(N):
    optimals = {1: 0}
    computed_sets, next_computed_sets = [(1,)], []
    num_steps = 0

    while len(optimals) < 200:
        num_steps += 1
        tmp_opts = {}
        for values in computed_sets:
            for i in range(len(values)):
                for j in range(i, len(values)):
                    x = values[i] + values[j]
                    if x > N:
                        break
                    if x not in optimals:
                        tmp_opts[x] = num_steps
                        next_computed_sets.append(values + (x,))

        optimals.update(tmp_opts)
        computed_sets, next_computed_sets = next_computed_sets, []

    return sum(optimals[i] for i in range(1, N + 1))


sol = M(200)
print('Solution:', sol)

end_time()
