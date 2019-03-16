import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    # If Javascript is disable , and data hasn't been entered go to the error page
    if not request.form.get("name") or not request.form.get("surname") or not request.form.get("gender"):
        return render_template("error.html", message="You must provide all the required information :'( ")
    # Loading and writing the csv file
    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((request.form.get("name"), request.form.get("surname"), request.form.get("gender"),
                     request.form.get("size"), request.form.get("products")))
    file.close()
    # go to Sheet page
    return get_sheet()


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # Loading and reading csv file
    file = open("survey.csv", "r")
    reader = csv.reader(file)
    registry = list(reader)
    file.close()
    # If the csv file is empty go to the error page
    if not registry:
        return render_template("error.html", message="No data has been entered :'(")
    # go to the sheet page with the data
    return render_template("sheet.html", registry=registry)