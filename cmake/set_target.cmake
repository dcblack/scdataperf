cmake_minimum_required ( VERSION 3.21 )

macro( set_target target )
  set( Target "${target}" )
  list( APPEND TargetS "${target}" )
endmacro()

# vim:nospell
