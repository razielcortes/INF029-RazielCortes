#include "aluno.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//teste github


/*GERAL*/

int menuGeral() {
  int opcao;
  printf("PROJETO ESCOLA\n");
  printf("0-SAIR\n");
  printf("1-ALUNO\n");
  printf("2-PROFESSOR\n");
  printf("3-DISCIPLINA\n");
  printf("4-RELATORIOS\n");
  scanf("%d", &opcao);

  return opcao;
}

//Só é utilizada para verificar data de nascimento, mas tentei criar algo mais universal
int validar_data(int dia, int mes, int ano)
{
  struct tm tm = {0};
      tm.tm_mday = dia;
      tm.tm_mon = mes - 1; // tm_mon é de 0 a 11
      tm.tm_year = ano - 1900; // tm_year é o número de anos desde 1900

      // Tenta converter a estrutura tm em um tempo calendário
      time_t t = mktime(&tm);

      // Verifica se a data foi ajustada corretamente
      if (tm.tm_mday != dia || tm.tm_mon != mes - 1 || tm.tm_year != ano - 1900) {
          return DATA_INVALIDA; // Data inválida
      }
      return DATA_VALIDA; // Data válida
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*GERAL*/



int menuAluno() {
  int opcao;
  printf("0-VOLTAR\n");
  printf("1-CADASTRAR ALUNO\n");
  printf("2-LISTAR ALUNO\n");
  printf("3-ATUALIZAR ALUNO\n");
  printf("4-DELETAR ALUNO\n");
  scanf("%d", &opcao);

  return opcao;
}

int cadastrarAluno(int qtdAluno, Aluno listarAluno[]) {
  printf("CADASTRAR ALUNO\n");
  if (qtdAluno == TAM_ALUNO) {
    return LISTA_ALUNO_CHEIA;
  } else {
    int matricula;
    char cpf[15];
    int diaNascimento, mesNascimento, anoNascimento;
    int diaAtual, mesAtual, anoAtual;
    char nome[20];
    int idade;
    char sexo;
    int i;
    int matriculaaluno;



    printf("DIGITE SEU NOME:\n");
    getchar();
    fgets(nome, sizeof(nome), stdin);

    // Remover a nova linha ao final da string nome, se presente
    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n') {
      nome[len - 1] = '\0';
    }

    //recebe a matricula e já verifica se é válida
    int achoualuno = 0;
    while (achoualuno == 0) {
      printf("DIGITE A MATRICULA DO ALUNO:\n");
      int retorno_verificador_aluno =
          verificarAluno(qtdAluno, listarAluno, &matriculaaluno);

      if (retorno_verificador_aluno == ALUNO_EXISTE) {
        printf("Já existe um aluno com essa matrícula\n");
      } else if (retorno_verificador_aluno == MATRICULA_ALUNO_INEXISTENTE) {
        printf("Matricula do aluno é válida\n");
        achoualuno = 1;
      }else if(retorno_verificador_aluno!= ALUNO_EXISTE && retorno_verificador_aluno!= MATRICULA_ALUNO_INEXISTENTE){
        printf("MATRICULA INVALIDA\n");
      }
    }
getchar();
    int cpfvalido = 0;
    while(cpfvalido == 0){
      printf("DIGITE O CPF DO ALUNO:(formato: 000.000.000-00)\n");
      int retorno_cpf = verificarCpfaluno(qtdAluno, listarAluno, cpf);
      

      if (retorno_cpf == CPF_ALUNO_JA_CADASTRADO) {
        printf("JA EXISTE UM ALUNO COM ESSE CPF\n");
      }else if(retorno_cpf == CPF_ALUNO_INVALIDO)
      {
        printf("CPF DO ALUNO INVALIDO\n");
      }else if (retorno_cpf== CPF_ALUNO_VALIDO)
      {
        printf("CPF DO ALUNO É VALIDO\n");
        cpfvalido = 1;
      }
    }

    printf("DIGITE O SEXO (M/F):\n");
    scanf(" %c", &sexo);
    sexo = toupper(sexo);

    int data_certa =0;
    while(data_certa == 0)
    {
      printf("DIGITE SUA DATA DE NASCIMENTO (formato: DD/MM/AAAA):\n");
      scanf("%d/%d/%d", &diaNascimento, &mesNascimento, &anoNascimento);
      int retorno_data = validar_data(diaNascimento, mesNascimento, anoNascimento);
      if(retorno_data == DATA_VALIDA)
      { 
        printf("Data válida!\n");
        data_certa = 1;
      }
      else if(retorno_data == DATA_INVALIDA)
        printf("Data inválida!\n");
    }
    // Entrada da data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Extrai dia, mês e ano
    diaAtual = tm.tm_mday;
    mesAtual = tm.tm_mon + 1; // tm_mon é de 0 a 11, então adicionamos 1
    anoAtual = tm.tm_year + 1900; // tm_year é o número de anos desde 1900

    // Calcular idade
    idade = anoAtual - anoNascimento;


    if (sexo == 'F' || sexo == 'M') {

      // nome do aluno
      strcpy(listarAluno[qtdAluno].nome, nome);

      // sexo do aluno
      listarAluno[qtdAluno].sexo = sexo;

      // matricula do aluno
      listarAluno[qtdAluno].matricula = matriculaaluno;

      // cpf do aluno
      strcpy(listarAluno[qtdAluno].cpf, cpf);

      // data de nascimento do aluno
      listarAluno[qtdAluno].diaNascimento = diaNascimento;
      listarAluno[qtdAluno].mesNascimento = mesNascimento;
      listarAluno[qtdAluno].anoNascimento = anoNascimento;

      // cadastrar idade
      listarAluno[qtdAluno].idade = idade;

      // data que o aluno entrou
      listarAluno[qtdAluno].diaAtual = diaAtual;
      listarAluno[qtdAluno].mesAtual = mesAtual;
      listarAluno[qtdAluno].anoAtual = anoAtual;

      // marca se o aluno está cadastrado ou não, serve para fazer exclusão
      // logica
      listarAluno[qtdAluno].ativo = 1;

      return CAD_ALUNO_SUCESSO;
    }
    else{
      return SEXO_ALUNO_INVALIDO;

    }
  }
}

