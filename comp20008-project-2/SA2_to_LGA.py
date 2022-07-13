import pandas as pandas

df = pandas.read_csv("datasets/2011_SA2_to_LGA_vic.csv", dtype = "string")

# Keep only Victorian LGAs
#df = df[df["LGA_CODE_2011"].str[0] == "2"]
# Only ones in AQ_to_LGA.csv
lgas = set(pandas.read_csv("PM10_to_LGA.csv", dtype = "string")["LGA_CODE_2011"].unique())
print(lgas)
df = df[df["LGA_CODE_2011"].isin(lgas)]

df = df.drop("RATIO", axis = 1)
df = df.drop("PERCENTAGE", axis = 1)
df = df.reindex(columns = ["LGA_CODE_2011", "LGA_NAME_2011", "SA2_MAINCODE_2011", "SA2_NAME_2011"])
df = df.sort_values(["LGA_CODE_2011", "SA2_MAINCODE_2011"])
df.to_csv(path_or_buf = "SA2_to_LGA.csv", index = False)