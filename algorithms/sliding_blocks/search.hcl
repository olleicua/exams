;;; Sam Auciello | 2013 | Algorithms Exam
;;; This module contains a search api for solving a 3x3 sliding block puzzle

(def _ (require "./underscore.js"))

;; Create a deep copy of the specified series of moves
;; then add the specied final move to the end.
(def copy-moves-plus
     (# (moves final-move)
        (var result (_.map moves (# (x) x)))
        (result.push final-move)
        result))

(def sb (require "./sliding_blocks.js"))

;; The module takes the form of a search function.
;; This function takes an options object as an argument.  The options argument
;; should have a grid property specifying the initial state of the puzzle and a
;; pop property specifying a function for popping an element out of the fringe.
;; Items are always added to the end of the fringe with push so the pop property
;; should use pop to specify a stack for depth-first search and shift to specify
;; a queue for breadth-first search.
(set module.exports
     (# (options)
        (let (moves-tried { } ; a hash to quickly determine whether a given
                              ; state has already been reached so that we don't
                              ; end up in a loop
              fringe [ [ ] ] ) ; a list of series' of moves that have not yet
                               ; been looked at
          
          (set sb.grid options.grid)

          ;; while there moves left to check
          (while (not (empty? fringe.length))
            
            ;; look at the next series of moves
            (let (moves (options.pop fringe))
              (for (move moves) (sb.move move))
              
              ;; check for a solution
              (when (sb.solved?)
                (console.log "solution found!" (JSON.stringify moves))
                (process.exit))
              
              (cond
               
               ((nil? (get moves-tried sb.grid))    
                ;; this state hasn't been seen yet
                (begin
                 ;; mark it as seen
                 (set moves-tried sb.grid moves)
                 ;; add it's children to the fringe
                 (for (move (sb.valid-moves))
                      (fringe.push (copy-moves-plus moves move)))))
               
               ((> (size (get moves-tried sb.grid)) (size moves))
                ;; this is a shorter path to this state
                (set moves-tried sb.grid moves))
               
               (true (nop)))
              
              (sb.undo-all))))))
