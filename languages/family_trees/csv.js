// compiled from Hot Cocoa Lisp

var __, fs, toString;

// ;;; Sam Auciello | 2013 | languages Exam
// ;;; This tiny library provides a simplified API for reading simplified csv files
// ;;; that have no quotes or commas in the values
// ;;;
// ;;; Usage:
// ;;; (def csv (require (compile "csv.hcl")))

__ = require("underscore");

// ;;; (csv "path/to/file")

fs = require("fs");

// ;;; 
// ;;; for a file like:
// ;;;   foo,bar,baz
// ;;;   1,2,3
// ;;;   4,5,6
// ;;;   7,8,9
// ;;;
// ;;; returns:
// ;;;   [ { foo 1 bar 2 baz 3 }
// ;;;     { foo 4 bar 5 baz 6 }
// ;;;     { foo 7 bar 8 baz 9 } ]
// (def _ (require "underscore"))

(module.exports = (function(path) {  return (function(lines) { return (function(head) { return __.map(__.filter(lines.slice(1), (function(line) {  return (! (line === null || (line).length === 0)); })), (function(line) {  return __.object(head, line.split(",")); })); }).call(this, lines[0].split(",")); }).call(this, fs.readFileSync(path).toString().split("\n")); }));