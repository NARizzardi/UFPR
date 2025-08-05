require 'active_record'

ActiveRecord::Base.establish_connection :adapter => "sqlite3",
                                      :database => "Tabelas.sqlite3"

class Estado < ActiveRecord::Base;
  validates :sigla, format:
    { with: /\A [a-zA-Z]+ z/, message: "Sigla pode ter somente caracteres"}
  validates :sigla, length:
    { is: 2, message: "Siga tem de ter tamanho dois"}
end

est = Estado.new ()
est.nome = "x"
est.sigla = "1"
if est.invalid?
  puts "Registro Invalido:"
  est.errors[:sigla].each do |s|
    puts "#{s}"
  end
end