import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

goals = pd.read_table('goals_2026.txt')
height = pd.read_table('height_2026.txt')
weight = pd.read_table('weight_2026.txt')
speed = pd.read_table('speed_2026.txt')

fig, ax = plt.subplots(2, 3, figsize=(12,8))

ax[0,0].scatter(goals, height, alpha=.8)
ax[0,0].set(title="Goals vs Height", xlabel="Goals", ylabel="Height")

ax[0,1].scatter(weight, goals, alpha=.8)
ax[0,1].set(title="Weight vs Goals", xlabel="Weight", ylabel="Goals")

ax[0,2].scatter(speed, goals, alpha=.8)
ax[0,2].set(title="Speed vs Goals", xlabel="Speed", ylabel="Goals")

ax[1,0].scatter(height, weight, alpha=.8)
ax[1,0].set(title="Height vs Weight", xlabel="Height", ylabel="Weight")

ax[1,1].scatter(height, speed, alpha=.8)
ax[1,1].set(title="Height vs Speed", xlabel="Height", ylabel="Speed")

ax[1,2].scatter(weight, speed, alpha=.8)
ax[1,2].set(title="Weight vs Speed", xlabel="Weight", ylabel="Speed")

for axes in ax.flat:
    axes.grid(True, alpha=.3)

plt.tight_layout()
plt.show()