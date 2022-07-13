#!/usr/bin/env python
# coding: utf-8

# In[41]:


import pandas as pd
import matplotlib.pyplot as plt
from statistics import mean
import numpy as np


# In[42]:


health = pd.read_csv('LGA_by_HEALTH.csv')
health_indexed = health.set_index('LGA_CODE_2011')


# In[43]:


pm10 = pd.read_csv('PM10_MAX_24HR_READING.csv')


# In[58]:


#average the health issues across Victoria
average_health_pm10 = {'Smoking': health['smokers'].mean(),
                         'Heart Disease': health['heart_disease'].mean(),
                         'Pre-Obesity': health['pre_obese'].mean(),
                         'Obesity': health['obese'].mean(),
                           'PM10 (max 24hr)': pm10['value'].mean()
                        }
averages_victoria= pd.Series(average_health_pm10)
averages_victoria.index.name = 'Factor'


# In[59]:


averages_df = pd.DataFrame(averages_victoria)
averages_df= averages_df.rename(columns = {0:'Average'})


# In[60]:


averages_victoria.to_csv('averages_health_pm10.csv', index = True, header = ["Average"])

