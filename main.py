import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

# Load data from .csv table
ori_data = pd.read_csv('ori.csv', encoding='gb18030')
fil_data = pd.read_csv('fil.csv', encoding='gb18030')

# Original Data
ori_x = np.array(ori_data['X-Angle(°)'][:15000])
ori_y = np.array(ori_data['Y-Angle(°)'][:15000])
ori_z = np.array(ori_data['Z-Angle(°)'][:15000])
# Filtered Data
fil_x = np.array(fil_data['X-Angle(°)'][:15000])
fil_y = np.array(fil_data['Y-Angle(°)'][:15000])
fil_z = np.array(fil_data['Z-Angle(°)'][:15000])
# Steps
steps = np.array(ori_data['Y-Angle(°)'][15000:])

for i in range(15000):
    ori_x[i] = eval(ori_x[i])
    fil_x[i] = eval(fil_x[i])

# Font Family Set
plt.rcParams['font.sans-serif']='Arial'
f = plt.figure(dpi=100)
# Number of Samples We Selected to Display
display_n = 120
# Public Horizontal Data
X = np.array([a for a in range(1, display_n+1)])


# x plot
plt.plot(X, ori_x[:display_n], color='#e73467', label='X-Axis')
# y plot
plt.plot(X, ori_y[:display_n], color='green', label='Y-Axis')
# z plot
plt.plot(X, ori_z[:display_n], color='#327b9d', label='Z-Axis')
# Loc Show
plt.legend(loc="upper right")
# Title Set
plt.title("Created Data")
# Axis Title
plt.xlabel("Samples")
plt.ylabel("Attitude deviation angle(°)")
# Display the Figure
plt.show()


# x plot
plt.plot(X, fil_x[:display_n], color='#e73467', label='X-Axis')
# y plot
plt.plot(X, fil_y[:display_n], color='green', label='Y-Axis')
# z plot
plt.plot(X, fil_z[:display_n], color='#327b9d', label='Z-Axis')
# Loc Show
plt.legend(loc="upper right")
# Title Set
plt.title("Filtered")
# Axis Title
plt.xlabel("Samples")
plt.ylabel("Attitude deviation angle(°)")
# Display the Figure
plt.show()

# Load Tabel
thresholds_table = pd.read_csv('th.csv', encoding='gb18030')['Thresholds']
# Extent it
thresholds = []
for x in thresholds_table:
    for i in range(50):
        thresholds.append(x)
thresholds = np.array(thresholds)
# Primary Axis
primary_axis = pd.read_csv('th.csv', encoding='gb18030')['Primary Axis'][0]



# Original
plt.plot(X, ori_x[:display_n], color='#e73467', label='Original')
# Filtered
plt.plot(X, fil_x[:display_n], color='green', label='Filtered')
# Threshold
if primary_axis == 0:
    plt.plot(X, thresholds[:display_n], color='#327b9d', label='Thresholds')
# Loc Show
plt.legend(loc="upper right")
# Title Set
plt.title("X-Axis Comparison")
# Axis Title
plt.xlabel("Samples")
plt.ylabel("Attitude deviation angle(°)")
# Display the Figure
plt.show()


# Original
plt.plot(X, ori_y[:display_n], color='#e73467', label='Original')
# Filtered
plt.plot(X, fil_y[:display_n], color='green', label='Filtered')
# Threshold
if primary_axis == 1:
    plt.plot(X, thresholds[:display_n], color='#327b9d', label='Thresholds')
# Loc Show
plt.legend(loc="upper right")
# Title Set
plt.title("Y-Axis Comparison")
# Axis Title
plt.xlabel("Samples")
plt.ylabel("Attitude deviation angle(°)")
# Display the Figure
plt.show()


# Original
plt.plot(X, ori_z[:display_n], color='#e73467', label='Original')
# Filtered
plt.plot(X, fil_z[:display_n], color='green', label='Filtered')
# Threshold
if primary_axis == 2:
    plt.plot(X, thresholds[:display_n], color='#327b9d', label='Thresholds')
# Loc Show
plt.legend(loc="upper right")
# Title Set
plt.title("Z-Axis Comparison")
# Axis Title
plt.xlabel("Samples")
plt.ylabel("Attitude deviation angle(°)")
# Display the Figure
plt.show()