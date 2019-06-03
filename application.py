import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
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

# users table
###############################
# id | username | hash | cash |
###############################

# transactions table
#####################################################
# idTrans | userid | symbol | shares | price | time |
#####################################################


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Taking data from transactions and users table (Mybe SUM(SHARES))
    rows = db.execute("SELECT symbol,SUM(shares),price FROM transactions JOIN users ON (transactions.userid=users.id) WHERE (users.id=:user_id) GROUP BY symbol",
                      user_id=session["user_id"])
    
    # Cash from user if it's new user
    user_cash = db.execute("SELECT cash FROM users WHERE (users.id=:user_id)",
                           user_id=session["user_id"])
 
    # Taking total cash from user and convert to $
    cash = usd(user_cash[0]['cash']) 
    
    """ CONTROL---------
    for row in rows:                
        print(row)
    -----------------"""
    
    # Stock list with dic 
    # https://docs.python.org/3/tutorial/datastructures.html?highlight=dictionary#dictionaries
    # https://docs.python.org/3/library/stdtypes.html#dict
    # https://docs.python.org/3/tutorial/datastructures.html?highlight=lists    
    stocks = []
    total = user_cash[0]['cash']
    
    for row in rows:
        data = {}
        data['symbol'] = row['symbol']
        data['company'] = lookup(row["symbol"])['name']
        data['shares'] = row['SUM(shares)']
        data['price'] = usd(lookup(row["symbol"])['price'])
        # temp store value for calculate it, and later convert it to $ (str)
        value = float(row['SUM(shares)']) * lookup(row["symbol"])['price']
        data['value'] = usd(value)
        total += value
        stocks.append(data)
    
    # Passing data (stoks), cash and total converted in usd format
    return render_template("index.html", stocks=stocks, cash=cash, total=usd(total))
  

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # Checking method
    if request.method == "POST":
        # Checking symbol input
        if not request.form.get("symbol"):
            return apology("MISSING SYMBOL")
        
        # Checking shares input
        elif not request.form.get("shares"):
            return apology("MISSING SHARES")
        
        elif not request.form.get("shares").isdigit():
            return apology("must provide valid number", 400) 
        
        # ----------------------------------
        # Takig Shares from buy.html
        shares = request.form.get("shares")
        
        # Obtaining quote from API
        quote = lookup(request.form.get("symbol"))
        
        # Checking if quote exist 
        if quote:
            
            # Obtaining cash like a float from querry[0]["cash"]
            cash = float(db.execute("SELECT cash FROM users WHERE id=:user_id",
                                    user_id=session["user_id"])[0]["cash"])
           
            value = float(shares) * quote["price"]
            
            # Checking if you have enogh money
            if cash >= value:
                    
                # Inserting transaction
                db.execute("INSERT INTO transactions( userid, symbol, shares, price, time) VALUES (:userid, :symbol, :shares, :price, CURRENT_TIMESTAMP)",
                           userid=session["user_id"], symbol=quote["symbol"], shares=shares, price=quote["price"])
                    
                # Updating the money 
                db.execute("UPDATE users SET cash = :cash - :value WHERE id = :userid", 
                           cash=cash, value=value, userid=session["user_id"])
                    
                return redirect("/")              
                
            else:
                return apology("YOU DON'T HAVE ENOUGH MONEY") 
        
        else:
            return apology("INVALID SYMBOL")
        # ---------------------------------------------------
    else:
        return render_template("buy.html")

    
@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    
    username = request.args.get("username")
    
    # Checking user in DB
    finduser = db.execute("SELECT * FROM users WHERE username=:username",
                          username=username)
                          
    if len(username) <= 0 or finduser:
        return jsonify(False)
    else:
        return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    rows = db.execute("SELECT * FROM transactions WHERE userid=:user_id",
                      user_id=session["user_id"])
    
    # Store the db query in a list of dict for convert srt.price format in usd(price) format
    transactions = []
    for row in rows:
        data = {}
        data['symbol'] = row['symbol']
        data['shares'] = row['shares']
        data['price'] = usd(float(row['price']))
        data['time'] = row['time']
        transactions.append(data)
    
    return render_template("history.html", transactions=transactions)


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
    

