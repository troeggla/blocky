" Vim syntax file
" Language: blocky, a small language for the compiler course 2011
" Maintainer: Thomas Röggla
" Latest Revision: 22 Jan 2012

if exists("b:current_syntax")
    finish
endif

syn keyword blockyKeyword puts put global pen scope 
syn keyword blockyCondition if else unless while times
syn keyword blockyDelim do end

syn match blockyVariable '\$[a-z][A-Za-z0-9_]*'
syn match blockyString1 '"[^"]*"'
syn match blockyString2 '\'[^\']*\''

syn match blockyNumber '\d\+'
syn match blockyNumber '-\d\+'
syn match blockyNumber '\d\+\.\d\+'
syn match blockyNumber '-\d\+\.\d\+'

syn match blockyComment "#.*$"

syn match blockyOperator '+'
syn match blockyOperator '-'
syn match blockyOperator '\*'
syn match blockyOperator '/'
syn match blockyOperator '%'
syn match blockyOperator '='
syn match blockyOperator '=='
syn match blockyOperator '!='
syn match blockyOperator '>='
syn match blockyOperator '<='
syn match blockyOperator '!'
syn match blockyOperator '>'
syn match blockyOperator '<'

syn match blockyNil '\<nil\>'

syn match blockyBool 'true'
syn match blockyBool 'false'

syn region blockyBlock start='\<do\>' end='\<end\>' fold transparent

let b:current_syntax = "blocky"

hi def link blockyComment   Comment
hi def link blockyDelim     Delimiter
hi def link blockyString1   String
hi def link blockyString2   String
hi def link blockyKeyword   Keyword
hi def link blockyCondition Conditional
hi def link blockyOperator  Operator
hi def link blockyVariable  Identifier
hi def link blockyNumber    Number
hi def link blockyBool      Boolean
hi def link blockyBlock     Statement
hi def link blockyNil       Constant
