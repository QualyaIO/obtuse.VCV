import numpy as np
import math

def beta(x, b):
    return 1 - math.pow((1 - x), b)

b = 1
print(beta(0.5,b))

chords = [0] * 6

print(chords)

i = 0
maxi = (len(chords) - 1)/ 2
print("maxi", maxi)


x = 1/len(chords)
print("x0", x)
chords[i] = beta(x, b);
chord_p = chords[i]
print("chord_p", chord_p)

# will scale to account for the fact that we aggregate two halves
scale_p = 0
if len(chords) > 1:
    scale_p = (1 - chord_p) * ((maxi) / (len(chords)-1 ))
print("scale", scale_p)

i = i + 1


while i <= maxi:
    x =  (i )/ (maxi)
    print("i", i)
    print("x", x)
    new_p = beta(x, b)
    print("new", new_p)
    print("new scale", new_p * scale_p)
    chords[i % len(chords)] =  chord_p + ( new_p) * scale_p 
    i = i + 1

# save last value we got
last_i = i - 1

print(chords)
print("---")

while i < len(chords) - 1:
    # index in this half
     x = (i - maxi) / (maxi)

    print("i", i)
    print("x", x)

    new_p =   beta(1-x, b)
    print("new", new_p)
    chords[i % len(chords)] =  1 - new_p * scale_p

    i = i + 1

# mandatory 1 for last
chords[-1] = 1

print(chords)

print(np.diff(chords))

