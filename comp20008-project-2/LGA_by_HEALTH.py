import pandas as pandas

df = pandas.read_csv("datasets/2015_LGA_health_profiles.csv", dtype = "string")

lgas = set(pandas.read_csv("PM10_to_LGA.csv", dtype = "string")["LGA_CODE_2011"].unique())

df = df[df[" lga_code"].isin(lgas)]
df = df.rename(columns = {" lga_code": "LGA_CODE_2011", "ppl_reporting_heart_disease_perc": "heart_disease", 
    " ppl_reporting_being_pre_obese_perc": "pre_obese", " ppl_reporting_being_obese_perc": "obese", " ppl_aged_over_18_who_are_current_smokers_perc": "smokers"})
df = df.sort_values(["LGA_CODE_2011"])
df = df.reindex(columns = ["LGA_CODE_2011", "smokers", "heart_disease", "pre_obese", "obese"])

df.to_csv(path_or_buf = "LGA_by_HEALTH.csv", index = False)