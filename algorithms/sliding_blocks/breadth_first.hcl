;;; Sam Auciello | 2013 | Algorithms Exam
;;; This file does a breadth-first search for the solution to a 3x3 sliding block puzzle

((require "./search.js") { grid [ "2" "1" "3"
                                  "5" "4" "6"
                                  "7" "8" "." ]
                           pop (# (stack) (stack.shift)) } )
