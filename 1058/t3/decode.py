# Recebe um bloco Hamming, verifica bits de paridade, retorna bloco corrigido
def corrige_erros (blocoHamming):
    hamming = list(blocoHamming)
    paridade = [0, 1, 3, 7, 15] # indices potencia de 2 adaptado -> 1,2,4,8,16
    pos_erro = 0

    # Verifica as paridades
    for p in paridade:
        xor = 0
        for i in range(1, 32):  # índice começa em 1
            if i & (p + 1):
                xor ^= int(hamming[i - 1])
        if xor != 0:
            pos_erro += (p + 1)

    # Corrige o bit, se necessario
    if pos_erro != 0 and pos_erro <= 31:
        hamming[pos_erro - 1] = '1' if hamming[pos_erro - 1] == '0' else '0'

    return ''.join(hamming)

# Remove bits de paridade e retorna os bits de dados (26 bits)
def coleta_bits_dados(blocoHamming):
    paridade = [0, 1, 3, 7, 15]
    bitsDados = ''
    for i in range(31):
        if i not in paridade:
            bitsDados += blocoHamming[i]
    return bitsDados

# Recebe um bloco de bytes e decodifica para utf8
def converte_binario_utf8(byte):
    byte_array = bytearray()
    for i in range(0, len(byte), 8): # itera de byte em byte
        bloco = byte[i:i+8]
        if len(bloco) < 8:
            break
        byte_array.append(int(bloco, 2))
    data = byte_array.decode('utf-8', errors='ignore')
    return data.rstrip("\x00") # garante que o python nao vai ficar corrigindo bytes de graça

# Recebe um bloco de bits no formato hamming e retorna em texto
def decodifica_hamming(blocoCodificado):
    bitsConvertidos = ''
    for bloco in blocoCodificado:
        blocoCorrigido = corrige_erros(bloco)
        bitsDado = coleta_bits_dados(blocoCorrigido)
        bitsConvertidos += bitsDado

    return converte_binario_utf8(bitsConvertidos)
