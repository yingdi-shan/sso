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

@app.route('/', methods=['GET', 'POST'])
def start():
	username = request.form.get('username')
	pwd = request.form.get('password')

	if username is not None and pwd is not None:
		url = baseurl + 'login?username='+username+'&pwd='+pwd
		try:
			response, content = http.request(url, 'GET')
			if content == 'SUCCESS':
				return redirect('/welcome')
			return render_template('index.html')
		except:
			print "sso failed"
			return redirect('/')
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
			return redirect('/')
		except:
			print 'sso failed'
			return render_template('register.html')
	
	return render_template('register.html')
