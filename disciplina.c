#include "disciplina.h"
#include "professor.h"
#include "aluno.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//

void zerandoqtdalunosdiscplina(Disciplina listarDisciplina[]) {
  for (int i = 0; i < TAM_DA_DISCIPLINA; i++) {
    listarDisciplina[i].qtdalunosdisciplina = 0;
  }
}

int menuDisciplina() {
  int opcao;
  printf("0-VOLTAR\n");
  printf("1-CADASTRAR DISCIPLINA\n");
  printf("2-LISTAR DISCIPLINA\n");
  printf("3-ATUALIZAR DISCIPLINA\n");
  printf("4-DELETAR DISCIPLINA\n");
  printf("5-CADASTRAR ALUNO NA DISCIPLINA\n");
  scanf("%d", &opcao);

  return opcao;
}

int cadastrarDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]) {
  printf("CADASTRAR DISCIPLINA\n");
  if (qtdDisciplina == TAM_DISCIPLINA) {
    return LISTA_DISCIPLINA_CHEIA;
  } else {
    int coddisciplina;
    int coddisciplinavalido;
    int diaAtual, mesAtual, anoAtual;
    int matriculaprofverificada;
    int matriculaprof;
    char nome[20];

    printf("DIGITE O NOME DA DISCIPLINA:\n");
    getchar();
    fgets(nome, sizeof(nome), stdin);

    // Remover a nova linha ao final da string nome, se presente
    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n') {
      nome[len - 1] = '\0';
    }

    // verificando se a disciplina existe
    int achoudisciplina = 0;
    while (achoudisciplina == 0)
    {
      printf("DIGITE O CODIGO DA MATERIA\n");
      int retorno_verificador_disciplina =
          verificadorDisciplina(qtdDisciplina, listarDisciplina, &coddisciplina);

      if (retorno_verificador_disciplina == DISCIPLINA_EXISTE) {
        printf("Codigo da disciplina inválido\n");
      } else if (retorno_verificador_disciplina == COD_DISCIPLINA_INEXISTENTE) {
        printf("Codigo da disciplina é válido\n");
        achoudisciplina = 1;
      }
    }

    // verificando se o professor existe
    int achouprof = 0;
    while (achouprof == 0) {
      printf("DIGITE A MATRICULA DO PROFESSOR:\n");
      int retornoverificarprof =
          verificarProfessor(qtdProfessor, listarProfessor, &matriculaprof);

      if (retornoverificarprof == PROFESSOR_EXISTE) {
        printf("Matricula do professor é válida\n");
        matriculaprofverificada = matriculaprof;
        achouprof = 1;
      } else if (retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE) {
        printf("Matricula do professor é inválida\n");
      }
    }

    // Entrada da data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Extrai dia, mês e ano
    diaAtual = tm.tm_mday;
    mesAtual = tm.tm_mon + 1; // tm_mon é de 0 a 11, então adicionamos 1
    anoAtual = tm.tm_year + 1900; // tm_year é o número de anos desde 1900

    if (coddisciplina < 0) {
      return COD_DISCIPLINA_INVALIDA;
    } else {
      // nome do aluno
      strcpy(listarDisciplina[qtdDisciplina].nome, nome);

      // cod da materia
      listarDisciplina[qtdDisciplina].coddisciplina = coddisciplina;

      // data que a materia entrou
      listarDisciplina[qtdDisciplina].diaAtual = diaAtual;
      listarDisciplina[qtdDisciplina].mesAtual = mesAtual;
      listarDisciplina[qtdDisciplina].anoAtual = anoAtual;

      //! linkar o professor a materia
      listarDisciplina[qtdDisciplina].matriculaprof = matriculaprofverificada;

      // marca se a disciplina está cadastrada ou não, serve para fazer exclusão
      // logica
      listarDisciplina[qtdDisciplina].ativo = 1;

      return CAD_DISCIPLINA_SUCESSO;
    }
  }
}

int verificadorDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int *coddisciplina)
{
  scanf("%i", coddisciplina);
  if (*coddisciplina < 0) {
    return COD_DISCIPLINA_INVALIDA;
  }

  for (int i = 0; i < qtdDisciplina; i++) {
    if (*coddisciplina == listarDisciplina[i].coddisciplina) {
      return DISCIPLINA_EXISTE;
    }
  }
  return COD_DISCIPLINA_INEXISTENTE;
}

void listarrDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[])
  {
  if (qtdDisciplina == 0) {
    printf("LISTA DE DISCIPLINA VAZIA\n");
  } else {
    for (int i = 0; i < qtdDisciplina; i++) {
      if (listarDisciplina[i].ativo == 1) {
        printf("DISCIPLINA %d:\n", i);
        printf("CODIGO DA DISCIPLINA: %d\n", listarDisciplina[i].coddisciplina);
        printf("NOME:%s\n", listarDisciplina[i].nome);
        for (int j = 0; j < qtdProfessor; j++) {
          if (listarDisciplina[i].matriculaprof ==
              listarProfessor[j].matricula) {
            printf("NOME DO PROFESSOR: %s\n", listarProfessor[j].nome);
          }
        }
        printf("DATA DE CADASTRO: %d/%d/%d\n", listarDisciplina[i].diaAtual,
               listarDisciplina[i].mesAtual, listarDisciplina[i].anoAtual);
        printf("\n");
      }
    }
  }
}

int cadastraralunodisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdAluno, Aluno listarAluno[]) {
  printf("CADASTRAR ALUNO NA DISCIPLINA\n");

  int coddisciplinavalido;
  int coddisciplina;
  // verificando se a disciplina existe
  int achoudisciplina = 0;
  while (achoudisciplina == 0) {
    printf("DIGITE O CODIGO DA MATERIA\n");
    int retorno_verificador_disciplina =
        verificadorDisciplina(qtdDisciplina, listarDisciplina, &coddisciplina);
    if (retorno_verificador_disciplina == DISCIPLINA_EXISTE) {
      printf("Codigo da disciplina é válido\n");
      achoudisciplina = 1;
    } else if (retorno_verificador_disciplina == COD_DISCIPLINA_INEXISTENTE) {
      printf("Codigo da disciplina inválido\n");
    }
  }

  int cadastroMATaluno;
  int matriculaaluno;
  // verificando se o aluno existe
  int achoualuno = 0;
  while (achoualuno == 0) {
    printf("DIGITE A MATRICULA DO ALUNO:\n");
    int retorno_verificador_aluno =
        verificarAluno(qtdAluno, listarAluno, &matriculaaluno);

    if (retorno_verificador_aluno == ALUNO_EXISTE) {
      printf("Matricula do aluno é válida\n");
      cadastroMATaluno = matriculaaluno;
      achoualuno = 1;
    } else if (retorno_verificador_aluno == MATRICULA_ALUNO_INEXISTENTE) {
      printf("Matricula do aluno é inválida\n");
    }
  }

  for (int i = 0; i < qtdDisciplina; i++) {
    if (coddisciplina == listarDisciplina[i].coddisciplina) {
      if (listarDisciplina[i].qtdalunosdisciplina == TAM_DA_DISCIPLINA) {
        return DISCIPLINA_CHEIA;
        break;
      }
      for (int j = 0; j < qtdAluno; j++) {
        if (cadastroMATaluno == listarAluno[j].matricula) {
          listarDisciplina[i].listaALNdisciplina[listarDisciplina[i].qtdalunosdisciplina].matricula = listarAluno[j].matricula;
strcpy(listarDisciplina[i].listaALNdisciplina[listarDisciplina[i].qtdalunosdisciplina].nome,listarAluno[j].nome);
listarDisciplina[i].listaALNdisciplina[listarDisciplina[i].qtdalunosdisciplina].idade=listarAluno[j].idade;
listarDisciplina[i].listaALNdisciplina[listarDisciplina[i].qtdalunosdisciplina].sexo=listarAluno[j].sexo;
listarDisciplina[i].listaALNdisciplina[listarDisciplina[i].qtdalunosdisciplina].qtdDisciplina=listarAluno[j].qtdDisciplina++;
          listarDisciplina[i].qtdalunosdisciplina++;
        }
      }
    }
  }
  return CAD_ALUNO_DISCIPLINA_SUCESSO;
}

int atualizarDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]) {
  printf("ATUALIZAR DISCIPLINAS\n");

  int coddisciplina;
  // verificando se a disciplina existe
  int achoudisciplina = 0;
  while (achoudisciplina == 0) {
    printf("DIGITE O CODIGO DA MATERIA\n");
    int retorno_verificador_disciplina = verificadorDisciplina(qtdDisciplina, listarDisciplina, &coddisciplina);

    if (retorno_verificador_disciplina == DISCIPLINA_EXISTE) {
      printf("Codigo da disciplina é válido\n");
      for (int i = 0; i < qtdDisciplina; i++)
      {
        if (coddisciplina == listarDisciplina[i].coddisciplina &&
            listarDisciplina[i].ativo) {
          // atualização
          int novocodigo;
          char novoNome[20];
          int novamatricula;
          int *matriculaprof;
          printf("DIGITE O NOVO CODIGO:\n");
          scanf("%d", &novocodigo);
          printf("NOVO NOME:\n");
          getchar();
          fgets(novoNome, sizeof(novoNome), stdin);

          size_t len = strlen(novoNome);
          if (len > 0 && novoNome[len - 1] == '\n') {
            novoNome[len - 1] = '\0';
          }

          int coddisciplinavalido;
          // verificando se a disciplina existe
          int achoudisciplina = 0;
          while (achoudisciplina == 0)
          {
            printf("DIGITE O NOVO CODIGO DA MATERIA\n");
            int retorno_verificador_disciplina =
              verificadorDisciplina(qtdDisciplina, listarDisciplina, &coddisciplinavalido);
            if (retorno_verificador_disciplina == DISCIPLINA_EXISTE) {
              printf("Codigo da disciplina inválido pois já existe\n");
            } else if (retorno_verificador_disciplina == COD_DISCIPLINA_INEXISTENTE) {
              printf("Codigo da disciplina é válido\n");
              coddisciplinavalido = coddisciplina;
              achoudisciplina = 1;
            }
          }
          int achouprof = 0;
          while (achouprof == 0) {
            printf("DIGITE A MATRICULA DO NOVO PROFESSOR:\n");
            int retornoverificarprof =
                verificarProfessor(qtdProfessor, listarProfessor, matriculaprof);

            if (retornoverificarprof == PROFESSOR_EXISTE) {
              printf("Matricula do professor é válida\n");
              novamatricula = *matriculaprof;
              achouprof = 1;
            } else if (retornoverificarprof == MATRICULA_PROFESSOR_INEXISTENTE) {
              printf("Matricula do professor é inválida\n");
            }
          }

          listarDisciplina[i].coddisciplina = novocodigo;
          strcpy(listarDisciplina[i].nome, novoNome);
          listarDisciplina[i].matriculaprof = novamatricula;
          achoudisciplina = 1;
          break;
        }
      }

    }
    else if(retorno_verificador_disciplina == COD_DISCIPLINA_INEXISTENTE)
    {
      printf("Codigo da disciplina inválido\n");
    }
  }
  if (achoudisciplina) {
    return ATUALIZADO_DISCIPLINA_SUCESSO;

  } else {
    return COD_DISCIPLINA_INEXISTENTE;
  }
}

int excluirDisciplina(int qtdDisciplina, Disciplina listarDisciplina[])
{
  printf("DELETAR DISCIPLINA\n");
  int coddisciplinavalido;
  int coddisciplina;
  // verificando se a disciplina existe
  int achoudisciplina = 0;
  while (achoudisciplina == 0) {
    printf("DIGITE O CODIGO DA MATERIA\n");
    int retorno_verificador_disciplina =
        verificadorDisciplina(qtdDisciplina, listarDisciplina, &coddisciplina);

    if (retorno_verificador_disciplina == DISCIPLINA_EXISTE) {
      printf("Codigo da disciplina é válido\n");
      for (int i = 0; i < qtdDisciplina; i++)
      {
        if (coddisciplina == listarDisciplina[i].coddisciplina)
        {

          // exclusão logica
          listarDisciplina[i].ativo = -1;
          for (int j = i; j < qtdDisciplina - 1; j++)
          {
            // movendo todas as disciplinas pra casa anterior
            listarDisciplina[j].nome[20] = listarDisciplina[j + 1].nome[20];
            listarDisciplina[j].coddisciplina =
                listarDisciplina[j + 1].coddisciplina;
            listarDisciplina[j].ativo = listarDisciplina[j + 1].ativo;

            // movendo as datas de cadastro
            // cadastro
            listarDisciplina[j].diaAtual = listarDisciplina[j + 1].diaAtual;
            listarDisciplina[j].mesAtual = listarDisciplina[j + 1].mesAtual;
            listarDisciplina[j].anoAtual = listarDisciplina[j + 1].anoAtual;
            // mover a matricula do prof
            listarDisciplina[j].matriculaprof =
                listarDisciplina[j + 1].matriculaprof;
          }
          achoudisciplina = 1;
          break;
        }
      }
    }
    else if (retorno_verificador_disciplina == COD_DISCIPLINA_INEXISTENTE)
    {
      printf("Codigo da disciplina inválido\n");
    }
  }
    if (achoudisciplina) {
      return EXCLUSAO_DISCIPLINA_SUCESSO;

    } else {
      return COD_DISCIPLINA_INEXISTENTE;
    }
  }