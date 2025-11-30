
def is_prime(n):
    isPrime = 1 
    i=2
    while i < n:
        if(n % i == 0):
            isPrime = 0
            break
        i = i + 1
    if(isPrime):
        print("True")
    else:
        print("False")

is_prime(97)
