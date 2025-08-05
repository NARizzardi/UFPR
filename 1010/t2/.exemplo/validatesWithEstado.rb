require 'active_record'
class String
  def only_letters?
    !!match(/ˆ[[:alpha:]]+$/)
  end
end

ActiveRecord::Base.establish_connection :adapter => "sqlite3",
                                      :database => "Tabelas.sqlite3"

class EstadoValidator < ActiveModel::Validator
  def validate(record)
    if (record.sigla.size != 2)
      record.errors.add(:sigla, "Siga tem de ter tamanho dois")
    end
    if !record.sigla.alpha?
      record.errors.add(:sigla, "Sigla pode ter somente caracteres")
    end
  end
end

class Estado < ActiveRecord::Base;
  validates_with EstadoValidator
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