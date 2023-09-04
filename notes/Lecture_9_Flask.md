# Flask
Web framework in Python.
Jinja - syntax for using placeholders in web page?

## HTTP Requeests

GET - not secure, will show stuff in plain text in the URL
POST - burries stuff deeper in packates so are not visible in header. Shows in plain text under Payload in Dev tools\network

Google get request for serching:
GET /search?q=cats

To run flask web server, execute flask run in terminal.

## Flask app layout

app.py # main application file
requirements.txt # dependencies which autoinstall
templates/
static/ # folder for static files, images, js files, etc.

## Hello wrold

app.py
```python

from flask import Flask, render_template, request

app = Flask(__name__) ## __name__ refers to this file (to itslef)

@app.route("/") ## when user wisits / (root, home), execute function below
def index():
  # return "hello, world" # to put html here manually
  return render_template("index.html") # to use html template from /template folder, it looks for templates/index.html so you need to have it there

```
## Getting user input by using request variable

app.py
```python

from flask import Flask, render_template, request

app = Flask(__name__) ## __name__ refers to this file (to itslef)

@app.route("/") ## when user wisits / (root, home), execute function below
def index():
  # Isntead of this
  #if "name" in request.args: # request.args is dictionary which will pickup key-value pairs #from url link if we use them. In URL, https://yourling/?key=value
  #  name = request.args["name"]
  #else:
  #  name = "world"
  
  # we can do this
  name = request.args.get("name", "world") # This searches for name key in the link, in case it's not there, defautls to "world"
  
  return render_template("index.html", placeholder = name) # We need to have a jinja placeholder variable name equal to our request variable name here
```

To have this work in html, we need placeholders.
```html
<!DOCTYPE html>

<html lang="en">
  <head>
    </title>Hello, title</title>
  </head>
  <body>
    hello, {{ placeholder }} <!-- Jinja syntax for templating -->
  </body>
</html>

```


## Handling dynamics with forms

app.py
```python

from flask import Flask, render_template, request

app = Flask(__name__) ## __name__ refers to this file (to itslef)

@app.route("/") ## when user wisits / (root, home), execute function below
def index():

  return render_template("index.html", placeholder = name) 

@app.route("/greet", methods=["POST"]) ## when user submits form with action "/greet", execute function below
def greet():
  return renter_template("greet.html", name=request.form.get("name", "world")) # If we use POST, we need request.form (request.args only works for GET)
```

Templates:

```html
<!DOCTYPE html>

<html lang="en">
  <head>
    </title>Hello, title</title>
  </head>
  <body>
    <form action="/greet" method="get">
      <input autocomplete="off" autofocus name="Name" name="name" type="text">
      <button type="submit"> Greet </button>
      <!-- Once user submits this, it will trigger greet method which by the route definition in app.py will render greet.html below with user inputed value as a placeholder -->
    </form> 
  </body>
</html>
```

```html
# This is for greet form fuction
<!DOCTYPE html>

<html lang="en">
  <head>
    </title>Hello, title</title>
  </head>
  <body>
    hello, {{ name }} <!-- Jinja syntax for templating -->
  </body>
</html>
```



## Templating

Inserting other template files

We create layout.html file which will be main template, then plug in other stuff from other files.

**templates/layout.html**
```html
<!DOCTYPE html>

<html lang="en">
  <head>
    </title>Hello, title</title>
  </head>
  <body>
    {% block body %}{% endblock %}  <!-- Jinja syntax, means here we'll be pluging something when we use this file as a template -->
  </body>
</html>
```

**templates/index.html**
```html
{% extends "layout.html" %} <!-- Here we are loading our main template file -->

{% block body %} <!-- Here start's the body from the template ({% block body %}) -->
    <!-- Template expects custom stuff here so either manually or from other templates we can plug things in -->
   hello, {{ name }} 
{% endblock %} <!-- Here body is ending from the template {% endblock %}  -->
```

## Cookies

Session data planted on computer which maintains credibility, integrity, data or configuration between host and the server.

Flask brings session variable for this.


## API

Application programming interface - any interfacing with fuctions offered by some service.

**AJAX** - Asynchronous JavaScript And XML
Its the use of the XMLHttpRequest object to communicate with servers. It can send and receive information in various formats, including JSON, XML, HTML, and text files.

**JSON** - Javascript Object Notation 
Format for exchanign data resebling JS objects. Usually, API will return requested data in this format.