int verificarAluno(int qtdAluno, Aluno listarAluno[], int *matriculaaluno) {
  scanf("%i", matriculaaluno);
  if (*matriculaaluno < 0) {
    return MATRICULA_ALUNO_INVALIDA;
  }
  int achoualuno = 0;
  for (int i = 0; i < qtdAluno; i++) {
    if (*matriculaaluno == listarAluno[i].matricula) {
      achoualuno = 1;
    }
  }
  if (achoualuno == 1)
    return ALUNO_EXISTE;
  else
    return MATRICULA_ALUNO_INEXISTENTE;
}

int verificarCpfaluno(int qtdAluno, Aluno listarAluno[], char *cpf){
  if (fgets(cpf, 15, stdin) == NULL) {
    printf("Erro ao ler o CPF.\n");
    return CPF_ALUNO_INVALIDO;
  }

  // Remove o caractere de nova linha se presente
  cpf[strcspn(cpf, "\n")] = 0;

  size_t tamanho_cpf = strlen(cpf);
    if (tamanho_cpf != 14) {
      printf("ESTE CPF TEM TAMANHO INVALIDO\n");
      printf("SEU TAMANHO DE CPF ATUAL É ESSE:%zu\n DIGITE CORRETAMENTE:\n", tamanho_cpf);
      return CPF_ALUNO_INVALIDO;
    }
    // Verifica se os caracteres estão nas posições corretas
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf[i] != '.') {
                printf("Erro na posição %d: esperado '.', encontrado '%c'\n", i, cpf[i]);
                return CPF_ALUNO_INVALIDO;
            }
        } else if (i == 11) {
            if (cpf[i] != '-') {
                printf("Erro na posição %d: esperado '-', encontrado '%c'\n", i, cpf[i]);
                return CPF_ALUNO_INVALIDO;
            }
        } else {
            if (!isdigit(cpf[i])) {
                printf("Erro na posição %d: esperado dígito, encontrado '%c'\n", i, cpf[i]);
                return CPF_ALUNO_INVALIDO;
            }
        }
    }
  // Verificar se o CPF já está cadastrado
    for (int i = 0; i < qtdAluno; i++) {
      if (strcmp(listarAluno[i].cpf, cpf) == 0) {
        printf("Este CPF já está cadastrado no sistema\n");
        return CPF_ALUNO_JA_CADASTRADO;
      }
    }

    return CPF_ALUNO_VALIDO;
}

