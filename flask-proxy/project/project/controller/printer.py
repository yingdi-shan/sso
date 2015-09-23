from project import app
from project.models import Printer
from flask import render_template, request, make_response

import urllib
import httplib2

http = httplib2.Http(timeout=0.5)

def hash_str(username):
	s = list(username)
	a = 0
	for c in s:
		a = a*33 + ord(c)
	return a

@app.route('/')
def start():
    return render_template('index.html')


@app.route('/add_user', methods=['GET', 'POST'])
def add_user():
	username = str(request.args.get('username'))
	pwd = str(request.args.get('pwd'))

	i = hash_str(username)%app.config['SERVER_NUMBER']
	url = 'http://' + app.config['SERVER_IPS'][i] + '/add_user?username='+username + '&pwd='+pwd

	print url
	headers = {'Content-type': 'application/x-www-form-urlencoded'}  

	try:
		response, content = http.request(url, 'GET', headers=headers)
		return content
	except:
		return "failed to connect sso"
	finally:
		pass

@app.route('/update_user', methods=['GET', 'POST'])
def update_user():
	username = str(request.args.get('username'))
	pwd = str(request.args.get('pwd'))
	new_pwd = request.args.get('new_pwd')

	i = hash_str(username)%app.config['SERVER_NUMBER']
	url = 'http://' + app.config['SERVER_IPS'][i] + '/update_user?username='+username+'&pwd='+pwd+'&new_pwd='+new_pwd

	headers = {'Content-type': 'application/x-www-form-urlencoded'}  
	
	try:
		response, content = http.request(url, 'GET', headers=headers)
		return content
	except:
		return "failed to connect sso"
	finally:
		pass

@app.route('/verify_token', methods = ['GET', 'POST'])
def verify_token():
	username = str(request.args.get('username'))
	token_id = str(request.cookies.get('TOKEN_ID'))
	print token_id

	headers = {'Content-type': 'application/x-www-form-urlencoded', 'Cookie': 'TOKEN_ID='+token_id}
	print headers

	i = hash_str(username)%app.config['SERVER_NUMBER']
	url = 'http://' + app.config['SERVER_IPS'][i] + '/verify_token?username='+username

	try:
		response, content = http.request(url, 'GET', headers=headers)
		print content
		return content
	except:
		return "connect failed"
	finally:
		pass

@app.route('/login', methods = ['GET'])
def login():
	username = str(request.args.get('username'))
	pwd = str(request.args.get('pwd'))

	i = hash_str(username)%app.config['SERVER_NUMBER']
	url = 'http://' + app.config['SERVER_IPS'][i] + '/login?username='+username+'&pwd='+pwd

	headers = {'Content-type': 'application/x-www-form-urlencoded'}  
	
	try:
		response, content = http.request(url, 'GET', headers=headers)

		resp = make_response(content)

		if content == 'SUCCESS':
			token_id = response['set-cookie'].split('=')[1]
			print token_id

			resp.set_cookie('TOKEN_ID', token_id)

			return resp
		else:
			return resp
	except:
		return "connect failed"
	finally:
		pass