from time import perf_counter
import random
import json
start = perf_counter()

class Monopoly(object):
    def __init__(self, dice_size=6):
        self.history = {i: 0 for i in range(40)}
        self.location = 0
        self.dice_size = dice_size

        self.GO = 0
        self.G2J = 30
        self.JAIL = 10
        self.RAILWAY = [5, 15, 25, 35]
        self.UTILITY = [12, 28]
        self.CHANCE = [7, 22, 36]
        self.COMMUNITY_CHEST = [2, 17, 33]

        self.community_chest_actions = [lambda x: x] * 14 + [
            lambda x: 0,
            lambda x: 10
        ]
        self.chance_actions = [lambda x: x] * 6 + [
            lambda x: 0,
            lambda x: 10,
            lambda x: 11,
            lambda x: 24,
            lambda x: 39,
            lambda x: 5,
            lambda x: next((i for i in self.RAILWAY if i > x), self.RAILWAY[0]),
            lambda x: next((i for i in self.RAILWAY if i > x), self.RAILWAY[0]),
            lambda x: next((i for i in self.UTILITY if i > x), self.UTILITY[0]),
            lambda x: (x - 3) % 40,
        ]

        random.shuffle(self.community_chest_actions)
        random.shuffle(self.chance_actions)

    def next_turn(self, doubles=0):
        a = random.randint(1, self.dice_size)
        b = random.randint(1, self.dice_size)
        if a == b:
            doubles += 1
            if doubles == 3:
                self.location = self.JAIL
            else:
                self.location = (self.location + a + b) % 40
                if self.location == self.G2J:
                    self.location = self.JAIL
                else:
                    self.next_turn(doubles)
                    return
        else:
            self.location = (self.location + a + b) % 40
            if self.location in self.CHANCE:
                self.location = self.chance_actions[-1](self.location)
                self.chance_actions.insert(0, self.chance_actions.pop(-1))
            if self.location in self.COMMUNITY_CHEST:
                self.location = self.community_chest_actions[-1](self.location)
                self.community_chest_actions.insert(0, self.community_chest_actions.pop(-1))
            if self.location == self.G2J:
                self.location = self.JAIL

        self.history[self.location] += 1


num_trials = 10000000
game = Monopoly(dice_size=4)
for _ in range(num_trials):
    game.next_turn()

freqs = {k: '{}%'.format(100 * v/num_trials) for k, v in game.history.items()}
print('Frequencies:', json.dumps(freqs, indent=4, sort_keys=True))

most_common = sorted(game.history.items(), key=lambda x: -x[1])
modal_string = ''.join(str(s[0]).zfill(2) for s in most_common[:3])
print('Solution:', modal_string)

end = perf_counter()
print('Finished in %f seconds' % (end - start))

# 101524
