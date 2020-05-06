import numpy as np
import plot as plot
import pandas as pd
from sklearn import datasets
from sklearn.linear_model import Perceptron
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier

class Activity:
    def __init__(self):
        pass
    
    def test(self):
        # import some data to play with
        iris = datasets.load_iris()
        features = iris.feature_names
        names = iris.target_names
        x = iris.data
        y = iris.target
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.33, random_state=True)

        # Perceptron setosa and versicolor
        x_p = x[y != 0]
        y_p = y[y != 0]
        x_p_train, x_p_test, y_p_train, y_p_test = train_test_split(x_p, y_p, test_size=0.33, random_state=True)
        perc = Perceptron(tol=1e-3, random_state=0, max_iter=1000)
        perc.fit(x_p_train, y_p_train)
        perc_score = perc.score(x_p_test, y_p_test)
        y_perc_predict = perc.predict(x_p_test)
        plot.Iris2D2Features(x_p_test, y_perc_predict, names[names != 'virginica'], 'Perceptron Prediction of IRIS dataset - Score ' + str(perc_score * 100) + '%')

        # Multi Layer Perceptron
        mlp = MLPClassifier(max_iter=1000)
        mlp.fit(x_train, y_train)
        mlp_score = mlp.score(x_test, y_test)
        y_mlp_predict = mlp.predict(x_test)
        plot.Iris2D(x_test, y_mlp_predict, names, 'MLP Prediction of IRIS dataset - Score ' + str(mlp_score * 100) + '%')

Activity().test()