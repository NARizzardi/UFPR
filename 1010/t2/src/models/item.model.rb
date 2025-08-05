
class Item < ActiveRecord::Base
    has_and_belongs_to_many :despensa, dependent: :destroy

    validates :nome, :marca, presence: true

    def imprime
        puts "Item ##{id}: #{nome} - #{marca}"
    end
end