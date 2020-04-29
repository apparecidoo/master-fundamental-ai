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
        features = iris.feature_names
        names = iris.target_names
        x = iris.data
        y = iris.target
        x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.33, random_state=True)

        # LinearRegression
        regr = linear_model.LinearRegression()
        regr.fit(x_train, y_train)
        y_regr_pred = regr.predict(x_test)
        plot.LinearRegressionIris2D(y_test, y_regr_pred)

        # Principal Analysis Component
        pca = PCA(n_components=2)
        pca_result = pca.fit(x).transform(x)
        plot.PcaIris2D(pca_result, y, names, np.transpose(pca.components_[0:2, :]))

        # Linear Dependent Analysis
        lda = LinearDiscriminantAnalysis(n_components=2)
        lda.fit(x, y).transform(x)
        y_lda_pred = lda.predict(x_test)
        plot.LdaIris2D(x_test, y_lda_pred, names)

        # Support Vector Machine
        x_df = pd.DataFrame(iris.data, columns = features).iloc[:,2:4].values
        clf = svm.LinearSVC(C=1).fit(x_df, y)
        x_svm_min, x_svm_max = x_df[:, 0].min() - 1, x_df[:, 0].max() + 1
        y_svm_min, y_svm_max = x_df[:, 1].min() - 1, x_df[:, 1].max() + 1
        xp_svm, yp_svm = np.meshgrid(np.arange(x_svm_min, x_svm_max, .02), np.arange(y_svm_min, y_svm_max, .02))
        svm_pred = clf.predict(np.c_[xp_svm.ravel(), yp_svm.ravel()]).reshape(xp_svm.shape)
        plot.SvmIris2D(x_df, y, features, names, xp_svm, yp_svm, svm_pred)

Activity3().test()
