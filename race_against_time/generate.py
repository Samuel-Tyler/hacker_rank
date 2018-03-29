from __future__ import print_function
from random import randint

N = randint(2, 10**3) # this is N
h = randint(0, 10**9) # this is h

print(N, h, sep='\n')

# this prints N-1 heights
for i in range(N-1):
    print(randint(0, 10**9), end=' ')
    
print('\n\n') # new lines

# this prints N-1 prices
for i in range(N-1):
    print(randint(-10**9, 0), end=' ')
