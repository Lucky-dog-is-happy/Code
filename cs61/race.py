# Discussion 1
def race(x,y):
    assert y > x and y <= 2*x
    tortoise, hare, minutes = 0, 0, 0
    while minutes == 0 or tortoise - hare:
        tortoise += x
        if minutes % 10 < 5:
            hare += y
        minutes += 1
    return minutes

# print(race(4,6))

# (3,4)永远运行

