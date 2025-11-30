
def unique_digits(n):
    count = 0
    for i in range(0, 10):
        if has_digit(n, i):
            count = count + 1
    print(count)

def has_digit(n, k):
    assert k >= 0 and k < 10
    while n != 0:
        tmp = n % 10
        n = n // 10
        if(tmp == k):
            return True
    return False

unique_digits(121312421313123345)
