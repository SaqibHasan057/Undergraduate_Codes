import numpy as np
import math
import re
from sklearn import datasets
from sklearn import preprocessing
from tensorflow.examples.tutorials.mnist import input_data
from matplotlib import pyplot as plt


class neural_network:

    def __init__(self,numberOfLayers,numberOfPerceptronsPerLayer,learning_rate):
        self.weight = None
        self.biases = None

        self.numberOfLayers = numberOfLayers
        self.numberOfPerceptronsPerLayer = numberOfPerceptronsPerLayer
        self.learning_rate = learning_rate

    def sigmoidFunction(self,x):
        return 1 / (1 + np.e ** (-x))

    def sigmoidDerivative(self,x):
        return self.sigmoidFunction(x) * (1 - self.sigmoidFunction(x))



    def initializeWeightBiasMatrices(self,numberOfLayers,numberOfPerceptronsPerLayer):
        np.random.seed(1305057)
        mean = 0
        std = 1

        weights = []
        biases = []

        for i in range(0, len(numberOfPerceptronsPerLayer) - 1):
            tempWeight = np.random.normal(mean, std,
                                          (numberOfPerceptronsPerLayer[i + 1], numberOfPerceptronsPerLayer[i]))
            tempBias = np.random.normal(mean, std, (numberOfPerceptronsPerLayer[i + 1], 1))

            weights.append(tempWeight)
            biases.append(tempBias)

        return weights, biases

    def feedForward(self,input, weights, biases):
        feedInput = input
        h = []
        z = []

        h.append(input)
        z.append("dummy")
        for i in range(0, len(weights)):
            weightHolder = weights[i]
            biasHolder = biases[i]
            output = np.matmul(weightHolder, feedInput) + biasHolder
            z.append(output)
            output = self.sigmoidFunction(output)
            h.append(output)
            feedInput = output

        return feedInput, h, z

    def backpropagationGradientDescent(self,h, z, y_actual, y_predicted, weights, biases, learning_rate):
        delta = []
        derivativeUpdate = []
        nl = len(h)

        cost = 0.5 * (y_actual - y_predicted) ** 2

        for i in range(0, nl):
            delta.append(0)

        ##Calculate outer layer delta
        outer_layer_delta = -(y_actual - h[nl - 1]) * self.sigmoidDerivative(z[nl - 1])
        delta[nl - 1] = outer_layer_delta

        ##Calculate the delta of the different layers
        for i in range(nl - 2, 0, -1):
            tempDelta = np.matmul(np.transpose(weights[i]), delta[i + 1]) * self.sigmoidDerivative(z[i])
            delta[i] = tempDelta

       ## print("Delta",delta)

        ##Caculate the partial derivative of cost against delta
        for i in range(nl - 1, 0, -1):
            ##print("Shape",delta[i].shape,np.transpose(h[i-1]).shape)
            tempCost = np.matmul(delta[i], np.transpose(h[i - 1]))
            ##print("Shape after multiplication",tempCost.shape)
            derivativeUpdate.append(tempCost)
        ##print("Derivatives",derivativeUpdate)
        derivativeUpdate.reverse()
        ##print("Derivatives",derivativeUpdate)




        return derivativeUpdate, delta, cost

    def addUpdate(self,derivativeUpdate,delta,delta_weight,delta_bias):

        if(delta_weight==0):
            delta_weight = derivativeUpdate
        else:
            for i in range(0,len(derivativeUpdate)):
                ##print("Delta",delta_weight[i])
                ##print("Div",derivativeUpdate[i])
                delta_weight[i]+=derivativeUpdate[i]

        if(delta_bias==0):
            delta_bias = delta
        else:
            for i in range(0,len(delta)):
                delta_bias[i]+=delta[i]

        return delta_weight,delta_bias


    def gradientDescent(self,weights,biases,derivativeUpdate,delta,lengthOfDataset):
        new_weights = []
        new_biases = []

        for i in range(0, len(derivativeUpdate)):
            derivativeUpdate[i]= 1/lengthOfDataset * derivativeUpdate[i]

        for i in range(0,len(delta)):
            delta[i] = 1/lengthOfDataset * delta[i]


        for i in range(0, len(weights)):
            # print("Iteration: ",i)
            tempWeight = weights[i] - learning_rate * derivativeUpdate[i]
            tempBias = biases[i] - learning_rate * delta[i + 1]
            new_weights.append(tempWeight)
            new_biases.append(tempBias)

        return new_weights, new_biases

    def trainNeuralNetwork(self,x_list, y_list, numberOfIterations):
        self.weights, self.biases = self.initializeWeightBiasMatrices(self.numberOfLayers, self.numberOfPerceptronsPerLayer)
        costList = []
        iterationList = []



        print("Started Neural Network Training:")

        for i in range(0, numberOfIterations):
            delta_weight = 0
            delta_bias = 0
            totalCostOfIteration = 0;

            for j in range(0,len(x_list)):
                print("Processing data number: ", j)
                y, h, z = self.feedForward(x_list[j], self.weights, self.biases)
                temp_weight_update, temp_bias_update, cost = self.backpropagationGradientDescent(h, z, y_list[j], y, self.weights, self.biases,
                                                                       self.learning_rate)
                delta_weight,delta_bias = self.addUpdate(temp_weight_update,temp_bias_update,delta_weight,delta_bias)
                totalCostOfIteration += sum(cost)
                print("Cost till now:", totalCostOfIteration)
            ##print("Performing gradient descent!!")
            self.weights,self.biases = self.gradientDescent(self.weights,self.biases,delta_weight,delta_bias,len(x_list))
            print("Completed Iteration Number: ", i)
            print("Total Cost of iteration: ", totalCostOfIteration)
            costList.append(totalCostOfIteration)
            iterationList.append(i+1)
            print()

        return costList,iterationList



    def testNeuralNetwork(self,x, y):
        count = 0

        for i in range(0, len(x)):
            test, h, z = self.feedForward(x[i], self.weights, self.biases)
            y_predicted_index = np.argmax(test)
            y_actual_index = np.argmax(y[i])
            ##print("Y_actual",y[i],y_actual_index)
            ##print("Y_Predicted",test,y_predicted_index)
            if (y_predicted_index == y_actual_index):
                count = count + 1

        return count / len(x)

