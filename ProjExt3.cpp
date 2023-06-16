#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//ESTRUTURA DO TIPO ITEM
typedef struct {
    char tipo[20];
    float preco;
} Item;

//ESTRUTURA DO TIPO VENDA
typedef struct {
    int dia;
    int mes;
    int ano;
    Item item;
    int quantidade;
    float peso = 0;
} Venda;

//CÁLCULO DO PREÇO DA QUENTINHA, BEBIDA E REFEIÇÃO À QUILO
float calcularPreco(Venda venda) {
    float preco = venda.item.preco;
    float valor_quilo;
    if (strcmp(venda.item.tipo, "quent") == 0) {
        preco = venda.quantidade * 20.5; // preço fixo de R$ 20,00 + R$0,50 da embalagem
    } else if (strcmp(venda.item.tipo, "bebida") == 0) {
        preco *= venda.quantidade;
    } else if (strcmp(venda.item.tipo, "quilo") == 0) {
    	if (venda.peso < 100) {
    		preco = 10;
		}
		else if ((venda.peso > 100) && (venda.peso < 200)) {
			preco = 20;
		}
		else if ((venda.peso > 200) && (venda.peso < 300)) {
			preco = 30;
		}
		else if ((venda.peso > 300) && (venda.peso < 400)) {
			preco = 40;
		}
		else if ((venda.peso > 400) && (venda.peso < 500)) {
			preco = 50;
		}
		else if (venda.peso > 500) {
			preco = 60;
		}
		}
		return preco;
	}
	    
//CALCULAR TOTAL DE VENDAS
float calcularTotalVendas(Venda vendas[], int numVendas) {
    float total = 0.0;
    for (int i = 0; i < numVendas; i++) {
        total += calcularPreco(vendas[i]);
    }
    return total;
}

//CRIANDO RELATÓRIO DE VENDAS DO DIA
void imprimirRelatorioDiario(Venda vendas[], int numVendas) {
	system("cls"); //limpar tela
    printf("Relatório diário:\n");
    printf("\n===============================================================================\n");
    printf("Data\t\tTipo\t\tQuantidade\t    Peso\t      Preço\n");
    for (int i = 0; i < numVendas; i++) {
        printf("%02d/%02d/%04d\t%s\t\t%d\t\t    %.2f\t      %.2f\n",
            vendas[i].dia, vendas[i].mes, vendas[i].ano,
            vendas[i].item.tipo, vendas[i].quantidade,
            vendas[i].peso, calcularPreco(vendas[i]));
    }
    printf("\n===============================================================================\n");
    printf("Total de vendas diárias: %.2f\n", calcularTotalVendas(vendas, numVendas));
}

//CRIANDO RELATÓRIO DE VENDAS DO MÊS
void imprimirRelatorioMensal(Venda vendas[], int numVendas, int mes, int ano) {
	system("cls"); //limpar tela
    printf("Relatório mensal (%02d/%04d):\n", mes, ano);
    printf("\n===============================================================================\n");
    printf("Data\t\tTipo\t\tQuantidade\t    Peso\t      Preço\n");
    float total = 0.0;
    float totalMeses[12] = {0.0};
    for (int i = 0; i < numVendas; i++) {
        if (vendas[i].mes == mes && vendas[i].ano == ano) {
            printf("%02d/%02d/%04d\t%s\t\t%d\t\t    %.2f\t      %.2f\n",
                vendas[i].dia, vendas[i].mes, vendas[i].ano,
                vendas[i].item.tipo, vendas[i].quantidade,
                vendas[i].peso, calcularPreco(vendas[i]));
            total += calcularPreco(vendas[i]);
        }
    }
    printf("\n===============================================================================\n");
    printf("Total de vendas mensais: %.2f\n", total);
}

