object IPRB extends App {
  // (2, 2, 2) => 0.78333
  // (20, 16, 18) => 0.7714884696016772
  val k :Integer = 20  // # homozygous dominant
  val m :Integer = 16  // # heterozygous
  val n :Integer = 18  // # homozygous recessive
  
  val calculator = new Calculator(k.toDouble, m.toDouble, n.toDouble)
  println(calculator.probabilityDominantAllele())
  
  class Calculator(val k: Double, val m: Double, n: Double ) {

    def probabilityDominantAllele() = {
      1.0 - (probabilityOfSelection(k, m, n)._3 * probabilityOfSelection(k, m, n-1)._3
             + probabilityOfSelection(k, m, n)._3 * probabilityOfSelection(k, m, n-1)._2 * .5
             + probabilityOfSelection(k, m, n)._2 * probabilityOfSelection(k, m-1, n)._3 * .5
             + probabilityOfSelection(k, m, n)._2 * probabilityOfSelection(k, m-1, n)._2 * .25)
    }
  
    private def probabilityOfSelection(k: Double, m: Double, n: Double) = {
      val total = k+m+n
      (k/total, m/total, n/total)
    }
  }
}