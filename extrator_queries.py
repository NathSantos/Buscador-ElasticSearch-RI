import xml.etree.ElementTree as et

#extrai par [id, texto] de todas as queries
arquivo = et.parse('queries.xml')
raiz = arquivo.getroot()
queries = []
for filho in raiz:
    queries.append([filho[0].text, filho[1].text])


#extrai os resultados de qrels.txt
arquivo = open("qrels.txt", "r")
queries_results = []
for line in arquivo.readlines():
    content = line.split()
    content[2] = content[2][6:]
    content.pop(1)
    queries_results.append(content)




arquivo.close()