$:.push './'
require './src/models/endereco.model.rb'

def populaEnderecos
  enderecos = [
    { rua: 'Rua Joao', numero: 1},
    { rua: 'Rua Jose', numero: 1},
    { rua: 'Rua Paulo', numero: 1},
    { rua: 'Rua Matheus', numero: 1},
    { rua: 'Rua Gabriel', numero: 1},
    { rua: 'Rua Judas', numero: 1},
  ]

  for endereco in enderecos do
    Endereco.find_or_create_by(endereco)
  end
end