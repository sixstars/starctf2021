from Crypto.Util.number import bytes_to_long
from flag import flag
assert flag[:5]=='*CTF{' and flag[-1]=='}'
flag=flag[5:-1]
def add(P,Q):
	if Q==0:
		return P
	x1,y1=P
	x2,y2=Q
	return (d1*(x1+x2)+d2*(x1+y1)*(x2+y2)+(x1+x1^2)*(x2*(y1+y2+1)+y1*y2))/(d1+(x1+x1^2)*(x2+y2)),(d1*(y1+y2)+d2*(x1+y1)*(x2+y2)+(y1+y1^2)*(y2*(x1+x2+1)+x1*x2))/(d1+(y1+y1^2)*(x2+y2))

def mul(k,P):
	Q=(0,0)
	while k>0:
		if is_even(k):
			k/=2
			P=add(P,P)
		else:
			k-=1
			Q=add(P,Q)
	return Q

F=GF(2**100)
R.<x,y>=F[]
d1=F.fetch_int(1)
d2=F.fetch_int(1)
x,y=(698546134536218110797266045394L, 1234575357354908313123830206394L)
G=(F.fetch_int(x),F.fetch_int(y))
P=mul(bytes_to_long(flag),G)
print (G[0].integer_representation(),G[1].integer_representation())
print (P[0].integer_representation(),P[1].integer_representation())
#(698546134536218110797266045394L, 1234575357354908313123830206394L)
#(403494114976379491717836688842L, 915160228101530700618267188624L)

