fun main(vararg args: String) {
  val n = readLine()!!.toInt()
  val cans = readLine()!!.split(' ').map{ it.toDouble() }.toDoubleArray()
  cans.sort()
  var min = (n+1).toDouble()
  for (i in 1..n) {
    min = minOf(min.toDouble(), cans[i-1]/i) 
    if (cans[i-1] > i) {
      println("impossible")
      return
    }
  }
  println(min)
}
