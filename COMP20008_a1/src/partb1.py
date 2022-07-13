import re
import pandas as pd
import os
import sys

files = sorted(os.listdir("cricket"))
idRegex = re.compile(r'[A-Z][A-Z][A-Z][A-Z]-[0-9][0-9][0-9]' )
idRegexop = re.compile(r'[A-Z][A-Z][A-Z][A-Z]-[0-9][0-9][0-9][A-Z]{1}')

idRegex_check1 = re.compile(r'[A-Z][A-Z][A-Z][A-Z]-[0-9][0-9][0-9][A-Z]{2}')
idRegex_check2 = re.compile(r'[A-Z][A-Z][A-Z][A-Z]-[0-9][0-9][0-9][A-Z]{1}[a-z]+')
csv = open(sys.argv[1],"w")
csv.write("filename, documentID\n")
for i in files:
    
    file = open("cricket/" + i, 'r')
    x = file.read()
    
    if(idRegex_check1.search(x)):
        
        id = idRegexop.search(x)
    
    elif(idRegex_check2.search(x)):
        
        id = idRegex.search(x)
        
    elif(idRegexop.search(x)):
             
        id = idRegexop.search(x)
    else:
        id = idRegex.search(x)
        
    csv.write(i+","+id.group()+"\n")

csv.close()


   
    
