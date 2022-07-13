import pandas as pandas
import math

data = pandas.read_csv("dataframe_for_MI.csv")

# PM10 entropy
pm10_entropy = -0.25*math.log(0.25,2) - 0.625 * math.log(0.625,2) - 0.125 * math.log(0.125,2)

# Asthma 
asthma_entropy = -0.5 * math.log(0.5,2) - 0.5 * math.log(0.5,2)
pm10_given_asthma = 0.5*( -0.5 * math.log(0.5, 2) -0.5 * math.log(0.5, 2) + -0.25 * math.log(0.25, 2) - 0.75 * math.log(0.75, 2))
asthma_given_pm10 = 0.625 * (-0.4 * math.log(0.4, 2) + -0.6 * math.log(0.6, 2))
mutual_info_asthma = pm10_entropy - pm10_given_asthma
norm_MI_asthma = mutual_info_asthma / asthma_entropy

# Smokers 
smokers_entropy = -0.125*math.log(0.125,2) - 0.75*math.log(0.75,2) - 0.125*math.log(0.125,2)
pm10_given_smokers = 0.125 * -1*math.log(1,2) + 0.75 * (-0.33*math.log(0.33,2) - 0.5*math.log(0.5,2) - 0.167*math.log(0.167,2)) + 0.125 * (-1*math.log(1,2))
smokers_given_pm10 = 0.25 * -1*math.log(1,2) + 0.625* (-0.2*math.log(0.2,2) - 0.6*math.log(0.6,2) - 0.2*math.log(0.2,2)) + 0.125 * (-1*math.log(1,2))
mutual_info_smokers = pm10_entropy - pm10_given_smokers
norm_MI_smokers = mutual_info_smokers / smokers_entropy

# Heart disease 
heart_entropy = -0.5 * math.log(0.5,2) - 0.5 * math.log(0.5,2)
pm10_given_heart = 0.5 * (-0.25*math.log(0.25,2) - 0.75*math.log(0.75,2)) + 0.5 * (-0.25*math.log(0.25,2) - 0.5*math.log(0.5,2) - 0.25*math.log(0.25,2))
heart_given_pm10 = 0.25 * (-0.5 * math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.625 * (-0.6 * math.log(0.6,2) - 0.4 * math.log(0.4,2)) + 0.125 * (-1*math.log(1,2))
mutual_info_heart = pm10_entropy - pm10_given_heart
norm_MI_heart = mutual_info_heart / heart_entropy

# Pre obese 
pre_obese_entropy = -0.25 * math.log(0.25,2) - 0.75 * math.log(0.75,2)
pm10_given_pre_obese = 0.25 * (-0.5 * math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.75 * (-0.167*math.log(0.167,2) - 0.667*math.log(0.667,2) - 0.167*math.log(0.167,2))
pre_given_pm10 = 0.25 * (-0.5 * math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.625 * (-0.2*math.log(0.2,2) - 0.8*math.log(0.8,2)) + 0.125 * (-1*math.log(1,2))
pre_obese_MI = pm10_entropy - pm10_given_pre_obese
norm_MI_pre_obese = pre_obese_MI / pre_obese_entropy

# Obese 
obese_entropy = -0.25 * math.log(0.25,2) - 0.5 * math.log(0.5,2) - 0.25 * math.log(0.25,2)
pm10_given_obese = 0.25 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.5 * (-0.25*math.log(0.25,2) - 0.75*math.log(0.75,2)) + 0.25 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2))
obese_given_pm10 = 0.25 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.625 * (-0.2*math.log(0.2,2) - 0.6*math.log(0.6,2) - 0.2*math.log(0.2)) + 0.125*(-1*math.log(1,2))
obese_MI = pm10_entropy - pm10_given_obese
norm_MI_obese = obese_MI / pm10_entropy


entropies = {'PM10': pm10_entropy, 'Asthma': asthma_entropy, 'Smokers': smokers_entropy, 'Heart Disease': heart_entropy, 'Pre obese': pre_obese_entropy, 'Obese': obese_entropy}
norm_MI = {'PM10': 'Na', 'Asthma': norm_MI_asthma, 'Smokers': norm_MI_smokers, 'Heart Disease': norm_MI_heart, 'Pre obese': norm_MI_pre_obese, 'Obese': norm_MI_obese}
entropies = pandas.Series(entropies)
norm_MI = pandas.Series(norm_MI)

df = pandas.DataFrame({'Entropies': entropies, 'MI between PM10 and Health Factors': norm_MI})
pandas.set_option('display.max_colwidth', 80)
print(df)