#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int main()
{
	//Variaveis// 
	
	int  n_auditorias=0,c,codigo_auditoria,data_dia,data_mes,data_ano,duracao, quant_vuln , vuln_min=9999 , vuln_max=0,i,j;
	double duracao_total = 0;
	char nome[80], report[9000], maiorvulnerabi[500], menosvulnerabi[500], aux[500], reportPass[100],reportDeci[500];
	void cifrar_password(int x);
	void decifrar_password(char naosei[500]);

	//Introducao//

  	printf("\n \n===============Bem-Vindo===============\n \n");
	printf("Digite o numero de Auditorias que prentende inserir na plataforma: ");
	scanf("%d", &n_auditorias);
	if (n_auditorias <= 0)
	{
		while (n_auditorias <=0)
		{
			printf("Numero de auditorias invalido, digite outra vez: ");
			scanf("%d", &n_auditorias);
		}	
	}
	system("cls");
	
	//Perguntar todas a informações//

	for(c=1;c<=n_auditorias;c++)
	{
		printf("\n \n=============Informacoes.A%d============\n \n", c);
		printf("\nDigite o codigo da auditoria n %d: ", c);
		scanf("%d", &codigo_auditoria);
		getchar();
		printf("\nDigite o nome do colaborador: ");
		gets(nome);
		printf("\nDigite o DIA em que a auditoria n %d se realizou: ", c);
		scanf("%d", &data_dia);
		if (data_dia <= 0 || data_dia > 31)
		{
			while (data_dia <= 0 || data_dia > 31)
			{
			printf("Dia invalido, digite outra vez: ");
			scanf("%d", &data_dia);
			}
		}
		printf("Digite o MES em que a auditoria n %d se realizou: ", c);

		scanf("%d", &data_mes);
		if (data_mes <= 0 || data_mes > 12 )
		{
			while (data_mes <= 0 || data_mes > 12)
			{
				printf("Mes invalido, digite outra vez: ");
				scanf("%d", &data_mes);
			}
		}
		printf("Digite o ANO em que a auditoria n %d se realizou: ", c);
		scanf("%d", &data_ano);
		if (data_ano < 1960)
		{
			while (data_ano < 1960)
			{
				printf("Nesse ano ainda nao existia computadores, digite outra vez: ");
				scanf("%d", &data_ano);
			}
		}
		printf("\nDigite a duracao da auditoria n %d em minutos: ", c);
		scanf("%d", &duracao);
		if (duracao < 0)
		{
			while (duracao <= 0)
			{
				printf("\nDuracao invalida, digite outra vez: ");
				scanf("%d", &duracao);
			}
		}
		printf("\nQuantas vulnerabilidades foram encontradas na auditoria n %d teve: ", c);
		scanf("%d", &quant_vuln);
		if (quant_vuln <= 0)
		{
			while (quant_vuln < 0)
			{
				printf("\nDado invalido, digite outra vez: ");
				scanf("%d", &quant_vuln);
			}
		}

		//Media do tempo de todas a auditorias//

		duracao_total = (duracao_total*(c-1) + duracao) / c;
		
		//Verificar qual a auditoria com mais e menos vulnerabilidade//
		
		if (quant_vuln < vuln_min)
		{
			vuln_min = quant_vuln;
			strcpy(menosvulnerabi, "");
			sprintf (aux, "\nA auditoria com menos Vulnerabilidades foi a auditoria %d_%d datada em %d/%d com o numero %d de Vulnerabilidades!\n \n \n", data_ano, codigo_auditoria, data_dia, data_mes, vuln_min);
			strcat(menosvulnerabi, aux);
		}
		if (quant_vuln > vuln_max)
		{
			vuln_max = quant_vuln;
			strcpy(maiorvulnerabi, "");
			sprintf(aux, "\nA auditoria com mais Vulnerabilidades foi a auditoria %d_%d datada em %d/%d com o numero %d de Vulnerabilidades!", data_ano, codigo_auditoria, data_dia, data_mes, vuln_max); 
			strcat(maiorvulnerabi,aux);
		}
		
		//Gravar o nome e o codigo//
		
		sprintf(aux,"\nA auditoria %d_%d teve como colaborador %s", data_ano, codigo_auditoria,nome);
		strcat(report, aux);
		system("cls");
	}

	//Relatorio Final//

	printf("\n \n \n \n===============Relatorio Final===============\n \n \n \n");
	printf("%s",report);
	printf("\n\nA duracao media das auditorias foi: %f\n", duracao_total);
	printf("%s", maiorvulnerabi);
	printf("%s", menosvulnerabi);
	printf("\n=============================================\n \n \n \n");
	system("pause");
    system("cls"); 

	//Password Generator//
	
	strcpy(report,"");
	printf("\n \n=============Gerar Password============\n \n");
	printf("\nSe desejar criar uma Password para as auditorias digite 1, senao desejar, pressione 2: ");
	scanf("%d",&c);
	if (c != 1 && c != 2)
	{
		while (c != 1 && c != 2 )
		{
			printf("\nDado invalido, escolha 1 ou 2: ");
			scanf("%d",&c);
		}
	}
	if (c == 2)
	{
		printf("\n\n\nTenha um bom dia :)\n\n\n");
	}
	else
	{
		printf("\nDigite o numero de Passwords que deseja gerar: ");
		scanf("%d", &j);
		system("cls");
		for (i=1; i<=j;i++)
		{
			strcpy(reportPass,"");
			strcpy(report,"");
			for ( c= 1; c <= 3; c++) 
			{
				char Maiuscula = 'A' + (rand() % 26), Minuscula = 'a' + (rand() % 26),Simbolo = "@#$%&€?!+" [rand () % 9];
      			int  num1 = rand() % 9;   
      	 		sprintf(aux,"%c%d%c%c",Simbolo, num1, Maiuscula, Minuscula);
      	 		strcat(report,aux);
      			if(c==3)
       		 	{
       	 		sprintf(aux,"%s%c\n",report, Simbolo);
       	 		strcat(reportPass, aux);
				}
   	 		}
		   	if(i==1)
   	 		{
   	 		printf("\n\n=================Password Gerada================= \n\n");
   	 		printf("\nA Password gerada: %s",reportPass);
   	 		sprintf(aux,"A Password gerada: %s",reportPass);
   	 		strcat(reportDeci,aux);
			}
			if(i>1 && i<j+1)
			{
			printf("A Password gerada: %s",reportPass);
			sprintf(aux,"A Password gerada: %s",reportPass);
   	 		strcat(reportDeci,aux);
			}
			if (i==j)
			{
			printf("\n\n================================================\n");		
			}					
		}
	}	
    
   //Crifar e posterior Decifracao//
    
    system("pause");
    system("cls");
    printf(" \n\n=============Cifrar Password============\n \n");
	printf("\nSe desejar criar uma Crifar a Password Gerada digite 1, senao desejar, pressione 2: ");
	scanf("%d",&c);
	if (c != 1 && c != 2)
	{
		while (c != 1 && c != 2 )
		{
			printf("\nDado invalido, escolha 1 ou 2: ");
			scanf("%d",&c);
		}
	}
	if (c == 2)
	{
		printf("\n\n\nTenha um bom dia :)\n\n\n");
	}
	else
	{
		system("cls");
		cifrar_password(j);
		printf("\nSe desejar sair precione guardar os dados e sair precione 2, se desejar decifrar outra vez precione 1: ");
		scanf("%d",&c);
		if (c != 1 && c != 2)
		{
			while (c != 1 && c != 2 )
			{
				printf("\nDado invalido, escolha 1 ou 2: ");
				scanf("%d",&c);
			}
		}
		if (c==1)
		{
		system("cls");
		decifrar_password(reportDeci);
		printf("\n\n\nAs suas Passwords foram decifradas com sucesso, tenha um bom dia :)\n\n\n")	;
				
	 	
		 
		 	
		}
		else
		{
			printf("\n\n\nAs suas Passwords foram gravadas com sucesso, tenha um bom dia :)\n\n\n")	;
		}
	
	return 0;
	}
}

//SubRotina Cifrar//

void cifrar_password(int x)
{
	int i;
	printf("\n\n=================Password Cifrada================= \n");
	for(i=1;i<=x;i++)
	{
		if(i>=1 && i<x+1)
		{
		printf("\nA Password gerada: $$$$$$$$$$$$$");
		}
		if (i==x)
		{
		printf("\n\n================================================\n");
		}
	}
	return;		
}

//subRotina decifrar

void decifrar_password(char naosei[500])
{

	printf("\n\n================Password Decifrada================\n \n");	
	printf("%s",naosei);
	printf("\n================================================\n");
	return;	
}

	
