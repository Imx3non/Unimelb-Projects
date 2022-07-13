#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import matplotlib.pyplot as plt
from statistics import mean
import numpy as np


# In[2]:


health = pd.read_csv('LGA_by_HEALTH.csv')
health_indexed = health.set_index('LGA_CODE_2011')


# In[3]:


#average the health issues across Victoria
average_health_issues = {'smokers': health['smokers'].mean(),
                         'heart_disease': health['heart_disease'].mean(),
                         'pre_obese': health['pre_obese'].mean(),
                         'obese': health['obese'].mean()
                        }
average_health_victoria= pd.Series(average_health_issues)
average_health_victoria.index.name = 'Health_factor'


# In[4]:


#pm10 average added to health
pm10 = pd.read_csv('PM10_AV_READING.csv')
pm10


# In[5]:


nameto_LGA = pd.read_csv('PM10_to_LGA.csv')
pm10['sp_name'] = nameto_LGA['LGA_CODE_2011']


# In[6]:


pm10 = pm10.sort_values('sp_name')
pm10_indexed = pm10.set_index('sp_name')
pm10_indexed


# In[7]:


pm10_health = health_indexed.join(pm10_indexed)
pm10_health = pm10_health.rename(columns = {'value': 'pm10'})
pm10_health.to_csv('HEALTH_and_PM10.csv', index = True)


# In[8]:


#correlation between pm10 and smokers
correlation_smokers = np.corrcoef(pm10_health['smokers'], pm10_health['pm10'])
#correlation between pm10 and obesity
correlation_obese = np.corrcoef(pm10_health['obese'], pm10_health['pm10'])
#correlation between pm10 and heart_disease
correlation_heart_disease = np.corrcoef(pm10_health['heart_disease'], pm10_health['pm10'])
#correlation between pm10 and pre obese
correlation_pre_obese = np.corrcoef(pm10_health['pre_obese'], pm10_health['pm10'])


# In[9]:


cor_obese=correlation_obese[1][0]
cor_heart_disease=correlation_heart_disease[1][0]
cor_pre_obese=correlation_pre_obese[1][0]
cor_smokers=correlation_smokers[1][0]


# In[10]:


correlations_pm10 = {'smokers': cor_smokers,
                     'heart_disease': cor_heart_disease,
                     'pre_obese': cor_pre_obese,
                     'obese': cor_obese
                    }
correlations_pm10 = pd.Series(correlations_pm10)
correlations_pm10.index.name='Health_factor'
correlations_pm10


# In[11]:


Victoria = pd.DataFrame({'Average': average_health_victoria, 
                        'Correlation_pm10':correlations_pm10})
Victoria


# In[12]:


Victoria.to_csv('health_average_correlation_pm10.csv', index = True)


# In[ ]:




