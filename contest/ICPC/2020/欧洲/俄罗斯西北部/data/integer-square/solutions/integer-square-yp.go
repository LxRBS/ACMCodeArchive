package main

import "fmt"

func main() {
  s := 0;
  fmt.Scanf("%d", &s);
  x := 0;
  for y := s; y >= 0; y-- {
    for ; x * x + y * y < s; x++ {
    }
    if x * x + y * y == s {
      fmt.Printf("%d %d\n%d %d\n%d %d\n%d %d\n",
        0, 0, x, y, -y, x, x - y, x + y);
        return
    }
  }
  fmt.Printf("Impossible");
}
