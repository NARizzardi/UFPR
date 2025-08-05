const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
canvas.width = window.innerWidth-10;
canvas.height = window.innerHeight-60;

const wCanvas = canvas.width;
const hCanvas = canvas.height;
const xCentro = wCanvas/2;
const yCentro = hCanvas/2;
const erro = 5;
const raio = 200;
ctx.lineWidth = 3;
ctx.strokeStyle = "#2E3130";

let arrastando = false;
let linhaSelecionada1 = -1;
let linhaSelecionada2 = -1;


class Linha {
    constructor(xInicial, yInicial, xFinal, yFinal) {
        this.xInicial = xInicial;
        this.yInicial = yInicial;
        this.xFinal = xFinal;
        this.yFinal = yFinal;
        this.isInicial = 0;
        this.isFinal = 0;
    }

    desenha_circulo(ctx, x, y, raio, cor) {
        ctx.beginPath(); 
        ctx.arc(x, y, raio, 0, 2 * Math.PI); 
        ctx.fillStyle = cor; 
        ctx.fill();     
        ctx.closePath(); 
    }

    desenha_linha(ctx) {
        ctx.beginPath();
        ctx.moveTo(this.xInicial, this.yInicial);
        ctx.lineTo(this.xFinal, this.yFinal);
        ctx.stroke();

        this.desenha_circulo(ctx, this.xInicial, this.yInicial, 7, '#2E3130');
        this.desenha_circulo(ctx, this.xInicial, this.yInicial, 5, '#4A322F');
        this.desenha_circulo(ctx, (this.xFinal+this.xInicial)/2, (this.yFinal+this.yInicial)/2, 6, '#2E3130');
        this.desenha_circulo(ctx, (this.xFinal+this.xInicial)/2, (this.yFinal+this.yInicial)/2, 4, '#7D635C');
        this.desenha_circulo(ctx, this.xFinal, this.yFinal, 7, '#2E3130');
        this.desenha_circulo(ctx, this.xFinal, this.yFinal, 5, '#4A322F');
    }

    atualiza_final(xFinal, yFinal) {
        this.xFinal = xFinal;
        this.yFinal = yFinal;
    }

    atualiza_inicial(xInicial, yInicial) {
        this.xInicial = xInicial;
        this.yInicial = yInicial;
    }

    calcula_meio() {
        return {
            x: (this.xInicial + this.xFinal) / 2,
            y: (this.yInicial + this.yFinal) / 2
        };
    }
}


function distanciaEntrePontos(x1, y1, x2, y2) {
    return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
}

function distanciaLinha(px, py, xInicial, yInicial, xFinal, yFinal) {
    const dx = xFinal - xInicial;
    const dy = yFinal - yInicial;
    const comprimentoLinha = Math.sqrt(dx * dx + dy * dy);
    const produtoEscalar = ((px - xInicial) * (xFinal - xInicial) + (py - yInicial) * (yFinal - yInicial)) / (comprimentoLinha * comprimentoLinha);
  
    if (produtoEscalar <= 0) {
      // O ponto está antes da linha, retorna a distância até o ponto inicial
      const distanciaInicial = Math.sqrt((px - xInicial) * (px - xInicial) + (py - yInicial) * (py - yInicial));
      return distanciaInicial;
    }
  
    if (produtoEscalar >= 1) {
      // O ponto está depois da linha, retorna a distância até o ponto final
      const distanciaFinal = Math.sqrt((px - xFinal) * (px - xFinal) + (py - yFinal) * (py - yFinal));
      return distanciaFinal;
    }
  
    // O ponto está entre as extremidades da linha, calcula a distância perpendicular
    const distanciaPerpendicular = Math.abs((py - yInicial) * dx - (px - xInicial) * dy) / comprimentoLinha;
    return distanciaPerpendicular;
}

function desenha_poligono() {
    linhas = [];
    let input = document.getElementById("lados");
    console.log(input)
    let lados = input.value;
    
    let angulo = 360 / lados;
    let xInicial = xCentro + raio;
    let yInicial = yCentro;
    let xFinal;
    let yFinal;
    let linha;

    for (let i = 0; i < lados; i++) {
        xFinal = xCentro + raio * Math.cos(angulo * Math.PI / 180);
        yFinal = yCentro + raio * Math.sin(angulo * Math.PI / 180);
        linha = new Linha(xInicial, yInicial, xFinal, yFinal);
        linhas.push(linha);
        angulo += 360 / lados;
        xInicial = xFinal;
        yInicial = yFinal;
    }
    linhas[lados-1].xFinal = linhas[0].xInicial;
    linhas[lados-1].yFinal = linhas[0].yInicial;
    desenha_tudo(linhas);

}


function init() {
    linhas = [];
    linhas.push(new Linha(wCanvas/2-150, hCanvas/2, wCanvas/2+150, hCanvas/2));
    desenha_tudo(linhas);
}


function desenha_tudo(linhas) {
    ctx.clearRect(0, 0, wCanvas, hCanvas);
    linhas.forEach(linha => {
        linha.desenha_linha(ctx);
    });
}


