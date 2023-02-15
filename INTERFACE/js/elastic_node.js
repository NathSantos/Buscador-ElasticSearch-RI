const path = require('path');
const axios = require('axios');
const express = require('express');

const app = express();

app.get('/', function (req, res) {
  const filePath = path.join(__dirname, 'teste.html');
  res.sendFile(filePath);
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

const PORT = process.env.PORT || 3000;
app.listen(PORT, function () {
  console.log(`Servidor rodando na porta ${PORT}`);
});
