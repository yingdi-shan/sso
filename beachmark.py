import httplib2
import threading
import time
import random

runtime = 5
thread_num = 100
baseurl = 'http://127.0.0.1:5000/'

x = 0

def random_str(number):
	return ''.join(random.sample('zyxwvutsrqponmlkjihgfedcba0123456789',number))

def add_user():
	global x
	username = random_str(8)
	pwd = random_str(16)
	start = time.time()

	while(time.time() - start) < runtime:
		url = baseurl + 'add_user?username='+username+'&pwd='+pwd

		try:
			http = httplib2.Http(timeout = 0.5)
			response, content = http.request(url, 'GET')
			x=  x+1
		except:
			print 'except'
		finally:
			pass

def login():
	global x
	username = 'lmx'
	pwd = '123'
	start = time.time()
	while (time.time() - start) < runtime:
		url = baseurl + 'login?username='+username+'&pwd='+pwd
	
		try:
			http = httplib2.Http(timeout=0.5)
			response, content = http.request(url, 'GET')
			x = x + 1
		except:
			print 'except'
		finally:
			pass

def test(func):
	print 'test'
	try:
		threads = []
		for i in range(1, thread_num+1):
			threads.append(threading.Thread(target=func))

		start = time.time()

		for t in threads:
			t.start()

		for t in threads:
			t.join()

		print time.time() - start
		print x

	except:
		print 'thread create error'
	finally:
		pass

test(add_user)

