
object FIB extends App {
  // (5, 3) = 19
  // 1 1 4 7 19
  println(fib3(5, 3))
  
  // Further improved solution
  def fib3(n: Int, k: Int) = {
    lazy val fibs: Stream[Int] = {
      def loop(h: Int, n: Int): Stream[Int] = h #:: loop(n, h*k+n)
      loop(1, 1)
    }
    fibs.take(n).last
}
  
  // Improved solution
  def fib2(n: Integer, k: Integer) = {
    val bigK = BigInt(k)
    lazy val fibs: Stream[BigInt] = 
      BigInt(1) #::
      BigInt(1) #::
      fibs.zip(fibs.tail).map { m => m._1*bigK + m._2 }
    fibs take n foreach println
  }
    
  
  // Original Solution
  def fib(n: Long, k: Long) = {
    var out_less_one = 1L
    var out = 1L
    for (i <- 0L until n-2) {
      var tmp = out_less_one
      out_less_one = out
      out = tmp*k + out
    }
    out
   }
}