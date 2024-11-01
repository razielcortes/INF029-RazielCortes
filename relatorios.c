#include "disciplina.h"
#include <string.h>
#include <ctype.h>
#include "relatorios.h"
#include <stdio.h>
#include <time.h>

int menuRelatorio() {
  int opcao;
  printf("0-VOLTAR\n");
  printf("1- LISTAR ALUNOS\n");
  printf("2-LISTAR PROFESSORES\n");
  printf("3-LISTAR DISCIPLINAS SEM ALUNOS\n");
  printf("4-LISTAR DISCIPLINAS COM ALUNOS\n");
  printf("5-LISTAR ALUNOS POR SEXO:\n");
  printf("6-ALUNOS POR ORDEM ALFABETICA:\n");
  printf("7-ALUNOS POR DATA DE NASCIMENTO:\n");
  printf("8-PROFESSOR POR SEXO:\n");
  printf("9-PROFESSOR POR ORDEM ALFABETICA:\n");
  printf("10-PROFESSOR POR DATA DE NASCIMENTO:\n");
  printf("11-ANIVERSARIANTES DO MES:\n");
  printf("12-DISCIPLINAS COM MAIS DE 40 ALUNOS:\n)");
  printf("13-ALUNOS MATRICULADOS EM MENOS DE 3 DISCIPLINAS:\n");
  printf("14- BUSCA DE ALUNOS POR LETRA:\n");
  scanf("%d", &opcao);

  return opcao;
}

// Listar todos os alunos
void listarAlunosSimples(int qtdAluno, Aluno listarAluno[]) {
    printf("LISTA DE ALUNOS\n");
    if(qtdAluno==0){
        printf("LISTA VAZIA\n");
    }else{
    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1) {
            printf("ALUNO %d:\n", i + 1);
            printf("NOME: %s\n", listarAluno[i].nome);
            printf("MATRICULA: %d\n", listarAluno[i].matricula);
            printf("SEXO: %c\n", listarAluno[i].sexo);
            printf("DATA DE NASCIMENTO: %d/%d/%d\n", listarAluno[i].diaNascimento, listarAluno[i].mesNascimento, listarAluno[i].anoNascimento);
            printf("CPF: %s\n\n", listarAluno[i].cpf);
        }
    }
    }
}
// Listar todos os professores
void listarProfessoresSimples(int qtdProfessor, Professor listarProfessor[]) {
    printf("LISTA DE PROFESSORES\n");
    if(qtdProfessor==0){
        printf("LISTA DE PROFESSORES VAZIA\n");
    }else{
    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1) {
            printf("PROFESSOR %d:\n", i + 1);
            printf("NOME: %s\n", listarProfessor[i].nome);
            printf("MATRICULA: %d\n", listarProfessor[i].matricula);
            printf("SEXO: %c\n", listarProfessor[i].sexo);
            printf("DATA DE NASCIMENTO: %d/%d/%d\n", listarProfessor[i].diaNascimento, listarProfessor[i].mesNascimento, listarProfessor[i].anoNascimento);
            printf("CPF: %s\n\n", listarProfessor[i].cpf);
        }
    }
    }
}

void listarDisciplinasSimples(int qtdDisciplina, Disciplina listarDisciplina[], int qtdProfessor, Professor listarProfessor[]) {
    printf("LISTA DE DISCIPLINAS\n");
    if(qtdDisciplina==0){
        printf("LISTA DE DISCIPLINAS VAZIA\n");
    }else{
    for (int i = 0; i < qtdDisciplina; i++) {
        if (listarDisciplina[i].ativo == 1) {
            printf("DISCIPLINA %d:\n", i + 1);
            printf("NOME: %s\n", listarDisciplina[i].nome);
            printf("CODIGO: %d\n", listarDisciplina[i].coddisciplina);
            printf("PROFESSOR MATRICULADO (Matrícula: %d): ", listarDisciplina[i].matriculaprof);

            // Encontrar e imprimir o nome do professor correspondente
            int professorEncontrado = 0;
            for (int j = 0; j < qtdProfessor; j++) {
                if (listarProfessor[j].matricula == listarDisciplina[i].matriculaprof && listarProfessor[j].ativo == 1) {
                    printf("%s\n\n", listarProfessor[j].nome);
                    professorEncontrado = 1;
                    break;
                }
            }
            // Caso o professor não seja encontrado (por exemplo, se foi excluído)
            if (!professorEncontrado) {
                printf("PROFESSOR NAO ENCONTRADO\n\n");
            }
        }
    }
}
}

