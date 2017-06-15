#defining our own binomial_number_system class, as per problem 38 of Concrete Mathematics Chapter 5
# i.e. any number can be uniquely written as some
# c choose 3 + b choose 2 + a choose 1 where c > b > a

binomial_number <- setClass(
  #name of class
  "Binomial Number",
  
  #defines the values the class holds
  slots = c(a="numeric",
            b="numeric",
            c="numeric"),
  
  #Set default value for the slots
  prototype=list(a = 0.0,
                 b = 1.0,
                 c = 2.0),
  
  #we can assign a validating function to catch invalid types being constructed
  validity = function(object)
  {
    #check if our invariant is violated
    if ((object@a > object@b) || (object@b > object@c) || ((object@a > object@c))){
      return ("Error, a<b<c principle is violated")
    }
    #we are here only if the condition was false
    return(TRUE)
  }
  )

#we now have a default way to create numbers in binomial representation
a <- binomial_number()
a
b <- binomial_number(a=1,b=2,c=3)
b
#if we try to run something like b <- binomial_number(a=1,b=3,c=2), our validity function will complain

#now let's create a function called "binomify" to convert real numbers to this special binomial representation
binomify <- function(n){
  #if n is real, we take the floor
  n <- floor(n)
  #from the falling factorial definition of n choose k(or even the normal factorial one), we know that n choose k
  #can be seen as a k-degree polynomial, so we can easily solve it with R(we want the largest positive solutions!)
  
  #solve for c
  answers <- polyroot(c(-6*n, 2, -3, 1))
  c <- floor(max(Re(answers)))
  #remove that chunk from n
  n <- n - choose(c,3)
  
  #solve for b
  b <- floor(max(Re(polyroot(c(-2*n, -1, 1)))))
  n <- n - choose(b,2)  #remove that chunk from n
  
  #solving the leftover choose 1 straightforward
  a <- n
  
  #return a binomial number
  return ( binomial_number(a=a,b=b,c=c) )
}

#Let's also convert to a normal number from a,b,c
toNum <- function(object){
  return (choose(object@a,1)+choose(object@b,2)+choose(object@c,3))
}

c <- binomify(24)
c
