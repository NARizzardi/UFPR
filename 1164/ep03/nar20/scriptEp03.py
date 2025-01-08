import os
import glob
import shutil
import subprocess
import matplotlib.pyplot as plt
import numpy as np

n1 = 10
n2 = 1000

k = [64, 128, 200]#, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 100000, 1000000, 10000000, 100000000]
data = ['N1+v1', 'N1+v2', 'N2+v1', 'N2+v2']
dataM = ['N1+v1', 'N1+v2', 'N2+v1', 'N2+v2', 'N1+v1+AVX', 'N1+v2+AVX', 'N2+v1+AVX', 'N2+v2+AVX']


def cria_pastas():
  os.makedirs('dados', exist_ok=True)
  os.makedirs('graficos', exist_ok=True)
  os.makedirs('dados/10', exist_ok=True)
  os.makedirs('dados/1000', exist_ok=True)

def gera_dados():
  for i in range(len(k)):
    outfile_v1 = 'dados/10/v1_' + str(k[i]) + '.out'
    command = './gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol > ' + outfile_v1 + ' && ./gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol >> ' + outfile_v1 + ' && ./gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol >> ' + outfile_v1
    subprocess.run(command, shell=True)
    
    outfile_v2 = 'dados/10/v2_' + str(k[i]) + '.out'
    command = './gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol_v2 > ' + outfile_v2 + ' && ./gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol_v2 >> ' + outfile_v2 + ' && ./gera_entrada ' + str(k[i]) + ' 10 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol_v2 >> ' + outfile_v2
    subprocess.run(command, shell=True)
    
    outfile_v1 = 'dados/1000/v1_' + str(k[i]) + '.out'
    command = './gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol > ' + outfile_v1 + ' && ./gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol >> ' + outfile_v1 + ' && ./gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol >> ' + outfile_v1
    subprocess.run(command, shell=True)
    
    outfile_v2 = 'dados/1000/v2_' + str(k[i]) + '.out'
    command = './gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol_v2 > ' + outfile_v2 + ' && ./gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol_v2 >> ' + outfile_v2 + ' && ./gera_entrada ' + str(k[i]) + ' 1000 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol_v2 >> ' + outfile_v2
    subprocess.run(command, shell=True)
  
  # for j in range(len(k)):
  #   outfile_v1 = 'dados/10/v1_' + str(k[j]) + '.out'
  #   command = './gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol > ' + outfile_v1 + ' && ./gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol >> ' + outfile_v1 + ' && ./gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol >> ' + outfile_v1
  #   subprocess.run(command, shell=True)
    
  #   outfile_v2 = '/nobackup/bcc/nar20/v2_' + str(k[j]) + '.out'
  #   command = './gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g L3CACHE -m ./ajustePol_v2 > ' + outfile_v2 + ' && ./gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g ENERGY -m ./ajustePol_v2 >> ' + outfile_v2 + ' && ./gera_entrada ' + str(k[j]) + ' 10 | likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol_v2 >> ' + outfile_v2
  #   subprocess.run(command, shell=True)

def formata_dados(l3_miss_ratio_sl, l3_miss_ratio_eg, energy_sl, energy_eg, flops_sl, flops_eg, tempo_sl, tempo_eg):
  arquivos = glob.glob(os.path.join('dados', '**', '*'), recursive=True)
  linhas_esp = [5, 35, 66, 105, 144, 187, 188, 222, 223]
  

  for arquivo in arquivos:
        if os.path.isfile(arquivo):  # Ensure it's a arquivo
            indexN = True if arquivo.split('/')[1] == '10' else False
            indexV = True if arquivo.split('/')[2].split('_')[0] == 'v1' else False
            matIndex = 0 if (indexN and indexV) else 1 if (indexN and not indexV) else 2 if (not indexN and indexV) else 3  
            indexK = k.index(int(arquivo.split('/')[2].split('_')[1].split('.')[0]))
            with open(arquivo, 'r') as f:
                linhas = f.readlines()
                for linha in linhas_esp:
                    if linha < len(linhas):
                        match (linha):
                          case 5:
                            tempo_eg[matIndex][indexK] = float(linhas[linha].split()[2])
                            tempo_sl[matIndex][indexK] = float(linhas[linha].split()[1])
                          case 35: 
                            l3_miss_ratio_sl[matIndex][indexK] = float(linhas[linha].split('|')[2].strip())
                          case 66:
                            l3_miss_ratio_eg[matIndex][indexK] = float(linhas[linha].split('|')[2].strip())
                          case 105:
                            energy_sl[matIndex][indexK] = float(linhas[linha].split('|')[2])
                          case 144:
                            energy_eg[matIndex][indexK] = float(linhas[linha].split('|')[2])
                          case 187:
                            flops_sl[matIndex][indexK] = float(linhas[linha].split('|')[2])
                          case 188:
                            flops_sl[matIndex+4][indexK] = float(linhas[linha].split('|')[2])
                          case 222:
                            flops_eg[matIndex][indexK] = float(linhas[linha].split('|')[2])
                          case 223:
                            flops_eg[matIndex+4][indexK] = float(linhas[linha].split('|')[2])                       