@app.route("/update", methods=["GET", "POST"])
@login_required
def update():
    """Update user password"""
    
    # Request only via post
    if request.method == "POST":
        
        new_pass = request.form.get("newpassword")
        confirm_pass = request.form.get("newpassword_confirm")

        # Ensure new password exist
        if not new_pass:
            return apology("missing new password", 403)

        # Ensure password confirmation exist
        elif not confirm_pass:
            return apology("missing password confirmation", 403)

        # Ensure passwords match
        elif not new_pass == confirm_pass:
            return apology("passwords don't match", 403)
        
        # generating new hash    
        
        new_hash = generate_password_hash(new_pass, 'pbkdf2:sha256', 8)
        
        # Updating password in db
        db.execute("UPDATE users SET hash=:new_hash WHERE id=:user_id",
                   user_id=session["user_id"], new_hash=new_hash)
            
        return redirect("/")
        
    else:
        return render_template("update.html")
        

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Request only via post
    if request.method == "POST":
        
        # Obteniendo quote
        quote = lookup(request.form.get("symbol"))
        
        # Checking if quote exist and sending information
        if quote:
            price = usd(quote['price'])
            return render_template("quoted.html", quote=quote, price=price)
        else:
            return apology("INVALID SYMBOL!")  
        
    else:
        return render_template("quote.html")
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Request only via post
    if request.method == "POST":

        # Ensure username exist
        if not request.form.get("username"):
            return apology("missing username", 400)

        # Ensure password exist
        elif not request.form.get("password"):
            return apology("missing password", 400)

        # Ensure password confirmation exist
        elif not request.form.get("confirmation"):
            return apology("missing password confirmation", 400)

        # Ensure passwords match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords don't match", 400)
        
        elif db.execute("SELECT username FROM users WHERE username=:username",
                        username=request.form.get("username")):
            return apology("User already exist", 400) 

        # Checking if user_name is available
        redirect("/check")
        
        # ------------------------------------
        # Generate hash from password.
        hash = generate_password_hash(request.form.get("password"), 'pbkdf2:sha256', 8)
    
        # Inserting User and hash into the DB
        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)",
                   username=request.form.get("username"), hash=hash)
        
        # Find the user id in the db for loging automatically and username for insert it in transaction table
        rows = db.execute("SELECT id,username FROM users WHERE username = :username",
                          username=request.form.get("username"))
      
        # Keep the session with the user id
        session["user_id"] = rows[0]["id"]
    
        # Redirect to main page
        return redirect("/")
        # -------------------------------------
        
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    # Selecting your companies avalibles for show it in the page
    symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE userid=:user_id",
                         user_id=session['user_id'])
    # Selecting user's total shares and send it to the web page (DON'T WORK : THE PAGE DONT KNOW symbol DATA)
    
    """ --control----------------
    print(session['user_id'])
    for symbol in symbols:
        print(symbol)
    # -------------------------"""
        
    # Checking method
    if request.method == 'POST':
        
        # Checking symbol input
        if not request.form.get("symbol"):
            return apology("MISSING SYMBOL")
        
        # Checking shares input
        elif not request.form.get("shares"):
            return apology("MISSING SHARES")
        
        # ---------------------------------------
        
        # Tacking Stock and quantity from user
        stock = request.form.get('symbol')
        quantity = int(request.form.get('shares'))
        # Selecting user's total shares in DB
        stock_quantity = db.execute("SELECT SUM(shares) FROM transactions WHERE (userid=:user_id AND symbol=:symbol)",
                                    user_id=session["user_id"], symbol=stock)[0]['SUM(shares)']
        
        # checking how many stocks do you have
        if quantity > stock_quantity:
            return apology("YOU HAVE : " + str(stock_quantity) + " SHARES FROM " + stock, 400) 
        
        # Total of earning
        earnings = float(quantity) * lookup(stock)['price']
        
        # updating transactions table in DB. (negative form)
        db.execute("INSERT INTO transactions (userid, symbol, shares, price, time) VALUES (:user_id, :symbol, :shares, :price, CURRENT_TIMESTAMP)",
                   user_id=session['user_id'], symbol=stock, shares=(-float(quantity)), price=lookup(stock)['price'])
      
        # update cash with the earnings           
        db.execute("UPDATE users SET cash=cash+:earnings WHERE id=:user_id",
                   earnings=earnings, user_id=session['user_id'])
        
        return redirect("/")
        # ----------------------------------------
    else:
        return render_template('sell.html', symbols=symbols,)
    

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
