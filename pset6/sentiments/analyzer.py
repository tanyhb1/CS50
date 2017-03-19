import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = []
        self.negatives = []
        f = open("positive-words.txt", "r")
        for line in f:
            line = line.strip()
            if line.startswith(';') is False:
                self.positives.append(line)
        f.close()
        
        f = open("negative-words.txt", "r")
        for line in f:
            line = line.strip()
            if line.startswith(';') is False:
                self.negatives.append(line)
        f.close()
        


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tknzr = TweetTokenizer()
        tokens = tknzr.tokenize(text)
        score = 0
        for e in tokens:
            e = e.lower()
            if e in self.positives:
                score = score + 1
            elif e in self.negatives:
                score = score -1
        return score
