import pandas as pd
import argparse
import matplotlib.pyplot as plt
import sys


df_covid = pd.read_csv('owid-covid-data.csv')
df_covid['date'] = pd.to_datetime(df_covid['date'])

df_covid = df_covid.loc[:,['location','date','total_cases','new_cases','total_deaths','new_deaths']]
df_covid = df_covid.sort_values(by = 'date')

df_covid['month'] = pd.DatetimeIndex(df_covid['date']).month

df_covid = df_covid.loc[(df_covid['date'] >= '2020-01-01') & (df_covid['date'] <= '2020-12-31')]
df_covid = df_covid.reindex(columns = ['location', 'month', 'total_cases', 'new_cases', 'total_deaths', 'new_deaths'])


df_covid = df_covid[(df_covid['month'].notna()) |(df_covid['location'].notna()) ]

df_covid = df_covid.groupby(['location']).agg({'total_cases': 'max','new_cases':'sum','total_deaths':'max','new_deaths':'sum'})
df_covid['case_fatality_rate'] = df_covid['total_deaths']/df_covid['total_cases']
df_covid = df_covid.reindex(columns = ['case_fatality_rate', 'total_cases', 'new_cases', 'total_deaths', 'new_deaths'])




for key, location in df_covid.iterrows():
    
   
    plt.scatter(location['total_cases'], location['case_fatality_rate'])
    
plt.title("COVID-19 Case Fatality Rate vs Total Cases In Locations(2020)")
plt.ylabel("case_fatality_rate")
plt.xlabel("total_cases")
plt.grid(True)
plt.ylim(0,0.3)

fig1 = plt.gcf()
fig1.savefig(sys.argv[1])




for key, location in df_covid.iterrows():
    
   
    plt.scatter(location['total_cases'], location['case_fatality_rate'])
    
plt.title("COVID-19 Case Fatality Rate vs Total Cases In Locations(2020)")
plt.ylabel("case_fatality_rate")
plt.xlabel("total_cases")
plt.grid(True)
plt.ylim(0,0.3)
plt.xscale('log')
fig2 = plt.gcf()
fig2.savefig(sys.argv[2])