void listarrAlunos(int qtdAluno, Aluno listarAluno[]) {
  if (qtdAluno == 0) {
    printf("LISTA DE ALUNO VAZIA\n");
  } else {
    for (int i = 0; i < qtdAluno; i++) {
      if (listarAluno[i].ativo == 1) {
        printf("ALUNO %d:\n", i);
        printf("SEXO: %c\n", listarAluno[i].sexo);
        printf("MATRICULA: %d\n", listarAluno[i].matricula);
        printf("NOME:%s\n", listarAluno[i].nome);
        printf("CPF: %s\n", listarAluno[i].cpf);
        printf("DATA DE NASCIMENTO: %d/%d/%d\n", listarAluno[i].diaNascimento,
              listarAluno[i].mesNascimento, listarAluno[i].anoNascimento);
        printf("IDADE: %d\n", listarAluno[i].idade);
        printf("DATA DE CADASTRO: %d/%d/%d\n", listarAluno[i].diaAtual,
              listarAluno[i].mesAtual, listarAluno[i].anoAtual);
        printf("\n");
      }
    }
  }
}

int atualizarAluno(int qtdAluno, Aluno listarAluno[]) {
  printf("ATUALIZAR ALUNO\n");
  int matricula;
  int achoualuno = 0;
  while (achoualuno == 0)
  {
    printf("DIGITE A MATRICULA DO ALUNO:\n");
    int retorno_verificador_aluno =
        verificarAluno(qtdAluno, listarAluno, &matricula);
    if(retorno_verificador_aluno == ALUNO_EXISTE){
      for (int i = 0; i < qtdAluno; i++)
      {
        if (matricula == listarAluno[i].matricula && listarAluno[i].ativo) {
          // atualização
          int novaMatricula;
          char novoNome[20];
          int newdiaNascimento;
          int newanoNascimento;
          int newmesNascimento;
          char newSexo;
          char novoCpf[15];

          int achoualuno = 0;
          while (achoualuno == 0)
          {
            printf("DIGITE A NOVA MATRICULA DO ALUNO:\n");
            int retorno_verificador_aluno =
                verificarAluno(qtdAluno, listarAluno, &novaMatricula);

            if (retorno_verificador_aluno == ALUNO_EXISTE) {
              printf("Já existe um aluno com essa matrícula\n");

            } else if (retorno_verificador_aluno == MATRICULA_ALUNO_INEXISTENTE) {
              printf("Matricula do aluno é válida\n");
              achoualuno = 1;
            }
          }

          printf("NOME:\n");
          getchar();
          fgets(novoNome, sizeof(novoNome), stdin);

          size_t len = strlen(novoNome);
          if (len > 0 && novoNome[len - 1] == '\n') {
            novoNome[len - 1] = '\0';
          }

          int cpfvalido = 0;
          while(cpfvalido == 0)
          {
            printf("DIGITE O NOVO CPF DO ALUNO:(formato: 000.000.000-00)\n");
            int retorno_cpf = verificarCpfaluno(qtdAluno, listarAluno, novoCpf);

            if (retorno_cpf == CPF_ALUNO_JA_CADASTRADO) {
              printf("Já existe um aluno com esse CPF\n");
            }

            else if(retorno_cpf == CPF_ALUNO_INVALIDO)
            {
              printf("CPF do aluno inválido\n");
            }

            else if (retorno_cpf== CPF_ALUNO_VALIDO)
            {
              printf("CPF do aluno é válida\n");
              cpfvalido = 1;
            }
          }

          int data_certa = 0;
          while(data_certa == 0)
          {
            printf("DIGITE SUA DATA DE NASCIMENTO NOVA(formato: DD/MM/AAAA):\n");
            scanf("%d/%d/%d", &newdiaNascimento, &newmesNascimento, &newanoNascimento);
            int retorno_data = validar_data(newdiaNascimento, newmesNascimento, newanoNascimento);
            if(retorno_data == DATA_VALIDA)
            { 
              printf("Data válida!\n");
              data_certa = 1;
            }
            else if(retorno_data == DATA_INVALIDA)
              printf("Data inválida!\n");
          }

          printf("SEXO (M/F):\n");
          scanf(" %c", &newSexo);

          if (novaMatricula < 0) {
            return MATRICULA_ALUNO_INVALIDA;
          }
          listarAluno[i].matricula = novaMatricula;
          strcpy(listarAluno[i].nome, novoNome);
          strcpy(listarAluno[i].cpf, novoCpf);
          listarAluno[i].diaNascimento = newdiaNascimento;
          listarAluno[i].mesNascimento = newmesNascimento;
          listarAluno[i].anoNascimento = newanoNascimento;
          listarAluno[i].sexo = newSexo;
          achoualuno = 1;
          break;
        }
      }
    }
    else if (retorno_verificador_aluno == MATRICULA_ALUNO_INEXISTENTE) {
      printf("Matricula do aluno é válida\n");
      }
    if (achoualuno) {
      return ATUALIZADO_ALUNO_SUCESSO;
    } else {
      return MATRICULA_ALUNO_INEXISTENTE;
    }
  }
}

