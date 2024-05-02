# ALUNOS

- [Andrei Rech | 23102140](https://github.com/AndreiRech)  
- [Eduardo Colla De Bastiani | ](https://github.com/eduardo-de-bastiani)
- [Mariah Backes Freire | ](https://github.com/mariahbf)

# INTRODUÇÃO

Biblioteca para Controle de Hardware Através de Registradores Mapeados em Memória em C

# 🛠 PRÉ REQUISITOS

É necessária a utilização de um sistema operacional baseado em Linux. Caso deseje acessar utilizando windows, recomenda-se a utilização do [WSL](https://learn.microsoft.com/pt-br/windows/wsl/install)

# ⚙ INICIALIZAÇÃO

- **EDIÇÃO**

Para podermos editar o projeto, é necessário abrir o terminal e digitar:

```bash
    gcc main.c register.c -o exec
```

```bash
    ./exec
```

Em outro terminal, acesse o emulador, utilizando:

```bash
    ./emulator
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
- [ ] Selecionar o modo de exibição
- [X] Define velocidade de atualização do display em valores múltiplos de 100 milisegundos para modo de exibição não estático
- [X] Liga/Desliga o LED de operação
- [X] Liga/Desliga o LED de status e define cor

**REGISTRADOR 1/2**

- [X] Mudar cor do display 

**REGISTRADOR 3**

- [X] Nível da bateria
- [ ] Mudar temperatura
- [ ] Verificar quantidade de repetições
- [ ] Resetar quantidade de repetições

**REGISTRADOR 4-15**

- [ ] Mudar mensagem do display

**AUXILIARES**

- [ ] Printar valores de todos os registradores
- [ ] Voltar registradores ao padrão  