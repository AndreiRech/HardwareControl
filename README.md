# ALUNOS

- [Andrei Rech | 23102140](https://github.com/AndreiRech)  
- [Eduardo Colla De Bastiani | 23106295](https://github.com/eduardo-de-bastiani)
- [Mariah Backes Freire | 23102560](https://github.com/mariahbf)

# INTRODUÇÃO

Biblioteca para Controle de Hardware Através de Registradores Mapeados em Memória em C

# 🛠 PRÉ REQUISITOS

É necessária a utilização de um sistema operacional baseado em Linux. Caso deseje acessar utilizando windows, recomenda-se a utilização do [WSL](https://learn.microsoft.com/pt-br/windows/wsl/install)

# ⚙ INICIALIZAÇÃO

- **EDIÇÃO**

Para podermos editar o projeto, é necessário abrir o terminal e digitar:

```bash
    make
```

```bash
    ./exec
```

Em outro terminal, acesse o emulador, utilizando:

```bash
    ./emulator
```

Após ter termiado, utilize o comando abaixo para limpar os arquivos criados:

```bash
    make clean
```

*Toda vez que fizer alguma alteração deve refazer os primeiros dois passos para mostrar no terminal*

- **VISUALIZAÇÃO**

Para visualizar o projeto, apenas utilize o comando a seguir:

```bash
    ./emulator
```

# O QUE FAZER

Aqui está a lista de a fazeres do trabalho.

**REGISTRADOR 0**

- [X] Liga/Desliga o display
- [X] Verificar situacao do display         
- [X] Selecionar o modo de exibição
- [X] verificar modo de exibicao            
- [X] Define velocidade de atualização do display em valores múltiplos de 100 milisegundos para modo de exibição não estático
- [X] verifica velocidade de atualizacao
- [X] Liga/Desliga o LED de operação
- [X] verifica situacao led de operacao     
- [X] Liga/Desliga o LED de status e define cor
- [X] Verificar cor LED de status

**REGISTRADOR 1/2**

- [X] Mudar cor do display 

**REGISTRADOR 3**

- [X] Retornar nível da bateria
- [X] Definir nivel da bateria (opcional)
- [X] Retornar nível bateria
- [X] Mudar temperatura (opcional) - *implementada - verificar implementação do negativo*
- [X] Verificar quantidade de repetições
- [X] Fazer o Makefile funcionar

**REGISTRADOR 4-15**

- [X] Mudar mensagem do display - *implementado - implementando com mais de 24 caracteres*

**AUXILIARES**

- [X] Voltar registradores ao padrão