int excluirAluno(int qtdAluno, Aluno listarAluno[])
{
  printf("DELETAR ALUNO\n");
  int matricula;
  int achoualuno = 0;
  while (achoualuno == 0)
  {
    printf("DIGITE A MATRICULA DO ALUNO:\n");
    int retorno_verificador_aluno = verificarAluno(qtdAluno, listarAluno, &matricula);
    if (retorno_verificador_aluno == ALUNO_EXISTE) {
      for (int i = 0; i < qtdAluno; i++)
      {
        if (matricula == listarAluno[i].matricula) {

          // exclusão logica
          listarAluno[i].ativo = -1;

          for (int j = i; j < qtdAluno - 1; j++) {
            // movendo todos os alunos pra casa anterior
            listarAluno[j].nome[20] = listarAluno[j + 1].nome[20];
            listarAluno[j].cpf[15] = listarAluno[j + 1].cpf[15];
            listarAluno[j].matricula = listarAluno[j + 1].matricula;
            listarAluno[j].sexo = listarAluno[j + 1].sexo;
            listarAluno[j].ativo = listarAluno[j + 1].ativo;

            // movendo as datas de cadastro e de nascimento
            // nascimento
            listarAluno[j].diaNascimento = listarAluno[j + 1].diaNascimento;
            listarAluno[j].mesNascimento = listarAluno[j + 1].mesNascimento;
            listarAluno[j].anoNascimento = listarAluno[j + 1].anoNascimento;
            // cadastro
            listarAluno[j].diaAtual = listarAluno[j + 1].diaAtual;
            listarAluno[j].mesAtual = listarAluno[j + 1].mesAtual;
            listarAluno[j].anoAtual = listarAluno[j + 1].anoAtual;
          }

          achoualuno = 1;
          break;
        }
      }
    }
    else if(retorno_verificador_aluno == MATRICULA_ALUNO_INEXISTENTE) {
      return MATRICULA_ALUNO_INEXISTENTE;
    }
  }
  if (achoualuno) {
    return EXCLUSAO_ALUNO_SUCESSO;
  } else {
    return MATRICULA_ALUNO_INEXISTENTE;
  }
}
