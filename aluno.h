#ifndef ALUNO_H
#define ALUNO_H
//

/* ========================================================================================
  INICIO ALUNO
======================================================================================== */

#define TAM_ALUNO 3
#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_ALUNO_INVALIDA -2
#define LISTA_ALUNO_CHEIA -3
#define ATUALIZADO_ALUNO_SUCESSO -4
#define MATRICULA_ALUNO_INEXISTENTE -5
#define EXCLUSAO_ALUNO_SUCESSO -6
#define SEXO_ALUNO_INVALIDO -7
#define MATRICULA_ALUNO_INDISPONIVEL -8
#define CPF_ALUNO_JA_CADASTRADO -9
#define ALUNO_EXISTE -10
#define CPF_ALUNO_INVALIDO -11
#define CPF_ALUNO_VALIDO -12
#define DATA_INVALIDA -13
#define DATA_VALIDA -14

typedef struct alu
{
int matricula;
char cpf[15];
int idade;
int diaNascimento, mesNascimento, anoNascimento;
int diaAtual, mesAtual, anoAtual;
char nome[20];
char sexo;
int ativo;
int qtdDisciplina;
}Aluno;


//prototipos das funções aluno
int menuGeral();
int menuAluno();
int cadastrarAluno(int qtdAluno, Aluno listarAluno[]);
void listarrAlunos(int qtdAluno, Aluno listarAluno[]);
int atualizarAluno(int qtdAluno, Aluno listarAluno[]);
int excluirAluno(int qtdAluno, Aluno listarAluno[]);
void listarrAlunos(int qtdAluno, Aluno listarAluno[]);
int verificarAluno(int qtdAluno, Aluno listarAluno[], int * matriculaaluno);
int verificarCpfaluno(int qtdAluno, Aluno listarAluno[], char *cpf);
void limpar_buffer();
int validar_data(int dia, int mes, int ano);

/* ========================================================================================
  FINAL ALUNO
======================================================================================== */






#endif