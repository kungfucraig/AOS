object HAMM extends App {
  
  val example_1 = "GAGCCTACTAACGGGAT"
  val example_2 = "CATCGTAATGACGGCCT"
  
  val s1 = example_1
  val s2 = example_2
   
  println(hammingDistance(s1, s2))
  
  def hammingDistance(s1: String, s2: String) = {
    (s1, s2).zipped.foldLeft(0)(
        (cur, x) => if (x._1 != x._2) cur + 1 else cur)
  }
}