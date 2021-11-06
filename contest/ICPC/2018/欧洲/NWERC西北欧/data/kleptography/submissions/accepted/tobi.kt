fun main(vararg args: String) {
  val (n, m) = readLine()!!.split(' ').map{ it -> it.toInt() }
  val last = readLine()!!.toCharArray()
  val encrypted = readLine()!!.toCharArray()
  val plain = CharArray(m)
  for (i in 0..n-1) plain[m-n+i] = last[i]
  for (i in m-n-1 downTo 0) {
    val diff = encrypted[i+n].toInt() - plain[i+n].toInt()
    val shift = (diff + 26) % 26
    plain[i] = (shift + 'a'.toInt()).toChar()
  }
  println(plain)
}
