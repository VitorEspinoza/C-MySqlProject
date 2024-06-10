# Banco C MySQL

## Descrição

Este app simula um banco e os métodos possíveis do banco como transação, saque e etc.

Construído em C com a lib mysql do C para conexão com o banco de dados.

Projeto realizado como parte da avaliação da disciplina DS123 Lingauem de Programação.

## Instalação

### Pré-requisitos

 - IDE DEV-C++
 - MySQL 8.0.37
 - Connector/ODBC 8.0.32 x64 & x86

### MySQL Config

 - Criar um schema (nome padrão no projeto: banco)
 - Rodar o script sql para criação das tabelas e seus relacionamentos (banco.sql)

### Config da biblioteca mysql com C no DEV-C++

 - Pressione ctrl + h para abrir as opções do projeto e vá para Directories.
 - Na aba de library directories adicione o caminho da pasta lib do MySQL (ex: C:\Program Files\MySQL\MySQL Server 8.0\lib)
 - Na aba de include directories adicione os caminhos para as pastas include e include/mysql (ex: C:\Program Files\MySQL\MySQL Server 8.0\include & C:\Program Files\MySQL\MySQL Server 8.0\include\mysql)
 - Vá para a Parameters nas opções do projeto e no bloco Linker adicioner o texto -lmysql

### Como rodar

 #### Abrir o projeto na IDE
 - Criar pasta destinada ao projeto
 - Clonar o projeto do github na pasta criada. git clone https://github.com/VitorEspinoza/C-MySqlProject.git
 - Abrir o DEV-C++
 - File -> Open OU ctrl + o
 - Selecionar o arquivo TrabFinalLingProg.dev

 ### Configurar a conexão com o banco
 - Abrir o arquivo databaseConnection.h
 - Configurar as variáveis HOST, USER, PASS e SCHEMA de acordo com o seu banco

 ### Rodar
 - Rebuild All(f12) e run(f10)

