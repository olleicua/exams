// compiled from Hot Cocoa Lisp

// ;;; Sam Auciello | 2013 | Algorithms Exam
// ;;; This file demonstrates the use of the sliding block puzzle api found in
// ;;; sliding_blocks.hcl by manually solving a puzzle
// (def sb (require "./sliding_blocks.js"))

var sb = require("./sliding_blocks.js");

// ;; initialize grid
// (set sb.grid [ "2" "1" "3"
//                "5" "4" "6"
//                "7" "8" "." ] )

(sb.grid = ["2", "1", "3", "5", "4", "6", "7", "8", "."]);

// ;; solve the puzzle
// (let (moves [ 7 4 3 0 1 2 5 4 3 6 7 8 5 2 1 4 3 6 7 4 5 8
//               7 6 3 4 7 8 5 4 3 6 7 8 5 4 7 8 ] )
//   (sb.print-grid)
//   (for (move moves) (sb.move move))
//   (sb.print-grid)
//   (sb.undo-all)
//   (sb.print-grid))

(function(moves) {sb.print__hyphen__grid(); for (var _i_ = 0; _i_ < moves.length; _i_++) { var move = moves[_i_]; sb.move(move); }; sb.print__hyphen__grid(); sb.undo__hyphen__all(); return sb.print__hyphen__grid(); }).call(this, [7, 4, 3, 0, 1, 2, 5, 4, 3, 6, 7, 8, 5, 2, 1, 4, 3, 6, 7, 4, 5, 8, 7, 6, 3, 4, 7, 8, 5, 4, 3, 6, 7, 8, 5, 4, 7, 8]);