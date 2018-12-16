from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
import nltk
from nltk.tokenize import TweetTokenizer
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives)
    
    if tweets == None:
        sys.exit("Invalid screen name or user has a private profile.")
    
    positive, negative, neutral, frequency = 0.0, 0.0, 0.0, 0
    
    tknzr = TweetTokenizer()
    for line in tweets:
        score = 0
        tokens = tknzr.tokenize(line)
        for e in tokens:
            e = e.lower()
            score = score + analyzer.analyze(e)
        if score > 0.0:
            positive = positive + 1.0
        elif score < 0.0:
            negative = negative + 1.0
        else:
            neutral = neutral + 1.0
        frequency = frequency + 1.0
            
    
    positive = (positive/frequency)*100.0
    negative = (negative/frequency)*100.0
    neutral = (neutral/frequency)*100.0

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
