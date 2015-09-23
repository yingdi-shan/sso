import httplib2

f = open('http.txt', 'r')

for line in f.readlines():

	url = line
	headers = {'Content-type': 'application/x-www-form-urlencoded'}  
	http = httplib2.Http(timeout=1.5)

	try:
		response, content = http.request(url, 'GET', headers=headers)
		print content
	except:
		print "failed"