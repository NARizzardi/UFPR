def createDB
    puts "Criando tabelas no banco de dados ..."
    ActiveRecord::Base.establish_connection :adapter => "sqlite3", :database => "./db/database.sqlite3"

    
    if not ActiveRecord::Base.connection.table_exists? 'enderecos'
        ActiveRecord::Base.connection.create_table :enderecos do |endereco|
            endereco.string :rua
            endereco.integer :numero
            endereco.timestamps
        end
    end

    if not ActiveRecord::Base.connection.table_exists? 'casas'
        ActiveRecord::Base.connection.create_table :casas do |casa|
            casa.string :nome
            casa.belongs_to :endereco, foreign_key: true
            casa.timestamps
        end
    end

    if not ActiveRecord::Base.connection.table_exists? 'despensas'
        ActiveRecord::Base.connection.create_table :despensas do |despensa|
            despensa.string :tipo
            despensa.belongs_to :casa, foreign_key: true
            despensa.timestamps
        end
    end

    if not ActiveRecord::Base.connection.table_exists? 'items'
        ActiveRecord::Base.connection.create_table :items do |item|
            item.string :nome
            item.string :marca
            item.timestamps
        end
    end


    if not ActiveRecord::Base.connection.table_exists? 'despensas_items'
        ActiveRecord::Base.connection.create_table :despensas_items do |despensaItem|
            despensaItem.integer :quantidade
            despensaItem.timestamps
            despensaItem.references :item
            despensaItem.references :despensa
        end
    end
    puts "Feito!"
    puts
end