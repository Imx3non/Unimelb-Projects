import pandas as pd
import argparse
import sys


#parta1
df_covid = pd.read_csv('owid-covid-data.csv')
df_covid['date'] = pd.to_datetime(df_covid['date'])

df_covid = df_covid.loc[:,['location','date','total_cases','new_cases','total_deaths','new_deaths']]
df_covid = df_covid.sort_values(by = 'date')

df_covid['month'] = pd.DatetimeIndex(df_covid['date']).month

df_covid = df_covid.loc[(df_covid['date'] >= '2020-01-01') & (df_covid['date'] <= '2020-12-31')]
df_covid = df_covid.reindex(columns = ['location', 'month', 'total_cases', 'new_cases', 'total_deaths', 'new_deaths'])


df_covid = df_covid[(df_covid['month'].notna()) |(df_covid['location'].notna()) ]

#parta2
df_covid = df_covid.groupby(['location','month']).agg({'total_cases': 'max','new_cases':'sum','total_deaths':'max','new_deaths':'sum'})
df_covid['case_fatality_rate'] = df_covid['new_deaths']/df_covid['new_cases']
df_covid = df_covid.reindex(columns = ['case_fatality_rate', 'total_cases', 'new_cases', 'total_deaths', 'new_deaths'])

print(df_covid.head())
df_covid.to_csv(sys.argv[1])

