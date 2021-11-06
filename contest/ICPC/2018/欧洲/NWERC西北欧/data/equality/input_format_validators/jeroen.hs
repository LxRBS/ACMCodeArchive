{-# LANGUAGE Strict #-}
import System.Exit
import System.IO
import Control.Monad
import Data.List
import Data.Char

main :: IO ()
main = do
  str1 <- getLine
  str2 <- getLine
  "" <- getContents
  -- Parse and validate
  when (length str1 < 3 || length str1 > 10^6) $ error "Program length incorrect"
  when (length str2 < 3 || length str2 > 10^6) $ error "Program length incorrect"
  let (e1, "") = parse str1
  let (e2, "") = parse str2
  let () = validate e1
  let () = validate e2
  -- This is not a failure
  exitWith $ ExitFailure 42

-- AST
data Expr = Lst [Integer]
          | Sorted Expr
          | Shuffle Expr
          | Concat Expr Expr

-- Parsing functions
parse :: String -> (Expr, String)
parse ('[':xs) =
  let f :: String -> ([Integer], String)
      f s = let (x,ys) = parseInt s
            in case ys of
                 ']':zs -> ([x], zs)
                 ',':zs -> let (xs,r) = f zs in (x:xs,r)
                 _      -> error $ "Expected ] or , in " ++ show (take 10 ys)
      (e,r) = f xs
  in  (Lst e, r)
parse ('s':'h':'u':'f':'f':'l':'e':'(':xs) =
  let (a,')':ys) = parse xs
  in  (Shuffle a, ys)
parse ('s':'o':'r':'t':'e':'d':'(':xs) =
  let (a,')':ys) = parse xs
  in  (Sorted a, ys)
parse ('c':'o':'n':'c':'a':'t':'(':xs) =
  let (a,',':ys) = parse xs
      (b,')':zs) = parse ys
  in  (Concat a b, zs)
parse xs = error $ "Could not parse expression starting with " ++ show (take 10 xs)

parseInt :: String -> (Integer, String)
parseInt ('0':xs) = (0, xs)
parseInt (x:xs) | isDigit x = let (ys,zs) = span isDigit xs
                              in  (read (x:ys), zs)                                  
parseInt xs = error $ "Could not parse integer from " ++ show (take 10 xs)

-- Extra validation, i.e. that integers fall in the range
validate :: Expr -> ()
validate (Lst []) = error "Empty lists not allowed"
validate (Lst xs) | any (>=10^10) xs = error "Number with 10 digits or more found"
                  | otherwise        = ()
validate (Sorted e) = validate e
validate (Shuffle e) = validate e
validate (Concat a b) = let () = validate a in validate b
