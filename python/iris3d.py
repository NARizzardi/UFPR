import matplotlib.pyplot as plt
import pandas as pd
from sklearn.cluster import KMeans

iris = pd.read_csv("iris.csv2")
print(iris.to_string())
x = iris["petal.length"]
z = iris["sepal.width"]
y = iris["petal.width"]
data = list(zip(x,y,z))

kmeans = KMeans(n_clusters=3)
kmeans.fit(data)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(x,y,z, c=kmeans.labels_)
ax.set_xlabel('Petal Length')
ax.set_ylabel('Petal Width')
ax.set_zlabel('Sepal Width')

plt.show()
