
class Endereco < ActiveRecord::Base
  has_one :casa, dependent: :destroy
  validates :rua, :numero, presence: true
  validates :numero, numericality: { only_integer: true, greater_than_or_equal_to: 0 }


  def imprime
    puts "Endereco ##{id}: #{rua} - Nº#{numero}"
end

end