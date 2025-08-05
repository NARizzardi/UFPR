# Recebe strings em utf8 e retorna em bits
def converte_utf8_binario(texto):
    bits = ""
    for byte in texto.encode('utf-8'):
        bits += format(byte, '08b')     
    return bits

# Insere bits de paridade num bloco de dados
def insere_paridade (bloco):
    hamming = ['0'] * 31
    paridade = [0, 1, 3, 7, 15] # indices de paridade 1,2,4,8,16
    j = 0
    for i in range(31):
        if i not in paridade:
            hamming[i] = bloco[j] # insere bits de dados
            j += 1

    for p in paridade:
        xor = 0
        for i in range(1, 32):
            if i & (p + 1) and i != (p + 1):
                xor ^= int(hamming[i - 1]) # calcula bit de paridade
        hamming[p] = str(xor)
    return ''.join(hamming)

# Recebe strings utf8, retorna um array de blocos Hamming
def codifica_hamming(texto):
    bits = converte_utf8_binario(texto)
    blocos = []
    i = 0
    while i < len(bits):
        blocoDados = bits[i:i+26] # extrai um grupo de 26 bits
        if len(blocoDados) < 26:
            blocoDados += '0' * (26 - len(blocoDados)) # preenche com 0s pra completar o bloco
        blocos.append(insere_paridade(blocoDados))
        i += 26
    return blocos # armazezena bits reais lidos (sem preenchimento)