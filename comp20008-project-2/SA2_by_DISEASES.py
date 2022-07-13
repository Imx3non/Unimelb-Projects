import pandas as pandas

df = pandas.read_csv("datasets/SA2_diseases_percentage_vic.csv", dtype = "string")

sa2s = set(pandas.read_csv("SA2_to_LGA.csv", dtype = "string")["SA2_MAINCODE_2011"].unique())

df = df[df["area_code"].isin(sa2s)]
df = df.drop("area_name", axis = 1)
df = df.rename(columns = {"area_code": "SA2_MAINCODE_2011", "arthritis0": "arthritis", "asthma_me0": "asthma", 
    "circ_me_2_": "circulatory_system_diseases", "copd_me_2_": "copd", "diabetes_0": "diabetes_t2", "hg_choles0": "high_cholestral", 
    "hypertens0": "hypertension", "respirtry0": "respiratory_system_diseases"})
df = df.sort_values(["SA2_MAINCODE_2011"])

df.to_csv(path_or_buf = "SA2_DISEASES.csv", index = False)