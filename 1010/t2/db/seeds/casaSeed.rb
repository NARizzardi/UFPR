$:.push './'
require './src/models/casa.model.rb'

def populaCasas
  casas = [
    { nome: 'Casa de Praia', endereco_id: 1},
    { nome: 'Casa de Colombo', endereco_id: 2},
    { nome: 'UFPR', endereco_id: 3},
    { nome: 'UtFPR', endereco_id: 4},
    { nome: 'PUC', endereco_id: 5},
    { nome: 'Ligga Arena', endereco_id: 6},
  ]

  for casa in casas do
    Casa.find_or_create_by(casa)
  end
end