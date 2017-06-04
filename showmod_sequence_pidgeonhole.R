showSequence <- function(n, m){
  x<-1:(m+1)
  y<-vector()
  for (i in x){
    ans <- (n*i) %% m  #%% is "mod" in R
    cat(sprintf("%d mod %d = %d\n",n*i ,m ,ans))
    y <- c(y, ans)
  }
  plot(x,y,type="n")
  segments(x[-length(x)],y[-length(x)],x[-1],y[-length(x)])
  points(x[-length(x)],y[-length(x)],pch=16)
  points(x[-1],y[-length(x)],pch=1) 
  #sort the coefficients so that they follow the order "n*i mod m = 1, 2, 3, ..." (we're removing the last element here because floor function)
  sorted_guy <- sort.int(y[1:length(y)-1], index.return=TRUE) #returns arguments
  sorted_indices <- sorted_guy$ix
  cat(sprintf("coefficients ordered by rising value %s",paste(sorted_indices, collapse=", ")))
}

showSequence(4,9)