void listarDisciplinaComAlunos(int qtdDisciplina, Disciplina listarDisciplina[]) {
    int codDisciplina;

    // Solicitar o código da disciplina ao usuário
    printf("DIGITE O CODIGO DA DISCIPLINA QUE DESEJA LISTAR: ");
    scanf("%d", &codDisciplina);

    // Procurar pela disciplina com o código fornecido
    for (int i = 0; i < qtdDisciplina; i++) {
        // Verificar se a disciplina é ativa e corresponde ao código fornecido
        if (listarDisciplina[i].ativo == 1 && listarDisciplina[i].coddisciplina == codDisciplina) {
            printf("DISCIPLINA: %s\n", listarDisciplina[i].nome);
            printf("CODIGO: %d\n", listarDisciplina[i].coddisciplina);

            // Listar alunos matriculados na disciplina
            if (listarDisciplina[i].qtdalunosdisciplina > 0) {
                printf("ALUNOS MATRICULADOS:\n");
                for (int j = 0; j < listarDisciplina[i].qtdalunosdisciplina; j++) {
                    printf("NOME: %s\n", listarDisciplina[i].listaALNdisciplina[j].nome);
                    printf("MATRICULA: %d\n", listarDisciplina[i].listaALNdisciplina[j].matricula);
                    printf("IDADE: %d\n", listarDisciplina[i].listaALNdisciplina[j].idade);
                    printf("SEXO: %c\n\n", listarDisciplina[i].listaALNdisciplina[j].sexo);
                    printf("\n");
                }
            } else {
                printf("NENHUM ALUNO MATRICULADO NESTA DISCIPLINA.\n\n");
            }
            return;
        }
    }
    printf("DISCIPLINA NAO ENCONTRADA OU INATIVA.\n");
}

void listarAlunosPorSexo(int qtdAluno, Aluno listarAluno[]) {
    char sexo;

    // Solicita ao usuário o sexo desejado para listar os alunos
    printf("DIGITE O SEXO DOS ALUNOS QUE DESEJA LISTAR (M PARA MASCULINO, F PARA FEMININO): ");
    scanf(" %c", &sexo);

    // Converte para maiúscula manualmente, caso o usuário insira uma letra minúscula
    if (sexo >= 'a' && sexo <= 'z') {
        sexo = sexo - ('a' - 'A');
    }

    // Verifica se o usuário inseriu um valor válido para sexo
    if (sexo != 'M' && sexo != 'F') {
        printf("SEXO INVALIDO. USE 'M' PARA MASCULINO ou 'F' PARA FEMININO.\n");
        return;
    }

    // Exibe a lista de alunos do sexo especificado
    printf("LISTA DE ALUNOS POR SEXO (%c)\n", sexo);
    int encontrou = 0;

    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1 &&
            (listarAluno[i].sexo == sexo || listarAluno[i].sexo == sexo + ('a' - 'A'))) {
            printf("NOME: %s\n", listarAluno[i].nome);
            encontrou = 1;
        }
    }

    // Caso nenhum aluno seja encontrado com o sexo especificado
    if (!encontrou) {
        printf("NENHUM ALUNO ENCONTRADO COM O SEXO ESPECIFICADO.\n");
    }
}


