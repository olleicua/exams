;;; Sam Auciello | 2013 | Algorithms Exam
;;; This file demonstrates the use of the sliding block puzzle api found in
;;; sliding_blocks.hcl by manually solving a puzzle

(def sb (require "./sliding_blocks.js"))

;; initialize grid
(set sb.grid [ "2" "1" "3"
               "5" "4" "6"
               "7" "8" "." ] )

;; solve the puzzle
(let (moves [ 7 4 3 0 1 2 5 4 3 6 7 8 5 2 1 4 3 6 7 4 5 8
              7 6 3 4 7 8 5 4 3 6 7 8 5 4 7 8 ] )
  (sb.print-grid)
  (for (move moves) (sb.move move))
  (sb.print-grid)
  (sb.undo-all)
  (sb.print-grid))
