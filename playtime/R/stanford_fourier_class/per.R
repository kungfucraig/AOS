## This is for problem #3 in the first problem set
## http://see.stanford.edu/materials/lsoftaee261/PS-1-2007.pdf

source("tri.R")

# To index a matrix mat[ROW,COL] (1-based)
# ?Extract
# Get a row: mat[ROW,]
# Get a column: mat[,COL]
# Get part of a column: mat[ROW_BEGIN:ROW_END,COL]
# Loop from 1 to 401 inclusive : for ( i in 1:401 ){...}


per <- function(t, T)
{
  BEGIN=-10
  END=10
  n=seq(BEGIN, END)*T

  stopifnot(T>0)

  f <- function(t)
  {
    return(tri(0.5, 1, 0, t))
  }

  w=mapply(function(x){return(x-n)}, t)

  y=c()
  for (i in 1: ncol(w) ){
    x=w[,i]
    z=f(x)
    y=append(y, sum(f(x)))
  }
  return(y)
}

permain <- function()
{
  t=seq(-2,2,by=0.01)
  y1=per(t,0.5)
  y2=per(t,0.75)
  y3=per(t,1)
  y4=per(t,2)
  return(list(t=t,y1=y1,y2=y2,y3=y3,y4=y4))
}

