module Helpers ((◁), (◀), (⊙), (●), (◇), fork, try') where

import Prelude ((.), (<>), IO, String, show)
import Control.Applicative (Applicative, (<*>), liftA2, pure)
import Control.Arrow ((|||))
import Control.Exception (IOException, try)
import Control.Monad (Monad, (<=<))
import Control.Monad.IO.Class (MonadIO, liftIO)
import Control.Monad.Except (MonadError, throwError)
import Data.Functor (Functor, (<$>), fmap)
import Data.Semigroup (Semigroup)

fork :: Applicative f ⇒ (a → b → c) → f a → f b → f c
fork = liftA2

try' ∷ (MonadIO m, MonadError String m) ⇒ IO a → m a
try' = err ◀ io
  where io  = liftIO . try @IOException
        err = (throwError . show) ||| pure

-- Digraph Tl
(◁) ∷ Functor f ⇒ (b → c) → (a → f b) → a → f c
f ◁ g = fmap f . g
infixr 9 ◁

-- Digraph PL
(◀) ∷ Monad m ⇒ (b → m c) → (a → m b) → a → m c
f ◀ g = f <=< g
infixr 1 ◀

-- Digraph 0.
(⊙) ∷ Functor f ⇒ (a → b) → f a → f b
f ⊙ g = f <$> g
infixl 4 ⊙

-- Digraph 0M
(●) ∷ Applicative f ⇒ f (a → b) → f a → f b
f ● g = f <*> g
infixl 4 ●

-- Digraph Dw
(◇) ∷ Semigroup a ⇒ a → a → a
α ◇ ω = α <> ω
infixr 5 ◇
