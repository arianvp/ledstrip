module LLVM.Bytecode where

import Data.Foldable
import Data.Monoid (mempty, (<>))
import qualified Data.ByteString.Builder as Builder
import Data.ByteString.Builder (Builder)

type Offset = Int
type Program = [Instruction]

data BinOp
  = ADD
  | SUB
  | MUL
  | DIV
  | MIN
  deriving Show

data UnOp
  = SIN
  deriving Show

data Instruction
  = LDC Float
  | LDS Offset
  | POP
  | BinOp BinOp
  | UnOp  UnOp
  deriving Show

encodeInstruction :: Instruction -> Builder
encodeInstruction = undefined

encode :: Program -> Builder
encode = foldMap encodeInstruction
