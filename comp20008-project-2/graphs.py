import pandas as pandas
import matplotlib.pyplot as plt

# Retrieve the maximum daily average for 2016 PM10, and then index by the appropriate LGA code
MAX_24HR = pandas.read_csv("PM10_MAX_24HR_READING.csv")
PM10_to_LGA = pandas.read_csv("PM10_to_LGA.csv")
data = MAX_24HR
data["LGA_CODE_2011"] = PM10_to_LGA["LGA_CODE_2011"]
data = data.set_index("LGA_CODE_2011")
data = data.rename(columns = {"value": "max_24hr"})

# Retrieve the yearly average for 2016 PM10
AV_YEAR = pandas.read_csv("PM10_AV_READING.csv")
AV_YEAR["LGA_CODE_2011"] = PM10_to_LGA["LGA_CODE_2011"]
AV_YEAR = AV_YEAR.set_index("LGA_CODE_2011")
data["av_year"] = AV_YEAR["value"]

# Add the adult smoker rate to this data
LGA_by_HEALTH = pandas.read_csv("LGA_by_HEALTH.csv")
LGA_by_HEALTH = LGA_by_HEALTH.set_index("LGA_CODE_2011")
data["smokers"] = LGA_by_HEALTH["smokers"]
data["pre_obese"] = LGA_by_HEALTH["pre_obese"]
data["obese"] = LGA_by_HEALTH["obese"]
data["overweight"] = data["pre_obese"] + data["obese"]

# Average out all SA2 data for each LGA
SA2_by_DISEASES = pandas.read_csv("SA2_by_DISEASES.csv")
SA2_to_LGA = pandas.read_csv("SA2_to_LGA.csv")
LGA_by_DISEASES = SA2_by_DISEASES.join(SA2_to_LGA.set_index("SA2_MAINCODE_2011"), on="SA2_MAINCODE_2011")
LGA_by_DISEASES = LGA_by_DISEASES.drop("SA2_MAINCODE_2011", axis = 1)
LGA_by_DISEASES = LGA_by_DISEASES.groupby(["LGA_CODE_2011"]).mean()

# Add asthma data
data["asthma"] = LGA_by_DISEASES["asthma"]
data = data.reset_index()
data = data.sort_values(["asthma"])

# Maximum PM10 24 hour average against asthma incidence for local government area
fig, ax = plt.subplots()
plt.scatter(data["max_24hr"], data["asthma"], c = "b")
ax.set_xlabel("Maximum PM10 daily reading (2016, μg/m³)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Maximum Daily PM10 Reading")
fig.savefig("graphs/pm1024hr_vs_asthma.png", bbox_inches='tight')
plt.close(fig)

# Overall average PM10 against asthma
fig, ax = plt.subplots()
plt.scatter(data["av_year"], data["asthma"], c = "b")
ax.set_xlabel("Average PM10 reading (2016, μg/m³)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Average PM10 Reading")
fig.savefig("graphs/pm10avyr_vs_asthma.png", bbox_inches='tight')
plt.close(fig)

# Smoker rate against asthma
fig, ax = plt.subplots()
ax.scatter(data["smokers"], data["asthma"],c = "r")
ax.set_xlabel("Adult smokers rate (percentage)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Adult Smoker Rate")
fig.savefig("graphs/smokers_vs_asthma.png", bbox_inches='tight')
plt.close(fig)

# Obesity rate against asthma
fig, ax = plt.subplots()
ax.scatter(data["obese"], data["asthma"], c = "r")
ax.set_xlabel("Adult obesity rate (percentage)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Adult Obesity Rate")
fig.savefig("graphs/obesity_vs_asthma.png", bbox_inches='tight')
plt.close(fig)

# Preobese rate against asthma
fig, ax = plt.subplots()
ax.scatter(data["pre_obese"], data["asthma"], c = "r")
ax.set_xlabel("Adult pre-obese rate (percentage)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Adult Pre-Obese")
fig.savefig("graphs/pre_obesity_vs_asthma.png", bbox_inches='tight')
plt.close(fig)

# Overweight rate against asthma
fig, ax = plt.subplots()
ax.scatter(data["overweight"], data["asthma"], c = "r")
ax.set_xlabel("Adult obese or pre-obese rate (percentage)")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Adult Obese or Pre-Obese Rate")
fig.savefig("graphs/overweight_vs_asthma.png", bbox_inches='tight')
plt.close(fig)


# Normalised addition of all three
min = data["max_24hr"].min()
max = data["max_24hr"].max()
data["pm10_normalised"] = (data["max_24hr"] - min) / (max - min)

min = data["overweight"].min()
max = data["overweight"].max()
data["overweight_normalised"] = (data["overweight"] - min) / (max - min)

data["normalised_average"] = (data["pm10_normalised"] +  data["overweight_normalised"])/2.0

fig, ax = plt.subplots()
ax.scatter(data["normalised_average"], data["asthma"], c = "purple")
ax.set_xlabel("Normalised maximum PM10 daily reading and obese or pre-obese percentage")
ax.set_ylabel("Asthma incidence (percentage)")
ax.set_title("Asthma Incidence vs Normalised PM10 Daily Reading and Adult Overweightness")
fig.savefig("graphs/normalised_vs_asthma.png", bbox_inches='tight')
plt.close(fig)