// Função para listar alunos em ordem alfabética
void listarAlunosOrdemAlfabetica(int qtdAluno, Aluno listarAluno[]) {
    Aluno temp;

    // Algoritmo de ordenação por seleção
    for (int i = 0; i < qtdAluno - 1; i++) {
        for (int j = i + 1; j < qtdAluno; j++) {
            if (listarAluno[i].ativo == 1 && listarAluno[j].ativo == 1 && 
                strcmp(listarAluno[i].nome, listarAluno[j].nome) > 0) {
                // Troca os alunos de posição caso estejam fora de ordem
                temp = listarAluno[i];
                listarAluno[i] = listarAluno[j];
                listarAluno[j] = temp;
            }
        }
    }

    // Exibe a lista de alunos em ordem alfabética
    printf("LISTA DE ALUNOS EM ORDEM ALFABÉTICA:\n");
    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1) {
            printf("Nome: %s\n", listarAluno[i].nome);
        }
    }
}

void ordenarAlunosPorDataNascimento(int qtdAluno, Aluno listarAluno[]) {
    for (int i = 0; i < qtdAluno - 1; i++) {
        for (int j = i + 1; j < qtdAluno; j++) {
            if (listarAluno[i].anoNascimento > listarAluno[j].anoNascimento || 
               (listarAluno[i].anoNascimento == listarAluno[j].anoNascimento && listarAluno[i].mesNascimento > listarAluno[j].mesNascimento) ||
               (listarAluno[i].anoNascimento == listarAluno[j].anoNascimento && listarAluno[i].mesNascimento == listarAluno[j].mesNascimento && listarAluno[i].diaNascimento > listarAluno[j].diaNascimento)) {
                Aluno temp = listarAluno[i];
                listarAluno[i] = listarAluno[j];
                listarAluno[j] = temp;
            }
        }
    }
    listarrAlunos(qtdAluno, listarAluno);
}

// Função para listar professores por sexo
void listarProfessoresPorSexo(int qtdProfessor, Professor listarProfessor[]) {
    char sexo;

    // Solicita o sexo ao usuário
    printf("DIGITE O SEXO DOS PROFESSORES QUE DESEJA LISTAR (M/F): ");
    scanf(" %c", &sexo);
    sexo = toupper(sexo);  

    printf("LISTA DE PROFESSORES POR SEXO (%c):\n", sexo);
    int encontrou = 0;  

    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1 && listarProfessor[i].sexo == sexo) {
            printf("%s\n", listarProfessor[i].nome);
            encontrou = 1;
        }
    }
    printf("\n");
}

// Função para listar professores em ordem alfabética
void listarProfessoresOrdemAlfabetica(int qtdProfessor, Professor listarProfessor[]){
    Professor temp;

    // Algoritmo de ordenação por seleção
    for (int i = 0; i < qtdProfessor - 1; i++) {
        for (int j = i + 1; j < qtdProfessor; j++) {
            if (listarProfessor[i].ativo == 1 && listarProfessor[j].ativo == 1 && 
                strcmp(listarProfessor[i].nome, listarProfessor[j].nome) > 0) {
                // Troca os professores de posição caso estejam fora de ordem
                temp = listarProfessor[i];
                listarProfessor[i] = listarProfessor[j];
                listarProfessor[j] = temp;
            }
        }
    }

    // Exibe a lista de professores em ordem alfabética
    printf("LISTA DE PROFESSORES EM ORDEM ALFABÉTICA:\n");
    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1) {
            printf("Nome: %s\n\n", listarProfessor[i].nome);
        }
    }
}

