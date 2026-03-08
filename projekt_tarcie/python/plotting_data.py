from matplotlib import pyplot
import seaborn as sns
import pandas as pd
import numpy as np 
import plotly.express as px

data = pd.read_csv("C:/Users/micha/OneDrive/arduino/projekt tarcie/python/data")

time = data[0]
hall_value = data[1]
rpm = data[2]

