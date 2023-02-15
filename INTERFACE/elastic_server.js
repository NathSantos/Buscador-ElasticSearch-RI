const path = require('path');
const axios = require('axios');
const express = require('express');

const app = express();

app.get('/', function (req, res) {
  const filePath = path.join(__dirname, 'index.html');
  res.sendFile(filePath);
});

app.get('/style.css', function(req, res) {
  res.set('Content-Type', 'text/css');
  res.sendFile(path.join(__dirname, 'style.css'));
});

app.get('/images/:imagem', function(req, res) {
  const imagem = req.params.imagem;
  const imagePath = path.join(__dirname, 'images', imagem);
  res.sendFile(imagePath, function(err) {
    if (err) {
      console.log(err);
      res.status(err.status).end();
    }
  });
});

app.get('/script.js', function(req, res) {
  res.set('Content-Type', 'text/js');
  res.sendFile(path.join(__dirname, 'script.js'));
});

app.get('/buscar', async function (req, res) {
  const termo = req.query.termo;

  try {
    const response = await axios.get('http://localhost:9200/regis_collection/_search', {
      params: {
        q: `text:${termo}`,
      },
    });

    const hits = response.data.hits.hits;

    if (hits.length === 0) {
      console.log(`Nenhum resultado encontrado para a busca: ${termo}`);
    }

    res.json(hits);
  } catch (err) {
    console.error(`Erro ao buscar por ${termo}: ${err.message}`);
    res.status(500).send(err.message);
  }
});

const PORT = process.env.PORT || 4000;
app.listen(PORT, function () {
  console.log(`Servidor rodando na porta ${PORT}`);
});
