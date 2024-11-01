#include "professor.h"
#include "aluno.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//

int menuProfessor() {
  int opcao;
  printf("0-VOLTAR\n");
  printf("1-CADASTRAR PROFESSOR\n");
  printf("2-LISTAR PROFESSOR\n");
  printf("3-ATUALIZAR PROFESSOR\n");
  printf("4-DELETAR PROFESSOR\n");
  scanf("%d", &opcao);

  return opcao;
}

int verificarCpfprofessor(int qtdprofessor, Professor listarProfessor[], char *cpf){
    getchar();
    scanf("%14s", cpf);

    size_t tamanho_cpf = strlen(cpf);
    // Verifica se o comprimento do CPF é 14
    if (tamanho_cpf != 14) {
      printf("Este CPF tem tamanho inválido\n");
      printf("seu tamanho de CPF atual é esse:%zu\nDigite corretamente\n", tamanho_cpf);
      return CPF_PROFESSOR_INVALIDO;
    }
    // Verifica se os caracteres estão nas posições corretas
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf[i] != '.') {
                printf("Erro na posição %d: esperado '.', encontrado '%c'\n", i, cpf[i]);
                return CPF_PROFESSOR_INVALIDO;
            }
        } else if (i == 11) {
            if (cpf[i] != '-') {
                printf("Erro na posição %d: esperado '-', encontrado '%c'\n", i, cpf[i]);
                return CPF_PROFESSOR_INVALIDO;
            }
        } else {
            if (!isdigit(cpf[i])) {
                printf("Erro na posição %d: esperado dígito, encontrado '%c'\n", i, cpf[i]);
                return CPF_PROFESSOR_INVALIDO;
            }
        }
    }
  // Verificar se o CPF já está cadastrado
    for (int i = 0; i < qtdprofessor; i++)
    {
      if (strcmp(listarProfessor[i].cpf, cpf) == 0)
      {
        printf("Este CPF já está cadastrado no sistema\n");
        return CPF_PROFESSOR_JA_CADASTRADO;
      }
    }
  return CPF_PROFESSOR_VALIDO;
}

int verificarProfessor(int qtdprofessor, Professor listarProfessor[], int *matriculaprof)
{
  scanf("%i", matriculaprof);
  if (*matriculaprof < 0) {
    return MATRICULA_PROFESSOR_INVALIDA;
  }
  int achouprof = 0;
  for (int i = 0; i < qtdprofessor; i++) {
    if (*matriculaprof == listarProfessor[i].matricula) {
      achouprof = 1;
    }
  }
  if (achouprof == 1)
    return PROFESSOR_EXISTE;
  else
    return MATRICULA_PROFESSOR_INEXISTENTE;
}

