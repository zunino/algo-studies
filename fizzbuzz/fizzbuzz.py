import sys

def fizzbuzz(n):
    for i in range(1, n+1):
        neither = True
        if i % 3 == 0:
            print("Fizz", end="")
            neither = False
        if i % 5 == 0:
            print("Buzz", end="")
            neither = False
        if neither:
            print(i, end="")
        print()

if len(sys.argv) != 2:
    print("Missing required FizzBuzz number", file=sys.stderr)
    sys.exit(1)

try:
    n = int(sys.argv[1])
except ValueError:
    print("Input should be a valid integer", file=sys.stderr)
    sys.exit(2)

fizzbuzz(n)

