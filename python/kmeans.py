import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def distance(p1, p2):
    return np.sqrt(np.sum((p1-p2)**2))

def assign_clusters(X, clusters):
    for idx in range(k):
        dist = []

        curr_x = X[idx]

        for i in range(k):
            dis = distance(curr_x, clusters[i]['center'])
            dist.append(dis)
        curr_cluster = np.argmin(dist)
        clusters[curr_cluster]['points'].append(curr_x)
    return clusters

def update_clusters(X, clusters):
    for i in range(k):
        points = np.array(clusters[i]['points'])
        if points.shape[0] > 0:
            new_center = points.mean(axis =0)
            clusters[i]['center'] = new_center

            clusters[i]['points'] = []
    return clusters


def pred_cluster(X, clusters):
    pred = []
    for i in range(X.shape[0]):
        dist = []
        for j in range(k):
            dist.append(distance(X[i], clusters[j]['center']))
        pred.append(np.argmin(dist))

    return pred



iris = pd.read_csv("iris.csv").to_numpy()
data = []
for i in range(99):
    a = []
    for j in range(2):
        a.append(iris[i][j+2])
    data.append(a)
data_arr = np.asarray(data)

k = 3
clusters = {}
np.random.seed(23)

for idx in range(k):
    center = 2*(2*np.random.random((data_arr.shape[1],))-1)
    points = []
    cluster = {
        'center': center,
        'points': []
    }
    clusters[idx] = cluster

clusters = assign_clusters(data_arr, clusters)
clusters = update_clusters(data_arr, clusters)
pred = pred_cluster(data_arr, clusters)

plt.scatter(data_arr[:,0], data_arr[:,1], c = pred)
plt.xlabel("Petal Length")
plt.ylabel("Petal Width")
plt.grid(True)
for i in clusters:
    center = clusters[i]['center']
    plt.scatter(center[0],center[1], marker = '*', c='red')
plt.show()


