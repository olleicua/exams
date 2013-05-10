=begin
Sam Auciello | 2013 | languages Exam
A script to generate a graphviz file for the family tree:
=end

require "csv"

graph = open "tree.graphviz", "w"
graph.write "digraph x {"

# make the legend
graph.write "mother1[label=\"\" color=white];mother2[label=\"mother\" color=white];"
graph.write "father1[label=\"\" color=white];father2[label=\"father\" color=white];"
graph.write "mother1->mother2[color=\"#0E5904\"];"
graph.write "father1->father2[color=\"#C26406\"];"

# for each line in the csv file add a node with the proper label and edges to
# the parents if they exist
CSV.open("people.csv", "r") do |person|
  if person[0] != "id" # omit the first line
    id, first, last, father, mother, born, died = person
    died = "present" if died.to_i < 0
    graph.write "p#{id}[label=\"#{first} #{last}\\n(#{born}-#{died})\", shape=square];"
    graph.write "p#{father}->p#{id}[color=\"#C26406\"];" if father.to_i >= 0
    graph.write "p#{mother}->p#{id}[color=\"#0E5904\"];" if mother.to_i >= 0
  end
end

graph.write "}"
