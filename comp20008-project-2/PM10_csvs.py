import pandas as pandas

air_quality_readings = pandas.read_csv("datasets/2016_1HR.csv", dtype="str", low_memory=False)
def time_to_iso8601(old):
    #01-01-16 0:00 to 2016-01-01T00:00
    parts = old.split(" ")
    old_date = parts[0]
    new_date = "20" + old_date[6:8] + "-" + old_date[3:5] + "-" + old_date[0:2]
    old_time = parts[1]
    time = new_date + "T" + old_time.zfill(5)
    return time

air_quality_readings["sample_datetime"] = air_quality_readings["sample_datetime"].apply(time_to_iso8601)
air_quality_readings = air_quality_readings.drop("time_basis_id", axis=1)

air_quality_readings = air_quality_readings.sort_values(['sp_name', 'sample_datetime'])
air_quality_readings['sample_datetime'] = pandas.to_datetime(air_quality_readings['sample_datetime'], format = "%Y-%m-%dT%H:%M")
air_quality_readings['value'] = air_quality_readings['value'].astype(float)
air_quality_readings = air_quality_readings.set_index(["sample_datetime"])
max_readings = air_quality_readings.groupby(['sp_name']).max()

max_readings.to_csv(path_or_buf = "PM10_MAX_1HR_READING.csv")

max_24HR = air_quality_readings.groupby(["sp_name"]).resample("D").mean().groupby(["sp_name"]).max()
max_24HR.to_csv(path_or_buf = "PM10_MAX_24HR_READING.csv")

average = air_quality_readings.groupby(["sp_name"]).mean()
average.to_csv(path_or_buf = "PM10_AV_READING.csv")