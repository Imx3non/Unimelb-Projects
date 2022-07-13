import pandas as pandas
import math

data = pandas.read_csv("dataframe_for_MI.csv")

# Asthma entropy
asthma_entropy = -0.5 * math.log(0.5,2) - 0.5 * math.log(0.5,2)

# PM10
pm10_entropy = -0.25*math.log(0.25,2) - 0.625 * math.log(0.625,2) - 0.125 * math.log(0.125,2)
pm10_given_asthma = 0.5*( -0.5 * math.log(0.5, 2) -0.5 * math.log(0.5, 2) + -0.25 * math.log(0.25, 2) - 0.75 * math.log(0.75, 2))
asthma_given_pm10 = 0.625 * (-0.4 * math.log(0.4, 2) + -0.6 * math.log(0.6, 2))
mutual_info_pm10 = pm10_entropy - pm10_given_asthma
norm_MI_pm10 = mutual_info_pm10 / asthma_entropy

# Smokers 
smokers_entropy = -0.125*math.log(0.125,2) - 0.75*math.log(0.75,2) - 0.125*math.log(0.125,2)
smokers_given_asthma = 0.5 * (-1*math.log(1,2)) + 0.5 * (-0.25*math.log(0.25,2) - 0.5*math.log(0.5,2) - 0.25*math.log(0.25,2))
asthma_given_smokers = 0.125 * (-1*math.log(1,2)) + 0.75 * (-0.667*math.log(0.667,2) - 0.333*math.log(0.333,2)) + 0.125 * (-1*math.log(1,2))
smokers_MI = smokers_entropy - smokers_given_asthma
smokers_norm_MI = smokers_MI / asthma_entropy

# Heart disease 
heart_entropy = -0.5 * math.log(0.5,2) - 0.5 * math.log(0.5,2)
heart_given_asthma = 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2))
asthma_given_heart = 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2))
heart_MI = heart_entropy - heart_given_asthma
heart_norm_MI = heart_MI / asthma_entropy

# Pre obese 
pre_obese_entropy = -0.25 * math.log(0.25,2) - 0.75 * math.log(0.75,2)
pre_given_asthma = 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.5 * (-1*math.log(1,2))
asthma_given_pre = 0.25 * (-1*math.log(1,2)) + 0.75 * (-0.333*math.log(0.333,2) - 0.667*math.log(0.667,2)) 
pre_obese_MI = pre_obese_entropy - pre_given_asthma
pre_norm_MI = pre_obese_MI / pre_obese_entropy

# Obese 
obese_entropy = -0.25 * math.log(0.25,2) - 0.5 * math.log(0.5,2) - 0.25 * math.log(0.25,2)
obese_given_asthma = 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) 
asthma_given_obese = 0.25 * (-1*math.log(1,2)) + 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2)) + 0.25 * (-1*math.log(1,2))
obese_MI = obese_entropy - obese_given_asthma
obese_norm_MI = obese_MI / asthma_entropy

# Overweight
overweight_entropy = -0.125 * math.log(0.125,2) - 0.625 * math.log(0.625,2) - 0.25 * math.log(0.25,2)
overweight_given_asthma = 0.5 * (-0.25*math.log(0.25,2) - 0.75*math.log(0.75,2)) + 0.5 * (-0.5*math.log(0.5,2) - 0.5*math.log(0.5,2))
asthma_given_overweight = 0.125 * (-1*math.log(1,2)) + 0.625 * (-0.6*math.log(0.6,2) - 0.4*math.log(0.4,2)) + 0.25 * (-1*math.log(1,2))
overweight_MI = overweight_entropy - overweight_given_asthma
overweight_norm_MI = overweight_MI / asthma_entropy



entropies = {'PM10': pm10_entropy, 'Asthma': asthma_entropy, 'Smokers': smokers_entropy, 'Heart Disease': heart_entropy, 
            'Pre obese': pre_obese_entropy, 'Obese': obese_entropy, 'Overweight': overweight_entropy}
norm_MI = {'PM10': norm_MI_pm10, 'Asthma': 'Na', 'Smokers': smokers_norm_MI, 'Heart Disease': heart_norm_MI, 
            'Pre obese': pre_norm_MI, 'Obese': obese_norm_MI, 'Overweight': overweight_norm_MI}
entropies = pandas.Series(entropies)
norm_MI = pandas.Series(norm_MI)


df = pandas.DataFrame({'Entropies': entropies, 'MI between Asthma and other Health Factors': norm_MI})
print(df)