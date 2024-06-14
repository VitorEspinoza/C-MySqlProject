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

 - Rodar o script sql para criação das tabelas e seus relacionamentos (script.sql)

### Config da biblioteca mysql com C no DEV-C++
 - Incluir arquivo "libmysql.dll" na pasta do projeto, encontrado na pasta lib do MySql (ex: C:\Program Files\MySQL\MySQL Server 8.0\lib)
 - Caso seu MySql não esteja instalado no disco padrão do windows ou você use outro sistema operacional, você deve:
   - Pressione ctrl + h para abrir as opções do projeto e vá para Directories.
   - Na aba de library directories adicione o caminho da pasta lib do MySQL (ex: C:\Program Files\MySQL\MySQL Server 8.0\lib)
   - Na aba de include directories adicione os caminhos para as pastas include e include/mysql (ex: C:\Program Files\MySQL\MySQL Server 8.0\include & C:\Program Files\MySQL\MySQL Server 8.0\include\mysql)

### Como rodar

 #### Abrir o projeto na IDE
 - Criar pasta destinada ao projeto
 - Clonar o projeto do github na pasta criada. `git clone https://github.com/VitorEspinoza/C-MySqlProject.git`
 - Abrir o DEV-C++
 - File -> Open OU ctrl + o
 - Selecionar o arquivo TrabFinalLingProg.dev

 ### Configurar a conexão com o banco
 - Abrir o arquivo databaseConnection.h
 - Configurar as variáveis HOST, USER, PASS de acordo com as configurações do seu MySql

 ### Rodar
 - Rebuild All(f12) e run(f10)