canvas.addEventListener("mousedown", (event) => {
    const px = event.clientX - canvas.offsetLeft;
    const py = event.clientY - canvas.offsetTop;
    linhaSelecionada1 = linhaSelecionada2 = -1;
    arrastando = false;    

    // fazer funcao busca_linha
    linhas.forEach((linha, i) => {
        const distanciaInicial = distanciaEntrePontos(px, py, linha.xInicial, linha.yInicial);
        const distanciaFinal = distanciaEntrePontos(px, py, linha.xFinal, linha.yFinal);
        const distanciaMeio = distanciaEntrePontos(px, py, linha.calcula_meio().x, linha.calcula_meio().y);
        console.log(erro)
        if (distanciaInicial < erro) {
            if(linhaSelecionada1 == -1) {
                linhaSelecionada1 = i;
            } else {
                linhaSelecionada2 = i;
            }
            linhas[i].isInicial = 1;
            arrastando = true;

        } else if (distanciaFinal < erro) {
            if(linhaSelecionada1 == -1) {
                linhaSelecionada1 = i;
            } else {
                linhaSelecionada2 = i;
            }
            linhas[i].isFinal = 1;
            arrastando = true;

        } else if (distanciaMeio < erro) {
            linhaSelecionada1 = i;
            arrastando = true;

        }
    });
    
    canvas.addEventListener("mouseup", (event) => {
        if(arrastando) {
            linhas[linhaSelecionada1].isInicial = 0;
            linhas[linhaSelecionada1].isFinal = 0;
            if(linhaSelecionada2 != -1) {
                linhas[linhaSelecionada2].isInicial = 0;
                linhas[linhaSelecionada2].isFinal = 0;
            }
            arrastando = false;
        }
    });

    canvas.addEventListener("mousemove", (event) => {
        if(arrastando) {
            const NovoPx = event.clientX - canvas.offsetLeft;
            const NovoPy = event.clientY - canvas.offsetTop;
            let meioX;
            let meioY;
            let aux1 = -1;
            let aux2 = -1;

            if(linhas[linhaSelecionada1].isInicial) {
                linhas[linhaSelecionada1].xInicial = NovoPx;
                linhas[linhaSelecionada1].yInicial = NovoPy;

            } else if(linhas[linhaSelecionada1].isFinal) {
                linhas[linhaSelecionada1].xFinal = NovoPx;
                linhas[linhaSelecionada1].yFinal = NovoPy;
            } else {
                // arrastando meio
                linhas.forEach((linha, i) => {
                    if(i != linhaSelecionada1) {
                        if(((linha.xInicial == linhas[linhaSelecionada1].xInicial) && (linha.yInicial == linhas[linhaSelecionada1].yInicial))
                        || ((linha.xInicial == linhas[linhaSelecionada1].xFinal) && (linha.yInicial == linhas[linhaSelecionada1].yFinal))) {
                            linha.isInicial = 1;

                            if(aux1 == -1) {
                                aux1 = i;
                            } else {
                                aux2 = i;
                            }
                        }
                        if (((linha.xFinal == linhas[linhaSelecionada1].xInicial) && (linha.yFinal == linhas[linhaSelecionada1].yInicial))
                        || ((linha.xFinal == linhas[linhaSelecionada1].xFinal) && (linha.yFinal == linhas[linhaSelecionada1].yFinal)) ) {
                            linha.isFinal = 1;
                            
                            if(aux1 == -1) {
                                aux1 = i;
                            } else {
                                aux2 = i;
                            }
                        }
                    }
                });

                meioX = linhas[linhaSelecionada1].calcula_meio().x;
                meioY = linhas[linhaSelecionada1].calcula_meio().y;
                
                linhas[linhaSelecionada1].xInicial += NovoPx - meioX;
                linhas[linhaSelecionada1].yInicial += NovoPy - meioY;
                linhas[linhaSelecionada1].xFinal += NovoPx - meioX;
                linhas[linhaSelecionada1].yFinal += NovoPy - meioY;

                if (aux1 != -1) {
                    if (linhas[aux1].isInicial) {
                        linhas[aux1].xInicial = linhas[linhaSelecionada1].xFinal;
                        linhas[aux1].yInicial = linhas[linhaSelecionada1].yFinal;
                        linhas[aux1].isInicial = 0;
                    } else {
                        linhas[aux1].xFinal = linhas[linhaSelecionada1].xInicial;
                        linhas[aux1].yFinal = linhas[linhaSelecionada1].yInicial;
                        linhas[aux1].isFinal = 0;
                    }
                }

                if (aux2 != -1) {
                    if (linhas[aux2].isInicial) {
                        linhas[aux2].xInicial = linhas[linhaSelecionada1].xFinal;
                        linhas[aux2].yInicial = linhas[linhaSelecionada1].yFinal;
                        linhas[aux2].isInicial = 0;
                    } else {
                        linhas[aux2].xFinal = linhas[linhaSelecionada1].xInicial;
                        linhas[aux2].yFinal = linhas[linhaSelecionada1].yInicial;
                        linhas[aux2].isFinal = 0;
                    }

                }
            }

            if(linhaSelecionada2 != -1) {
                if(linhas[linhaSelecionada2].isInicial) {
                    linhas[linhaSelecionada2].xInicial = NovoPx;
                    linhas[linhaSelecionada2].yInicial = NovoPy;
                } else {
                    linhas[linhaSelecionada2].xFinal = NovoPx;
                    linhas[linhaSelecionada2].yFinal = NovoPy;
                }
            }
            desenha_tudo(linhas);
        }
    });

});

canvas.addEventListener("contextmenu", (event) => {
    event.preventDefault(); // impede o menu de contexto aparecer
    const px = event.clientX - canvas.offsetLeft;
    const py = event.clientY - canvas.offsetTop;
    let i = 0;

    while(i < linhas.length) {
        if(distanciaLinha(px, py, linhas[i].xInicial, linhas[i].yInicial, linhas[i].xFinal, linhas[i].yFinal) <= ctx.lineWidth) {
            linhas.splice(i+1, 0, new Linha(px, py, linhas[i].xFinal, linhas[i].yFinal, 0, 0)); 
            linhas.splice(i, 1, new Linha(linhas[i].xInicial, linhas[i].yInicial, px, py, 0, 0));
            desenha_tudo(linhas);
            break;
        }
        i++;
    }
}); 