void ordenarProfessoresPorDataNascimento(int qtdProfessor, Professor listarProfessor[]) {
    for (int i = 0; i < qtdProfessor - 1; i++) {
        for (int j = i + 1; j < qtdProfessor; j++) {
            // Comparação entre as datas de nascimento (ano, mês e dia)
            if (listarProfessor[i].ativo == 1 && listarProfessor[j].ativo == 1 &&
                (listarProfessor[i].anoNascimento > listarProfessor[j].anoNascimento ||
                (listarProfessor[i].anoNascimento == listarProfessor[j].anoNascimento && listarProfessor[i].mesNascimento > listarProfessor[j].mesNascimento) ||
                (listarProfessor[i].anoNascimento == listarProfessor[j].anoNascimento && listarProfessor[i].mesNascimento == listarProfessor[j].mesNascimento && listarProfessor[i].diaNascimento > listarProfessor[j].diaNascimento))) {

                // Troca de posições dos professores
                Professor temp = listarProfessor[i];
                listarProfessor[i] = listarProfessor[j];
                listarProfessor[j] = temp;
            }
        }
    }

    // Exibir a lista de professores ordenada por data de nascimento
    printf("LISTA DE PROFESSORES POR DATA DE NASCIMENTO:\n");
    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1) {
            printf("NOME: %s\n", listarProfessor[i].nome);
            printf("MATRICULA: %d\n", listarProfessor[i].matricula);
            printf("DATA DE NASCIMENTO: %02d/%02d/%04d\n\n", listarProfessor[i].diaNascimento, listarProfessor[i].mesNascimento, listarProfessor[i].anoNascimento);
        }
    }
}

// Função para listar aniversariantes do mês (alunos e professores)
void listarAniversariantesDoMes(int qtdAluno, Aluno listarAluno[], int qtdProfessor, Professor listarProfessor[]) {
    int diaAtual, mesAtual, anoAtual;

    // Entrada da data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Extrai dia, mês e ano
    diaAtual = tm.tm_mday;
    mesAtual = tm.tm_mon + 1; // tm_mon é de 0 a 11, então adicionamos 1
    anoAtual = tm.tm_year + 1900; // tm_year é o número de anos desde 1900

    printf("\nANIVERSARIANTES DO MÊS %d:\n\n", mesAtual);

    // Listar alunos aniversariantes do mês
    printf("ALUNOS:\n");
    int encontrouAniversarianteAluno = 0;
    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1 && listarAluno[i].mesNascimento == mesAtual) {
            printf("- %s (DATA DE NASCIMENTO: %02d/%02d/%04d)\n", 
                   listarAluno[i].nome, listarAluno[i].diaNascimento, listarAluno[i].mesNascimento, listarAluno[i].anoNascimento);
            encontrouAniversarianteAluno = 1;
        }
    }
    if (!encontrouAniversarianteAluno) {
        printf("NENHUM ALUNO FAZ ANIVERSARIO NESTE MES.\n");
    }

    // Listar professores aniversariantes do mês
    printf("\n PROFESSORES:\n");
    int encontrouAniversarianteProfessor = 0;
    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1 && listarProfessor[i].mesNascimento == mesAtual) {
            printf("- %s (Data de Nascimento: %02d/%02d/%04d)\n", 
                   listarProfessor[i].nome, listarProfessor[i].diaNascimento, listarProfessor[i].mesNascimento, listarProfessor[i].anoNascimento);
            encontrouAniversarianteProfessor = 1;
        }
    }
    if (!encontrouAniversarianteProfessor) {
        printf("NENHUM PROFESSOR FAZ ANIVERSARIO NESTE MES.\n");
    }
}

void listarDisciplinasExcedendo40Alunos(int qtdDisciplina, Disciplina listarDisciplina[]) {
    printf("LISTA DE DISCIPLINAS COM MAIS DE 40 ALUNOS:\n");
    int encontrou = 0; 

    for (int i = 0; i < qtdDisciplina; i++) {
        if (listarDisciplina[i].ativo == 1 && listarDisciplina[i].qtdalunosdisciplina > 40) {
            printf("DISCIPLINA: %s\n", listarDisciplina[i].nome);
            printf("CODIGO: %d\n", listarDisciplina[i].coddisciplina);
            printf("QUANTIDADE DE ALUNOS: %d\n", listarDisciplina[i].qtdalunosdisciplina);
            printf("PROFESSOR MATRICULADO: %d\n", listarDisciplina[i].matriculaprof);
            printf("\n");
            encontrou = 1; 
        }
    }

    if (!encontrou) {
        printf("NENHUMA DISCIPLINA COM MAIS DE 40 ALUNOS ENCONTRADA.\n");
    }
}

