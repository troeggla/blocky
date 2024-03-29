# Compiler Project 2011

This is my compiler/interpreter. While designing the language, I tried to blend
some of the features from my favorite languages together:

- Variables start with a `$` so they can easily be distinguished, much like
  in *PHP/Perl*
- Blocks are delimited by the keywords `do` and `end`, like in *Ruby*
- Comments are introduced by a hash sign
- Newlines are statement separators, however, if one wants to put multiple statements
  into one line, semicolons can be used to separate them
- In conditional statements/loops, parentheses around the conditions are optional
- In addition to the common `if`/`else`, the language supports also the `unless`/`else`
  construct, coming from *Ruby*
- Another idea from *Ruby* is the `times` loop, which is an easy version of a `for`
  loop
- Each block introduces its own scope, but can access variables from parent scopes
- However, there is a keyword `global`, like in *PHP*, which enables us to allocate
  a variable in the global scope
- As additional gimmick, the language uses the *SDL graphics library* to implement
  functionality which enables one to programmatically create drawings using the
  `pen.*` commands built into the language

To see how these features work in greater detail, please refer to the files in
the samples/ directory.

**Note**: In order to build the compiler, I have created a *Makefile* for your convenience.
          However, make sure you have `libSDL-devel` and `libSDL_gfx-devel` installed, as they
          have to be linked into the final executable.
