from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir
import time
from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    stocks_owned = db.execute("SELECT * FROM portfolio WHERE id = :id", id=session["user_id"])
    length = len(stocks_owned)
    cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
    total = 0
    for stocks in range(length):
        total = total + stocks_owned[stocks]["total"]
    worth = cash[0]["cash"] + total
    stocks_current = []
    sum123 = []
    for stocks in range(length):
        stocks_current.append(lookup(stocks_owned[stocks]["symbol"]))
        sum123.append(stocks_current[stocks]["price"]*stocks_owned[stocks]["quantity"]) 
    return render_template("index.html", length=length, stocks=stocks_owned, stocks_current=stocks_current, sum123=sum123, balance=round(cash[0]["cash"], 2), worth=round(worth, 2))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("stock"):
            return apology("must provide stock symbol")
        elif not lookup(request.form.get("stock")):
            return apology("stock does not exist")
        elif not request.form.get("quantity"):
            return apology("please enter a value")
        elif int(request.form.get("quantity")) < 0:
            return apology("please enter a positive value")
            
        stock = lookup(request.form.get("stock"))
        price = stock["price"] * int(request.form.get("quantity"))
        cash = db.execute("SELECT cash FROM users WHERE id= :id", id=session["user_id"])
        
        if price > cash[0]["cash"]:
            return apology("you do not have enough cash")
        else:
            db.execute("UPDATE users SET cash = cash - :price where id = :id", price=price ,id=session["user_id"])
            db.execute("INSERT INTO portfolio (name, symbol, price, quantity, total, id) VALUES(:name, :symbol, :price, :quantity, :total, :id)", name = stock["name"], symbol = stock["symbol"], price = stock["price"], quantity = request.form.get("quantity"), total = price, id = session["user_id"])
            db.execute("INSERT INTO history (buy, date, name, symbol, price, total, quantity, id) VALUES (:buy, :date, :name, :symbol, :price, :total, :quantity, :id)", buy="Buy", date=time.strftime("%c"), name=stock["name"], symbol=stock["symbol"], price=stock["price"], total=price, quantity=int(request.form.get("quantity")), id=session["user_id"])
    else:
        return render_template("buy.html")
    return apology("TODO")

@app.route("/history")
@login_required
def history():
    stocks = db.execute("SELECT * FROM history WHERE id=:id", id=session["user_id"])
    length = len(stocks)
    return render_template("history.html", length=length, stocks=stocks)
    return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()
    
    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("stock"):
            return apology("please enter your stock")
        stock = lookup(request.form.get("stock"))
        if stock == None:
            return apology("stock is not valid")
        return render_template("quoted.html", name=stock["name"], symbol=stock["symbol"], price=stock["price"])
    else:
        return render_template("quote.html")
    return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    session.clear()
    
    if request.method == "POST":
        
        if not request.form.get("username"):
            return apology("Please enter your username")
        elif not request.form.get("password"):
            return apology("Please enter your username")
        elif not request.form.get("password") == request.form.get("password2"):
            return apology("Your passwords do not match")
        
        hash = pwd_context.encrypt(request.form.get("password"))
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username = request.form.get("username"), hash = hash)
        if not result:
            return apology("Sorry, your username has already been registered.")
        
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect(url_for("index"))
    else:
        return render_template("register.html")
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("stock"):
            return apology("please enter the symbol of the stock you want to purchase")
        if not request.form.get("quantity"):
            return apology("please enter the quantity you want to purchase")
        elif int(request.form.get("quantity")) < 0:
            return apology("please enter a positive value")
        symbol=request.form.get("stock")
        symbol = symbol.upper()
        stock = db.execute("SELECT * FROM portfolio WHERE id=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol)
        if not stock:
            return apology("you do not have that stock")
        elif stock[0]["quantity"] < int(request.form.get("quantity")):
            return apology("you do not have enough stocks to sell off")
        stock_current = lookup(stock[0]["symbol"])
        total = stock_current["price"] * stock[0]["quantity"]
        db.execute("UPDATE users SET cash = cash + :total where id = :id", total=total ,id=session["user_id"])
        db.execute("UPDATE portfolio SET quantity = quantity - :number WHERE id=:id AND symbol=:symbol", number=int(request.form.get("quantity")), id=session["user_id"], symbol=symbol)
        db.execute("INSERT INTO history (buy, date, name, symbol, price, total, quantity, id) VALUES (:buy, :date, :name, :symbol, :price, :total, :quantity, :id)", buy="S ell", date=time.strftime("%c"), name=stock[0]["name"], symbol=symbol, price=stock_current["price"], total=total, quantity=stock[0]["quantity"], id=session["user_id"])
        db.execute("DELETE FROM portfolio WHERE quantity=0")
        return render_template("sell.html")
    else:
        return render_template("sell.html")
    return apology("TODO")
