object GC extends App {
  
  val example = """>Rosalind_6404
CCTGCGGAAGATCGGCACTAGAATAGCCAGAACCGTTTCTCTGAGGCTTCCGGCCTTCCC
TCCCACTAATAATTCTGAGG
>Rosalind_5959
CCATCGGTAGCGCATCCTTAGTCCAATTAAGTCCCTATCCAGGCGCTCCGCCGAAGGTCT
ATATCCATTTGTCAGCAGACACGC
>Rosalind_0808
CCACCCTCGTGGTATGGCTAGGCATTCAGGAACCGGAGAACGCTTCAGACCAGCCCGGAC
TGGGAACCTGCGGGCAGTAGGTGGAAT
"""

  val input = example
  val maxGCContent = computeMaxGCContent(input)
  println(maxGCContent._1)
  println(maxGCContent._2 * 100)
  

  def computeGCContent(input: String) = {
    val groupedData = input.groupBy((x) => x)
    val countSeq = for (x <- "ACGT") yield (x, groupedData(x).length.toDouble)
    val counts = Map(countSeq:_*)
    (counts('G') + counts('C'))/ counts.values.sum
  }

  def computeMaxGCContent(input: String) = {
    val re = """>(Rosalind_\d+)\s*([TACG\s]+)""".r
    val gcContent = for(m <- re.findAllIn(input)) 
      yield m match {
            case re(name, seq) => (name, computeGCContent(seq))
      } 
    gcContent.maxBy((x) => x._2)
  }
}