void listarAlunosMenosDeTresDisciplinas(int qtdAluno, Aluno listarAluno[]) {
    printf("LISTA DE ALUNOS MATRICULADOS EM MENOS DE 3 DISCIPLINAS:\n");
    int encontrou = 0; 

    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1 && listarAluno[i].qtdDisciplina < 3) {
            printf("NOME: %s\n", listarAluno[i].nome);
            printf("MATRICULA: %d\n", listarAluno[i].matricula);
            printf("QUANTIDADE DE DISCIPLINAS: %d\n", listarAluno[i].qtdDisciplina);
            printf("\n");
            encontrou = 1; 
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno matriculado em menos de 3 disciplinas encontrado.\n");
    }
}

void PessoasPorSubstring(int qtdAluno, Aluno listarAluno[], int qtdProfessor, Professor listarProfessor[]) {
    char busca[4];
    printf("Informe uma string de busca com exatamente três letras: ");
    getchar();
    fgets(busca, sizeof(busca), stdin);

    // Remove o caractere de nova linha, se presente
    if (busca[strlen(busca) - 1] == '\n') {
        busca[strlen(busca) - 1] = '\0';
    }

    // Verifica se a entrada contém exatamente três letras
    if (strlen(busca) != 3) {
        printf("Erro: A string de busca deve conter exatamente três letras.\n");
        return;
    }

    printf("PESSOAS ENCONTRADAS QUE CONTÊM AS LETRAS '%s' NO NOME:\n\n", busca);
    int encontrou = 0;

    // Função de busca para alunos
    for (int i = 0; i < qtdAluno; i++) {
        if (listarAluno[i].ativo == 1) {
            // Copia o nome do aluno para uma variável temporária
            char nomeTemp[50];
            strcpy(nomeTemp, listarAluno[i].nome);

            // Verifica cada uma das letras da busca
            char *pos1 = strstr(nomeTemp, (char[]){busca[0], '\0'});
            char *pos2 = pos1 ? strstr(pos1 + 1, (char[]){busca[1], '\0'}) : NULL;
            char *pos3 = pos2 ? strstr(pos2 + 1, (char[]){busca[2], '\0'}) : NULL;

            if (pos1 && pos2 && pos3) {
                printf("Aluno: %s (Matrícula: %d)\n", listarAluno[i].nome, listarAluno[i].matricula);
                encontrou = 1;
            }
        }
    }

    // Função de busca para professores
    for (int i = 0; i < qtdProfessor; i++) {
        if (listarProfessor[i].ativo == 1) {
            // Copia o nome do professor para uma variável temporária
            char nomeTemp[50];
            strcpy(nomeTemp, listarProfessor[i].nome);

            // Verifica cada uma das letras da busca
            char *pos1 = strstr(nomeTemp, (char[]){busca[0], '\0'});
            char *pos2 = pos1 ? strstr(pos1 + 1, (char[]){busca[1], '\0'}) : NULL;
            char *pos3 = pos2 ? strstr(pos2 + 1, (char[]){busca[2], '\0'}) : NULL;

            if (pos1 && pos2 && pos3) {
                printf("Professor: %s (Matrícula: %d)\n", listarProfessor[i].nome, listarProfessor[i].matricula);
                encontrou = 1;
            }
        }
    }

    if (!encontrou) {
        printf("Nenhuma pessoa encontrada com as letras '%s' no nome.\n", busca);
    }
}