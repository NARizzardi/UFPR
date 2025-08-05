$:.push'./'
require 'estado.rb'
#Método 1
  est = Estado.new()
  est.nome="Acre"
  est.sigla="AC"
  est.save

#Método 2
est = Estado.new({:nome=>"Alagoas",:sigla=>"AL"})
est.save

#Método 3
  lista_estados=[
    {:nome=>"Amapá",:sigla=>"AP"},
    {:nome=>"Amazonas",:sigla=>"AM"},
    {:nome=>"Bahia",:sigla=>"BA"},
    {:nome=>"Ceará",:sigla=>"CE"},
    {:nome=>"Distrito Federal",:sigla=>"DF"},
    {:nome=>"Espírito Santo",:sigla=>"ES"},
    {:nome=>"Goiás",:sigla=>"GO"},
    {:nome=>"Maranhão",:sigla=>"MA"},
    {:nome=>"Mato Grosso",:sigla=>"MT"},
    {:nome=>"Mato Grosso do Sul",:sigla=>"MS"},
    {:nome=>"Minas Gerais",:sigla=>"MG"},
    {:nome=>"Pará",:sigla=>"PA"},
    {:nome=>"Paraíba",:sigla=>"PB"},
    {:nome=>"Paraná",:sigla=>"PR"},
    {:nome=>"Pernambuco",:sigla=>"PE"},
    {:nome=>"Piauṕi",:sigla=>"PI"},
    {:nome=>"Rio de Janeiro",:sigla=>"RJ"},
    {:nome=>"Rio Grande do Norte",:sigla=>"RN"},
    {:nome=>"Rio Grande do Sul",:sigla=>"RS"},
    {:nome=>"Rondônia",:sigla=>"RO"},
    {:nome=>"Roraima",:sigla=>"RR"},
    {:nome=>"Santa Catarina",:sigla=>"SC"},
    {:nome=>"São Paulo",:sigla=>"SP"},
    {:nome=>"Sergipe",:sigla=>"SE"},
    {:nome=>"Tocantins",:sigla=>"TO"},

  ]

  lista_estados.each do |e|
    est = Estado.new()
    est.nome = e[:nome]
    est.sigla = e[:sigla]
    est.save
  end
