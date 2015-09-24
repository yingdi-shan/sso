from project import app
from project.models import Printer
from flask import render_template, request, make_response, redirect, url_for

import urllib
import httplib2

http = httplib2.Http(timeout=0.5)

baseurl = "http://0.0.0.0:5000/"

def hash_str(username):
	s = list(username)
	a = 0
	for c in s:
		a = a*33 + ord(c)
	return a

@app.route('/', methods=['GET'])
def start():
	token = request.cookies.get('TOKEN_ID')
	username = request.cookies.get('username')

	if username is None:
		print "username miss"
	if token is None:
		print "token miss"

	if token is not None and username is not None:
		url = baseurl + 'verify_token?username=' + username
		print url
		headers = {"Cookie": "TOKEN_ID="+token}
		try:
			response, content = http.request(url, 'GET', headers=headers)
			print content
			if content == 'SUCCESS':
				return render_template('welcome.html')

			return redirect('https://0.0.0.0:1024/login')
		except:
			return redirect('https://0.0.0.0:1024/login')
		finally:
			pass
	return redirect('https://0.0.0.0:1024/login')

@app.route('/login', methods=['GET', 'POST'])
def login():
	username = request.form.get('username')
	pwd = request.form.get('password')

	if username is not None and pwd is not None:
		url = baseurl + 'login?username='+username+'&pwd='+pwd
		try:
			response, content = http.request(url, 'GET')
			if content == 'SUCCESS':
				print response
				resp = make_response(render_template('welcome.html'))

				response_cookie = response['set-cookie'].split(';')[0]
				resp.set_cookie('TOKEN_ID', response_cookie.split('=')[1], max_age=10000)
				resp.set_cookie('username', username, max_age=10000)

				return resp
			print content

			return render_template('index.html')
		except:
			print "sso failed"
			return render_template('index.html')

	return render_template('index.html')


@app.route('/welcome', methods=['GET', 'POST'])
def welcome():
	return render_template('welcome.html')

@app.route('/register', methods=['GET', 'POST'])
def register():

	username = request.form.get('username')
	pwd = request.form.get('password')

	if username is not None and pwd is not None:
		url = baseurl + 'add_user?username='+username+'&pwd='+pwd
		try:
			response, content = http.request(url, 'GET')
			return redirect('https://0.0.0.0:1024/login')
		except:
			print 'sso failed'
			return render_template('register.html')
	
	return render_template('register.html')
