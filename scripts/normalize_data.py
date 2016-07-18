# coding=utf-8
"""
Read a column in order to normalize the data
"""
import pandas as pd

#
# Configuration section
#

data_csv = 'collected_data.csv'
processed_csv = 'rescaled_data.csv'
desired_column = 'my_column'

df = pd.read_csv(data_csv)
maximum = df[desired_column].max()
minimal = df[desired_column].min()

print 'max and minimal from data frame: (%s, %s' % (maximum, minimal)

# used to normalize data
def rescale(value):
    return float(value - minimal) / float(maximum - minimal)


normal_array = [rescale(i) for i in df[desired_column]]

df['normalized_column'] = normal_array
df.to_csv(path_or_buf=processed_csv, sep=',')

