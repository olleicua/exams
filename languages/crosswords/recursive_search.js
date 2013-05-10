// compiled from Hot Cocoa Lisp

var __, _caret_2 = function(x){return x*x;}, unused_hyphen_squares, solution, intersections, remove_hyphen_from_hyphen_list, square_hyphen_allowed, search;

// (def _ (require "underscore"))

__ = require("underscore");

// (var unused-squares (_.map (_.range 10 32) (# (x) (string (^2 x)))))

unused_hyphen_squares = __.map(__.range(10, 32), (function(x) {  return ((x * x)).toString(); }));

// (var solution [ ] )

solution = [];

// ;; TODO: explain this in a comment
// (var intersections [ [ 0 1 1 0 ]
// 	                 [ 1 2 2 1 ]
// 					 [ 2 0 3 0 ]
// 					 [ 2 2 4 0 ]
// 					 [ 3 2 5 0 ]
// 					 [ 4 2 5 2 ]
// 					 [ 5 1 6 0 ]
// 					 [ 6 2 7 1 ]
// 					 [ 7 0 8 0 ]
// 					 [ 7 2 9 0 ]
// 					 [ 8 2 10 0 ]
// 					 [ 9 2 10 2 ]
// 					 [ 10 1 11 0 ]
// 					 [ 11 2 12 1 ] ] )

intersections = [[0, 1, 1, 0], [1, 2, 2, 1], [2, 0, 3, 0], [2, 2, 4, 0], [3, 2, 5, 0], [4, 2, 5, 2], [5, 1, 6, 0], [6, 2, 7, 1], [7, 0, 8, 0], [7, 2, 9, 0], [8, 2, 10, 0], [9, 2, 10, 2], [10, 1, 11, 0], [11, 2, 12, 1]];

// (def remove-from-list
// 	 (# (list element)
// 		(when (contains? list element)
// 		  (list.splice (list.indexOf element) 1))))

remove_hyphen_from_hyphen_list = (function(list, element) {  return ((list.indexOf(element) !== -1) && (function() { list.splice(list.indexOf(element), 1); }).call(this)); });

// (def square-allowed
// 	 (# (square position)
// 		(var result true)
// 		(for (intersection intersections)
// 			 (when (or (and (= position (get intersection 0))
// 							(not (nil? (get solution (get intersection 2))))
// 							(!= (get square (get intersection 1))
// 								(get (get solution (get intersection 2))
// 									 (get intersection 3))))
// 					   (and (= position (get intersection 2))
// 							(not (nil? (get solution (get intersection 0))))
// 							(!= (get square (get intersection 3))
// 								(get (get solution (get intersection 0))
// 									 (get intersection 1)))))
// 			   (set result false)))
// 		result))

square_hyphen_allowed = (function(square, position) {var result, _i0_, intersection; result = true; for (_i0_ = 0; _i0_ < intersections.length; _i0_++) { intersection = intersections[_i0_]; (((((position === intersection[0])) && (! (solution[intersection[2]] === null || solution[intersection[2]] === undefined)) && ((square[intersection[1]] !== solution[intersection[2]][intersection[3]]))) || (((position === intersection[2])) && (! (solution[intersection[0]] === null || solution[intersection[0]] === undefined)) && ((square[intersection[3]] !== solution[intersection[0]][intersection[1]])))) && (function() { (result = false); }).call(this)); }; return result; });

// (def search
// 	 (# ()
// 		(if (= 13 solution.length) (console.log solution)
// 		  (begin (for (square unused-squares)
// 					  (when (square-allowed square solution.length)
// 						(solution.push square)
// 						(remove-from-list unused-squares square)
// 						(if (search) true
// 						  (begin
// 						   (solution.pop)
// 						   (unused-squares.push square)
// 						   (unused-squares.sort))))
// 					  false)))))

search = (function() {var _i0_, square;  return (((13 === solution.length)) ? console.log(solution) : (function() {  for (_i0_ = 0; _i0_ < unused_hyphen_squares.length; _i0_++) { square = unused_hyphen_squares[_i0_]; (square_hyphen_allowed(square, solution.length) && (function() { solution.push(square); remove_hyphen_from_hyphen_list(unused_hyphen_squares, square); (search() ? true : (function() {solution.pop(); unused_hyphen_squares.push(square); return unused_hyphen_squares.sort(); }).call(this)); }).call(this)); false; }; }).call(this)); });

// (search)

search();