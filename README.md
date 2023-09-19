<h1 align="center">
	✏️ WebServ
</h1>

<p align="center"><br>
Esse projeto é sobre escrever seu próprio servidor HTTP. Uma versão <i>bem</i> mais simplificada de um NGINX ou Apache.<br>
Nele é possível configurar seu(s) servidor(es) com porta, server_name, rotas e muito mais.<br>
</p>

<p align="center">
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/rafaelabdm/Webserv?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/rafaelabdm/Webserv?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/rafaelabdm/Webserv?color=green" />
</p>

<p align="center">
<SUB>Por Rafaela Bustamante e Raphael dos Santos Esteves, cadetes na 42 São Paulo.</SUB>
</p>

---

<h2>📃 Sobre o projeto</h2>

> _This is when you finally understand why a URL starts with HTTP_
<p>
Para fazer um servidor web, primeiro precisamos aprender sobre <b>sockets</b> (ou soquetes). Depois sobre I/O Multiplexing com select(), poll() ou epoll(). 
E, por fim, seguir o protocolo HTTP para transferência de informação entre nosso servidor e o cliente. Esse protocolo nada mais é do que uma padronização para 
o envio de informações pela web. Os requisitos mínimos para seu funcionamento, é informar o protocolo (HTTP/1.1, é o que vamos usar) e o status da resposta (200 
OK, 404 Not Found, etc...). Outras informações que podemos enviar são: o tipo de conteúdo da resposta (se é texto ou imagem), a data, o tamanho da resposta, 
o corpo da resposta (a página html de um site, por exemplo), entre outras mais. Podemos checar todos os requsitos lendo o próprio 
<a href=https://www.ietf.org/rfc/rfc2616.txt>Hypertext Transfer Protocol -- HTTP/1.1</a>.
</p>

<h2>📩 Métodos implementados</h2>
<p>
<b>GET:</b> ao bater em uma rota do nosso servidor, que são configuradas no arquivo .conf, o cliente usa o método GET para receber de volta o conteúdo da página ou arquivo
que está acessando.<br><br>
<b>POST:</b> ao usar o método POST em uma rota que aceita esse método, o cliente consegue mandar informações para o nosso servidor processar. Pode ser uma imagem/texto pra ser 
armazenada no servidor, ou um texto para ser mandado para um programa que vai ser executado, entre outros usos diversos.<br><br>
<b>DELETE:</b> ao usar o método DELETE em uma das rotas que aceita esse método, o cliente consegue informar qual conteúdo quer retirar do servidor, informando o nome do 
arquivo.<br>
</p>

<h2>🔨 O que pode ser configurado</h2>
<ul>
<li><b>SERVER NAME</b>: nome do seu servidor, o que vem logo após o "http://SERVER_NAME", pode ser qualquer coisa, desde que conste no arquivo hosts da sua máquina local;</li>
<li><b>PORT</b>: porta que seu servidor vai escutar -> "http://SERVERNAME:PORT". Fique lembrado que portas abaixo de 1024 precisa de permissão sudo para rodar;</li>
<li><b>ERROR PAGES</b>: páginas de erro personalizadas para o servidor, caso não queira usar as páginas default;</li>
<li><b>ROOT</b>: diretório correspondente à rota buscada pelo cliente. Onde será buscado o recurso requisitado;<br></li>
<li><b>INDEXES</b>: arquivo que vai responder caso a rota aponte para um diretório do servidor. Normalmente combinamos Root+Indexes para responder o cliente;</li>
<li><b>REDIRECT</b>: rota que se o cliente acessar, irá redirecioná-lo para outro endereço;</li>
<li><b>AUTOINDEX</b>: ao habilitar a listagem de diretório o cliente consegue navegar pelas pastas daquela rota como se fossem páginas html;</li>
<li><b>ALLOWED METHODS</b>: métodos permitidos naquela rota. Por padrão são permitidos todos os implementados;</li>
<li><b>UPLOAD DIR</b>: onde serão salvos os arquivos que o cliente quiser armazenar no servidor. Importante lembrar que o diretório deve existir no camihho especificado 
pelo Root para conseguir salvar o arquivo de fato. Caso não exista o servidor devolverá 404;</li>
<li><b>MAX BODY SIZE</b>: o tamanha máximo do arquivo que pode ser armazenado no servidor. Por padrão é 1MB;</li>
<li><b>CGI</b>: habilita sites diâmicos, em que o conteúdo da página quando o cliente acessar pode mudar de acordo com o programa que estiver rodando por trás dela.</li>
</ul>

<h2>⚙️ Como configurar seu servidor</h2>

```
# Exemplo de arquivo de configuração para servidor HTTP

# Configurações para o primeiro servidor
server {
	port			8080			# Porta do servidor
	server_names		localhost		# Nome do servidor (opcional)
	error_page		404 404.html		# Página de erro personalizada (opcional)

	# Configurações para rotas
	location / {
		root	/var/www/html			# Diretório raiz da rota
		indexes	index.html index2.html		# Páginas de índice padrão da rota
	}

	location /about {
		root	/var/www/html
		indexes	about.html
	}

	# Configuração para rota que redireciona
	location /redirect {
		root				/var/www/html
		redirect			/about		# Redireciona para a rota /about
	}

	# Configuração para rota que aceita uploads de arquivos
	location /upload {
		root			/var/www/html
		indexes			upload.html
		allowed_methods		GET POST		# informa quais métodos são permitidos nessa rota (opcional)
		upload_dir		/var/www/uploads	# Diretório onde os arquivos enviados serão salvos (opcional)
		max_body_size		300000			# Tamanho permitido do arquivo em bytes (opcional)
	}

	# Configuração para rota que executa um CGI
	location /delete {
		root			/var/www/html/delete
		indexes			delete.html
		allowed_methods		GET DELETE		
	}

	# Configuração para rota que executa um CGI
	location /cgi {
		root		/var/www/cgi
		indexes		game.py				# arquivo do programa a ser executado
	}

	location /autoindex {
		root			/var/www/html/autoindex
		autoindex		true			# habilita listagem de diretórios
	}
}
```

<h2>💻 Como usar</h2>
<p>
Na pasta raiz do projeto rode o Makefile: <TT>make</TT> <br>
Depois de compilado, suba o servidor com as configurações padrão: <TT>./webserv</TT> <br>
Ou com o arquivo de configuração de sua escolha: <TT>./webserv [caminho_para_seu_arquivo.conf]</TT>
</p>
