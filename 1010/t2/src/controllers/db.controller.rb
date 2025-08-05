def printDB
  puts 'CREATE TABLE IF NOT EXISTS "casas" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "nome" varchar, "endereco" varchar, "created_at" datetime(6) NOT NULL, "updated_at" datetime(6) NOT NULL);'
  puts 'CREATE TABLE sqlite_sequence(name,seq);'
  puts 'CREATE TABLE IF NOT EXISTS "despensas" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "tipo" varchar, "casa_id" integer, "created_at" datetime(6) NOT NULL, "updated_at" datetime(6) NOT NULL, CONSTRAINT "fk_rails_ba51664976"'
  puts 'FOREIGN KEY ("casa_id")'
  puts '  REFERENCES "casas" ("id")'
  puts ');'
  puts 'CREATE INDEX "index_despensas_on_casa_id" ON "despensas" ("casa_id");'
  puts 'CREATE TABLE IF NOT EXISTS "enderecos" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "rua" varchar, "numero" integer, "casa_id" integer, "created_at" datetime(6) NOT NULL, "updated_at" datetime(6) NOT NULL, CONSTRAINT "fk_rails_88fbffd5fc"'
  puts 'FOREIGN KEY ("casa_id")'
  puts '  REFERENCES "casas" ("id")'
  puts ');'
  puts 'CREATE INDEX "index_enderecos_on_casa_id" ON "enderecos" ("casa_id");'
  puts 'CREATE TABLE IF NOT EXISTS "items" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "nome" varchar, "marca" varchar, "created_at" datetime(6) NOT NULL, "updated_at" datetime(6) NOT NULL);'
  puts 'CREATE TABLE IF NOT EXISTS "item_despensas" ("id" integer PRIMARY KEY AUTOINCREMENT NOT NULL, "quantidade" integer, "created_at" datetime(6) NOT NULL, "updated_at" datetime(6) NOT NULL, "item_id" integer, "despensa_id" integer);'
  puts 'CREATE INDEX "index_item_despensas_on_item_id" ON "item_despensas" ("item_id");'
  puts 'CREATE INDEX "index_item_despensas_on_despensa_id" ON "item_despensas" ("despensa_id");'
end

def printAjuda
  
  ############################################## TUTORIAL ##############################################
  puts 'Modo de uso:'
  puts
  puts '< operação > < tabela > { atributo = valor }'
  puts
  puts '< operação > pode ser "insere", "altera", "exclui", "lista";'
  puts '< tabela > indica o nome da tabela (casas, despensas, items, item_despensas, enderecos);'
  puts 'atributo = valor indica o valor do atributo envolvido na operação (0..n valores);'
  puts '{...} indica repetição, os colchetes não devem ser adicionados.'
  puts
  puts 'Exemplos:'
  puts '- insere enderecos rua="Rua Fulano" numero=1'
  puts '- lista despensas'
  puts '- exclui items nome="arroz"'
  puts
  puts 'Comando uteis:'
  puts '- db: retorna o schema da tabela (copiado do sqlite3);'
  puts '- clear: limpa o console'
  puts '- help: mostra como usar o programa.'
  puts '- exit: sai do programa.'
    
  puts
  puts
    
    ######################################################################################################
end

def trataEntrada input
  entrada = {}
  split = []
  aux = []
  tmp = ''

  split = input.split(/ /, 3)
  entrada['comando'] = split[0]
  entrada['tabela'] = split[1]
  tmp = split[2]

  if !tmp.nil?
    tmp = tmp.gsub /( |(".*?"))/, '\\2-'
    tmp = tmp.split('"--')

    entrada['valores'] = Hash.new
    for valor in tmp do
      if valor.include? '='
        aux = valor.delete!('"-').split('=')
        entrada['valores'][aux[0].strip] = aux[1].strip
      else
        entrada = nil
        break
      end
    end
  end
  entrada
end

def validaComando entrada

  if !comandos.include? entrada['comando']
    return "Erro: comando inválido."
  end
  if !tabelas.include? entrada['tabela']
    return "Erro: tabela inválida."
  end

  cv = comandosValorosos.include? entrada['comando'] 
  ev = (entrada['valores'].nil? || entrada['valores'].empty?)

  if cv && ev
    return "Erro: Este comando precisa de parâmetros."
  end

  if entrada['comando'] == 'altera' && entrada['valores']['id'].nil?
    return "Erro: Este comando precisa de um id."
  end
end

def trataComando entrada
  tabela = modelos.find { |model| model.constantize.table_name == entrada['tabela'] }
  tabela = tabela.constantize
  case entrada['comando']
  when 'insere'
    insere(tabela: tabela, comando: entrada['valores'])
  when 'exclui'
    exclui(tabela: tabela, comando: entrada['valores'])
  when 'altera'
    altera(tabela: tabela, comando: entrada['valores'])
  when 'lista'
    lista(tabela: tabela)
  end
end

def insere (tabela: ,comando:)
  novo_item = tabela.new(comando)
  
  if novo_item.save
    puts "Item inserido com sucesso."
  else
     puts "Erro ao inserir na tabela #{tabela}: #{novo_item.errors.full_messages.join(', ')}"
  end
end

def exclui (tabela: ,comando:)
  item_excluido = tabela.where(comando).first
  item_excluido.destroy if item_excluido
  if item_excluido
    puts "Item excluído com sucesso."
  else
    puts "Erro ao excluir na tabela #{tabela}: #{item_excluido.errors.full_messages.join(', ')}"
  end
end

def altera (tabela: ,comando:)
  item_alterado = tabela.find_by_id(comando['id'])
  if item_alterado.update(comando.except(:id))
    puts "Item alterado com sucesso."
  else
    puts "Erro ao alterar item na tabela #{tabela}: #{item_alterado.errors.full_messages.join(', ')}"
  end
end

def lista (tabela: )
  if tabela.all.size >= 1
    tabela.find_each{ |item| item.imprime}
  else
    puts "Tabela vazia."
  end
end
