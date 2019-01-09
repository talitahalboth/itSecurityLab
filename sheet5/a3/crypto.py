def modulo_multiplicative_inverse(A, M):
    """
    Assumes that A and M are co-prime
    Returns multiplicative modulo inverse of A under M
    """
    # Find gcd using Extended Euclid's Algorithm
    gcd, x, y = extended_euclid_gcd(A, M)

    # In case x is negative, we handle it by adding extra M
    # Because we know that multiplicative inverse of A in range M lies
    # in the range [0, M-1]
    if x < 0:
        x += M
    
    return x

def extended_euclid_gcd(a, b):
    """
    Returns a list `result` of size 3 where:
    Referring to the equation ax + by = gcd(a, b)
        result[0] is gcd(a, b)
        result[1] is x
        result[2] is y 
    """
    s = 0; old_s = 1
    t = 1; old_t = 0
    r = b; old_r = a

    while r != 0:
        quotient = old_r//r
        # This is a pythonic way to swap numbers
        # See the same part in C++ implementation below to know more
        old_r, r = r, old_r - quotient*r
        old_s, s = s, old_s - quotient*s
        old_t, t = t, old_t - quotient*t
    return [old_r, old_s, old_t]

def find_invpow(x,n):
    """Finds the integer component of the n'th root of x,
    an integer such that y ** n <= x < (y + 1) ** n.
    """
    high = 1
    while high ** n < x:
        high *= 2
    low = high/2
    while low < high:
        mid = (low + high) // 2
        if low < mid and mid**n < x:
            low = mid
        elif high > mid and mid**n > x:
            high = mid
        else:
            return mid
    return mid + 1
#the criptographed messages
file = open("msg1.bin", "rb")
cb = file.read() 

#open the each encrypted message and turns it into a numeric value (integer)
cb = int(cb.encode('hex'), 16)
file.close()
file = open("msg2.bin", "rb")
cc = file.read() 
cc = int(cc.encode('hex'), 16)
file.close()
file = open("msg3.bin", "rb")
cd = file.read() 
cd = int(cd.encode('hex'), 16)
file.close()

#turn each module into an integer value
file = open("parampk1", "r")
nb = file.read() 
nb = int(nb,0)
file.close()
file = open("parampk2", "r")
nc = file.read() 
nc = int(nc,0)
file.close()
file = open("parampk3", "r")
nd = file.read() 
nd = int(nd,0)
file.close()

tb = cb * (nc*nd)*(modulo_multiplicative_inverse(nc*nd, nb))
tc = cc * (nb*nd)*(modulo_multiplicative_inverse(nb*nd, nc))
td = cd * (nb*nc)*(modulo_multiplicative_inverse(nb*nc, nd))

c = (tb+tc+td) % (nb*nc*nd)
croot = find_invpow(c,3)
croot = hex(croot)
croot = list(croot)[2:len(croot)-1]
l = ''.join(croot)
print l.decode('hex')