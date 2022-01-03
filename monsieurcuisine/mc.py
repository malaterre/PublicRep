import requests
from bs4 import BeautifulSoup

headers = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Methods': 'GET',
    'Access-Control-Allow-Headers': 'Content-Type',
    'Access-Control-Max-Age': '3600',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0'
    }

url = "https://shop.monsieur-cuisine.com/fr/monsieur-cuisine-connect/124-messereinsatz-mit-dichtungsring.html"
req = requests.get(url, headers)
soup = BeautifulSoup(req.content, 'html.parser')
#print(soup.prettify())

span = soup.find(id="product-availability")
#print(span)
#print(list(span))
#print(type(span))
#del span.i
#print(span.attrs)
#print(span.contents)

refstr = 'Rupture de stock'

rupture = False
for string in span.stripped_strings:
    #print(string)
    if string == refstr:
      rupture = True
print(rupture)
    
#print(span.string)
#text = span.get_text().strip()
#print(text)
