def add(P,Q):
	if Q==0:
		return P
	x1,y1=P
	x2,y2=Q
	x3=(d1*(x1+x2)+d2*(x1+y1)*(x2+y2)+(x1+x1^2)*(x2*(y1+y2+1)+y1*y2))/(d1+(x1+x1^2)*(x2+y2))
	y3=(d1*(y1+y2)+d2*(x1+y1)*(x2+y2)+(y1+y1^2)*(y2*(x1+x2+1)+x1*x2))/(d1+(y1+y1^2)*(x2+y2))
	return x3,y3

def mul(k,P):
	Q=0
	while k>0:
		if is_even(k):
			k/=2
			P=add(P,P)
		else:
			k-=1
			Q=add(P,Q)
	return Q
def ed2el(P):
	x,y=P
	return (d1*(d1^2+d1+d2)*(x+y)/(x*y+d1*(x+y)),d1*(d1^2+d1+d2)*(x/(x*y+d1*(x+y))+d1+1))

def el2ed(P):
	u,v=P
	return (d1*(u+d1^2+d1+d2)/(u+v+(d1^2+d1)*(d1^2+d1+d2)),d1*(u+d1^2+d1+d2)/(v+(d1^2+d1)*(d1^2+d1+d2)))

F=GF(2**100)
R.<x,y>=F[]
d1=F.fetch_int(1)
d2=F.fetch_int(1)
a2=d1^2+d2
a6=d1^4*(d1^4+d1^2+d2^2)
E=EllipticCurve(y^2+x*y-x^3-a2*x^2-a6)
factor(E.order())
x,y=(698546134536218110797266045394L, 1234575357354908313123830206394L)
G=(F.fetch_int(x),F.fetch_int(y))
x,y=(403494114976379491717836688842L, 915160228101530700618267188624L)
P=(F.fetch_int(x),F.fetch_int(y))
P=E(ed2el(P))
G=E(ed2el(G))
print hex(discrete_log(P,G,G.order(),operation="+")).decode('hex')

