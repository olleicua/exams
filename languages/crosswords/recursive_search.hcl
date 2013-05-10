;;; Sam Auciello | 2013 | languages Exam
;;; A script to recursively search for solutions to a crossword of three digit
;;; squares of the form:
;;;
;;; #   # # #   # # #   #
;;; # # #   # # #   # # #
;;; #   # # #   # # #   #


(def _ (require "underscore"))

;; An array of squares that have not yet been tried in the search
(var unused-squares (_.map (_.range 10 32) (# (x) (string (^2 x)))))

;; A sequence of squares that can be filled in to solve the puzzle
(var solution [ ] )

;; Define a list of intersections [ a b c d ] where space a digit b intersects
;; with space c digit d.  So for example the fact that the middle digit of the
;; left most vertical space in the puzzle intersects with the first digit of the
;; left most horizontal space is encoded by [ 0 1 1 0 ].
(var intersections [ [ 0 1 1 0 ]
	                 [ 1 2 2 1 ]
					 [ 2 0 3 0 ]
					 [ 2 2 4 0 ]
					 [ 3 2 5 0 ]
					 [ 4 2 5 2 ]
					 [ 5 1 6 0 ]
					 [ 6 2 7 1 ]
					 [ 7 0 8 0 ]
					 [ 7 2 9 0 ]
					 [ 8 2 10 0 ]
					 [ 9 2 10 2 ]
					 [ 10 1 11 0 ]
					 [ 11 2 12 1 ] ] )

;; Modify the list in place by removing the first occurance specified element
(def remove-from-list
	 (# (list element)
		(when (contains? list element)
		  (list.splice (list.indexOf element) 1))))

;; Determine whether a given square can be placed in given position by checking
;; each intersection
(def square-allowed
	 (# (square position)
		(var result true)
		(for (intersection intersections)
			 (when (or (and (= position (get intersection 0))
							(not (nil? (get solution (get intersection 2))))
							(!= (get square (get intersection 1))
								(get (get solution (get intersection 2))
									 (get intersection 3))))
					   (and (= position (get intersection 2))
							(not (nil? (get solution (get intersection 0))))
							(!= (get square (get intersection 3))
								(get (get solution (get intersection 0))
									 (get intersection 1)))))
			   (set result false)))
		result))

;; Search for a solution
(def search
	 (# ()
		(if (= 13 solution.length) (console.log solution)
		  (begin (for (square unused-squares)
					  (when (square-allowed square solution.length)
						(solution.push square)
						(remove-from-list unused-squares square)
						(if (search) true
						  (begin
						   (solution.pop)
						   (unused-squares.push square)
						   (unused-squares.sort))))
					  false)))))

(search)