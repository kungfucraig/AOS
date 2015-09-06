

object SUBS extends App {
  val example_1_s = "GATATATGCATATACTT"
  val example_1_t = "ATAT"
  // output: 2 4 10
  
  val example_2_s = "ATCCGCTCGGATAAAAGGGCATAAAAGATAAAAGCTATAAAAGATAAAAGCCATATAAAAGAATAAAAGGGATAAAAGTCATAAAAGATAAAAGATCGGATAAAAGCATAAAAGAATAAAAGGATAAAAGATAAAAGGGATAAAAGGAGGTGTGGGCTATAAAAGATAAAAGATAAAAGCTATAAAAGTGATATAAAAGAGATAAAAGTTAATAAAAGTATGATAAAAGATAAAAGCTGCCATAAAAGAGAATAAAAGATGGATATAAAAGAGGATAAAAGCGGCTATAAAAGGAATAAAAGAGATAAAAGACCATAAAAGTTACGGATAAAAGTTTCGATAAAAGCGGATAAAAGGATAAAAGATAAAAGATAAAAGTACTTTTATAAAAGATAAAAGCAATAAAAGCATAAAAGGGAATAAAAGTGATAAAAGTATAAAAGATAAAAGCATAAAAGACATAAAAGCGATAAAAGGTTAGAATAAAAGAACATAAAAGAATAAAAGCATAAAAGATAAAAGTGATAAAAGAGGATAAAAGATAAAAGCTTGTATTATAAAAGAACTGCATAAAAGGGATAAAAGTATAAAAGTAATAAAAGTATAAAAGATAAAAGATAAAAGGGGATAAAAGAATAAAAGAGGGGGTGTTTAATAAAAGATATAAAAGGTCTATAAAAGCGATAAAAGATAAAAGTGGACCACTCTGCCAATAAAAGGTATAAAAGCACATAAAAGATAAAAGCATAAAAGATAAAAGAAAATAAAAGATAAAAGACTGCCAATAAAAGTGTATAAAAGCGATAAAAGGATAAAAGGATAAAAGATAAAAGATAAAAGATAAAAGTCGCGTCGATAAAAGAATAAAAGGAT"
  val example_2_t = "ATAAAAGAT"
  // output: 21 37 81 88 124 159 166 223 252 358 365 386 437 509 535 604 611 655 684 732 747 764 820 827 834
  
  val (input_s, input_t) = (example_2_s, example_2_t)
  val out = stringSearch(input_s, input_t).map(_+1).mkString(" ")
  println(out)

  def stringSearch(s: String, t: String) = {
    val rng = 0 until s.length
    rng.filter((i)=>
      s.view(i, i+t.length) == t.view(0, t.length))
  }
}