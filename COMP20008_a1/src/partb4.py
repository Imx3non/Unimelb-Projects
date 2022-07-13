## Part B Task 4
import re
import pandas as pd
import os
import sys
import nltk



ps = nltk.stem.PorterStemmer()

def preProcessing(article):
    
    file = open("cricket/" + article)
    x = file.read()
    
    
    x=re.sub("[^a-zA-Z\\s\\t\\n\\r]+", " ", x).lower()
    
    x = re.sub("/(\r\n)+|\r+|\n+|\t+/", " "  , x)
    
    return x


files = pd.read_csv("partb1.csv")
files.set_index("filename", inplace = True)
keywords =[ps.stem(w) for w in sys.argv[1:]]




for article, documentID in files.iterrows():
    processed_text = preProcessing(article)
    new_text = nltk.tokenize.word_tokenize(processed_text)
    
    words = [ps.stem(w) for w in new_text]
    
    
    if(all(word in words for word in keywords)):
        
         print(documentID[0])


