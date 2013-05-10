;;; Sam Auciello | 2013 | languages Exam
;;; This program reads in people from people.csv constructs a linked family tree
;;; structure from it, then provides a console interface to navigate the tree.

(def _ (require "underscore"))
(def csv (require (compile "./csv.hcl")))

;; generate a list of people from the csv file
(def people
	 (_.map (csv "people.csv")
			;; modify each person object to have methods connecting them to the
			;; rest of the tree
			(# (person)
			   (when (= "-1" person.died) (set person.died "present"))
			   (_.extend person {
				  
				  ;; returns the actual parent person object
				  getFather
				  (# () (get people (integer this.father)))
				  getMother
				  (# () (get people (integer this.mother)))
				  
				  ;; returns a list of children
				  children
				  (# ()
					 (let (that this) ; keep the correct 'this' in scope
					   (_.filter people
								 (# (person)
									(contains? [ person.mother person.father ]
											   that.id)))))
				  
				  ;; returns the nth child
				  child
				  (# (n) (get (this.children) n))
				  
				  ;; returns the spouce
				  spouce
				  (# ()
					 (if (empty? (this.children)) undefined
					   (if (= this.id (get (this.children) 0).mother)
						   ((get (this.children) 0).getFather)
						 ((get (this.children) 0).getMother))))
				  
				  ;; print out the person in form "Jane Doe (1902 - 1987)\n"
				  print
				  (# () (console.log (format "~~ ~~ (~~ - ~~)"
											 [ (get this "first_name")
											   (get this "last_name")
											   this.born this.died ] )))
				  
				  ;; print the person, their parents, their spouce, and their
				  ;; children
				  info
				  (# ()
					 (process.stdout.write "\n")
					 (this.print)
					 (process.stdout.write "\nMother: ")
					 (if (this.getMother) ((this.getMother).print)
					   (console.log "N/A"))
					 (process.stdout.write "Father: ")
					 (if (this.getFather) ((this.getFather).print)
					   (console.log "N/A"))
					 (when (not (empty? (this.children)))
					   (process.stdout.write "Spouce: ")
					   ((this.spouce).print)
					   (process.stdout.write "Children:\n")
					   (for (child (this.children)) (child.print)))) } ))))

;; command prompt loop
(def prompt "\nEnter a relative to navigate to (mother, father, spouce, child_n): ")
(var current_person (get people 0))
(current_person.info)
(process.stdout.write prompt)

(process.stdin.resume)
(process.stdin.setEncoding "utf8")

(process.stdin.on "data"
				  (# (input)
					 (let (command (input.trim))
					   (cond
						((= command "quit") (process.exit))
						((= command "mother")
						 (if (nil? (current_person.getMother))
							 (console.log "\n! no mother available")
						   (set current_person (current_person.getMother))))
						((= command "father")
						 (if (nil? (current_person.getFather))
							 (console.log "\n! no father available")
						   (set current_person (current_person.getFather))))
						((= command "spouce")
						 (if (nil? (current_person.spouce))
							 (console.log "\n! no spouce available")
						   (set current_person (current_person.spouce))))
						(((re "^child_\d+$").exec command)
						 (let (child (current_person.child
									  (command.replace "child_" "")))
						   (if (nil? child)
							   (console.log (cat "\n! no child "
												 (command.replace "child_" "")
												 "  available"))
							 (set current_person child))))
						(true (console.log (cat "\n! invalid command: "
												command )))))
					 (current_person.info)
					 (process.stdout.write prompt)))