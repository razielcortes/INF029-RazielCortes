#include "disciplina.h"
#ifndef RELAT_H
#define RELAT_H

#define SEM_ALUNOS -1
#define SEM_PROFESSORES -2
#define SEM_DISCIPLINAS -3



int menuRelatorio();
void listarAlunosSimples(int qtdAluno, Aluno listarAluno[]);
void listarProfessoresSimples(int qtdProfessor, Professor listarProfessor[]);
void listarDisciplinasSimples(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]);
void listarDisciplinaComAlunos(int qtdDisciplina, Disciplina listarDisciplina[]);
void listarAlunosPorSexo(int qtdAluno, Aluno listarAluno[]);
void ordenarAlunosPorNome(int qtdAluno, Aluno listarAluno[]);
void listarAlunosOrdemAlfabetica(int qtdAluno, Aluno listarAluno[]);
void ordenarAlunosPorDataNascimento(int qtdAluno, Aluno listarAluno[]);
void listarProfessoresPorSexo(int qtdProfessor, Professor listarProfessor[]);
void listarProfessoresOrdemAlfabetica(int qtdProfessor, Professor listarProfessor[]);
void ordenarProfessoresPorDataNascimento(int qtdProfessor, Professor listarProfessor[]);
void listarAniversariantesDoMes(int qtdAluno, Aluno listarAluno[], int qtdProfessor, Professor listarProfessor[]);
void listarDisciplinasExcedendo40Alunos(int qtdDisciplina, Disciplina listarDisciplina[]);
 void listarAlunosMenosDeTresDisciplinas(int qtdAluno, Aluno listarAluno[]);
void PessoasPorSubstring(int qtdAluno, Aluno listarAluno[], int qtdProfessor, Professor listarProfessor[]);


#endif