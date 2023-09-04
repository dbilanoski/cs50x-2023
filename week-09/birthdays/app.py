import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # Get data from the form
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        # Insert form data to database
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        # Return to home page
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)

# Removal route


@app.route("/deregister", methods=["POST"])
# Removal function
def deletion():
    # Get ID from the form
    id = request.form.get("id")
    # Check if id exists, if yes, remove from the database
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    # Return to home page
    return redirect("/")
