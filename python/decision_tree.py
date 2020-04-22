import pandas as pd
import numpy as np
import operator
import pprint
from sklearn.datasets import load_iris

class DecisionTree:
    def __init__(self, dataset):
        self.__dataset = dataset

    def __EntropyCalculation(self, dictCountableAttributes):
        eps = np.finfo(float).eps
        result = 0
        sumCounts = 0

        for i in dictCountableAttributes:
            sumCounts += dictCountableAttributes[i]

        for i in dictCountableAttributes:
            result += -dictCountableAttributes[i]/sumCounts * np.log2((dictCountableAttributes[i]/sumCounts + eps))

        return result

    def __DatasetEntropyCalculation(self, dataset):
        listAttributes = dataset.iloc[:, - 1].unique()
        dictCountableAttributes = dict()
        for i in listAttributes:
            dictCountableAttributes[i] = dataset[dataset.iloc[:, - 1] == i].count()[0]
        
        return self.__EntropyCalculation(dictCountableAttributes), dictCountableAttributes

    def __FeatureEntropyCalculation(self, dataset):
        dictEntropy = dict()    
        decisionCol = dataset.iloc[:, - 1].name
        featureCols = dataset.columns.tolist()[:-1]
        
        for feature in featureCols:
            dictEntropy[feature] = dict()        
            currentFeature = dataset[[feature, decisionCol]]
            
            for currentFeature, subDataset in currentFeature.groupby(currentFeature.columns[0]):
                curr_it = subDataset.iloc[0,0]
                dictEntropy[feature][curr_it] = dict()
                dictEntropy[feature][curr_it]['entropy'], dictEntropy[feature][curr_it]['pn'] = self.__DatasetEntropyCalculation(subDataset)

        return dictEntropy

    def __DatasetGainCalculation(self, dataset):    
        dictGain = dict()
        infoGain = dict()
        totalEntropy, totalPositiveNegative = self.__DatasetEntropyCalculation(dataset)
        datasetEntropy = self.__FeatureEntropyCalculation(dataset)
        
        denominator = 0
        for i in totalPositiveNegative:
            denominator += totalPositiveNegative[i]
        
        for feature in datasetEntropy:
            attributes = datasetEntropy.get(feature)
            sumEntropy = 0
            for i in attributes:    
                attribute = attributes.get(i)            
                numerator = 0            
                for c in attribute['pn']:
                    numerator += attribute['pn'][c]
                    
                sumEntropy += (abs(numerator) / abs(denominator)) * attribute['entropy']
                infoGain[feature] = sumEntropy

        for i in infoGain:
            val = infoGain.get(i)
            dictGain[i] = totalEntropy - val
        
        return dict(sorted(dictGain.items(), key=operator.itemgetter(1),reverse=True))

    def __BuildTree(self, dataset):
        tree = dict()    
        decisionCol = dataset.iloc[:, - 1].name    
        datasetGain = self.__DatasetGainCalculation(dataset)
        currentFeature = list(datasetGain.keys())[0]    

        attributesDistinct = dataset[currentFeature].unique().tolist()
        tb = dataset.groupby([currentFeature, decisionCol]).size().reset_index(name='Count')
        tree[currentFeature] = {}

        for i in attributesDistinct:
            occ = tb[currentFeature].tolist().count(i)
            
            if occ == 1:
                tree[currentFeature][i] = tb[tb[currentFeature] == i][decisionCol].values[0]
            else:            
                subDataset = dataset[dataset[currentFeature] == i].reset_index(drop=True)
                tree[currentFeature][i] = self.__BuildTree(subDataset)
                
        return tree

    def BuildTree(self):
        return self.__BuildTree(self.__dataset)        

iris = load_iris()
iris_ds = pd.DataFrame(data= np.c_[iris['data'], iris['target']], columns= iris['feature_names'] + ['target'])
clf = DecisionTree(iris_ds)
pprint.pprint(clf.BuildTree())