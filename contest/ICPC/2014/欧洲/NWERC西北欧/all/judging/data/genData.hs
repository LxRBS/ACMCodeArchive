import Control.Monad
import System.Random

maxn :: Int
maxn = 100000

case3 :: IO ()
case3 = do
  print maxn
  replicateM_ maxn $ putStrLn "indexoutofbound"
  replicateM_ maxn $ putStrLn "indexoutofbound"

-- only randomize last 3 chars to make sure there is some overlap
randStr :: IO String
randStr = do
  len <- randomRIO (5,15)
  start <- replicateM 3 $ randomRIO ('a','z')
  return $ replicate (len - 3) 'a' ++ start

randomCase :: IO ()
randomCase = do
  n <- randomRIO (1,maxn)
  print n
  replicateM_ n $ randStr >>= putStrLn
  replicateM_ n $ randStr >>= putStrLn


main = randomCase
