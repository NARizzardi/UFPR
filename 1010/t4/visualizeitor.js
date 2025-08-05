let grade = [];
let alunos = [];

carregaXML();
validaInput();
preencheGrade(grade);

class Aluno {
  constructor(matricula, nome) {
    this.matricula = matricula;
    this.nome = nome;
    this.inscricoes = [];
  }

  inscreverNaMateria(materia) {
    const inscricao = new Inscricao(this, materia);
    this.inscricoes.push(inscricao);
    materia.adicionarInscricao(inscricao);
  }
}

class Materia {
  constructor(codigo, nome, tipo) {
    this.codigo = codigo;
    this.nome = nome;
    this.tipo = tipo;
    this.inscricoes = [];
  }

  adicionarInscricao(inscricao) {
    this.inscricoes.push(inscricao);
  }
}

class Inscricao {
  constructor(aluno, materia, nota, frequencia, periodo, ano, situacao) {
    this.aluno = aluno;
    this.materia = materia;
    this.nota = nota;
    this.frequencia = frequencia;
    this.periodo = periodo;
    this.ano = ano;
    this.situacao = situacao;
  }

}

function validaInput() {
  const input = document.getElementById('matricula');
  const fixedText = "GRR";

  input.addEventListener('keydown', function (event) {
    const cursorPosition = this.selectionStart;
  });

  input.addEventListener('input', function () {
    const enteredText = this.value;

    if (!enteredText.startsWith(fixedText)) {
      this.value = fixedText;
    }

    if (this.value.length > 11) {
      this.value = this.value.slice(0, 11);
    }
  });
}

function carregaXML() {
  // Cria um objeto XMLHttpRequest
  let xhttp = new XMLHttpRequest();

  // Define a função de callback para quando a requisição estiver pronta
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      // O arquivo XML foi carregado com sucesso 
      let xmlDoc = this.responseXML; // Obtém o documento XML

      // Agora você pode acessar e manipular os elementos XML
      let blocos = xmlDoc.getElementsByTagName("ALUNO");

      for (let i = 0; i < blocos.length; i++) {
        let aluno = new Aluno(blocos[i].getElementsByTagName("MATR_ALUNO")[0].textContent, blocos[i].getElementsByTagName("NOME_ALUNO")[0].textContent);
        let materia = new Materia(blocos[i].getElementsByTagName("COD_ATIV_CURRIC")[0].textContent, blocos[i].getElementsByTagName("NOME_ATIV_CURRIC")[0].textContent, blocos[i].getElementsByTagName("DESCR_ESTRUTURA")[0].textContent);
        let inscricao = new Inscricao(aluno, materia, blocos[i].getElementsByTagName("MEDIA_FINAL")[0].textContent, blocos[i].getElementsByTagName("FREQUENCIA")[0].textContent, blocos[i].getElementsByTagName("PERIODO")[0].textContent, blocos[i].getElementsByTagName("ANO")[0].textContent, blocos[i].getElementsByTagName("SIGLA")[0].textContent);
        aluno.inscricoes.push(inscricao);
        materia.adicionarInscricao(inscricao);

        let indice = buscarAluno(aluno.matricula, alunos);
        if (indice == -1) {
          alunos.push(aluno);
        } else {
          alunos[indice].inscricoes.push(inscricao);
        }

      }
    }
  };
  // Abre a requisição para o arquivo XML
  xhttp.open("GET", "./alunos.xml", true);

  // Define o tipo de resposta como XML
  xhttp.responseType = "document";

  // Envie a requisição
  xhttp.send();
}

function preencheGrade(grade) {
  let tabela = document.getElementsByTagName('tbody')[0];
  let linhas = tabela.getElementsByTagName('tr');

  for (let i = 0; i < linhas.length; i++) {
    let colunas = linhas[i].getElementsByTagName('td');
    for (let j = 0; j < colunas.length; j++) {
      grade.push(colunas[j].id);
    }
  }
}

function selecionaOPT(aluno, id) {
  const nmr = parseInt(id.charAt(id.length - 1));
  let qtde = 0;
  let indice = -1;
  for (let i = 0; i < aluno.inscricoes.length; i++) {
    if (aluno.inscricoes[i].materia.tipo == "Optativas") {
      indice = i;
      qtde++;
      if (qtde == nmr) {
        break;
      }
    }
  }
  if (qtde < nmr) {
    indice = -1;
  }
  return indice;
}

function isOPT(tipo, materia) {
  if ((tipo == "Optativas") && (materia.startsWith("OPT"))) {
    return true;
  }
  return false;
}

function isTG(tipo, materia) {
  if (((tipo == "Trabalho de Graduação I") && (materia == "TG1")) || ((tipo == "Trabalho de Graduação II") && (materia == "TG2"))) {
    return true;
  }
  return false;
}

