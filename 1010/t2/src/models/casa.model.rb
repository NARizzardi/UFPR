class Casa < ActiveRecord::Base
    belongs_to :endereco, required: true
    has_many :despensa, dependent: :destroy

    validates :nome, presence: true
    
    def imprime
        puts "Casa: #{nome}"
        self.endereco.imprime
        if !self.despensa.nil?
            puts "Despensas:"
            self.despensa.find_each {|obj| obj.imprime}
            puts
        end 
    end
end