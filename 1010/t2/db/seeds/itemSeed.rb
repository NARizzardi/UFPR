$:.push './'
require './src/models/item.model.rb'

def populaItems
  items = [
    { nome: 'Pasta de Dente', marca: 'Sorriso' },
    { nome: 'Vinho', marca: 'Campo Largo' },
    { nome: 'Bolacha', marca: 'Marilan' },
    { nome: 'Macarrão', marca: 'Todeschini' },
    { nome: 'Bola de Volei', marca: 'Rainha' },
    { nome: 'Detergente', marca: 'Ype' },
  ]

  for item in items do
    Item.find_or_create_by(item)
  end
end