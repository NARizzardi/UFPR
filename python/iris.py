import matplotlib.pyplot as plt
import pandas as pd
from sklearn.cluster import KMeans

iris = pd.read_csv("iris.csv")
print(iris.to_string())
x = iris["petal.length"]
y = iris["petal.width"]
data = list(zip(x,y))

kmeans = KMeans(n_clusters=2)
kmeans.fit(data)

plt.scatter(x, y, c=kmeans.labels_)
plt.xlabel("Petal Length")
plt.ylabel("Petal Width")
plt.show()
