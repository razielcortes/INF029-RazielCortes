#include "aluno.h"
#include "professor.h"

#ifndef DISC_H
#define DISC_H

/* =======================================================================================
  INICIO DISCPLINA
======================================================================================== */

#define TAM_DISCIPLINA 3
#define TAM_DA_DISCIPLINA 3
#define CAD_DISCIPLINA_SUCESSO -1
#define COD_DISCIPLINA_INVALIDA -2
#define LISTA_DISCIPLINA_CHEIA -3
#define ATUALIZADO_DISCIPLINA_SUCESSO -4
#define COD_DISCIPLINA_INEXISTENTE -5
#define EXCLUSAO_DISCIPLINA_SUCESSO -6
#define COD_DISCIPLINA_INDISPONIVEL -8
#define DISCIPLINA_EXISTE -10
#define CAD_ALUNO_DISCIPLINA_SUCESSO -11
#define DISCIPLINA_CHEIA -12

typedef struct discip
{
int coddisciplina;
int diaAtual, mesAtual, anoAtual;
char nome[20];
int matriculaprof;
int ativo;
Aluno listaALNdisciplina[TAM_DA_DISCIPLINA]; //!Lista de alunos DENTRO da disciplina
int qtdalunosdisciplina;
Aluno aluno;
}Disciplina;

//prototipos das funções professor
int menuDisciplina();

int cadastrarDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]);

void listarrDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]);

int atualizarDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]);

int excluirDisciplina(int qtdDisciplina, Disciplina listarDisciplina[]);

int verificadorDisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int * coddisciplina);

void zerandoqtdalunosdiscplina(Disciplina listarDisciplina[]);

int cadastraralunodisciplina(int qtdDisciplina, Disciplina listarDisciplina[], int qtdAluno, Aluno listarAluno[]);

/* ========================================================================================
  FINAL DISCIPLINA
======================================================================================== */

#endif