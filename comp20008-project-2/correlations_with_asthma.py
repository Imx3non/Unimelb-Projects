import pandas as pandas
import numpy as np

data = pandas.read_csv("dataframe_for_MI.csv")

# Pearson correlation coefficients of health factors with asthma data
PM10_corr = np.corrcoef(data["PM10_max24"], data["asthma"])
smokers_corr = np.corrcoef(data["smokers"], data["asthma"])
heart_corr = np.corrcoef(data["heart_disease"], data["asthma"])
pre_obese_corr = np.corrcoef(data["pre_obese"], data["asthma"])
obese_corr = np.corrcoef(data["obese"], data["asthma"])
overweight_corr = np.corrcoef(data["overweight"], data["asthma"])

correlations = {'PM10': PM10_corr[0][1], 'Smokers': smokers_corr[0][1], 'Heart Disease': heart_corr[0][1],
                'Pre-obesity': pre_obese_corr[0][1], 'Obesity': obese_corr[0][1], 'Overweight': overweight_corr[0][1]}
correlations = pandas.Series(correlations)

print(correlations)