def convertDataForFeeding(x,y):
    X = []
    Y = []

    for i in range(0,len(x)):
        xtemp = x[i]
        ytemp = y[i]
        xtemp = np.array([xtemp])
        ytemp = np.array([ytemp])
        xtemp = np.transpose(xtemp)
        ytemp = np.transpose(ytemp)
        X.append(xtemp)
        Y.append(ytemp)

    X = np.array(X)
    Y = np.array(Y)

    return X,Y

def readDatasetFromFile(trainData,testData,numberOfFeatures,numberOfClasses):
    train_file = open(trainData,"r")
    test_file = open(testData,"r")

    x_train = []
    y_train = []

    x_test = []
    y_test = []


    ##x = re.sub('[\n\t]', '', x)
    train_list = []

    for x in train_file:
        x = re.sub('[\n\t]'," ",x)
        x = x.split()
        featureVector = x[:numberOfFeatures]
        featureVector = [float(x) for x in featureVector]
        classVector = int(x[numberOfFeatures])
        oneHotClassVector = [0]*numberOfClasses
        oneHotClassVector[classVector-1] = 1

        x_train.append(featureVector)
        y_train.append(oneHotClassVector)

    for x in test_file:
        x = re.sub('[\n\t]', " ", x)
        x = x.split()
        featureVector = x[:numberOfFeatures]
        featureVector = [float(x) for x in featureVector]
        classVector = int(x[numberOfFeatures])
        oneHotClassVector = [0] * numberOfClasses
        oneHotClassVector[classVector - 1] = 1

        x_test.append(featureVector)
        y_test.append(oneHotClassVector)


    x_train,y_train = convertDataForFeeding(x_train,y_train)
    x_test,y_test = convertDataForFeeding(x_test,y_test)

    return x_train,y_train,x_test,y_test







def simpleTestData():
    x_data = np.array([[[0], [0]], [[0], [1]], [[1], [0]], [[1], [1]]])
    y_data = np.array([[[0], [0]], [[1], [1]], [[1], [1]], [[0], [0]]])
    return x_data,y_data


def irisDataset():
    iris = datasets.load_iris()
    X = iris.data
    X = preprocessing.normalize(X)
    Y = iris.target

    X = np.array(X)

    y_one_hot = []
    for i in range(0,len(Y)):
        one_hot_vector = [0,0,0]
        one_hot_vector[Y[i]]=1
        y_one_hot.append(one_hot_vector)

    y_one_hot = np.array(y_one_hot)

    X,y_one_hot = convertDataForFeeding(X,y_one_hot)

    return X,y_one_hot


def tensorflowMnistDataset():
    mnist = input_data.read_data_sets('MNIST_data', one_hot=True)
    x_train_data = mnist.train.images
    y_train_data = mnist.train.labels

    x_test_data = mnist.test.images
    y_test_data = mnist.test.labels

    x_train_data, y_train_data = convertDataForFeeding(x_train_data, y_train_data)
    x_test_data, y_test_data = convertDataForFeeding(x_test_data, y_test_data)

    return x_train_data,y_train_data,x_test_data,y_test_data


def plotCostGraph(x,y):
    plt.plot(x,y)
    plt.xlabel("Iteration")
    plt.ylabel("Cost")
    plt.show()






numberOfInputFeatures = 3
numberOfOutputClasses = 3
iterations = 100
numberOfLayers = 4 ##number of layers including the input and output layers
numberOfPerceptronsPerLayer = [numberOfInputFeatures,10,10,numberOfOutputClasses] ##number of layers of perceptrons in each of the layers including the input and output layer
learning_rate = 0.5

x_train,y_train,x_test,y_test = readDatasetFromFile("Train.txt","Test.txt",numberOfInputFeatures,numberOfOutputClasses)

##x_train,y_train = irisDataset()
##x_test,y_test = x_train,y_train

##x_train,y_train,x_test,y_test = tensorflowMnistDataset()


mlp = neural_network(numberOfLayers,numberOfPerceptronsPerLayer,learning_rate)


cost,iteration = mlp.trainNeuralNetwork(x_train,y_train,iterations)
accuracy = mlp.testNeuralNetwork(x_test,y_test)

print("Accuracy:",accuracy*100)
plotCostGraph(iteration,cost)









