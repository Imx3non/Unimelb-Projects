# Part B Task 2
import re
import os
import sys

def preProcessing(file):
    
    x = file.read()
    x=re.sub("[^a-zA-Z\\s\\t\\n\\r]+", " ", x).lower()
    x = re.sub("/(\r\n)+|\r+|\n+|\t+/", " "  , x)
    return x

   



file = open(sys.argv[1], "r+")
x = preProcessing(file)
print(x)
