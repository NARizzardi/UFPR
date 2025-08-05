require 'rubygems'
require 'active_record'

require_relative 'db/db.rb'
require_relative 'db/seeder.rb'
require_relative 'src/controllers/db.controller.rb'
# variaveis
input = ''

def comandos
  %w[insere altera exclui lista]
end
def comandosValorosos
  %w[insere altera exclui]
end
def tabelas
  %w[casas despensas items enderecos despensas_items]
end
def modelos
  %w[Casa Despensa Item Endereco DespensasItems]
end


# Conexão com o banco de dados
createDB
populateDB

puts "Programa iniciado!"
puts

loop do
  puts 'Insira um comando:'
  input = gets.chomp

  case input
  when 'db'
    puts `clear`
    printDB
  when 'help'
    puts `clear`
    printAjuda
  when 'clear'
    puts `clear`
  when 'exit'
    puts `clear`
    puts "Saindo..."
  else
    # puts `clear`
    entrada = trataEntrada input
    
    if entrada.nil?
      puts "Erro: comando inválido."
    else
      erro = validaComando entrada
      if !erro.nil?
        puts "#{erro}"
      else
        trataComando entrada
      end
    end
  end

break if input == 'exit'
end