int cadastrarProfessor(int qtdProfessor, Professor listarProfessor[]) {
  printf("CADASTRAR PROFESSOR\n");
  if (qtdProfessor == TAM_PROFESSOR) {
    return LISTA_PROFESSOR_CHEIA;
  } else {
    int matriculaprof;
    char cpf[15];
    int diaNascimento, mesNascimento, anoNascimento;
    int diaAtual, mesAtual, anoAtual;
    char nome[20];
    int idade;
    char sexo;
    int i;

    printf("DIGITE O NOME DO PROFESSOR:\n");
    getchar();
    fgets(nome, sizeof(nome), stdin);

    // Remover a nova linha ao final da string nome, se presente
    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n') {
      nome[len - 1] = '\0';
    }

    // verificando se o professor existe
    int achouprof = 0;
    while (achouprof == 0)
    {
      printf("DIGITE A MATRICULA DO PROFESSOR:\n");
      int retornoverificarprof = verificarProfessor(qtdProfessor, listarProfessor, &matriculaprof);
      if (retornoverificarprof == PROFESSOR_EXISTE) {
        printf("Matricula do professor é inválida pois já existe\n");
      } else if (retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE) {
        printf("Matricula do professor é válida\n");
        achouprof = 1;
      }
    }

    printf("DIGITE O SEXO (M/F):\n");
    scanf(" %c", &sexo);
    sexo = toupper(sexo);

    int cpfvalido = 0;
    while(cpfvalido == 0){
      printf("DIGITE O CPF DO PROFESSOR:(formato: 000.000.000-00)\n");
      int retorno_cpf = verificarCpfprofessor(qtdProfessor, listarProfessor, cpf);

      if (retorno_cpf == CPF_PROFESSOR_JA_CADASTRADO) {
        printf("Já existe um professor com esse CPF\n");
      }

      else if(retorno_cpf == CPF_PROFESSOR_INVALIDO)
      {
        printf("CPF do professor inválido\n");
      }

      else if (retorno_cpf== CPF_PROFESSOR_VALIDO)
      {
        printf("CPF do professor é válida\n");
        cpfvalido = 1;
      }
    }

    int data_certa =0;
    while(data_certa == 0)
    {
      printf("DIGITE A DATA DE NASCIMENTO (formato: DD/MM/AAAA):\n");
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

    if (matriculaprof < 0) {
      return MATRICULA_PROFESSOR_INVALIDA;
    } else {
      if (sexo == 'F' || sexo == 'M') {

        // nome do professor
        strcpy(listarProfessor[qtdProfessor].nome, nome);

        // sexo do professor
        listarProfessor[qtdProfessor].sexo = sexo;

        // matricula do professor
        listarProfessor[qtdProfessor].matricula = matriculaprof;

        // cpf do professor
        strcpy(listarProfessor[qtdProfessor].cpf, cpf);

        // data de nascimento do professor
        listarProfessor[qtdProfessor].diaNascimento = diaNascimento;
        listarProfessor[qtdProfessor].mesNascimento = mesNascimento;
        listarProfessor[qtdProfessor].anoNascimento = anoNascimento;

        // cadastrar idade
        listarProfessor[qtdProfessor].idade = idade;

        // data que o professor entrou
        listarProfessor[qtdProfessor].diaAtual = diaAtual;
        listarProfessor[qtdProfessor].mesAtual = mesAtual;
        listarProfessor[qtdProfessor].anoAtual = anoAtual;

        // marca se o professor está cadastrado ou não, serve para fazer
        // exclusão logica
        listarProfessor[qtdProfessor].ativo = 1;

        return CAD_PROFESSOR_SUCESSO;
      } else {
        return SEXO_PROFESSOR_INVALIDO;
      }
    }
  }
}

void listarrProfessor(int qtdProfessor, Professor listarProfessor[]) {
  if (qtdProfessor == 0) {
    printf("LISTA DE PROFESSORES VAZIA\n");
  } else {
    for (int i = 0; i < qtdProfessor; i++) {
      if (listarProfessor[i].ativo == 1) {
        printf("PROFESSOR %d:\n", i);
        printf("SEXO: %c\n", listarProfessor[i].sexo);
        printf("MATRICULA: %d\n", listarProfessor[i].matricula);
        printf("NOME:%s\n", listarProfessor[i].nome);
        printf("CPF: %s\n", listarProfessor[i].cpf);
        printf(
            "DATA DE NASCIMENTO: %d/%d/%d\n", listarProfessor[i].diaNascimento,
            listarProfessor[i].mesNascimento, listarProfessor[i].anoNascimento);
        printf("IDADE: %d\n", listarProfessor[i].idade);
        printf("DATA DE CADASTRO: %d/%d/%d\n", listarProfessor[i].diaAtual,
               listarProfessor[i].mesAtual, listarProfessor[i].anoAtual);
        printf("\n");
      }
    }
  }
}