int compararVendas(const void *v1, const void *v2) {
    Venda *venda1 = (Venda*) v1;
    Venda *venda2 = (Venda*) v2;
    float total1 = calcularPreco(*venda1);
    float total2 = calcularPreco(*venda2);
    
    if (total1 > total2) {
        return -1; // RETORNA NEGATIVO PARA ORDEM DECRESCENTE
    } else if (total1 < total2) {
        return 1;
    } else {
        return 0;
    }
}
//IMPRENSÃO DE RANK DURANTE O ANO 
void imprimirRankingAnual(Venda vendas[], int numVendas) {
	system("cls"); //limpar tela
	printf("Ranking anual:\n\n");
	printf("===================================\n");
	printf("Mês\t\tTotal de vendas\n");
	Venda vendasOrdenadas[numVendas];
	memcpy(vendasOrdenadas, vendas, numVendas * sizeof(Venda));
	qsort(vendasOrdenadas, numVendas, sizeof(Venda), compararVendas);
	int mesAnterior = vendasOrdenadas[0].mes;
	float totalMes = 0.0;
	
	for (int i = 0; i < numVendas; i++) {
		if (vendasOrdenadas[i].mes != mesAnterior) {
		printf("%02d/%04d\t        %.2f\n", mesAnterior, vendasOrdenadas[i-1].ano, totalMes);
		totalMes = 0.0;
		mesAnterior = vendasOrdenadas[i].mes;
		}
	totalMes += calcularPreco(vendasOrdenadas[i]);
	}
printf("%02d/%04d\t        %.2f\n", mesAnterior, vendasOrdenadas[numVendas-1].ano, totalMes);
	printf("\n===================================\n");
}


int main(void) {
	
	setlocale(LC_ALL, "Portuguese");
	
Venda vendas[36500]; // 100 VENDAS DIÁRIAS EM 365 DIAS
int numVendas = 0;
int opcao = -1;

//MENU DE ESCOLHAS DO RESTAURANTE
while (opcao != 0) {
	printf("\n====BEM VINDOS AO RESTAURANTE X====\n\n");
	printf("Menu:\n");
	printf("1 - Registrar venda\n");
	printf("2 - Imprimir relatório diário\n");
	printf("3 - Imprimir relatório mensal\n");
	printf("4 - Imprimir ranking anual\n");
	printf("0 - Sair\n\n");
	printf("Opção: ");
	scanf("%d", &opcao);
	
	switch (opcao) {
		case 1: {
			system("cls"); //limpar tela
			printf("Digite a data da venda (DD/MM/AAAA): ");
			int dia, mes, ano;
			scanf("%d/%d/%d", &dia, &mes, &ano);
			Venda venda;
			venda.dia = dia;
			venda.mes = mes;
			venda.ano = ano;
			printf("\n==============================\n");
			printf("|    quent para QUENTINHA    |\n");
			printf("|     bebida para BEBIDA     |\n");
			printf("| quilo para COMIDA À QUILO  |\n");
			printf("==============================\n\n");
			printf("# Quentinha tem um valor fixo de R$20,00 + R$0,50 da embalagem #\n");
			printf("\nDigite o tipo de item vendido: ");
			scanf("%s", venda.item.tipo);
			
			if(strcmp(venda.item.tipo, "quent") == 0) {
				printf("Digite a quantidade vendida: ");
				scanf("%d", &venda.quantidade);
			}
			else if (strcmp(venda.item.tipo, "bebida") == 0) {
				printf("Digite a quantidade vendida: ");
				scanf("%d", &venda.quantidade);
				printf("Digite o preço do item vendido: R$");
				scanf("%f", &venda.item.preco);
			}
			else if (strcmp(venda.item.tipo, "quilo") == 0) {
				printf("Digite o peso do item vendido (em gramas): ");
				scanf("%f", &venda.peso);
				venda.quantidade = 1;
			}
			else {
				venda.quantidade = 1;
			}
			vendas[numVendas] = venda;
			numVendas++;
			printf("Venda registrada com sucesso!\n");
		break;
		}
		case 2: {
			imprimirRelatorioDiario(vendas, numVendas);
			break;
		}
		case 3: {
			printf("Digite o mês e o ano do relatório (MM/AAAA): ");
			int mes, ano;
			scanf("%d/%d", &mes, &ano);
			imprimirRelatorioMensal(vendas, numVendas, mes, ano);
		break;
		}
		case 4: {
			imprimirRankingAnual(vendas, numVendas);
		break;
		}
		case 0: {
			printf("Encerrando programa...\n");
		break;
		}
		default: {
			printf("Opção inválida");
		break;
		}
	}
}
	return 0;
}
