;;; Sam Auciello | 2013 | languages Exam
;;; This tiny library provides a simplified API for reading simplified csv files
;;; that have no quotes or commas in the values
;;;
;;; Usage:
;;; (def csv (require (compile "csv.hcl")))
;;; (csv "path/to/file")
;;; 
;;; for a file like:
;;;   foo,bar,baz
;;;   1,2,3
;;;   4,5,6
;;;   7,8,9
;;;
;;; returns:
;;;   [ { foo 1 bar 2 baz 3 }
;;;     { foo 4 bar 5 baz 6 }
;;;     { foo 7 bar 8 baz 9 } ]


(def _ (require "underscore"))
(def fs (require "fs"))

(set module.exports
	 (# (path)
		(let (lines (((fs.readFileSync path).toString).split "\n"))
		  (let (head ((get lines 0).split ","))
			(_.map (_.filter (lines.slice 1) (# (line) (not (empty? line))))
				   (# (line) (_.object head (line.split ","))))))))