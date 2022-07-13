#!/usr/bin/env python
# coding: utf-8

# In[42]:


import pandas as pd
import matplotlib.pyplot as plt
from statistics import mean
import numpy as np


# In[43]:


health = pd.read_csv('HEALTH_and_PM10_average.csv')
health_indexed = health.set_index('LGA_CODE_2011')


# In[44]:


#pm10 max24hr
pm10 = pd.read_csv('PM10_MAX_24HR_READING.csv')
pm10


# In[45]:


nameto_LGA = pd.read_csv('PM10_to_LGA.csv')
pm10['sp_name'] = nameto_LGA['LGA_CODE_2011']


# In[46]:


pm10 = pm10.sort_values('sp_name')
pm10_indexed = pm10.set_index('sp_name')
pm10_indexed


# In[47]:


pm10_health = health_indexed.join(pm10_indexed)
pm10_health = pm10_health.rename(columns = {'value': 'pm10_max24hr'})
pm10_health.to_csv('HEALTH_PM10avg_max24hr.csv', index = True)
pm10_health


# In[9]:


#correlation between pm10 and smokers
correlation_smokers = np.corrcoef(pm10_health['smokers'], pm10_health['pm10_max24hr'])
#correlation between pm10 and obesity
correlation_obese = np.corrcoef(pm10_health['obese'], pm10_health['pm10_max24hr'])
#correlation between pm10 and heart_disease
correlation_heart_disease = np.corrcoef(pm10_health['heart_disease'], pm10_health['pm10_max24hr'])
#correlation between pm10 and pre obese
correlation_pre_obese = np.corrcoef(pm10_health['pre_obese'], pm10_health['pm10_max24hr'])


# In[10]:


cor_obese=correlation_obese[1][0]
cor_heart_disease=correlation_heart_disease[1][0]
cor_pre_obese=correlation_pre_obese[1][0]
cor_smokers=correlation_smokers[1][0]


# In[26]:


correlations_pm10 = {'smokers': cor_smokers,
                     'heart_disease': cor_heart_disease,
                     'pre_obese': cor_pre_obese,
                     'obese': cor_obese
                    }
correlations_pm10 = pd.Series(correlations_pm10)
correlations_pm10.index.name='Health_factor'
correlations_pm10 = pd.DataFrame(correlations_pm10)
correlations_pm10


# In[38]:


df = pd.read_csv('health_cor_pm10_avg.csv')
pre_24hr = df.set_index('Health_factor')

df_joined = pre_24hr.join(correlations_pm10)
df_joined = df_joined.rename(columns = {'Cor_pm10_avg': 'Avg_PM10_cor', 0: 'Max24hr_PM10_cor'})
df_joined


# In[41]:


df_joined.to_csv('corr_health_avg__max24hr_pm10.csv', index = True)


# In[ ]:




