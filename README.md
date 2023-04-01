# Trabalho-RI-elastic-search

Este trabalho consiste em um buscador que pesquisa consultas digitadas na interface pelo usuário e as busca na base de documentos indexados no ElasticSearch.

A versão utilizada do ElasticSearch foi a ```7.17.8```.

A seguir estão as instruções de como proceder para utilizar o código, de acordo com seu sistema:

## Instalando e executando o ElasticSearch

 - Siga o passo a passo a seguir para instalar e executar o ElasticSearch de acordo com o seu sistema: https://www.elastic.co/guide/en/elasticsearch/reference/7.17/install-elasticsearch.html
 
 - Para verificar se o ElasticSearch está corretamente executado, digite ```localhost:9200``` na url de um web browser e verifique se a conexão foi realmente estabelecida (obs: 9200 é a porta padrão do elasticsearch, caso você tenha alterado essa porta, digite o número da nova porta)
 
 ## Indexando documentos no ElasticSearch
 
 - Para este trabalho, foi utilizado a base de documentos da Petrobras: https://github.com/Petroles/regis-collection/tree/master/documents
 
 - Após ter baixado os documentos e salvado eles em uma pasta (ex: 'regis_collection/documents'), abra o arquivo 'indexing_documents.py'
 
 - Na seguinte célula, modifique o "path_to_data" para o diretório da pasta onde estão os documentos baixados:
 
```Python 
position_start_id = 6 

def id_converter(id):
    id = id[position_start_id:]
    return id

def text_converter(text):
    text = text.replace("\"", " ")
    text = text.replace("\n", " ")
    return text
#put here the path for regis-collection-master
path_to_data = 'regis_collection/documents'

files_names = os.listdir(path_to_data)
```

  - Em seguida, rode todas as células do notebook e aguarde a indexação de todos os documentos (obs: no código, estamos indexando os documentos no índice ```regis_collection``` mas caso você queira, pode trocar o nome no próprio notebook).
  
  - Ao concluir a indexação dos documentos, a seguinte célula deve retornar um documento presente no índice ```regis_collection```:
 
 ```Python 
 es.get(index="regis_collection", id=x)
 ```

## Abrindo e utilizando o Buscador

  - Após os documentos terem sido indexados, estamos prontos para usar o buscador. Entretanto, antes precisamos instalar alguns frameworks e bibliotecas que estão sendo utilizados no código. 
  
  - Assumindo que você tenha o Node.js e o npm (Node Package Manager) instalados no seu computador, você deve instalar os seguintes pacotes _**caso ainda não os tenha em seu sistema**_. Para isso, execute os seguintes comandos dentro do diretório principal do trabalho (obs: no trabalho foram utilizadas as versões ```v18.4.0``` do Node e ```9.3.1``` do npm):
  
 ```
 $ npm install jquery
 ```
 
 ```
 $ npm install ajax
 ```
 
 ```
 $ npm install axios
 ```
 
 ```
 $ npm install express
 ```
 
 ```
 $ npm install path
 ```

  - Após a instalação dos pacotes, navegue no terminal até a pasta ```INTERFACE```:
  
  ```
  $ cd INTERFACE
  ```
  
  - Em seguida, execute o servidor:
  
  ```
  $ node elastic_server.js
  ```
  
  - Caso tudo tenha sido executado corretamente, a mensagem "_Servidor rodando na porta 4000_" deve aparecer no terminal.
  
  - Com o servidor e o elasticsearch sendo executados, você já pode abrir o buscador em ```localhost:4000``` e realizar sua busca.
  
  - Caso você esteja utilizando a base de documentos da Petrobras, os campos <title> do arquivo ```queries.xml``` servem como consultas que podem ser feitas no buscador.
 
## Finalizando o servidor e o elasticsearch

  - Quando você desejar terminar a conexão com o servidor e com o elasticsearch, basta apertar ```Ctrl+C``` no terminal onde está sendo executado cada um e a conexão se encerrará.
