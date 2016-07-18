# -*- coding: utf-8 -*-
import pandas as pd
from scipy.interpolate import griddata
import matplotlib.pyplot as plt
import numpy as np


def rescale(nums, new_min, new_max):
    """
    Recebe uma série de dados (nums) e retorna a série
    em uma nova escala (entre new_min e min_max)
    """
    return ((nums - nums.min()) / (nums.max() - nums.min())) * (new_max - new_min) + new_min

arquivo = 'my_uav_data.csv'
# loads data frame
df = pd.read_csv(arquivo)            
df['latitude'] = rescale(df.latitude, 0, 1)
df['longitude'] = rescale(df.longitude, 0, 1)

temperaturas = rescale(df.bartemp, -1, 1).values

d = df[['longitude', 'latitude']].values
grid_x, grid_y = np.mgrid[0:1:100j, 0:1:100j]       # creates a grid
fig, ax = plt.subplots()

# create a grid data with points, values and interpolation method
z = griddata(d, temperaturas, (grid_x, grid_y), method='linear')

cax = plt.imshow(z.T, origin='lower')

ax.set_title('Temperatura em Celcius')
cbar = fig.colorbar(cax)

# subtitle
fraction = 0.17
v = []
c = 27.2
for i in range(10):
    legend = float(c) + float(fraction)
    c += fraction
    v.append("%.2f" % legend)

cbar.ax.set_yticklabels(v)    # color bar
plt.ylabel('Longitude')
plt.xlabel('Latitude')
plt.show()

