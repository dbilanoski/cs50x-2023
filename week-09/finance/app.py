import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get db and user data
    user_id = session["user_id"]

    # Get user's name
    user_name_query = user_money_query = db.execute(
        "SELECT username FROM users WHERE id = ?", user_id)
    # This returns array of dictionaries
    # Get cash value from the recieved dictionary in user_money_query
    user_name = user_name_query[0]["username"]

    # Get each stock total balance from pruchases table
    # Will need to get each stock, then for each select symbol, sum of shares, and price for the currently loged in user
    # SELECT symbol, SUM(shares) AS shares, price, shares*price AS total FROM purchases WHERE user = user_id GROUP BY symbol ORDER BY SUM(shares);
    # purchases = db.execute("SELECT symbol, SUM(shares) AS shares, price, shares*price AS total FROM purchases WHERE user = ? GROUP BY symbol ORDER BY SUM(shares)", user_id)
    # No good, I need to lookup current price for each stock so will grab sum of shares per stock and use it to create another dictionary where I'll store lookup data
    purchases = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM purchases WHERE user = ? GROUP BY symbol", user_id)

    # Loop over user stock holdings and get the current price from the yahoo api. Use/calculate rest of the data for new dict object to carry to the template
    # Will have symbol, shares, price, total
    user_portfolio = []
    for index, purchase in enumerate(purchases):
        # Get current price using lookup function from helper.py and convert to float
        current_price = float(lookup(purchase["symbol"])["price"])

        # Create new dictionary for current symbol and append values
        index = {
            "symbol": purchase["symbol"],
            "shares": purchase["shares"],
            "price": current_price,
            "total": round(purchase["shares"] * current_price, 2)
        }

        # Append to user_portfolio
        user_portfolio.append(index)

    # Get user's cash balance
    user_money_query = db.execute(
        "SELECT cash FROM users WHERE id = ?", user_id)
    # This returns array of dictionaries
    # Get cash value from the recieved dictionary in user_money_query
    user_money = user_money_query[0]["cash"]

    # Render index.html template and feed the data to it
    return render_template("index.html", user_name=user_name, user_purchases=user_portfolio, user_money=user_money)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Check used method - if GET is used, show the buy page
    if request.method == "POST":
        # Get form data
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares amount most be a whole number.")

        # If blank, render appology
        if not symbol or not shares:
            return apology("Please input stock symbol and shares amount")

        # If shares in less than 0, render apology
        if shares < 0:
            return apology("Shares amount most be greater than 0.")

        # Get stock data from the api (lookup function from helpers.py, returns None if not found)
        stock = lookup(symbol)
        if stock == None:
            return apology("Stock symbol not found")

        # Created new table called puchases in finance.db where I'll write all puchases
            # ID, username (will be the user ID from the users table), date, sybol, price, shares, type (buy or sale)

        # 1. Check if user has enough money for the purchase
        # 1.1 Get user from session cookie
        user_id = session["user_id"]

        # 1.2 Get balance from the db
        user_money_query = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        # This returns array of dictionaries
        # Get cash value from the recieved dictionary in user_money_query
        user_money = user_money_query[0]["cash"]

        # 1.3 Calculate total cost of the purchase
        purchase_cost = shares * stock["price"]

        # 1.4 Check if user has enough money and return apology
        if purchase_cost > user_money:
            return apology("Not enough money on the balance for this purchase.")

        # 2. Handle the database if purchase is possible
        # 2.1. Update user's cash balance (where user is user_id and new cash will be user_money - purchase cost)
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_money - purchase_cost, user_id)

        # 2.2 Update new "purchases" table (username will be user_id, date will be time stamp we get from datetime.now())
        # 2.2.1. Create timestamp
        time_stamp = datetime.datetime.now()
        # 2.2.2 Update database
        db.execute("INSERT INTO purchases (user, date, symbol, price, shares, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, time_stamp, stock["symbol"], stock["price"], shares, "buy")

        # 3. Inform users
        message = f"You bought {shares} shares of {stock['symbol']} for {purchase_cost} Dollars."
        flash(message)

        # Return user to home screen
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Here I'm only working working with get
    # Get user id
    user_id = session["user_id"]
    # Get purchases data from the db
    purchases = db.execute("SELECT * FROM purchases WHERE user = ?", user_id)

    # Get user's name
    user_name_query = user_money_query = db.execute(
        "SELECT username FROM users WHERE id = ?", user_id)
    # This returns array of dictionaries
    # Get cash value from the recieved dictionary in user_money_query
    user_name = user_name_query[0]["username"]

    # Render history page and feed db data to it
    return render_template("history.html", user_purchases=purchases, user_name=user_name)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # Check used method - if GET is used, show the quote page
    if request.method == "POST":
        # Get form data
        symbol = request.form.get("symbol")

        # If blank, render appology
        if not symbol:
            return apology("Please input stock symbol")

        # Get stock data from the api and check if symbol exists (lookup function from helpers.py, returns None if not found)
        stock = lookup(symbol)
        if stock == None:
            return apology("Stock symbol not found")

        # Stock found, return quoted page from templates with data returned from the lookup function (name returns just symbol so ommiting it, price, symbol)
        return render_template("quoted.html", price=stock["price"], symbol=stock["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Check used method - if GET is used, show the registration page
    if request.method == "POST":
        # Get form data first
        username = request.form.get("username")
        password = request.form.get("password")
        confirmed_password = request.form.get("confirmation")

        # If username or password is empty, render appology
        if not username or not password or not confirmed_password:
            return apology("Please write username and password")

        # If passwords do not match, render appology
        if password != confirmed_password:
            return apology("Passwords do not match. Try again")

        # Check if the user already exist in the database
        users = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(users) != 0:
            return apology("Username already exists. Try another one.")

        # Hash the password for the storage
        hashed_password = generate_password_hash(password)

        # Insert username and hashed password to the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, hashed_password)

        # Get user's id
        user_id = db.execute(
            "SELECT id FROM users WHERE username = ?", username)
        # Write which user has logged in
        session["user_id"] = user_id[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        # Get user back to the register page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Check used method - if GET is used, check db for current user's stock and feed them to the the sell page
    if request.method == "POST":

        # Get form data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # If blank, render appology
        if not symbol or not shares:
            return apology("Please input stock symbol and shares amount")

        # If shares in less than 0, render apology
        if int(shares) < 0:
            return apology("Shares amount most be greater than 0.")

        # Get user's data from the db
        user_id = session["user_id"]
        user_stocks = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM purchases WHERE user = ? GROUP BY symbol HAVING sum(shares) > 0", user_id)

        # Collect user's stocks from the list of dictionaries in user_stocks
        user_stocks_arr = []
        for stock in user_stocks:
            # Append stock symbol to a list
            user_stocks_arr.append(stock["symbol"])
            # If user does not have enough shares to sell, render apology
            if symbol == stock["symbol"] and int(shares) > stock["shares"]:
                return apology("Cannot sell more than you own.")

            # If user does not own that share, render apology
            if symbol not in user_stocks_arr:
                return apology("Seems you do not own this stock.")

        # Get stock data from the api (lookup function from helpers.py, returns None if not found)
        stock = lookup(symbol)
        if stock == None:
            return apology("Stock symbol not found")

        user_money_query = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        # This returns array of dictionaries
        # Get cash value from the recieved dictionary in user_money_query
        user_money = user_money_query[0]["cash"]

        # Calculate total value of the sell
        sell_value = int(shares) * stock["price"]

        # Update user's cash balance (where user is user_id and new cash will be user_money - purchase cost)
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user_money + sell_value, user_id)

        # 2.2 Update new "purchases" table (username will be user_id, date will be time stamp we get from datetime.now())
        # 2.2.1. Create timestamp
        time_stamp = datetime.datetime.now()
        # 2.2.2 Update database
        db.execute("INSERT INTO purchases (user, date, symbol, price, shares, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, time_stamp, stock["symbol"], stock["price"], -abs(int(shares)), "sale")

        # 3. Inform users
        message = f"You sold {shares} shares of {stock['symbol']} for {sell_value} Dollars."
        flash(message)

        # Return user to home screen
        return redirect("/")

    else:
        # Get user id from current session
        user_id = session["user_id"]
        # Get stock symbols from db but only ones which user actualy has (greater than 0)
        # stock_symbols = db.execute("SELECT DISTINCT symbol FROM purchases WHERE user = ? AND shares > 0", user_id)
        # Get stock and shares count
        stock_symbols = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM purchases WHERE user = ? GROUP BY symbol HAVING sum(shares) > 0", user_id)

        return render_template("sell.html", stocks=stock_symbols)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    """Basic user settings"""
    # Get user id
    user_id = session["user_id"]

    # Get user's name and cash
    user_query = user_money_query = db.execute(
        "SELECT username, cash FROM users WHERE id = ?", user_id)
    # This returns array of dictionaries
    # Get cash value from the recieved dictionary in user_money_query
    user_name = user_query[0]["username"]
    user_money = user_query[0]["cash"]

    # Check used method - if GET is used, render the settings page
    if request.method == "POST":

        # Get form data
        submit = request.form.get("id")

        # Case for add cash
        if submit == "cash_deposit":
            # Get cash value
            new_cash = request.form.get("cash")

            # If value is blank
            if not new_cash:
                return apology("Please input amount")

            # If value is less than 0, render apology
            if int(new_cash) < 0:
                return apology("Amount most be greater than 0.")

            # Update user's cash balance (where user is user_id and new cash will be user_money + new_cash)
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       int(user_money) + int(new_cash), user_id)

            # Inform user
            message = f"You added ${new_cash}."
            flash(message)

            # Return to settings
            return redirect("/settings")

        # Case for change password
        if submit == "change_password":
            return redirect("/password")

    else:
        # Render settings page, feed data to it
        return render_template("settings.html", user_money=user_money, user_name=user_name)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change password"""
    # Check usexd method, if GET, render password template
    if request.method == "POST":
        # Get user id
        user_id = session["user_id"]

        # Get form data
        old_password_input = request.form.get("old-password")
        new_password = request.form.get("new-password")
        confirmed_password = request.form.get("confirmation")

        # If password imputs are empty, render appology
        if not old_password_input or not new_password or not confirmed_password:
            return apology("Please write current and passwords")

        # If passwords do not match, render appology
        if new_password != confirmed_password:
            return apology("New passwords do not match. Try again")

        # Grab old password's hash from the db and check with check_password_hash(hashed value, plain text) if matches
        hashed_old_password = db.execute(
            "SELECT hash FROM users WHERE id = ?", user_id)
        if not check_password_hash(hashed_old_password[0]["hash"], old_password_input):
            return apology("Current password is wrong. Try again")

        # Hash the password for the storage
        hashed_password = generate_password_hash(new_password)

        # Update hashed password to the database
        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   hashed_password, user_id)

        # Inform user
        flash("Password updated successfully.")

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("password.html")
