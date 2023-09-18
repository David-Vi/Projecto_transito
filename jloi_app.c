#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Conta {
    int idconta;
    char  bi[100];
    char  iban[100];
    double saldo;
};


struct Cliente{
    char  bi[100];
    char nome[100];  
    char morada[100]; 
};

struct Usuario{
    int idusuario;
    char nome[100];
    int tipo;   
    char senha[100]; 
};

// inserir Cliente
void adicionardeposito() {
    int id,n;
    double valor,m,res;
    FILE* arquivo = fopen("contas.txt", "r+b");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero da conta a ser depositado: ");
    scanf("%d", &id);
    printf("Digite a posicao da conta na lista ser depositado: ");
    scanf("%d", &n);
    printf("Digite de deposito saldo da conta: ");
    scanf("%lf", &m);
            
  
 
    struct Conta conta;
    int encontrada = 0;
    while (fread(&conta, sizeof(struct Conta), 1, arquivo)==1) {
        if (conta.idconta == id) {
            printf("Conta encontrada:\n");
            printf("Nª da Conta\tCod. do Cliente\tIBAN\tSaldo\n");    
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);			
			conta.saldo+=m;
            long int posicao=sizeof(struct Conta)*(n-1);
			if(fseek(arquivo,posicao, SEEK_SET)!=0){
				printf("Erro no posicionamento do ponteiro");
				fclose(arquivo);
				encontrada = 0;
			   break;
			}
            fwrite(&conta, sizeof(struct Conta), 1, arquivo);
            printf("Saldo Actual da Conta:\n");
            printf("Nª da Conta\tCod. do Cliente\tIBAN\tSaldo\n");    
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);			
			
            encontrada = 1;
            break;
        }
    }
     fclose(arquivo);
  
    if (encontrada) {
        printf("cliente alterado com sucesso!\n");
    } else {
        printf("cliente alterado encontrada.\n");
    }
}
void adicionarlevantamento() {
    int id,n;
    double valor,m,res;
    FILE* arquivo = fopen("contas.txt", "r+b");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero da conta a ser levantado: ");
    scanf("%d", &id);
    printf("Digite a posicao da Conta na lista ser levantado: ");
    scanf("%d", &n);
    printf("Digite o valor do Levamento saldo da conta: ");
    scanf("%lf", &m);
            
  
 
    struct Conta conta;
    int encontrada = 0;
    double n1,n2,t,m1,m2;
    while (fread(&conta, sizeof(struct Conta), 1, arquivo)==1) {
        if (conta.idconta == id) {
            printf("Conta encontrada:\n");
            printf("Nª da Conta\t Cod. do Cliente\tIBAN\tSaldo\n");    
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);
			n1=n2=conta.saldo;
			m1=m2=m;
			conta.saldo=n1;
			t=n2-m2;
			if(t>=0){
			conta.saldo-=m1;
            long int posicao=sizeof(struct Conta)*(n-1);
			if(fseek(arquivo,posicao, SEEK_SET)!=0){
				printf("Erro no posicionamento do ponteiro");
				fclose(arquivo);
				encontrada = 0;
			   break;
			}
            fwrite(&conta, sizeof(struct Conta), 1, arquivo);
            printf("Saldo Actual da Conta:\n");
            printf("Nª da Conta\tCod.do Cliente\t IBAN\t Saldo\n");    
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);			
			
            encontrada = 1;
            break;	
			}
			else{
				printf("Operação Invalida!\n");
			}		
		
        }
    }
     fclose(arquivo);
  
    if (encontrada) {
        printf("cliente alterado com sucesso!\n");
    } else {
        printf("cliente alterado encontrada.\n");
    }
}

// inserir Cliente
void adicionarcliente() {
    struct Cliente cliente;
    FILE* arquivo2 = fopen("cliente1.txt", "ab");

    printf("Digite o Cod. do Cliente: ");
    scanf("%s", &cliente.bi);
    printf("Digite o nome do Cliente: ");
    scanf("%s",&cliente.nome);
    printf("Digite o morada:");
    scanf("%s", &cliente.morada);    
   
    fwrite(&cliente, sizeof(struct Cliente), 1, arquivo2);

    fclose(arquivo2);

    printf("Cliente adicionada com sucesso!\n");
}

void removercliente() {
    char id[100];
    FILE* arquivo2 = fopen("cliente1.txt", "r+b");

    if (arquivo2 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }
    else{
    printf("Digite o Cod. do Cliente a ser removida: ");
    scanf("%s",&id);

	}
    
    struct Cliente cliente;
    int encontrada = 0;

    FILE* novoArquivo2 = fopen("temp2.txt", "wb");

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2)) {
    	int res=strcmp(cliente.bi,id);
        if (res==(-1)) {
            fwrite(&cliente, sizeof(struct Cliente), 1, novoArquivo2);
        } else {
            encontrada = 1;
        }
    }

    fclose(arquivo2);
    fclose(novoArquivo2);

    remove("cliente1.txt");
    rename("temp2.txt", "cliente1.txt");

    if (encontrada) {
        printf("cliente removida com sucesso!\n");
    } else {
        printf("cliente nao encontrada.\n");
    }
}
void Alterarcliente() {
    char id[100];
    int pos=0,n;
    FILE* arquivo2 = fopen("cliente1.txt", "r+b");

    if (arquivo2 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Cod. do Cliente a ser alterado: ");
    scanf("%s",&id);

   

    printf("Digite  a posicao do Cliente na lista ser alterada: ");
    scanf("%d", &n);
 struct Cliente cliente;
    int encontrada = 0;
  
  
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2)) {
        int res=strcmp(cliente.bi,id);
		if (res == 0) {
            printf("Conta encontrada:\n");
             printf("Digite o Cod. do Cliente: ");
            scanf("%s", &cliente.bi);
            printf("Digite o nome do Cliente: ");
            scanf("%s",&cliente.nome);
            printf("Digite o morada:");
            scanf("%s", &cliente.morada);  
            
            long int posicao=sizeof(struct Cliente)*(n-1);
			if(fseek(arquivo2,posicao, SEEK_SET)!=0){
				printf("Erro no posicionamento do ponteiro");
				fclose(arquivo2);
			   break;
			}
			fwrite(&cliente,sizeof(struct Cliente), 1, arquivo2);
			encontrada = 1;
             break;
		}
	}
      
    fclose(arquivo2);
  
    if (encontrada) {
        printf("cliente alterado com sucesso!\n");
    } else {
        printf("cliente alterado encontrada.\n");
    }
}

void exibircliente() {
    FILE* arquivo2 = fopen("cliente1.txt", "rb");

    if (arquivo2 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    struct Cliente cliente;

    printf("Cod. do Cliente\t Nome \t Morada\n");
     
        
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2)) {
    printf("%s\t\t%s\t%s\n",cliente.bi,cliente.nome,cliente.morada);
    }

    fclose(arquivo2);
}
void pesquisarcliente() {
    char id[100];
    FILE* arquivo2 = fopen("cliente1.txt", "rb");

    if (arquivo2 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Cod. do Cliente a ser pesquisada: ");
    scanf("%s", &id);

    struct Cliente cliente;
    int encontrada = 0;

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2)) {
    	int res=strcmp(cliente.bi,id);
        if (res == 0) {
            printf("Conta encontrada:\n");
          
        printf("Cod. do Cliente\t Nome \t Morada\n");
    
        printf("%s\t\t%s\t%s\n",cliente.bi,cliente.nome,cliente.morada);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("cliente nao encontrada.\n");
    }

    fclose(arquivo2);
}
  
// inserir unsuário
void adicionarusuario() {
    struct Usuario usuario;
    FILE* arquivo1 = fopen("usuario.txt", "ab");

    printf("Digite o Cod. do Usuario: ");
    scanf("%d", &usuario.idusuario);
    printf("Digite o nome do Usuario: ");
    scanf("%s",&usuario.nome);
    printf("Digite o tipo de Usuario->\n 0-Administrador \n 1-Atendente \n 2- Recursos Humano\n");
    scanf("%d", &usuario.tipo);    
    printf("Digite Senha do Usuario: ");
    scanf("%s",&usuario.senha);

    fwrite(&usuario, sizeof(struct Usuario), 1, arquivo1);

    fclose(arquivo1);

    printf("Usuario adicionada com sucesso!\n");
}
void alterarusuario() {
    int id,n;
    FILE* arquivo1 = fopen("usuario.txt", "r+b");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }
    
    printf("Digite o Cod. do usuario a ser alterada: ");
    scanf("%d", &id);
    printf("Digite o a posicao na lista ser alterada: ");
    scanf("%d", &n);

    struct Usuario usuario;
    int encontrada = 0;

    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo1)) {
        if (usuario.idusuario == id) {
            printf("Conta encontrada:\n");
            printf("Digite o Cod. do Usuario: ");
            scanf("%d", &usuario.idusuario);
            printf("Digite o nome do Usuario: ");
            scanf("%s",&usuario.nome);
            printf("Digite o tipo de Usuario->\n 0-Administrador \n 1-Atendente \n 2- Recursos Humano\n");
            scanf("%d", &usuario.tipo);    
            printf("Digite Senha do Usuario: ");
            scanf("%s",&usuario.senha);
            long int posicao=sizeof(struct Usuario)*(n-1);
			if(fseek(arquivo1,posicao, SEEK_SET)!=0){
				printf("Erro no posicionamento do ponteiro");
				fclose(arquivo1);
			   break;
			}
           fwrite(&usuario, sizeof(struct Usuario), 1, arquivo1);
            
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Usuario nao encontrada.\n");
    } else {
        printf("Usuario alterada com sucesso!\n");
    }

    fclose(arquivo1);
}


void removerusuario() {
    int id;
    FILE* arquivo1 = fopen("usuario.txt", "r+b");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Cod. do usuario a ser removida: ");
    scanf("%d", &id);

    struct Usuario usuario;
    int encontrada = 0;

    FILE* novoArquivo1 = fopen("temp1.txt", "wb");

    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo1)) {
        if (usuario.idusuario != id) {
            fwrite(&usuario, sizeof(struct Usuario), 1, novoArquivo1);
        } else {
            encontrada = 1;
        }
    }

    fclose(arquivo1);
    fclose(novoArquivo1);

    remove("usuario.txt");
    rename("temp1.txt", "usuario.txt");

    if (encontrada) {
        printf("usuario removida com sucesso!\n");
    } else {
        printf("usuario nao encontrada.\n");
    }
}


void exibirusuario() {
    FILE* arquivo1 = fopen("usuario.txt", "rb");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    struct Usuario usuario;

  printf("Cod. do Usuario\tNome\tTipo\tSenha\n");
     
        
    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo1)) {
    printf("%d\t\t%s\t%d\t%s\n",usuario.idusuario,usuario.nome,usuario.tipo,usuario.senha);
    }

    fclose(arquivo1);
}
void pesquisarusuario() {
    int id;
    FILE* arquivo1 = fopen("usuario.txt", "rb");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero do usuario a ser pesquisada: ");
    scanf("%d", &id);

    struct Usuario usuario;
    int encontrada = 0;

    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo1)) {
        if (usuario.idusuario == id) {
            printf("Conta encontrada:\n");
            printf("Cod. do Usuario\tNome\tTipo\tSenha\n");
     
            printf("%d\t\t%s\t%d\t%s\n",usuario.idusuario,usuario.nome,usuario.tipo,usuario.senha);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Usuario nao encontrada.\n");
    }

    fclose(arquivo1);
}


// ADICIONAR CONTA
void adicionarConta() {
    struct Conta conta;
    FILE* arquivo = fopen("contas.txt", "ab");

    printf("Digite o Numero da conta: ");
    scanf("%d", &conta.idconta);
    printf("Digite o B.I do titular da conta: ");
    scanf("%s", conta.bi);
    printf("Digite o IBAN do titular da conta: ");
    scanf("%s",  conta.iban);    
    printf("Digite o saldo da conta: ");
    scanf("%lf", &conta.saldo);

    fwrite(&conta, sizeof(struct Conta), 1, arquivo);

    fclose(arquivo);

    printf("Conta adicionada com sucesso!\n");
}
//PESQUISAR CONTA
void pesquisarConta() {
    int id;
    FILE* arquivo = fopen("contas.txt", "rb");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero da conta a ser pesquisada: ");
    scanf("%d", &id);

    struct Conta conta;
    int encontrada = 0;

    while (fread(&conta, sizeof(struct Conta), 1, arquivo)) {
        if (conta.idconta == id) {
            printf("Conta encontrada:\n");
            printf("Nª da Conta\tB.I.\tIBAN\tSaldo\n");
     
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Conta nao encontrada.\n");
    }

    fclose(arquivo);
}
//REMOVER CONTA
void removerConta() {
    int id;
    FILE* arquivo = fopen("contas.txt", "r+b");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero da conta a ser removida: ");
    scanf("%d", &id);

    struct Conta conta;
    int encontrada = 0;

    FILE* novoArquivo = fopen("temp.txt", "wb");

    while (fread(&conta, sizeof(struct Conta), 1, arquivo)) {
        if (conta.idconta != id) {
            fwrite(&conta, sizeof(struct Conta), 1, novoArquivo);
        } else {
            encontrada = 1;
        }
    }

    fclose(arquivo);
    fclose(novoArquivo);

    remove("contas.txt");
    rename("temp.txt", "contas.txt");

    if (encontrada) {
        printf("Conta removida com sucesso!\n");
    } else {
        printf("Conta nao encontrada.\n");
    }
}
//EXIBIR CONTA
void exibirContas() {
    FILE* arquivo = fopen("contas.txt", "rb");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    struct Conta conta;

    printf("Nª da Conta\tB.I.\tIBAN\tSaldo\n");     
    while (fread(&conta, sizeof(struct Conta), 1, arquivo)) {
          printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);
    }

    fclose(arquivo);
}
//ALTERAR CONTA
void alterarConta() {
    int id,n;
    FILE* arquivo = fopen("contas.txt", "r+b");

    if (arquivo == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

    printf("Digite o Numero da conta a ser alterada: ");
    scanf("%d", &id);
    printf("Digite a posicao do Numero Conta na lista ser alterada: ");
    scanf("%d", &n);

    
    struct Conta conta;
    int encontrada = 0;
    while (fread(&conta, sizeof(struct Conta), 1, arquivo)) {
        if (conta.idconta == id) {
            printf("Conta encontrada:\n");
            printf("Nª da Conta\tB.I.\tIBAN\tSaldo\n");    
            printf("%d\t\t%s\t%s\t%.2lf\n", conta.idconta, conta.bi,conta.iban, conta.saldo);
            
		    printf("Digite o Numero da conta: ");
            scanf("%d", &conta.idconta);
            printf("Digite o B.I do titular da conta: ");
            scanf("%s", conta.bi);
            printf("Digite o IBAN do titular da conta: ");
            scanf("%s",  conta.iban);    
            printf("Digite o saldo da conta: ");
            scanf("%lf", &conta.saldo);
            long int posicao=sizeof(struct Conta)*(n-1);
			if(fseek(arquivo,posicao, SEEK_SET)!=0){
				printf("Erro no posicionamento do ponteiro");
				fclose(arquivo);
			   break;
			}
            fwrite(&conta, sizeof(struct Conta), 1, arquivo);
           
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Conta nao encontrada.\n");
    } else {
        printf("Conta alterada com sucesso!\n");
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    int tipo,tp;
    char nome[100];
    char senha[100];
    int p;
    char benvindo[]={'B','E','N','V','I','N','D','O','_','A','O','_','B','A','N','C','O','-','D','V','M'};
    
	system("color 70");
    printf("\t");
    for( p=0; p< 21 ; p++){
    	printf("%c",benvindo[p]);
    	sleep(1);
	}
	printf("\n\n");
    inicio:

    system("color 75");
   
/*
    struct Cliente cliente;
    FILE* arquivo2 = fopen("cliente1.txt", "ab");

    printf("Digite o Cod. do Cliente: ");
    scanf("%s", &cliente.bi);
    printf("Digite o nome do Cliente: ");
    scanf("%s",&cliente.nome);
    printf("Digite o morada:");
    scanf("%s", &cliente.morada);    
   
    fwrite(&cliente, sizeof(struct Cliente), 1, arquivo2);

    fclose(arquivo2);

    printf("Cliente adicionada com sucesso!\n");
    
    struct Usuario usuario;
    FILE* arquivo1 = fopen("usuario.txt", "ab");

    printf("Digite o ID do Usuario: ");
    scanf("%d", &usuario.idusuario);
    printf("Digite o nome do Usuario: ");
    scanf("%s",&usuario.nome);
    printf("Digite o tipo de Usuario->\n 0-Administrador \n 1-Atendente \n 2- Recursos Humano\n");
    scanf("%d", &usuario.tipo);    
    printf("Digite Senha do Usuario: ");
    scanf("%s",&usuario.senha);

    fwrite(&usuario, sizeof(struct Usuario), 1, arquivo1);

    fclose(arquivo1);

    printf("Usuario adicionada com sucesso!\n");
    
    
    
    FILE* arquivo_ = fopen("usuario.txt", "rb");

    if (arquivo_ == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

 
  printf("Cod. do Usuario\tNome\tTipo\tSenha\n");
     
        
    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo_)) {
    printf("%d\t\t%s\t%d\t%s\n",usuario.idusuario,usuario.nome,usuario.tipo,usuario.senha);
    }

    fclose(arquivo_);
   
   
    FILE* arquivo2_ = fopen("cliente1.txt", "rb");

    if (arquivo2_ == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

   
    printf("Cod. do Cliente\t Nome \t Morada\n");
     
        
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2_)) {
    printf("%s\t\t%s\t%s\n",cliente.bi,cliente.nome,cliente.morada);
    }

    fclose(arquivo2_);
   
*/
	printf("\t ESCOLHA O SEU PANEL.....\n");
	printf("1-USUARIO\n2-CLIENTE\n3-LIMPAR A TELA\n0-Sair\n");
    printf("Opcao: ");
    scanf("%d", &tp);
    switch(tp){
    	case 0:
    		printf("App terminado!");
    		break;
    	case 1:
    printf("\t******************************** \n");
    printf("\t**********  LOGIN   ************ \n");
	printf("\t******************************** \n");	
	printf("\t NOME DO USUARIO: \n");
	scanf("%s",&nome);	
	printf("\t SEMHA DO USUARIO: \n");
	scanf("%s",&senha);	
	int id;
  
    FILE* arquivo1 = fopen("usuario.txt", "rb");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }

  
    struct Usuario usuario;
    int encontrada = 0;

    while (fread(&usuario, sizeof(struct Usuario), 1, arquivo1)) {
    	int res1=strcmp(usuario.nome,nome);
    	int res2=strcmp(usuario.senha,senha);
        if (res1==0 && res2==0) {
            printf("Conta encontrada:\n");
            printf("Cod. do Usuario\tNome\tTipo\tSenha\n");  
            printf("%d\t\t%s\t%d\t%s\n",usuario.idusuario,usuario.nome,usuario.tipo,usuario.senha);
            
    if(usuario.tipo==0){
    
         do{
         	//Usuario Administrador
        printf("\t\t Tela de Administrador \n");
        printf("\t Selecione uma opcao:\n");
        printf("\t 1. Adicionar Usuario\n");
        printf("\t 2. Pesquisar Usuario\n");
        printf("\t 3. Remover Usuario\n");
        printf("\t 4. Exibir Usuario\n");
        printf("\t 5. Alterar Usuario\n");
        printf("\t 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
         switch (opcao) {
            case 1:
                adicionarusuario();
                break;
             case 2:
            pesquisarusuario();
                break;
            case 3:
               removerusuario();
                break;
            case 4:
                 exibirusuario();
                break;
            case 5:
            	alterarusuario();
             break;
            case 0:
                printf("Saindo...\n");
                goto inicio;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
         	
		 }while(opcao!=0);
	     	
	}
	else if(usuario.tipo==1){
       //Usuario Atendente	
    do {
    	printf("\t\t Tela do Atendente \n");
        printf("\t Selecione uma opcao:\n");
        printf("\t 1. Adicionar conta\n");
        printf("\t 2. Pesquisar conta\n");
        printf("\t 3. Remover conta\n");
        printf("\t 4. Exibir contas\n");
        printf("\t 5. Alterar conta\n");
        printf("\t Selecione uma opcao de deposito:\n");
        printf("\t 6. Efectuar deposito\n");
        printf("\t 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarConta();
                break;
             case 2:
               pesquisarConta();
                break;
            case 3:
                removerConta();
                break;
            case 4:
                exibirContas();
                break;
            case 5:
                alterarConta();
                break;   
            case 6:
                adicionardeposito();
                break;      
                
            case 0:
                printf("Saindo...\n");
                goto inicio;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

	}		
	 else if(usuario.tipo==2){
       //Usuario Recursos Humanos	
    do {
    	printf("\t\t Tela do Recurso Humano\n");
        printf("\t Selecione uma opcao:\n");
        printf("\t 1. Adicionar Cliente\n");
        printf("\t 2. Pesquisar Cliente\n");
        printf("\t 3. Remover Cliente\n");
        printf("\t 4. Exibir Cliente\n");
        printf("\t 5. Alterar Cliente\n");
        printf("\t 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarcliente();
                break;
             case 2:
             	
                pesquisarcliente();
                break;
            case 3:
                removercliente();
                break;
            case 4:
                exibircliente();
                break;
            case 5:
            	 Alterarcliente();
            	break;
            case 0:
                printf("Saindo...\n");
                goto inicio;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

	}		
			encontrada = 1;
            break;
        }
      /*  else{
        	  printf("Conta Nao encontrada!");
		}*/
    }

    if (!encontrada) {
        printf("Usuario nao encontrada.\n");
    }

    fclose(arquivo1);
		
 	goto inicio;
    	break;
    	
    	
    	case 2:
    printf("\t******************************** \n");
    printf("\t**********  LOGIN   ************ \n");
	printf("\t******************************** \n");
	printf("\t NOME DO CLIENTE: \n");
	scanf("%s",&nome);	
	printf("\t CODIGO DO CLIENTE: \n");
	scanf("%s",&senha);	
    FILE* arquivo2 = fopen("cliente1.txt", "rb");

    if (arquivo1 == NULL) {
        printf("Nenhuma conta encontrada.\n");
        return;
    }
    struct Cliente cliente;
  
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo2)) {
    	int res1=strcmp(cliente.bi,senha);
    	int res2=strcmp(cliente.nome,nome);
        if (res1 == 0 && res2==0) {
            printf("Conta encontrada:\n");
          
        printf("Cod. do Cliente\t Nome \t Morada\n");
    
        printf("%s\t\t%s\t%s\n",cliente.bi,cliente.nome,cliente.morada);
       
       //Cliente	
    do {
        printf("\t\t Tela do Cliente\n");
        printf("\t Selecione uma opcao:\n");
        printf("\t 1. Levantamento\n");
        printf("\t 2. Consultar Conta\n");    
        printf("\t 0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarlevantamento();
                break;
             case 2:
               pesquisarConta();
                break;
           
            case 0:
                printf("Saindo...\n");
                goto inicio;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

	 








            encontrada = 1;
            break;
        }
    }	goto inicio;
    	break;
    	case 3:
    		system("cls");
    		goto inicio;
    		break;
    	default:
    		printf("Dados Invalido!");
	}
    

    
   
   
    return 0;
}


