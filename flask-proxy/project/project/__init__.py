# -*- coding: utf-8 -*-

__version__ = '0.1'

from flask import Flask
app = Flask('project')
app.config['SECRET_KEY'] ='random'
app.config.from_object('config')

import project.models
import project.controller


