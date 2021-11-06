sealed class RE {
    data class Str(val s: String) : RE()
    data class Conc(val l: List<RE>) : RE()
    data class Alt(val l: List<RE>) : RE()
    data class Paren(val e: RE) : RE()
    data class Star(val e: RE) : RE()
    data class Plus(val e: RE) : RE()
    data class Question(val e: RE) : RE()
}

class Parser(val s: String) {
    var i = 0

    fun parse(): RE = parseExpr().also { check(i == s.length) { "Unexpected pos $i" } }

    fun parseExpr(): RE {
        val l = ArrayList<RE>()
        while (i < s.length) {
            l += parseAlt()
            if (i >= s.length || s[i] != '|') break
            i++
        }
        check(l.isNotEmpty())
        if (l.size == 1) return l.single()
        return RE.Alt(l)
    }

    fun parseAlt(): RE {
        val l = ArrayList<RE>()
        while (i < s.length) {
            when (s[i]) {
                '(', in 'A'..'Z' -> {
                    val e = parseAtom()
                    val p = l.lastOrNull()
                    if (p is RE.Str && e is RE.Str) {
                        l.removeLast()
                        l += RE.Str(p.s + e.s)
                    } else
                        l += e
                }
                else -> break
            }
        }
        check(l.isNotEmpty())
        if (l.size == 1) return l.single()
        return RE.Conc(l)
    }

    fun parseAtom(): RE {
        val c = s[i++]
        var e = when(c) {
            '(' -> RE.Paren(parseExpr()).also { check(s[i++] == ')') }
            in 'A'..'Z' -> RE.Str("$c")
            else -> error("Unexpected '$c'")
        }
        while (i < s.length) {
            when (s[i++]) {
                '*' -> e = RE.Star(e)
                '+' -> e = RE.Plus(e)
                '?' -> e = RE.Question(e)
                else -> { i--; break }
            }
        }
        return e
    }
}

data class Dim(val w: Int, val h: Int)

fun RE.dim(): Dim = when(this) {
    is RE.Str -> Dim(4 + s.length, 3)
    is RE.Conc -> {
        val d = l.map { it.dim() }
        Dim(d.sumOf { it.w } + 2 * (l.size - 1), d.maxOf { it.h })
    }
    is RE.Alt -> {
        val d = l.map { it.dim() }
        Dim(d.maxOf { it.w } + 6, d.sumOf { it.h } + (d.size - 1))
    }
    is RE.Paren -> e.dim()
    is RE.Star -> {
        val d = e.dim()
        Dim(d.w + 6, d.h + 5)
    }
    is RE.Plus -> {
        val d = e.dim()
        Dim(d.w + 6, d.h + 2)
    }
    is RE.Question -> {
        val d = e.dim()
        Dim(d.w + 6, d.h + 3)
    }
}

