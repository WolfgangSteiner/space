import os
import ycm_core

flags = [
  '-Wall',
  '-Wextra',
  '-Werror',
  '-Wno-long-long',
  '-Wno-variadic-macros',
  '-DNDEBUG',
  '-std=c11',
  '-Iunity/src',
  ]

SOURCE_EXTENSIONS = [ '.c', ]

def FlagsForFile( filename, **kwargs ):
  return {
  'flags': flags,
  'do_cache': True
}
