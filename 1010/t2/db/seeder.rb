require_relative 'seeds/casaSeed.rb'
require_relative 'seeds/despensaSeed.rb'
require_relative 'seeds/itemSeed.rb'
require_relative 'seeds/despensaItemSeed.rb'
require_relative 'seeds/enderecoSeed.rb'

def populateDB
  puts "Populando base de dados..."
  populaEnderecos
  populaCasas
  populaDespensas
  populaItems
  populaDespensasItems

  puts "Feito!"
  puts
end