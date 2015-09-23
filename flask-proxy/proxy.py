import urllib
import httplib2

import time

start = time.time()

for i in range(0, 2000+1):
	http = httplib2.Http()

	url = 'http://0.0.0.0:8080/login?username=lmx&pwd=123'
	body = {'username': 'lmx', 'pwd': '123'}

	headers = {'Content-type': 'application/x-www-form-urlencoded'}  
	response, content = http.request(url, 'GET', headers=headers, body=urllib.urlencode(body))


end = time.time()

print end - start
