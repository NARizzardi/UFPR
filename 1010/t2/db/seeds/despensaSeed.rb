$:.push './'
require './src/models/despensa.model.rb'

def populaDespensas
  despensas = [
    { tipo: 'Adega', casa_id: 1},
    { tipo: 'Adega', casa_id: 2},
    { tipo: 'Farmacia', casa_id: 3},
    { tipo: 'Farmacia', casa_id: 4},
    { tipo: 'Pet Shop', casa_id: 5},
    { tipo: 'Pet Shop', casa_id: 6},
    { tipo: 'Escritorio', casa_id: 1},
    { tipo: 'Escritorio', casa_id: 2},
    { tipo: 'Inventário', casa_id: 3},
    { tipo: 'Inventário', casa_id: 4},
    { tipo: 'Armario', casa_id: 5},
    { tipo: 'Armario', casa_id: 6},
  ]

  for despensa in despensas
      Despensa.find_or_create_by(despensa)
  end
end