
class DespensasItems < ActiveRecord::Base
    belongs_to :despensa, required: true
    belongs_to :item, required: true
    
    validates :quantidade, numericality: { greater_than_or_equal_to: 0 }

    def imprime
        puts "Despensa: #{despensa_id}"
        puts "##{id}: Item #{item_id}"
        puts "Quantidade: #{quantidade}"
        puts
    end
end