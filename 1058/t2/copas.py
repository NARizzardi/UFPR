import os
import re
import sys
import time
import random
import socket

def cria_socket(MY_ADDR):
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  sock.bind(MY_ADDR)
  return sock

def embaralha():
  baralho = []
  starter = 1
  for carta in range(2, 15):
    for naipe in range(1, 5):
        if(naipe == 1): naipe = 'Ouro'
        elif(naipe == 2): naipe = 'Espada'
        elif(naipe == 3): naipe = 'Copas'
        elif(naipe == 4): naipe = 'Paus'
        baralho.append((str(carta), naipe))
  baralho = random.sample(baralho, 52)

  maos = []
  for i in range(4):
    mao = []
    for j in range(13):
      mao.append(baralho.pop())
    if(('2','Paus') in mao):
      starter = str(i + 1)
    mao_string = " ".join(str(x) for x in mao)
    maos.append(mao_string)
  return maos, starter

def get_ip(id):
  ip_map = {
    1: "10.254.223.83",
    2: "10.254.223.84",
    3: "10.254.223.69",
    4: "10.254.223.68",
  }
  return ip_map.get(id)

def get_next_ip_by_id(id):
  ip_map = {
    1: "10.254.223.84",
    2: "10.254.223.69",
    3: "10.254.223.68",
    4: "10.254.223.83",
  }
  return ip_map.get(id)

def get_id_by_ip(id):
  ip_map = {
    "10.254.223.83": 1,
    "10.254.223.84": 2,
    "10.254.223.69": 3,
    "10.254.223.68": 4,
  }
  return ip_map.get(id)

def imprime_mao(mao, turno, rodada, copas_foi_jogado):
  jogaveis = []
  carta = ""
  # Primeira rodada
  if(rodada == 0): # O jogador que tiver o dois de paus deverá começar o jogo, iniciando com ele
    if(len(turno) == 0):
      for i in range(len(mao)):
        if(mao[i] == ("2", "Paus")):
          print(f'[{i+1}]: 2 de Paus')
          jogaveis.append(i)
    
    else: 
      for i in range(len(mao)): # Os jogadores devem seguir o naipe iniciado.
        if(mao[i][1] == turno[0][2]):
          if(mao[i][0] == "14"): carta = 'A'
          elif(mao[i][0] == "11"): carta = 'J'
          elif(mao[i][0] == "12"): carta = 'Q'
          elif(mao[i][0] == "13"): carta = 'K'
          else: carta = mao[i][0]
          print(f'[{i+1}]: {carta} de {mao[i][1]}')
          jogaveis.append(i)

      if(len(jogaveis) == 0): # Se não tiver uma carta do naipe iniciado
        for i in range(len(mao)):
          if(not(mao[i][0] == "12" and mao[i][1] == "Espada") or not(mao[i][1] == "Copas")): # não pode jogar uma carta de copas ou a rainha de espadas.
            if(mao[i][0] == "14"): carta = 'A'
            elif(mao[i][0] == "11"): carta = 'J'
            elif(mao[i][0] == "12"): carta = 'Q'
            elif(mao[i][0] == "13"): carta = 'K'
            else: carta = mao[i][0]
            print(f'[{i+1}]: {carta} de {mao[i][1]}')
            jogaveis.append(i)
  
  # Demais rodadas
  else:
    if(len(turno) == 0): # O jogador que iniciar a rodada poderá usar qualquer carta
      if(copas_foi_jogado): 
        for i in range(len(mao)):
          if(mao[i][0] == "14"): carta = 'A'
          elif(mao[i][0] == "11"): carta = 'J'
          elif(mao[i][0] == "12"): carta = 'Q'
          elif(mao[i][0] == "13"): carta = 'K'
          else: carta = mao[i][0]
          print(f'[{i+1}]: {carta} de {mao[i][1]}')
          jogaveis.append(i)

      else: # Exceto uma de copas, se ainda não foi usado na rodada.
        for i in range(len(mao)): 
          if(not(mao[i][1] == "Copas")):
            if(mao[i][0] == "14"): carta = 'A'
            elif(mao[i][0] == "11"): carta = 'J'
            elif(mao[i][0] == "12"): carta = 'Q'
            elif(mao[i][0] == "13"): carta = 'K'
            else: carta = mao[i][0]
            print(f'[{i+1}]: {carta} de {mao[i][1]}')
            jogaveis.append(i)
    
    else: 
      for i in range(len(mao)): # Os jogadores devem seguir o naipe iniciado
        if(mao[i][1] == turno[0][2]):
          if(mao[i][0] == "14"): carta = 'A'
          elif(mao[i][0] == "11"): carta = 'J'
          elif(mao[i][0] == "12"): carta = 'Q'
          elif(mao[i][0] == "13"): carta = 'K'
          else: carta = mao[i][0]
          print(f'[{i+1}]: {carta} de {mao[i][1]}')
          jogaveis.append(i)

      if(len(jogaveis) == 0): # Se não tiver uma carta do naipe iniciado poderá jogar qualquer uma
        for i in range(len(mao)):
          if(mao[i][0] == "14"): carta = 'A'
          elif(mao[i][0] == "11"): carta = 'J'
          elif(mao[i][0] == "12"): carta = 'Q'
          elif(mao[i][0] == "13"): carta = 'K'
          else: carta = mao[i][0]
          print(f'[{i+1}]: {carta} de {mao[i][1]}')
          jogaveis.append(i)

  return jogaveis

