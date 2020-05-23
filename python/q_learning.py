import numpy as np
import random as rd

class QLearning:
    def __init__(self, mRewards = None, numberStates = None, gama = 0.5, alpha = 1, episodes = 50, startState = 0, goalState = None):
        rd.seed(1)
        if mRewards is None:
            if numberStates is not None:
                self.__numberStates = numberStates
                self.__mRewards = np.zeros((self.__numberStates, self.__numberStates))
            else:
                raise Exception('mRewards is null and numberStates also')
        else:
            self.__mRewards = mRewards
            self.__numberStates = len(mRewards)
        
        self.__startState = 0
        self.__episodes = episodes
        self.__alpha = alpha
        self.__gama = gama
        self.__mQ = np.zeros((self.__numberStates, self.__numberStates))
        self.__mAdj = np.zeros((self.__numberStates, self.__numberStates))
        if goalState is None:
            self.__goalState = self.__numberStates - 1

    def __randomSelection(self, state):
        options = []
        for i in range(len(self.__mAdj[state])):
            if self.__mAdj[state][i] == 1:
                options.append(i)

        nextState = rd.choice(options)

        return nextState

    def addConnection(self, sFrom, sTo, reward = 0, biDirectional = False):
        self.__mRewards[sFrom][sTo] = reward
        self.__mAdj[sFrom][sTo] = 1

        if biDirectional is True:
            self.__mRewards[sTo][sFrom] = reward
            self.__mAdj[sTo][sFrom] = 1

    def __hasConnection(self, sFrom, sTo):
        if self.__mAdj[sFrom][sTo] == 1:
            return True
        else:
            return False

    def __maximizeState(self, action):
        maxQ = 0
        for i in range(len(self.__mQ)):
            if self.__hasConnection(action, i):
                maxAux = self.__mQ[action][i]
                if maxAux > maxQ:
                    maxQ = maxAux

        return maxQ

    def __updateQ(self, state, action):
        if self.__goalState == state:
            return

        self.__mQ[state][action] = ((1 - self.__alpha) * self.__mRewards[state][action]) + self.__alpha * (self.__mRewards[state][action] + (self.__gama * self.__maximizeState(action)))

    def run(self):
        state = self.__startState
        while self.__episodes > 0:
            randomAction = self.__randomSelection(state)
            self.__updateQ(state, randomAction)
            state = randomAction
            self.__episodes -= 1 

    def printResult(self):
        for i in range(self.__numberStates):
            maxVal = 0
            maxIndex = -1
            
            for j in range(len(self.__mQ[i])):
                if self.__mQ[i][j] > maxVal:
                    maxVal = self.__mQ[i][j]
                    maxIndex = j

            if i == self.__goalState:
                print('Goal State ' + str(i))
            else:
                for j in range(len(self.__mQ[i])):
                    if self.__mQ[i][j] == maxVal:
                        print('State ' + str(i) + ' go to state ' + str(j))



ql = QLearning(numberStates=6, gama=0.8, startState=1)
ql.addConnection(0, 4, 0, True)
ql.addConnection(2, 3, 0, True)
ql.addConnection(1, 3, 0, True)
ql.addConnection(3, 4, 0, True)
ql.addConnection(1, 5, 100)
ql.addConnection(4, 5, 100)
ql.addConnection(5, 1, 0)
ql.addConnection(5, 4, 0)

ql.run()
ql.printResult()