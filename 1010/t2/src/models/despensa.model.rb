class Despensa < ActiveRecord::Base
    belongs_to :casa, required: true
    has_and_belongs_to_many :item, dependent: :destroy


    validates :tipo, presence: true
    
    def imprime
        puts "Despensa ##{id}: - #{tipo}"
        self.item.find_each {|obj| obj.imprime}
    end
end