def imprime_turno(turno):
  if(len(turno)>0):
    for i in range(len(turno)):
      if(turno[i][1] == "14"): carta = 'A'
      elif(turno[i][1] == "11"): carta = 'J'
      elif(turno[i][1] == "12"): carta = 'Q'
      elif(turno[i][1] == "13"): carta = 'K'
      else: carta = turno[i][1]
      print(f'#{turno[i][0]}: {carta} de {turno[i][2]}')
    print("\n")
    
def send_data(sock, NEXT_ADDR, data):
  data = data.encode()

  sock.sendto(data, NEXT_ADDR)

def receive_data(sock):
  data, PREV_ADDR = sock.recvfrom(4096)
  data = data.decode()
  data = str(data).split()
  return data


####################### "Main" #######################

id = int(sys.argv[1])
PORT = 5000
token = False

mao = []
maos = []
turno = []
levadas = [[],[],[],[]]
pontuacao = [0,0,0,0]

## bloco de endereçamento
MY_IP = get_ip(id)
MY_ADDR = (MY_IP, PORT)

NEXT_IP = get_next_ip_by_id(id)
NEXT_ADDR = (NEXT_IP, PORT)

sock = cria_socket(MY_ADDR)

################### Inicio do jogo ###################
while True:
  copas_foi_jogado = False
  starter = "1";
  if id == 1: # Embaralha o deck e distribui as mãos
    maos, starter = embaralha()

  if id == 1: # Envia o marcador de inicio para o jogador correto
    if(starter == str(id)):
      token = True
    mensagem = MY_IP + " " + NEXT_IP + " " + "1" + " " + starter
    send_data(sock, NEXT_ADDR, mensagem)
    receive_data(sock)
    i = 0
    mao = re.findall(r"\('([^']+)', '([^']+)'\)", maos[i])
    i+=1
    for i in range(1, 4): # Envia as cartas pros demais jogadores
      mensagem = MY_IP + " " +  get_next_ip_by_id(i) + " " + "2" + " " +maos[i]
      send_data(sock, NEXT_ADDR, mensagem)
      receive_data(sock)
  else:
    # Recebe e transmite o marcador de inicio para o jogador correto
    data = receive_data(sock)
    data[1] = NEXT_IP
    mensagem = data[0] + " " + data[1] + " " + data[2] + " " + data[3]
    send_data(sock, NEXT_ADDR, mensagem)  
    
    if(data[3] == str(id)):
      token = True
    
    i = 1
    for i in range(1,4):
      data = receive_data(sock)
      if(data[1] == MY_IP):
        aux = data[3:]
        for j in range(0, len(aux), 2):
          carta = aux[j].replace("(", "").replace(",", "").replace("'", "").strip()
          naipe = aux[j+1].replace(")", "").replace("'", "").strip()
          mao.append((carta, naipe))
      j = 0
      mensagem = ""
      for j in range(len(data)):
        mensagem =  mensagem + data[j] + " "
      send_data(sock, NEXT_ADDR, mensagem)
  

