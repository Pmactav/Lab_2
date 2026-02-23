import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

results = pd.read_csv('task1_results.csv')
weighted = pd.read_csv('task1_weighted.csv')
obsA = pd.read_csv('obsA.csv', header=None).squeeze()
obsB = pd.read_csv('obsB.csv', header=None).squeeze()
resA = pd.read_csv('residualsA.csv', header=None).squeeze()
resB = pd.read_csv('residualsB.csv', header=None).squeeze()

meanA = results.loc[results["Statistic"] == "Mean", "ObsA"].iloc[0]
meanB = results.loc[results["Statistic"] == "Mean", "ObsB"].iloc[0]
ciLowA = weighted.loc[weighted["Statistic"] == "CI95Low","Value"].iloc[0]
ciHighA = weighted.loc[weighted["Statistic"] == "CI95High","Value"].iloc[0]
cilowB = weighted.loc[weighted["Statistic"] == "CI95Low","Value"].iloc[0]
cihighB = weighted.loc[weighted["Statistic"] == "CI95High","Value"].iloc[0]
weightedMean = weighted.loc[weighted['Statistic'] == 'WeightedMean','Value'].values[0]

plt.figure()
plt.plot(obsA, marker='o')
plt.axhline(meanA, linestyle='--', label="Mean")
plt.axhline(weightedMean, linestyle='-.', label="Weighted Mean")
plt.axhline(ciLowA, linestyle=':', label="95% CI")
plt.axhline(ciHighA, linestyle=':')
plt.title("Observer A Observations over Time")
plt.xlabel("Observation Index")
plt.ylabel("Value")
plt.legend()

plt.figure()
plt.plot(obsB, marker='o')
plt.axhline(meanB, linestyle='--', label="Mean")
plt.axhline(weightedMean, linestyle='-.', label="Weighted Mean")
plt.axhline(cilowB, linestyle=':', label="95% CI")
plt.axhline(cihighB, linestyle=':')
plt.title("Observer B Observations over Time")
plt.xlabel("Observation Index")
plt.ylabel("Value")
plt.legend()

resMeanA = resA.mean()
resStdA = resA.std(ddof=1)
resSEM_A = resStdA / np.sqrt(len(resA))
margin99 = 2.576 * resSEM_A
plt.figure()
plt.hist(resA, bins='auto', density=True)
plt.axvline(resMeanA, linestyle='--', label="Residual Mean")
plt.axvline(resMeanA - margin99, linestyle=':', label="99% CI")
plt.axvline(resMeanA + margin99, linestyle=':')
plt.title("Residual Histogram - Observer A")
plt.legend()

resMeanB = resB.mean()
resStdB = resB.std(ddof=1)
resMeanDevB = resStdB / np.sqrt(len(resB))
margin99 = 2.576 * resMeanDevB
plt.figure()
plt.hist(resB, bins='auto', density=True)
plt.axvline(resMeanB, linestyle='--', label="Residual Mean")
plt.axvline(resMeanB - margin99, linestyle=':', label="99% CI")
plt.axvline(resMeanB + margin99, linestyle=':')
plt.title("Residual Histogram - Observer B")
plt.legend()
plt.show()