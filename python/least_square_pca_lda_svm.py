import numpy as np
import plot as plot
import pandas as pd
from sklearn import datasets
from sklearn.decomposition import PCA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn import linear_model
from sklearn import svm
from sklearn.model_selection import train_test_split

class Activity3:
    def __init__(self):
        pass
    
    def test(self):
        # import some data to play with
        iris = datasets.load_iris()
        names = iris.target_names
        x = iris.data
        y = iris.target

        # pure plot
        plot.LdaIris2D(x, y, names, 'Iris projection')

        # LinearRegression
        regr = linear_model.LinearRegression()
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.33, random_state=True)
        regr.fit(x_train, y_train)
        y_pred = regr.predict(x_test)
        print('LinearRegression Coefficients: \n', regr.coef_)

        # Principal Analysis Component
        pca = PCA(n_components=2)
        pca_result = pca.fit(x).transform(x)
        plot.PcaIris2D(pca_result, y, names, 'Iris projection with PCA')

        # Linear Dependent Analysis
        lda = LinearDiscriminantAnalysis(n_components=2)
        lda_result = lda.fit(x, y).transform(x)
        plot.LdaIris2D(lda_result, y, names, 'Iris projection with LDA')

        # Support Vector Machine
        clf = svm.SVC(kernel = 'rbf', gamma = 'auto')
        clf.fit(x, y)
        print('SVM Coefficients: \n', clf.coef_)

Activity3().test()