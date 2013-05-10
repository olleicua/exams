;;; Sam Auciello | 2013 | Algorithms Exam
;;; This module contains a simple api for a 3x3 sliding block puzzle

(def _ (require "./underscore.js"))

(set module.exports {
     
     ;; The dimensions of the puzzle
     size 3
     
     ;; The initial state of the puzzle grid as a one dimentional array
     ;; "." is the empty square.
     grid [ "1" "2" "3"
            "4" "5" "6"
            "7" "8" "." ]
     
     ;; A list to be made to undo the moves made so far
     undo-buffer [ ]
     
     ;; Prints out the current state of the grid e.g.:
     ;; 1 2 3
     ;; 4 5 6
     ;; 7 8 .
     print-grid
     (# ()
        (for ((var i 0) (< i (^2 this.size)) (set+ i this.size))
             (console.log ((this.grid.slice i (+ i this.size)).join " ")))
        (console.log ""))
     
     ;; Returns a list of all valid moves from the current position.
     ;; A move is represented by the index of a square that can be slid into the
     ;; empty space.
     valid-moves
     (# ()
        (_.filter (_.range (^2 this.size))
                  (# (n) (or (and (< 0 (% n this.size))
                                  (= "." (nth this.grid (-1 n))))
                             (and (> 2 (% n this.size))
                                  (= "." (nth this.grid (+1 n))))
                             (= "." (nth this.grid (- n this.size)))
                             (= "." (nth this.grid (+ n this.size))))) this))
     
     ;; Takes the index of a square that can be slid into the empty space,
     ;; updates the grid to reflect the move, and updates the undo buffer.
     move
     (# (move)
        (when (contains? (this.valid-moves this.grid) move)
          (this.undo-buffer.push (this.grid.indexOf "."))
          (set this.grid (this.grid.indexOf ".") (nth this.grid move))
          (set this.grid move ".")))
     
     ;; Undoes the most recent move in the undo buffer
     undo
     (# ()
        (let (move (this.undo-buffer.pop))
          (set this.grid (this.grid.indexOf ".") (nth this.grid move))
          (set this.grid move ".")))
     
     ;; Undoes all of the moves in the undo buffer
     undo-all (# () (while (not (empty? this.undo-buffer)) (this.undo)))
     
     ;; Returns true if the grid is in the solved state
     solved? (# () (= "12345678." (this.grid.join ""))) } )