## An R-Program to explore the sum of two sin waves.
## Problem number four in the first problem set.
## http://see.stanford.edu/materials/lsoftaee261/PS-1-2007.pdf

gcd <- function(a, b)
{
  a=as.integer(a)
  b=as.integer(b)
  stopifnot(!(a==0 && b==0))
  if ( a == 0 )
    return(b)

  if ( b == 0 )
    return(a)

  return(abs(gcd(b, a-b*floor(a/b))))
}


lcm <- function(a, b)
{
  a=as.integer(a)
  b=as.integer(b)
  return(abs(a*b)/gcd(a,b))
}


sincomp <- function(t, p1, p2)
{
  #x11()
  #par(mfrow=c(3,1))
  ticks= c(t[1], t[length(t)], t[length(t)]-t[1])

  y1=sin(2*pi*p1*t)
  y2=sin(2*pi*p2*t)
  plot(t,y1, xaxp=ticks)
  plot(t,y2, xaxp=ticks)
  plot(t,y1+y2, xaxp=ticks) 
}

sincomp2 <- function(t, m, r, n, s)
{
  sincomp(t, m/r, n/s)
  print(lcm(r,s)/gcd(m,r))
}

# problem 4d
p4d <- function(t, v1, v2)
{
  y1 = 3*cos(2*pi*v1*t-1.3)
  y2 = 5*cos(2*pi*v2*t+0.5)
  return(y1+y2)
}

