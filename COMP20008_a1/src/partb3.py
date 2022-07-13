## Part B Task 3
import re
import sys
import pandas as pd
import nltk
import os


def preProcessing(article):
    
    file = open("cricket/" + article)
    x = file.read()
    
    
    x=re.sub("[^a-zA-Z\\s\\t\\n\\r]+", " ", x).lower()
    x = re.sub("/(\r\n)+|\r+|\n+|\t+/", " "  , x)
    
    return x



files = pd.read_csv("partb1.csv")
files.set_index("filename", inplace = True)


keywords = sys.argv[1:]


for article, documentID in files.iterrows():
    processed_text = preProcessing(article)
    new_text = nltk.tokenize.word_tokenize(processed_text)
    if(all(word in new_text for word in keywords)):
        

        print(documentID[0])
        

