
object IEV extends App {
  
  val example_1 = Vector(1, 0, 0, 1, 0, 1)
  // out: 3.5
  val example_2 = Vector(19905, 19212, 19141, 19636, 16581, 18144)
  // out: 162551

  val input = example_2

  val out = iev(input)
  println(out)
  
  def iev(input: Vector[Int]) = {
    val pobabilities = Vector(1.0, 1.0, 1.0, 0.75, 0.5, 0.0)
    val perCoupleExpectation = pobabilities.map(_*2)
    val inputExpectation = input.zip(perCoupleExpectation).map((x) => x._1 * x._2)
    inputExpectation.sum.toInt
  }


  
}