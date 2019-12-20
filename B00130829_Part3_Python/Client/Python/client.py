import numpy as np
import urllib.request
import matplotlib as mplot
import xml.etree.ElementTree as eletree
import matplotlib.pyplot as plot 

response = urllib.request.urlopen("http://localhost:8080/")
data = response.read().decode()
Temperature_Value = []
Time_Range = []
root = eletree.fromstring(data.strip("\n"))

for reading in root.findall('reading'):
    time = reading.find('time').text
    Time_Range.append(time[time.find(' '):])
    Temperature_Value.append(int(reading.find('temperature').text))
    
plot.style.use("ggplot")
title_obj = plot.title("Temperature Vs Time")
plot.grid(True)
plot.setp(title_obj,fontsize="15",color="red")
plot.xlabel("Time")
plot.ylabel("Temperature")
plot.plot(Time_Range,Temperature_Value,"black")
plot.show()