

object FIBD extends App {
  // classic 0 1 1 2 3 5 8

  // (5, 3) = 19
  // 1 1 4 7 19
  //println(fibd(3, 1, 0))
  //println(fibd(6, 1, 3))
  
  // #R 0 0 1 1 2 
  // #L  1 1 2 2 4
  // #D       1 
  
  // RND 1 (1)
  // # in generation 0 - 1
  // # in generation 1 - 0
  // # in generation 2 - 0
 
  
  // RND 2 (1)
  // # in generation 0 - 0
  // # in generation 1 - 1
  // # in generation 2 - 0
  
  // RND 3 (2)
  // # in generation 0 - 1
  // # in generation 1 - 0
  // # in generation 2 - 1
      
  // RND 4 (2)
  // # in generation 0 - 1
  // # in generation 1 - 1
  // # in generation 2 - 0
  
  // RND 5 (4)
  // # in generation 0 - 1
  // # in generation 1 - 1
  // # in generation 2 - 1
 
  // RND 6 (4)
  // # in generation 0 - 2
  // # in generation 1 - 1
  // # in generation 2 - 1
  
  println(fibd(82, 16))
  // out = 60467010349760561

  println(fibd(6, 3))
  // out = 4
  
  def fibd(iterations: Long, gen: Int) = {
    import annotation.tailrec
    @tailrec def helper(iterationsLeft: Long, l: List[Long]) : Long = {
      if (iterationsLeft == 0) {
        l.sum
      } else {
        // The number in the 0th generation is the sum of the numbers in n, n-(n-2)
        // The head does not reproduce
        val babies = l.tail.sum
        helper(iterationsLeft-1, babies :: l.dropRight(1))
      }
    }
    val l = 1L :: List.fill(gen-1)(0L)
    helper(iterations-1, l)
  }
}