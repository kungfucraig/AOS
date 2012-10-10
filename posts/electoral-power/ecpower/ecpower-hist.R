# http://had.co.nz/ggplot/
library(ggplot2)
raw = read.table("ecpower-rwins.csv", sep = ",")
x <- data.frame(power=raw$V3, rwinstweaked=raw$V4, rwins=raw$V5)
x$lab <- raw$V2

raw2 = read.table("ecpower-by-power.csv", sep = ",")
y <- data.frame(power=raw2$V1, lab=raw2$V2)
#y$lab <- raw2$V2


rwinsCounts <- as.data.frame(table(x$rwins))

#hist(x$power,
#     col="lightblue",
#     xlab="Voting Power Per Capita",
#     ylab="Number of States",
#     main="Number of States Versus Voting Power Per Capita",
#     ylim=c(0,20))
#dev.copy(jpeg,'ecpower-histogram.jpeg')
#dev.off()

jpeg(filename='rwins-histogram.jpeg', width=600, height=600, units="px")
ggplot(data=rwinsCounts) + geom_bar(aes(Var1, Freq), binwidth=1, color="black", fill="blue") + scale_x_discrete("Number of Republican State Victories Since 1980") + scale_y_discrete("Count of States") + opts(title="Count of States with Given Number of\nRepublican Presidential Election Victories Since 1980")
dev.off()

jpeg(filename='ecpower-histogram.jpeg', width=600, height=600, units="px")
ggplot(data=x) + geom_histogram(aes(power), binwidth=0.25, color="black", fill="blue") + scale_x_continuous("Voting Power Per Capita") + scale_y_discrete("Count of States") + opts(title="Histogram of States With\nGiven Voting Power Per Capita")
dev.off()

#ggplot(data=x, aes(b, qplot(ecpow$V3)
#hist(x$rwins,
#     col="lightblue",
#     xlab="Number of Republican Wins Since 1980",
#     ylab="Number of States",
     #main="Number of States Versus Number Times Republicans Have Won Since 1980",
     #ylim=c(0,13),
     #xlim=c(0,9))
#dev.copy(jpeg,'ecpower-histogram.jpeg')
#dev.off()
qplot(x$power)

jpeg(filename='electoral-power-rank.jpeg', width=600, height=800, units="px")
ggplot(data=y, aes(power, 1:50, label=lab)) + geom_text(vjust=0, size=3) + scale_x_continuous("Voting Power Per Capita") + scale_y_discrete("Rank") + opts(title="Electoral Power Ranked by State")
dev.off()




# Now the scatter.
jpeg(filename='ecpower-rwins-plot.jpeg', width=600, height=800, units="px")
ggplot(data=x, aes(rwinstweaked, power, label=lab)) + geom_text(vjust=0, size=3) + scale_x_continuous("Number of Republican Wins Since 1980") + scale_y_continuous("Voting Power Per Capita") + opts(title="Plot of States With Respect to\n Voting Power Per Capita and Republican Wins Since 1980")
dev.off()

