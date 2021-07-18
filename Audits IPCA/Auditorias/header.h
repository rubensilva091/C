#ifndef HEADER_H_
#define HEADER_H_
#define TAM 20
#define FICHEIRO_SAVE "save.txt"

/*Enum para atividades*/

typedef enum
{
    ativo = 0,
    inativo = 1
} atividade;

/*Enum para o Estado de Resolução*/

typedef enum
{
    resolvido = 1,
    Naoresolvido = 0
} estadoResolucao;

/*Enumeraçao do nivel de impacto*/

typedef enum
{
    baixo = 1,
    moderado = 2,
    elevado = 3
} nImpacto;

/*Struct da data*/

typedef struct
{
    int dia;
    int mes;
    int ano;

} Data;

/*Struct da Descriçao das vulnerabilidades*/

typedef struct
{
    estadoResolucao resoluc;
    int codigoVuln;
    char marca[50];
    char modelo[50];
    Data data;
    char tipo[50];
} DescricaoVuln;

/*Struct do Colaborador*/

typedef struct
{
    int codigoColab;
    char nome[50];
    atividade atividade;
} Colaborador;

/*Struct da Vulnerabilidade*/

typedef struct
{
    int numero;
    DescricaoVuln descricao;
    nImpacto nivelImpact;
} Vulnerabilidade;

/*Struct da Auditoria*/

typedef struct
{
    Vulnerabilidade vuln[50];
    Colaborador colaborador;
    int codigoAudi;
    int duracao;
    Data data;
} Auditoria;

/*Save*/

int carregaSave(Auditoria *auditoria);
void inserirSave(Auditoria *auditoria, int id);

/*Funcoes no Menu Principal*/

/*Op-1Main*/

Auditoria novaAuditoria(Auditoria *auditoria, int id);

/*Op-2Main*/

int dadosAuditoria(Auditoria *auditoria, int cod);
int dadosVulnerabilidade(Auditoria *auditoria, int cod);
Auditoria editarAuditoriaID(Auditoria *auditoria, int id);
Auditoria edicaoColaborador(Auditoria *auditoria, int cod);
Auditoria edicaoVulnerabilidades(Auditoria *auditoria, int cod, int n);
Auditoria addVulnerabilidades(Auditoria *auditoria, int id);
Auditoria adicionarRemoverVulnerabilidades(Auditoria *auditoria, int cod);
Auditoria remVulnerabilidades(Auditoria *auditoria, int id);

/*Op-3Main*/

void dashboard(Auditoria *auditoria, int id);
float mediaVulnerabilidadesAuditorias(Auditoria *auditoria, int id);
int auditoriaComMaisVuln(Auditoria *auditoria, int id);
int auditoriaComMenosVuln(Auditoria *auditoria, int id);
void tabelaAuditoriasTodas(Auditoria *auditoria, int id);

/*Op-4Main*/
void listagem(Auditoria *auditoria, int id);
void listaColabAudi(Auditoria *auditoria, int id);
void listaAuditoriasColaboradores(Auditoria *auditoria, int id);
void listaVulnerabilidadesNImpacto(Auditoria *auditoria, int id);

/*Op-5Main*/

Auditoria resolucaoVuln(Auditoria *auditoria, int id);
Auditoria alterarEstadoReso(Auditoria *auditoria, int id);

/*Op-6Main*/

Auditoria remocaoIntegral(Auditoria *auditoria, int id);
Auditoria alterarIntegral(Auditoria *auditoria, int id);
Auditoria removerColabIntegridadeReferencial(Auditoria *auditoria, int t, int id);

#endif