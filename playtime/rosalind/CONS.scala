

object CONS extends App {
  val input = """>Rosalind_1
ATCCAGCT
>Rosalind_2
GGGCAACT
>Rosalind_3
ATGGATCT
>Rosalind_4
AAGCAACC
>Rosalind_5
TTGGAACT
>Rosalind_6
ATGCCATT
>Rosalind_7
ATGGCACT 
"""
  // Outputs:
  // ATGCAACT
  // A: 5 1 0 0 5 5 0 0
  // C: 0 0 1 4 2 0 6 1
  // G: 1 1 6 3 0 1 0 0
  // T: 1 5 0 0 0 1 1 6
  
  outputConsensusAndProfile(input)
  
  def outputConsensusAndProfile(input: String) {
    val summary : IndexedSeq[Vector[Int]] = summarize(input)
    val consensus = getConsensus(summary)
    println(consensus.mkString(""))
    val profile = getProfile(summary)
    Vector("A", "C", "G", "T").zip(profile).foreach((x) => 
      println(String.format("%s: %s", x._1, x._2.mkString(" "))))
  }
  
  def getConsensus(input: IndexedSeq[Vector[Int]]) = {
    input.map((x) =>
      x.zipWithIndex.maxBy(_._1)._2 match {
        case 0 => "A"
        case 1 => "C"
        case 2 => "G"
        case 3 => "T"
      }
    )
  }
  
  def getProfile(input: IndexedSeq[Vector[Int]]) = {
    Range(0, 4).map((i) => input.map((x) => x(i)))
  }
  
  def summarize(input: String) = {
    val strings = extractDnaStrings(input)
    val tuples = strings.map(getNucleotideCountTuple)
    tuples.reduce((x, y) => x.zip(y).map((z) => z._1.zip(z._2).map((w) => w._1 + w._2)))
  }
  
  def getNucleotideCountTuple(dna: String) = {
    dna.map((x) =>
      x match {
        case 'A' => Vector(1, 0, 0, 0)
        case 'C' => Vector(0, 1, 0, 0)
        case 'G' => Vector(0, 0, 1, 0)
        case 'T' => Vector(0, 0, 0, 1)
      }
    )
  }
  
  def extractDnaStrings(input: String) = {
    val re = """>(Rosalind_\d+)\s*([TACG\s]+)\n""".r
    for(m <- re.findAllIn(input)) 
        yield m match {
          case re(name, seq) => seq.replaceAll("""\s+""", "")
        } 
  }
}