################ Começo de uma rodada ################
  print("Começando uma nova rodada!\n")
  for j in range(13): # Uma rodada
    while len(turno) < 4: # Um turno
      if token:
        imprime_turno(turno)

        cartas_jogaveis = imprime_mao(mao, turno, j, copas_foi_jogado)
        card = -1;
        while card not in cartas_jogaveis:
          entrada = input("Escolha sua carta: ")
          try:
            card = int(entrada)
          except ValueError:
            print("Entre com um valor válido")
          card = card - 1
        
        aux = mao.pop(card) 
        card = " ".join(aux)
        jogada = (id, aux[0], aux[1])
        turno.append(jogada)

        mensagem = MY_IP + " " +  NEXT_IP + " " + "3" + " " + card
        send_data(sock, NEXT_ADDR, mensagem)
        data = receive_data(sock)
        
        if(len(turno) < 4): # Último jogador do turno não passa o token
          token = False
          mensagem = MY_IP + " " +  NEXT_IP + " " + "0"
          send_data(sock, NEXT_ADDR, mensagem)
   
      else:

        data = receive_data(sock)

        if(data[2] == "3"): # Recebeu uma carta
          data[1] = NEXT_IP
          mensagem = data[0] + " " + data[1] + " " + data[2] + " " + data[3] + " " + data[4]
          send_data(sock, NEXT_ADDR, mensagem)
          jogador = get_id_by_ip(data[0])
          jogada = (jogador, data[3], data[4])
          turno.append(jogada)
        elif(data[2] == "0"): # Recebeu o Token
          token = True

    if("Copas" in jogada): # Controle da regra de jogar carta de copas
        copas_foi_jogado = True
    
    # Averigua quem perdeu o turno
    maior = (turno[0][0], turno[0][1], turno[0][2])
    for i in range(0,4):
      if(turno[i][2] == maior[2]):
        if(int(turno[i][1]) > int(maior[1])):
          maior = (turno[i][0], turno[i][1], turno[i][2])

    imprime_turno(turno)
    perdedor = maior[0]
    print(f"O perdedor do turno #{j+1} foi o jogador #{perdedor}")

    for i in range(0,4):
      levadas[perdedor-1].append((turno[i][1], turno[i][2]))
    
    # Passa o token pro jogador que inicia o turno
    if(token):
      mensagem = MY_IP + " " + NEXT_IP + " " + "1" + " " + str(maior[0])
      starter = str(maior[0])
      send_data(sock, NEXT_ADDR, mensagem)
      receive_data(sock)
    else:
      data = receive_data(sock)
      data[1] = NEXT_IP
      mensagem = data[0] + " " + data[1] + " " + data[2] + " " + data[3]
      starter = data[3]
      send_data(sock, NEXT_ADDR, mensagem)
      
    if(starter == str(id)):
      token = True      
    else:
      token = False
    
    turno = []
    time.sleep(7)
    os.system('clear')
  
  print("Fim da rodada...\n\n")
  print(f"Pontuação após a rodada {j+1}: ")
  for i in range(4): # Contabiliza os pontos da rodada para cada jogador
    score = 0
    for k in range(len(levadas[i])):
      if(levadas[i][k][1] == "Copas"):
        score += 1
      elif(levadas[i][k][0] == "12" and levadas[i][k][1] == "Espada"):
        score +=13
    if(score == 26): # Acertou o moonshot
      for k in range(4):
        if(k != i):
          pontuacao[k] += score
    else: # Contabiliza a pontuacao normal
      pontuacao[i] += score

  if any(x >= 100 for x in pontuacao):
    os.system('clear')
    menor = [(int(1), pontuacao[0])]
    for i in range(4):
      if(menor[0][1] > pontuacao[i]):
        menor[0] = (i+1, pontuacao[i])
    for i in range(4):
      if(menor[0][1] == pontuacao[i] and menor[0][0] != i+1):
        menor.append((i+1, pontuacao[i]))
    print("Fim de jogo!")
    if(len(menor) == 1):
      print(f"O vencedor foi o jogador #{menor[0][0]}, com uma pontuação de {menor[0][1]}")
    else:
      print("Houve um empate entre os vencedores!")
      for i in range(len(menor)):
        print(f"O vencedor foi o jogador #{menor[i][0]}, com uma pontuação de {menor[i][1]}")

    print("\nPontuação geral:")
    for i in range(4):
      print(f"Jogador #{i+1} - {pontuacao[i]} pontos")
    sys.exit(0)
  for i in range(0,4):
      print(f'#{i+1}: {pontuacao[i]} pontos')

  token = False