fun RE.draw(r: Int, c: Int, a: Array<CharArray>): Unit = when(this) {
    is RE.Str -> {
        a[r][c] = '+'
        a[r + 1][c] = '+'
        a[r + 2][c] = '+'
        val n = s.length
        for (i in 0 until n + 2) {
            a[r][c + 1 + i] = '-'
            a[r + 2][c + 1 + i] = '-'
        }
        for (i in 0 until n) {
            a[r + 1][c + 2 + i] = s[i]
        }
        a[r][c + 3 + n] = '+'
        a[r + 1][c + 3 + n] = '+'
        a[r + 2][c + 3 + n] = '+'
    }
    is RE.Conc -> {
        var cc = c
        for ((i, e) in l.withIndex()) {
            e.draw(r, cc, a)
            if (i == l.lastIndex) break
            cc += e.dim().w + 2
            a[r + 1][cc - 2] = '-'
            a[r + 1][cc - 1] = '>'
        }
    }
    is RE.Alt -> {
        var rr = r
        val d = l.map { it.dim() }
        val w = d.maxOf { it.w }
        for ((i, e) in l.withIndex()) {
            e.draw(rr, c + 3, a)
            a[rr + 1][c] = '+'
            a[rr + 1][c + 1] = '-'
            a[rr + 1][c + 2] = '>'
            a[rr + 1][c + w + 3] = '-'
            a[rr + 1][c + w + 4] = '>'
            a[rr + 1][c + w + 5] = '+'
            for (cv in d[i].w until w) {
                a[rr + 1][c + cv + 3] = '-'
            }
            if (i == l.lastIndex) break
            val rn = rr + d[i].h + 1
            for (rv in rr + 2..rn) {
                a[rv][c] = '|'
                a[rv][c + w + 5] = '|'
            }
            rr = rn
        }
    }
    is RE.Paren -> e.draw(r, c, a)
    is RE.Star -> {
        e.draw(r + 3, c + 3, a)
        val d = e.dim()
        a[r + 1][c] = '+'
        a[r + 1][c + d.w + 4] = '>'
        a[r + 1][c + d.w + 5] = '+'
        for (j in c + 1 until c + d.w + 4) {
            a[r + 1][j] = '-'
        }
        a[r + 2][c] = '|'
        a[r + 3][c] = '|'
        a[r + 4][c] = '+'
        a[r + 2][c + d.w + 5] = '|'
        a[r + 3][c + d.w + 5] = '|'
        a[r + 4][c + d.w + 5] = '+'

        a[r + 4][c + 1] = '-'
        a[r + 4][c + 2] = '>'
        a[r + 4][c + d.w + 3] = '-'
        a[r + 4][c + d.w + 4] = '>'
        a[r + 4][c + d.w + 5] = '+'
        
        for (i in r + 5..r + d.h + 3) {
            a[i][c] = '|'
            a[i][c + d.w + 5] = '|'
        }
        a[r + d.h + 4][c] = '+'
        a[r + d.h + 4][c + d.w + 5] = '+'
        a[r + d.h + 4][c + 1] = '<'
        for (j in c + 2..c + d.w + 4) {
            a[r + d.h + 4][j] = '-'
        }
    }
    is RE.Plus -> {
        e.draw(r, c + 3, a)
        val d = e.dim()
        a[r + 1][c] = '+'
        a[r + 1][c + 1] = '-'
        a[r + 1][c + 2] = '>'
        a[r + 1][c + d.w + 3] = '-'
        a[r + 1][c + d.w + 4] = '>'
        a[r + 1][c + d.w + 5] = '+'
        for (i in r + 2..r + d.h) {
            a[i][c] = '|'
            a[i][c + d.w + 5] = '|'
        }
        a[r + d.h + 1][c] = '+'
        a[r + d.h + 1][c + d.w + 5] = '+'
        a[r + d.h + 1][c + 1] = '<'
        for (j in c + 2..c + d.w + 4) {
            a[r + d.h + 1][j] = '-'
        }
    }
    is RE.Question -> {
        e.draw(r + 3, c + 3, a)
        val d = e.dim()
        a[r + 1][c] = '+'
        a[r + 1][c + d.w + 4] = '>'
        a[r + 1][c + d.w + 5] = '+'
        for (j in c + 1 until c + d.w + 4) {
            a[r + 1][j] = '-'
        }
        a[r + 2][c] = '|'
        a[r + 2][c + d.w + 5] = '|'
        a[r + 3][c] = '|'
        a[r + 3][c + d.w + 5] = '|'
        a[r + 4][c] = '+'
        a[r + 4][c + d.w + 5] = '+'
        a[r + 4][c + 1] = '-'
        a[r + 4][c + 2] = '>'
        a[r + 4][c + d.w + 3] = '-'
        a[r + 4][c + d.w + 4] = '>'
    }
}

fun main() {
    val input = readLine()!!
    require(input.isNotEmpty() && input.length <= 100)
    val re = Parser(input).parse()
    val d = re.dim()
    val h = d.h
    val w = d.w + 6
    val a = Array(h) { CharArray(w) { ' ' } }
    a[1][0] = 'S'
    a[1][1] = '-'
    a[1][2] = '>'
    a[1][d.w + 3] = '-'
    a[1][d.w + 4] = '>'
    a[1][d.w + 5] = 'F'
    re.draw(0, 3, a)
    println("$h $w")
    a.forEach { println(it.concatToString()) }
}
