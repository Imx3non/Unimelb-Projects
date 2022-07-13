## Part B Task 5
import re
import os
import sys
import pandas as pd
import nltk
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.feature_extraction.text import TfidfVectorizer
from nltk.corpus import stopwords
from numpy import dot
from numpy.linalg import norm 
from numpy import around
import math
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


documents = []

for article, documentID in files.iterrows():
    processed_text = preProcessing(article)
    new_text = nltk.tokenize.word_tokenize(processed_text)
    
    words = [ps.stem(w) for w in new_text]
    
    
    if(all(word in words for word in keywords)):
        
        documents.append(documentID.name)


score = {'documentID' : [], 'score': []}

for document, documentID in files.iterrows():
    if document in documents:
        
        score['documentID'].append(documentID[0])
        
articles = []
for article in documents:
    processed_text = preProcessing (article)
    new_text = nltk.tokenize.word_tokenize(processed_text)
    words = [ps.stem(w) for w in new_text]
    processed_text = " ".join(words)
    
    articles.append(processed_text)

keywords_num = len(keywords)
keyword = " ".join(keywords)
keywords = [keyword]

stopWords = stopwords.words('english')
vectorizer = CountVectorizer(stop_words = stopWords)
transformer = TfidfTransformer()
term_counts_for_articles = vectorizer.fit_transform(articles).toarray()
term_counts_for_keywords = vectorizer.transform(keywords).toarray()
q_unit = [x/(math.sqrt(keywords_num)) for x in term_counts_for_keywords[0]]

tfidf = transformer.fit_transform(term_counts_for_articles).toarray()


def cos_sim(q1,v1):
    return dot(q1,v1)/ (norm(q1)*norm(v1))


sims = [cos_sim(q_unit,vector) for vector in tfidf]
sims = around(sims,4)


for scores in sims: 
    score['score'].append(scores)
   
    

df_score = pd.DataFrame(score)
df_score = df_score.sort_values(by = 'score', ascending = False, inplace = False)
print(df_score.to_string(index = False))

    
