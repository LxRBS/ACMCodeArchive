object German_DS {
    def reverse (c: Char): Char = {
	if (c == '>')
	    return '<';
	else
	    return '>';
    }

    def main (args: Array [String]): Unit = {
	val a = scala.io.StdIn.readLine ();

	var stack = List[Char]()
	var result = ""
	var phase_wait = false;

	for (x <- a) {
	    phase_wait = !phase_wait;
	    if (phase_wait) {
		stack match {
		    case hd :: tail if hd == x => stack = tail; result += ']'

		    case hd :: tail => stack = reverse (x) :: hd :: tail;  result += '['
		    case Nil        => stack = List (reverse (x));         result += '['
		}
	    }
	}

	if (stack.length != 0)
	    println ("Keine Loesung")
	else
	    println (result)
    }
}