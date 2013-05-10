// compiled from Hot Cocoa Lisp

// ;;; Sam Auciello | 2013 | Algorithms Exam
// ;;; This file does a depth-first search for the solution to a 3x3 sliding block puzzle
// ((require "./search.js") { grid [ "." "5" "2"
//                                   "1" "4" "3"
//                                   "7" "8" "6" ]
//                            pop (# (queue) (queue.pop)) } )

require("./search.js")({ grid: [".", "5", "2", "1", "4", "3", "7", "8", "6"], pop: (function(queue) {  return queue.pop(); }) });