{-# LANGUAGE TupleSections #-}
module LLVM.Assembly where

import Control.Monad (foldM)
import Control.Applicative
import Data.Maybe (catMaybes)
import qualified LLVM.Bytecode as Bytecode
import Data.Text (Text)

type Program = [Instruction]

data BinOp
  = ADD
  | SUB
  | MUL
  | DIV
  | MIN
  deriving (Show)

data UnOp
  = SIN
  deriving (Show)

data Instruction
  = LBL Text
  | LDC Float
  | LDS Text
  | POP
  | BinOp BinOp
  | UnOp  UnOp
  deriving (Show)

type Offset = Int
type Env = [(Text, Offset)]


mapEnv :: (Offset -> Offset) -> Env -> Env
mapEnv f =  fmap (\(t, o) -> (t, f o))

assembleBinOp :: BinOp -> Bytecode.BinOp
assembleBinOp x =
  case x of
    ADD -> Bytecode.ADD
    SUB -> Bytecode.SUB
    MUL -> Bytecode.MUL
    DIV -> Bytecode.DIV
    MIN -> Bytecode.MIN

assembleUnOp :: UnOp -> Bytecode.UnOp
assembleUnOp x =
  case x of
    SIN -> Bytecode.SIN

data AssemblerError
  = AssemblerError
  deriving Show


env :: Program -> Env
env = foldr h [] . scanr1 g . map f

f (LBL x) = (0, LBL x)
f (LDC x) = (1, LDC x)
f (LDS x) = (1, LDS x)
f POP = (-1, POP)
f (BinOp x) = (1, BinOp x)
f (UnOp x) = (0, UnOp x)
g (offset1, x) (offset2, y) = (offset1+offset2, x)
h x xs =
  case x of
    (o, LBL t) -> (t, o - 1) : xs
    (_, _)  -> xs


assembleInstr :: Env -> Instruction -> Either AssemblerError (Maybe Bytecode.Instruction)
assembleInstr e instr =
  case instr of
    LBL _ -> Right Nothing
    LDC x -> Right $ Just $ Bytecode.LDC x
    LDS l ->
      case lookup l e of
        Nothing -> Left AssemblerError
        Just y -> Right $ Just $ Bytecode.LDS y
    POP -> Right $ Just $ Bytecode.POP
    BinOp x -> Right $ Just $ Bytecode.BinOp $ assembleBinOp $ x
    UnOp x -> Right $ Just $ Bytecode.UnOp $ assembleUnOp $ x

assemble :: Program -> Either AssemblerError Bytecode.Program
assemble prog =
    fmap catMaybes $ mapM (assembleInstr (env prog)) prog
