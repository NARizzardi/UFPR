$:.push './'
require './src/models/itemDespensa.model.rb'

def populaDespensasItems
  itemsDepensas = [
    { item_id: 1, despensa_id: 1, quantidade: 10 },
    { item_id: 2, despensa_id: 2, quantidade: 2 },
    { item_id: 3, despensa_id: 3, quantidade: 3 },
    { item_id: 4, despensa_id: 4, quantidade: 9 },
    { item_id: 5, despensa_id: 5, quantidade: 1 },
    { item_id: 6, despensa_id: 6, quantidade: 5 },
    { item_id: 1, despensa_id: 6, quantidade: 7 },
    { item_id: 2, despensa_id: 5, quantidade: 8 },
    { item_id: 3, despensa_id: 4, quantidade: 6 },
    { item_id: 4, despensa_id: 3, quantidade: 4 },
    { item_id: 5, despensa_id: 2, quantidade: 2 },
    { item_id: 6, despensa_id: 1, quantidade: 3 },
  ]

  for itemsDepensa in itemsDepensas do
    DespensasItems.find_or_create_by(itemsDepensa)
  end
end