def gera_graficos(l3_miss_ratio_eg, l3_miss_ratio_sl, energy_eg, energy_sl, flops_eg, flops_sl, tempo_eg, tempo_sl):
   

  #  Grafico L3 Miss Ratio EG 
  x = np.array(k)
  plt.figure()

  for i, row in enumerate(l3_miss_ratio_sl):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('L3 Miss Ratio SL')
  plt.title('L3 Miss Ratio SL / k')
  plt.legend()

  plt.savefig("graficos/l3_miss_ratio_sl.jpg")
     

  #  Grafico L3 Miss Ratio SL

  plt.figure()

  for i, row in enumerate(l3_miss_ratio_eg):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('L3 Miss Ratio EG')
  plt.title('L3 Miss Ratio EG / k')
  plt.legend()

  plt.savefig("graficos/l3_miss_ratio_eg.jpg")
   
 
  #### Grafico Energy SL
  plt.figure()

  for i, row in enumerate(energy_sl):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('Energia [J] SL')
  plt.title('Energia [J] SL / k')
  plt.legend()

  plt.savefig("graficos/energy_sl.jpg")


  #### Grafico EnergyEG
  plt.figure()

  for i, row in enumerate(energy_eg):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('Energia [J]EG')
  plt.title('Energia [J]EG / k')
  plt.legend()

  plt.savefig("graficos/energy_eg.jpg")


  #### Grafico MFLOPS/s SL
  plt.figure()

  for i, row in enumerate(flops_sl):
    plt.plot(x, row, label=dataM[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('MFLOPS/s sl')
  plt.title('MFLOPS/s SL / k')
  plt.legend()

  plt.savefig("graficos/flops_sl.jpg")

  #### Grafico MFLOPS/s EG
  plt.figure()

  for i, row in enumerate(flops_eg):
    plt.plot(x, row, label=dataM[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.ylabel('MFLOPS/s EG')
  plt.title('MFLOPS/s EG / k')
  plt.legend()

  plt.savefig("graficos/flops_eg.jpg")

  #### Grafico Tempo SL
  plt.figure()

  for i, row in enumerate(tempo_sl):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.yscale('log')
  plt.ylabel('Tempo SL')
  plt.title('Tempo SL / k')
  plt.legend()

  plt.savefig("graficos/tempo_sl.jpg")

  #### Grafico Tempo EG
  plt.figure()

  for i, row in enumerate(tempo_eg):
    plt.plot(x, row, label=data[i])

  plt.xscale('log')
  plt.xlabel('Numero de pontos')
  plt.yscale('log')
  plt.ylabel('Tempo EG')
  plt.title('Tempo EG / k')
  plt.legend()

  plt.savefig("graficos/tempo_eg.jpg")
  
  

def remove_pastas():
  shutil.rmtree('dados')

l3_miss_ratio_sl = [[0 for _ in range(len(k))] for _ in range(len(data))]
l3_miss_ratio_eg = [[0 for _ in range(len(k))] for _ in range(len(data))]
energy_sl = [[0 for _ in range(len(k))] for _ in range(len(data))]
energy_eg = [[0 for _ in range(len(k))] for _ in range(len(data))]
flops_sl = [[0 for _ in range(len(k))] for _ in range(len(data) * 2)]
flops_eg = [[0 for _ in range(len(k))] for _ in range(len(data) * 2)]
tempo_sl = [[0 for _ in range(len(k))] for _ in range(len(data))]
tempo_eg = [[0 for _ in range(len(k))] for _ in range(len(data))]

subprocess.run('make', shell=True)
cria_pastas()
gera_dados()
# formata_dados(l3_miss_ratio_sl, l3_miss_ratio_eg, energy_sl, energy_eg, flops_sl, flops_eg, tempo_sl, tempo_eg)
# gera_graficos(l3_miss_ratio_eg, l3_miss_ratio_sl, energy_eg, energy_sl, flops_eg, flops_sl, tempo_eg, tempo_sl)
# remove_pastas()
subprocess.run('make purge', shell=True)