=begin

Sam Auciello | 2013 | Languages Exam
This script generates a random family with and stores it in people.csv

A family consists of 30 or more people across 5 or more generations.
Each person has a first and last name and a year in-which they were born.
Each person either has a year in-which they died or is still alive.
Each person either has both a father and a mother or neither.
People live between 40 and 100 years.
People don't have genders; anyone can be a father or a mother.
Each parent can only have children with at most one other parent within 20 years
 of their age although they may swap mother/father roles for different children.
Children cannot be born to parents younger than 30.
Children may inherit their last name from either parent.
Names are taken at random from names.csv which was found at:
 http://www.opensourcecf.com/1/2009/05/10000-Random-Names-Database.cfm

=end

class RandomNames
  @@names = (open "names.csv").each_line.map{ |line| line.split "," }
  def self.first_name; @@names.choice[0]; end
  def self.last_name; @@names.choice[1]; end
end

class Person
  attr_accessor :first_name, :last_name, :father, :mother, :born, :died
  def ancestorHeight
    [@father.nil? ? 0 : @father.ancestorHeight + 1,
     @mother.nil? ? 0 : @mother.ancestorHeight + 1].max
  end
end

def newPerson options = {}
  result = Person.new
  result.first_name = RandomNames.first_name
  result.last_name = (options[:last_name].nil? ?
                      RandomNames.last_name :
                      options[:last_name])
  result.father = options[:father]
  result.mother = options[:mother]
  result.born = options[:born].to_a.choice
  result.died = result.born + (40..100).to_a.choice
  result.died = nil if result.died > Time.now.year
  return result
end

people = [newPerson :born => (1900..1970)]

until people.size >= 30 and people.map{ |x| x.ancestorHeight }.max >= 5
  case [:child, :child, :parents, :sibling].choice
  when :child
    mother = people.select{ |x| x.born <= Time.now.year - 40 }.choice
    previous_children = people.select{ |x| [x.mother, x.father].index mother }
    if previous_children.empty?
      father = newPerson :born => (mother.born - 20 ..
                                   [mother.born + 20, Time.now.year - 40].min)
      people << father
    else
      child1 = previous_children[0]
      father = child1.mother == mother ? child1.father : child1.mother
    end
    last_name = [father.last_name, mother.last_name].choice
    born = (([mother.born, father.born].max + 30) ..
            [(mother.died or Time.now.year), (father.died or Time.now.year)].min)
    people << newPerson(:last_name => last_name, :father => father,
                        :mother => mother, :born => born)
  when :parents
    child = people.select{ |x| x.mother.nil? }.choice
    parent_birth_range = (child.born - 40 .. child.born - 30)
    father = newPerson :last_name => child.last_name, :born => parent_birth_range
    mother = newPerson :born => parent_birth_range
    child.mother = mother
    child.father = father
    people << father
    people << mother
  when :parents
    sibling1 = people.select{ |x| not x.mother.nil? }.choice
    mother = sibling1.mother
    father = sibling1.father
    born = (([mother.born, father.born].max + 30) ..
          [(mother.died or Time.now.year), (father.died or Time.now.year)].min)
    sibling2 = newPerson(:last_name => sibling1.last_name, :father => father,
                         :mother => mother, :born => born)
    people sibling2
  end
end

csv = (open "people.csv", "w")
csv.write "id,first_name,last_name,father,mother,born,died\n"
people.each do |person|
  id = people.index person
  first = person.first_name
  last = person.last_name
  father = (people.index person.father) || "-1"
  mother = (people.index person.mother) || "-1"
  born = person.born
  died = person.died || "-1"
  csv.write "#{id},#{first},#{last},#{father},#{mother},#{born},#{died}\n"
end