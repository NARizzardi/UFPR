$:.push'./'
require 'estado.rb'

#Método 1.1: usando a chave primária
est = Estado.find(1)
puts est.nome

#Método 1.2: fazendo consulta com busca por nome
est = Estado.find_by({:sigla=>"AL"})
puts est.nome

#Método 1.3: fazendo consulta usando dynamic finders
est = Estado.find_by_sigla("AM")
puts est.nome

#Método 2.1: usando SQL
est = Estado.find_by_sql("SELECT * from estados")
puts est.class # Array

#Método 2.2: pegando todos
est = Estado.all
puts est.class # Estado::ActiveRecord_Relation

est.each do |e|
    puts "#{e.sigla} = #{e.nome}"
end
