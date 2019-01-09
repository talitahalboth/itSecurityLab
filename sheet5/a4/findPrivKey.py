import hashlib
from ecdsa import SigningKey, VerifyingKey, NIST256p


def inverse_mod( a, m ):
    """Inverse of a mod m."""
    if a < 0 or m <= a: a = a % m
    # From Ferguson and Schneier, roughly:
    c, d = a, m
    uc, vc, ud, vd = 1, 0, 0, 1
    while c != 0:
        q, c, d = divmod( d, c ) + ( c, )
        uc, vc, ud, vd = ud - q*uc, vd - q*vc, uc, vc

    # At this point, d is the GCD, and ud*a+vd*m = d.
    # If d == 1, this means that ud is a inverse.
    assert d == 1
    if ud > 0: return ud
    else: return ud + m

#i pre-calculated all values so i woudn't need to include the original files
z=0xdfcaf5e269a530c571d856783ed1b15647a54625
z2=0x4b6d51036ccc95cb6f97f08deb36fdf0f564b412
s  = 0x615B3B0D09A5B0D2F79571392A7278BB7BB58542C5BA0D6B71A934BC17A65C4E
s2 = 0x63089FBACCDC2C5C8AA9583A7627B79F25C0D1188A94B569B5D90F317C4FAF65
r = 0xBFE855905780E8470494024E6BF8E5FE7FE32BF812DCBBD16993B1EA465A2874
#the Recommended Parameters for secp256r1
#(in ANSI X9.62 the curve secp256r1 is designated prime256v1.)
#our curve is prime256v1
p  = 0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551



#(a * b) mod c = (a mod c) * (b mod c) mod c
k = (((z-z2)%p) * inverse_mod((s-s2),p)%p)
#s - s2 = k^-1 * (z - z2) mod n
if not (((s-s2)%p) - (inverse_mod(k,p)*((z-z2)%p))%p):

    d = (((s*k - z)%p) * inverse_mod(r,p)%p)
    #s = k^-1 * (z + rd)
    #s - k^-1 mod p * (z + r*d)
    if not s - (inverse_mod(k,p)*((z+(r*d)%p)%p)%p):
        d = hex(d)
        d = list(d)[2:len(d)-1]
        l = ''.join(d)
        sk = SigningKey.from_string(l.decode('hex'), curve=NIST256p)
        print sk.to_pem()

