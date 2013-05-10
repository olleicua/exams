// compiled from Hot Cocoa Lisp

var __, csv, format = function(f,v){var i=0;return f.replace(/~([a-zA-Z0-9_]*)~/g,function(_,k){if(k===''){k=i;i++;}if(v[k]===undefined){return'';}return v[k];})}, people, prompt, current__person;

// ;;; Sam Auciello | 2013 | languages Exam
// ;;; This program reads in people from people.csv constructs a linked family tree
// ;;; structure from it, then provides a console interface to navigate the tree.
// (def _ (require "underscore"))

__ = require("underscore");

// (def csv (require (compile "./csv.hcl")))

csv = require("./csv.js");

// (def people
// 	 (_.map (csv "people.csv")
// 			(# (person)
// 			   (when (= "-1" person.died) (set person.died "present"))
// 			   (_.extend person {
// 						 
// 				  getFather
// 				  (# () (get people (integer this.father)))
// 				  
// 				  getMother
// 				  (# () (get people (integer this.mother)))
// 				  
// 				  children
// 				  (# ()
// 					 (let (that this)
// 					   (_.filter people
// 								 (# (person)
// 									(contains? [ person.mother person.father ]
// 											   that.id)))))
// 				  
// 				  child
// 				  (# (n) (get (this.children) n))
// 				  
// 				  spouce
// 				  (# ()
// 					 (if (empty? (this.children)) undefined
// 					   (if (= this.id (get (this.children) 0).mother)
// 						   ((get (this.children) 0).getFather)
// 						 ((get (this.children) 0).getMother))))
// 				  
// 				  print
// 				  (# () (console.log (format "~~ ~~ (~~ - ~~)"
// 											 [ (get this "first_name")
// 											   (get this "last_name")
// 											   this.born this.died ] )))
// 				  
// 				  info
// 				  (# ()
// 					 (process.stdout.write "\n")
// 					 (this.print)
// 					 (process.stdout.write "\nMother: ")
// 					 (if (this.getMother) ((this.getMother).print)
// 					   (console.log "N/A"))
// 					 (process.stdout.write "Father: ")
// 					 (if (this.getFather) ((this.getFather).print)
// 					   (console.log "N/A"))
// 					 (when (not (empty? (this.children)))
// 					   (process.stdout.write "Spouce: ")
// 					   ((this.spouce).print)
// 					   (process.stdout.write "Children:\n")
// 					   (for (child (this.children)) (child.print)))) } ))))

people = __.map(csv("people.csv"), (function(person) { ((("-1" === person.died)) && (function() { (person.died = "present"); }).call(this)); return __.extend(person, { getFather: (function() {  return people[Math.floor(parseFloat(this.father))]; }), getMother: (function() {  return people[Math.floor(parseFloat(this.mother))]; }), children: (function() {  return (function(that) { return __.filter(people, (function(person) {  return ([person.mother, person.father].indexOf(that.id) !== -1); })); }).call(this, this); }), child: (function(n) {  return this.children()[n]; }), spouce: (function() {  return ((this.children() === null || (this.children()).length === 0) ? undefined : (((this.id === this.children()[0].mother)) ? this.children()[0].getFather() : this.children()[0].getMother())); }), print: (function() {  return console.log(format("~~ ~~ (~~ - ~~)", [this["first_name"], this["last_name"], this.born, this.died])); }), info: (function() {var _i0_, child; process.stdout.write("\n"); this.print(); process.stdout.write("\nMother: "); (this.getMother() ? this.getMother().print() : console.log("N/A")); process.stdout.write("Father: "); (this.getFather() ? this.getFather().print() : console.log("N/A")); return ((! (this.children() === null || (this.children()).length === 0)) && (function() { process.stdout.write("Spouce: "); this.spouce().print(); process.stdout.write("Children:\n"); for (_i0_ = 0; _i0_ < this.children().length; _i0_++) { child = this.children()[_i0_]; child.print(); }; }).call(this)); }) }); }));

// (def prompt "\nEnter a relative to navigate to (mother, father, spouce, child_n): ")

prompt = "\nEnter a relative to navigate to (mother, father, spouce, child_n): ";

// (var current_person (get people 0))

current__person = people[0];

// (current_person.info)

current__person.info();

// (process.stdout.write prompt)

process.stdout.write(prompt);

// (process.stdin.resume)

process.stdin.resume();

// (process.stdin.setEncoding "utf8")

process.stdin.setEncoding("utf8");

// (process.stdin.on "data"
// 				  (# (input)
// 					 (let (command (input.trim))
// 					   (cond
// 						((= command "quit") (process.exit))
// 						((= command "mother")
// 						 (if (nil? (current_person.getMother))
// 							 (console.log "\n! no mother available")
// 						   (set current_person (current_person.getMother))))
// 						((= command "father")
// 						 (if (nil? (current_person.getFather))
// 							 (console.log "\n! no father available")
// 						   (set current_person (current_person.getFather))))
// 						((= command "spouce")
// 						 (if (nil? (current_person.spouce))
// 							 (console.log "\n! no spouce available")
// 						   (set current_person (current_person.spouce))))
// 						(((re "^child_\d+$").exec command)
// 						 (let (child (current_person.child
// 									  (command.replace "child_" "")))
// 						   (if (nil? child)
// 							   (console.log (cat "\n! no child "
// 												 (command.replace "child_" "")
// 												 "  available"))
// 							 (set current_person child))))
// 						(true (console.log (cat "\n! invalid command: "
// 												command )))))
// 					 (current_person.info)
// 					 (process.stdout.write prompt)))

process.stdin.on("data", (function(input) { (function(command) { return (((command === "quit")) ? process.exit() : ((command === "mother")) ? ((current__person.getMother() === null || current__person.getMother() === undefined) ? console.log("\n! no mother available") : (current__person = current__person.getMother())) : ((command === "father")) ? ((current__person.getFather() === null || current__person.getFather() === undefined) ? console.log("\n! no father available") : (current__person = current__person.getFather())) : ((command === "spouce")) ? ((current__person.spouce() === null || current__person.spouce() === undefined) ? console.log("\n! no spouce available") : (current__person = current__person.spouce())) : (new RegExp("^child_\\d+$", "")).exec(command) ? (function(child) { return ((child === null || child === undefined) ? console.log(("\n! no child " + command.replace("child_", "") + "  available")) : (current__person = child)); }).call(this, current__person.child(command.replace("child_", ""))) : true ? console.log(("\n! invalid command: " + command)) : undefined); }).call(this, input.trim()); current__person.info(); return process.stdout.write(prompt); }));