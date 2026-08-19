module Models.Config (Config, config) where

import Prelude (Int)

data Config = Config
  { sampleRate ∷ Int,
    channels ∷ Int
  }

config ∷ Config
config = Config 4800 2
