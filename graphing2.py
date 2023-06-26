import pandas as pd
import matplotlib
from matplotlib import pyplot as plt
import seaborn as sns
import argparse
import regex as re

file1 = "data/rawdata/noGoldInLeague2."
file2 = "data/rawdata/noGoldBigMult."

files1 = [file1 + str(trial) + ".results" for trial in range(10)]
files2 = [file2 + str(trial) + ".results" for trial in range(10)]

filesL1 = [open(fname, "r") for fname in files1]
filesL2 = [open(fname, "r") for fname in files2]

color = matplotlib.cm.get_cmap('viridis', 9)
leagues, steps = [], []
for numPlayers in range(500000):
    lgs, stps = [], []
    for f in filesL1:
        line = f.readline()
        id, wins, losses, l, s = line.split()
        l = int(l)
        s = int(s)
        lgs.append(l)
        stps.append(s)

    leagues.append(round(sum(lgs)/10))
    steps.append(sum(stps)/10)
todf = []
for l,s in zip(leagues, steps):
    todf.append([l,s])

fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(8, 4))
df = pd.DataFrame(todf, columns=["League", "Step"])
sns.histplot(ax = ax[0],data = df, x = "Step", hue = "League", discrete = True, palette = color)

leagues, steps = [], []
for numPlayers in range(500000):
    lgs, stps = [], []
    for f in filesL2:
        line = f.readline()
        id, wins, losses, l, s = line.split()
        l = int(l)
        s = int(s)
        lgs.append(l)
        stps.append(s)

    leagues.append(round(sum(lgs)/10))
    steps.append(sum(stps)/10)
todf = []
for l,s in zip(leagues, steps):
    todf.append([l,s])

df = pd.DataFrame(todf, columns=["League", "Step"])
ax[0].set_title("55-Step Path")
ax[1].set_title("66-Step Path")
sns.histplot(ax = ax[1],data = df, x = "Step", hue = "League", discrete = True, palette = color)
plt.tight_layout()
plt.show()
