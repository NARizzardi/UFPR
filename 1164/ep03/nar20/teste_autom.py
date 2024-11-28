import subprocess

n1 = 10
n2 = 1000
k = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 100000, 1000000, 10000000, 100000000]

i = 0
subprocess.call("gcc gera_entrada.c -o gera_entrada", shell = True)

for i in range(len(k)-3):
  output1 = 'teste_n1_' + str(k[i]) + '.dat'
  output2 = 'teste_n2_' + str(k[i]) + '.dat'
  with open(output1, "w") as outfile:
    subprocess.run(["./gera_entrada", str(k[i]), str(n1)], stdout=outfile)
    # roda programa v1
    # roda programa v2 e apaga o arquivo de dados
  with open(output2, "w") as outfile:
    subprocess.run(["./gera_entrada", str(k[i]), str(n2)], stdout=outfile)
    # roda programa v1
    # roda programa v2 e apaga o arquivo de dados

for j in range(i+1, len(k)):
  output1 = 'teste_n1_' + str(k[j]) + '.dat'
  with open(output1, "w") as outfile:
    subprocess.run(["./gera_entrada", str(k[j]), str(n1)], stdout=outfile)
    # roda programa v1
    # roda programa v2 e apaga o arquivo de dados