function historicoMateria(aluno, codigo) {
  let htmlTabelaDados = '';
  if (ultimaOcorrencia(aluno, codigo) != -1) {
    aluno.inscricoes.forEach(function (inscricao) {
      if ((inscricao.materia.codigo == codigo) || isTG(inscricao.materia.tipo, codigo) || isOPT(inscricao.materia.tipo, codigo)) {
        htmlTabelaDados += '<tr>' +
          '<td>' + inscricao.materia.codigo + '</td>' +
          '<td>' + inscricao.materia.nome + '</td>' +
          '<td>' + inscricao.ano + '</td>' +
          '<td>' + inscricao.periodo + '</td>' +
          '<td>' + inscricao.frequencia.slice(0, 5) + '%</td>' +
          '<td>' + inscricao.situacao + '</td>' +
          '<td>' + inscricao.nota + '</td>' +
          '</tr>';

        $('#tabelaHistorico tbody').html(htmlTabelaDados);
      }
    });
  } else {
    htmlTabelaDados = 'Nenhum registro encontrado';
    $('#tabelaHistorico tbody').html(htmlTabelaDados);
  }
}

function ultimaCursada(aluno, codigo) {
  let htmlTabelaDados = '';
  if (codigo.startsWith("OPT")) {
    indiceInscricao = selecionaOPT(aluno, codigo);
  } else {
    indiceInscricao = ultimaOcorrencia(aluno, codigo);
  }
  if (indiceInscricao != -1) {
    htmlTabelaDados += '<tr>' +
      '<td>' + aluno.inscricoes[indiceInscricao].materia.codigo + '</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].materia.nome + '</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].ano + '</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].periodo + '</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].frequencia.slice(0, 5) + '%</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].situacao + '</td>' +
      '<td>' + aluno.inscricoes[indiceInscricao].nota + '</td>' +
      '</tr>';
  } else {
    htmlTabelaDados = 'Nenhum registro encontrado';
  }

  $('#tabelaHistorico tbody').html(htmlTabelaDados);
}

function carregaHistoricos(aluno) {
  let cells = document.querySelectorAll('.tableCell');

  cells.forEach(function (cell) {
    cell.addEventListener('click', function () {
      let cellId = this.id;
      openModal();
      ultimaCursada(aluno, cellId);
    });

    cell.addEventListener('contextmenu', function (event) {
      event.preventDefault();
      let cellId = this.id;
      openModal();
      historicoMateria(aluno, cellId)
    });
  });
}

function busca() {
  const matricula = document.getElementById('matricula').value;
  const indice = buscarAluno(matricula, alunos);

  if (indice != -1) {
    pintarGrade(alunos[indice], grade);
    carregaHistoricos(alunos[indice]);
  } else {
    alert('Aluno não encontrado!');
  }

}

function ultimaOcorrencia(aluno, materia) {
  let indice = -1;
  for (let i = 0; i < aluno.inscricoes.length; i++) {
    if ((aluno.inscricoes[i].materia.codigo == materia) || (isTG(aluno.inscricoes[i].materia.tipo, materia)) || (isOPT(aluno.inscricoes[i].materia.tipo, materia))) {
      indice = i;
    }
  }
  return indice;
}

function pintarGrade(aluno, grade) {
  let indice;
  grade.forEach(nomeAula => {
    if (nomeAula.startsWith("OPT")) {
      indice = selecionaOPT(aluno, nomeAula);
    } else {
      indice = ultimaOcorrencia(aluno, nomeAula);
    }
    let cell = document.getElementById(nomeAula);

    if (indice != -1) {
      if (aluno.inscricoes[indice].situacao == "Aprovado") {
        cell.className = 'verde tableCell';
      } else if ((aluno.inscricoes[indice].situacao == "Reprovado") || (aluno.inscricoes[indice].situacao == "Repr. Freq")) {
        cell.className = 'vermelho tableCell';
      } else if (aluno.inscricoes[indice].situacao == "Matricula") {
        cell.className = 'azul tableCell';
      } else if ((aluno.inscricoes[indice].situacao == "Equivale")) {
        cell.className = 'amarelo tableCell';
      } else if ((aluno.inscricoes[indice].situacao == "Tr. Total") || (aluno.inscricoes[indice].situacao == "Cancelado")) {
        cell.className = 'preto tableCell';
      }
    } else {
      cell.className = 'branco tableCell';
    }
  });
}

function buscarAluno(matricula, alunos) {
  for (var i = 0; i < alunos.length; i++) {
    if (alunos[i].matricula == matricula) {
      return i;
    }
  }
  return -1;
}

function listaInscricoes(aluno) {
  for (let i = 0; i < aluno.inscricoes.length; i++) {
    console.log(aluno.inscricoes[i].materia.nome);
  }
}

function openModal() {
  var modal = document.getElementById("modal");
  modal.style.display = "block";
}

function closeModal() {
  var modal = document.getElementById("modal");
  modal.style.display = "none";
}
function voltar(){
  window.location.href = "../index.html";
}