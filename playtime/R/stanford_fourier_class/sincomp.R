## An R-Program to explore the sum of two sin waves.
## Problem number four in the first problem set.
## http://see.stanford.edu/materials/lsoftaee261/PS-1-2007.pdf

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

# problem 4d
p4d <- function(t, v1, v2)
{
  y1 = 3*cos(2*pi*v1*t-1.3)
  y2 = 5*cos(2*pi*v2*t+0.5)
  return(y1+y2)
}

