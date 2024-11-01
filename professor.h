#ifndef PROF_H
#define PROF_H

/* =======================================================================================
  INICIO PROFESSOR
========================================================================================
*/

#define TAM_PROFESSOR 3
#define CAD_PROFESSOR_SUCESSO -1
#define MATRICULA_PROFESSOR_INVALIDA -2
#define LISTA_PROFESSOR_CHEIA -3
#define ATUALIZADO_PROFESSOR_SUCESSO -4
#define MATRICULA_PROFESSOR_INEXISTENTE -5
#define EXCLUSAO_PROFESSOR_SUCESSO -6
#define SEXO_PROFESSOR_INVALIDO -7
#define MATRICULA_PROFESSOR_INDISPONIVEL -8
#define CPF_PROFESSOR_JA_CADASTRADO -9
#define PROFESSOR_EXISTE -10
#define CPF_PROFESSOR_INVALIDO -11
#define CPF_PROFESSOR_VALIDO -12

typedef struct prof {
  int matricula;
  char cpf[15];
  int idade;
  int diaNascimento, mesNascimento, anoNascimento;
  int diaAtual, mesAtual, anoAtual;
  char nome[20];
  char sexo;
  int ativo;
} Professor;

// prototipos das funções professor
int menuGeral();
int menuAluno();
int cadastrarProfessor(int qtdProfessor, Professor listarProfessor[]);
void listarrProfessor(int qtdProfessor, Professor listarProfessor[]);
int atualizarProfessor(int qtdProfessor, Professor listarProfessor[]);
int excluirProfessor(int qtdProfessor, Professor listarProfessor[]);
void listarrProfessor(int qtdProfessor, Professor listarProfessor[]);
int verificarProfessor(int qtdprofessor, Professor listarProfessor[],
                       int *matriculaprof);

/* ========================================================================================
  FINAL PROFESSOR
========================================================================================
*/
#endif