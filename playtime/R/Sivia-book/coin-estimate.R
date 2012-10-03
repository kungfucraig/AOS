# From an example in "Data Analysis: A Bayesian Tutorial" by Devinderjit Sivia 
# Also see the following:
#   http://en.wikipedia.org/wiki/Checking_whether_a_coin_is_fair
#   http://en.wikipedia.org/wiki/Beta_function

# This is the parameter we are trying to estimate.
p=0.85
ntrials=1024
data=rbinom(ntrials, 1, p)

estimate <- function(x,data) 
{
  nheads=sum(data==1)
  ntails=sum(data==0)
  yhat=(x^nheads)*((1-x)^ntails)/beta(nheads+1, ntails+1)
  return(yhat)
}

slices=c(0, 1, 2, 4, 32, 64, 128, 256, 512, 1024)
x=seq(0,1,by=0.001)
par(mfrow=c(5,2))

w <- mapply(
            function(s) { 
              yhat=estimate(x, data[1:s])
              plot(x,yhat,main=sprintf("No. Points = %d",s))
              }, 
            slices)