int atualizarProfessor(int qtdProfessor, Professor listarProfessor[])
{
  printf("ATUALIZAR PROFESSOR\n");
  int matriculaprof;

  int achou = 0;
  if (matriculaprof < 0) {
    return MATRICULA_PROFESSOR_INVALIDA;
  }
  // verificando se o professor existe
  int achouprof = 0;
  while (achouprof == 0)
  {
    printf("DIGITE A MATRICULA DO PROFESSOR:\n");
    int retornoverificarprof = verificarProfessor(qtdProfessor, listarProfessor, &matriculaprof);
    if (retornoverificarprof == PROFESSOR_EXISTE)
    {
      printf("Matricula do professor é válida\n");
      for (int i = 0; i < qtdProfessor; i++)
      {
        if (matriculaprof == listarProfessor[i].matricula && listarProfessor[i].ativo)
        {
          // atualização
          int novaMatricula;
          char novoNome[20];
          int newdiaNascimento;
          int newanoNascimento;
          int newmesNascimento;
          char newSexo;

          // verificando se o professor existe
          int achouprofnov = 0;
          while (achouprofnov == 0) {
            printf("DIGITE A NOVA MATRICULA DO PROFESSOR:\n");
            int retornoverificarprof = verificarProfessor(qtdProfessor, listarProfessor, &novaMatricula);
            if (retornoverificarprof == PROFESSOR_EXISTE) {
              printf("Matricula do professor é inválida\n");
            } else if (retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE) {
              printf("Matricula do professor é válida\n");
              achouprofnov = 1;
            }
          }

          printf("NOVO NOME:\n");
          getchar();
          fgets(novoNome, sizeof(novoNome), stdin);

          size_t len = strlen(novoNome);
          if (len > 0 && novoNome[len - 1] == '\n') {
            novoNome[len - 1] = '\0';
          }

          int data_certa =0;
          while(data_certa == 0)
          {
            printf("DIGITE A DATA DE NASCIMENTO (formato: DD/MM/AAAA):\n");
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

          printf("NOVO SEXO:\n");
          scanf(" %c", &newSexo);


          listarProfessor[i].matricula = novaMatricula;
          strcpy(listarProfessor[i].nome, novoNome);
          listarProfessor[i].diaNascimento = newdiaNascimento;
          listarProfessor[i].mesNascimento = newmesNascimento;
          listarProfessor[i].anoNascimento = newanoNascimento;
          listarProfessor[i].sexo = newSexo;
          achouprof = 1;
          break;
        }
      }
    }
    else if (retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE)
    {
      printf("Matricula do professor é inválida\n");
    }
  }
    if (achouprof) {
      return ATUALIZADO_PROFESSOR_SUCESSO;

    } else {
      return MATRICULA_PROFESSOR_INEXISTENTE;
    }
}

int excluirProfessor(int qtdProfessor, Professor listarProfessor[]) {
  printf("DELETAR PROFESSOR\n");

  int matriculaprof = 0;
  int achouprof = 0;
  while (achouprof == 0)
  {
    printf("DIGITE A MATRICULA DO PROFESSOR:\n");
    int retornoverificarprof = verificarProfessor(qtdProfessor, listarProfessor, &matriculaprof);
    if (retornoverificarprof == PROFESSOR_EXISTE)
    {
      printf("Matricula do professor é válida\n");
      for (int i = 0; i < qtdProfessor; i++)
      {
        if (matriculaprof == listarProfessor[i].matricula) {

          // exclusão logica
          listarProfessor[i].ativo = -1;

          for (int j = i; j < qtdProfessor - 1; j++) {
            // movendo todos os professores pra casa anterior
            listarProfessor[j].nome[20] = listarProfessor[j + 1].nome[20];
            listarProfessor[j].cpf[15] = listarProfessor[j + 1].cpf[15];
            listarProfessor[j].matricula = listarProfessor[j + 1].matricula;
            listarProfessor[j].sexo = listarProfessor[j + 1].sexo;
            listarProfessor[j].ativo = listarProfessor[j + 1].ativo;

            // movendo as datas de cadastro e de nascimento
            // nascimento
            listarProfessor[j].diaNascimento =
                listarProfessor[j + 1].diaNascimento;
            listarProfessor[j].mesNascimento =
                listarProfessor[j + 1].mesNascimento;
            listarProfessor[j].anoNascimento =
                listarProfessor[j + 1].anoNascimento;
            // cadastro
            listarProfessor[j].diaAtual = listarProfessor[j + 1].diaAtual;
            listarProfessor[j].mesAtual = listarProfessor[j + 1].mesAtual;
            listarProfessor[j].anoAtual = listarProfessor[j + 1].anoAtual;
          }

          achouprof = 1;
          break;
        }
      }
    }
    else if(retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE)
    {
        printf("Matricula do professor é inválida pois não existe\n");
    }
  }
    if (achouprof) {
      return EXCLUSAO_PROFESSOR_SUCESSO;

    } else {
      return MATRICULA_PROFESSOR_INEXISTENTE;
    }
}