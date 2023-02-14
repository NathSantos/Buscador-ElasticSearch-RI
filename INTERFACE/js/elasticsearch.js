const { Client } = require('es7')

const client = new Client({ node: 'http://localhost:9200' })

//client.info(console.log)

client.search({
  index: 'regis_collection',
  body: {
    query: {
      match: { text: 'História da geoquímica na Petrobras' }
    }
  }
}, (err, result) => {
  if (err) console.log(err)
  else console.log(result.body.hits)
})


// console.log(result.body.hits) - printa os docs resultantes
// console.log(result.body.hits.hits) - printa todos os textos dos docs resultantes