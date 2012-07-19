
# An R-Program to explore triangle function composition from
# problem number two in the following problem set.
# http://see.stanford.edu/materials/lsoftaee261/PS-1-2007.pdf

tri <- function(a, b, c, t)
{
  stopifnot(a>0)
  stopifnot(b>0)
  y <- mapply(function(x) { 
    if (abs(x)<a) return(b*(1-1/a*abs(x))) else return(0) }, t-c)
  return(y)
}

tri2 <- function(a1, b1, c1, a2, b2, c2, t)
{
  y1 <- tri(a1,b1,c1,t)
  y2 <- tri(a2,b2,c2,t)
  return(y1+y2)
}

tri3 <- function(x1, x2, x3, y2, t)
{
  stopifnot(x1<x2)
  stopifnot(x2<x3)
  stopifnot(y2>0)

  a1=x2-x1
  b1=y2
  c1=x2

  a2=(x3-x2)/2
  b2=y2/2
  c2=x2+a2

  y = tri2(a1, b1, c1, a2, b2, c2, t)
  return(y)
}

# From fourier homework #1, problem 2
t = seq(-10,10,by=.01)

#See: http://sphaerula.com/legacy/R/multiplePlotFigure.html
par(mfrow=c(2,2))
plot(t,tri2(2,1,0, 2,1,2,t), main="Problem 2a")
plot(t,tri2(2,2,0, 2,2,3,t), main="Problem 2b")
plot(t,tri2(2,6,3, 2,3,5,t), main="Problem 2c")

# Problem 2c:
#screen(3) 
#par(mfrow=c(3,1))
plot(t,tri3(1,3,7,6,t), main="Problem 2d")
