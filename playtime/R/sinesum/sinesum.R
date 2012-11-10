

sinesum <- function(A, phi)
{
  stopifnot(length(A) == length(phi))

  begin=0;
  end=1.0;
  t=seq(begin, end, by=.001)
  y=seq(0,0,length.out=length(t))

  n=length(A)
  for(tindex in 1:length(t))
  {
    tscale=t[tindex]*2*pi
    for(k in 1:n)
    {
      y[tindex] = y[tindex] + A[k]*sin(tscale*k+phi[k])
    }
  }
  return(y)
}
