
def fizzbuzz(n):
    for i in range(1, n+1):
        if(i % 15 == 0):
            print("fizzbuzz")
        elif(i % 3):
            print("fizz")
        elif(i % 5):
            print("buzz")
        else:
            print(i)

fizzbuzz(100)
