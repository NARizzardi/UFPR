import sys
import encode
import decode

def main():
    if len(sys.argv) < 3:
        print("Uso: ./hamming.py -c <arquivo_entrada>")
        print(" ./hamming.py -d <bloco codificado por hamming>")
        return

    modo = sys.argv[1]

    # modo codificação (arquivo.txt)
    if modo == "-c":
        arqTexto = sys.argv[2]
        try:
            with open(arqTexto, 'r', encoding='utf-8') as arquivo:
                texto = arquivo.read()
        except FileNotFoundError:
            print("Erro: Arquivo '" + arqTexto + "' não encontrado.")
            return
        # Codifica o arquivo .txt com o metodo Hamming(31,26)
        blocos = encode.codifica_hamming(texto)
        ponto = arqTexto.find(".")
        textoCodificado = arqTexto
        if ponto != -1:
            textoCodificado = arqTexto[:ponto] # Pega o nome do arquivo (sem .tipoArquivo)
        textoCodificado +=".hamming"
        
        # Abre arquivo de escrita NomeOrignal.hamming
        with open(textoCodificado, 'w') as fw:
            for b in blocos:
                fw.write(b + " ")


    # modo decodificação (arquivo.hamming)
    elif modo == "-d":
        arqHamming = sys.argv[2]
        try:
            with open(arqHamming, 'r') as arquivo:
                aux = [linha.replace(" ", "\n") for linha in arquivo if linha.replace(" ", "\n")]
                blocos = aux[0].split("\n")
                blocos = blocos[0:len(blocos)-1]
        except FileNotFoundError:
            print("Erro: Arquivo '"+ arqHamming +"' não encontrado.")
            return

        # Converte blocos de bits no formato Hamming
        resultado = decode.decodifica_hamming(blocos)
        ponto = arqHamming.find(".")
        textoDecodificado = arqHamming
        if ponto != -1:
            textoDecodificado = arqHamming[:ponto] # Pega o nome do arquivo (sem .tipoArquivo)
        textoDecodificado +=".dec"
        with open(textoDecodificado, 'w') as fw:
            for b in resultado:
                fw.writelines(b)

    else:
        print("Modo inválido. Use -c para codificar ou -d para decodificar.")

if __name__ == "__main__":
    main()
