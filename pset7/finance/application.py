import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # id of user
    id = session["user_id"]
    # user username
    username_response = db.execute("SELECT username FROM users WHERE id = :id", id = session["user_id"])
    username = username_response[0]["username"]

    # select user all stocks
    stocks = db.execute("SELECT symbol, sum(shares) AS shares, name FROM portfolio WHERE username = :username GROUP BY symbol", username = username)

    cash_response = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])

    stocksTotalValue = 0

    if stocks and cash_response:
        for data in stocks:
            symbol = data["symbol"]
            quote = lookup(symbol)
            price = float(quote["price"])
            data["price"] = usd(price)
            data["total"] = usd(price * data["shares"])
            stocksTotalValue += price * data["shares"]

        # calculate user cash
        cash = float(cash_response[0]["cash"])
        stocksAndCash = stocksTotalValue + cash
        return render_template("index.html", stocks = stocks, cash = usd(cash), stocksAndCash = usd(stocksAndCash))

    elif cash_response:
        cash = float(cash_response[0]["cash"])
        return render_template("index_empty.html", cash = usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # aapl tsla bac goog
    # buy stocks
    if request.method == "POST":

        # read user cash from database
        cash_response = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        username_response = db.execute("SELECT username FROM users WHERE id = :id", id = session["user_id"])
        # fetch data about symbol
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("symbol not found")
        price = float(quote["price"])
        symbol = quote["symbol"]
        name = quote["name"]

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)
        if shares <= 0:
            return apology("shares must be a positive integer", 400)

        cash = float(cash_response[0]["cash"])
        username = username_response[0]["username"]
        totalPrice = shares * price

        # check if user can affort to buy
        if cash > totalPrice:
            # insert data into portfolio
            result = db.execute("INSERT INTO portfolio (username, symbol, name, shares, price) VALUES(:username, :symbol, :name, :shares, :price)",
            username = username,
            symbol = symbol,
            name = name,
            shares = shares,
            price = price)
            if not result:
                return apology("user already in database")
            # update cash on users
            result = db.execute("UPDATE users SET cash = cash - :totalPrice WHERE id = :id",
            id = session["user_id"],
            totalPrice = totalPrice)
            return redirect("/")
        else:
            return apology("not enough cash")

    # present form to buy
    else:
        return render_template("buy.html")

    #return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username_response = db.execute("SELECT username FROM users WHERE id = :id", id = session["user_id"])
    username = username_response[0]["username"]

    stocks = db.execute("SELECT symbol, shares, price, name, date FROM portfolio WHERE username = :username", username = username)
    if stocks :
        for data in stocks:
            data["price"] = usd(data["price"])
            if data["shares"] > 0:
                data["operation"] = "buy"
            else:
                data["operation"] = "sell"

    return render_template("history.html", stocks = stocks)
    #return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    if request.method == "POST":

        # Ensure user provided symbol for stock
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("symbol not found", 400)
        return render_template("symbol.html",
            name = quote["name"],
            price = usd(quote["price"]),
            symbol = quote["symbol"])
    else:
        return render_template("quote.html")
    #return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

    # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password was submitted
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # hash password
        hash = generate_password_hash(request.form.get("password"))

        # check is username already in database
        username_response = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if username_response:
            username = username_response[0]["username"]
            if username == request.form.get("username"):
                return apology("user already in database", 400)

        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
        username = request.form.get("username"),
        hash = hash)

        #login automatically
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        return redirect("/")
        if not result:
            return apology("user already in database", 400)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    username_response = db.execute("SELECT username FROM users WHERE id = :id", id = session["user_id"])
    username = username_response[0]["username"]

    # select user all stocks
    sumedShares = db.execute("SELECT symbol, sum(shares) AS sum_shares, price, sum(price) AS sum_price, name FROM portfolio WHERE username = :username GROUP BY symbol", username = username)

    # calculate users stocks
    stocks = []
    for data in sumedShares:
        stocks.append(data['symbol'])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        sharesToSell = int(request.form.get("shares"))

        stockToDelete = []
        for data in sumedShares:
            if data['symbol'] == symbol.upper():
                stockToDelete.append(data)

        if stockToDelete[0]['sum_shares'] >= sharesToSell:
            # fetch stock price
            quote = lookup(request.form.get("symbol"))
            price = float(quote["price"])
            # symbol = quote["symbol"]
            name = quote["name"]

            # delete users stock
            # result = db.execute("UPDATE portfolio SET shares = shares - :sharesToSell WHERE username = :username",
            # username = username,
            # sharesToSell = sharesToSell)
            result = db.execute("INSERT INTO portfolio (username, symbol, name, shares, price) VALUES(:username, :symbol, :name, :shares, :price)",
            username = username,
            symbol = symbol,
            name = name,
            shares = -sharesToSell,
            price = price)

            # if stockToDelete[0]['sum_shares'] == sharesToSell:
            #     result = db.execute("DELETE FROM portfolio WHERE shares = :sharesToSell AND username = :username",
            #     username = username,
            #     sharesToSell = sharesToSell)
            # update users cash
            # calculate value
            totalPrice = price * sharesToSell
            result = db.execute("UPDATE users SET cash = cash + :totalPrice WHERE id = :id",
            id = session["user_id"],
            totalPrice = totalPrice)

            # check is user has 0 shares if then delete stock
            # result = db.execute("DELETE FROM portfolio WHERE shares <= 0")

        else:
            return apology("wrong number of shares")

        return redirect("/")
    else:
        return render_template("sell.html", stocks = stocks)



def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

def search(data, symbol):
  if data['symbol'] == symbol:
    return True
  else:
    return False