import math
import csv
import numpy as np
from matplotlib import pyplot as plt
from scipy.stats import multivariate_normal
import sklearn.datasets as skd
from scipy.stats import chi2
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse
import re

N = 0
k = 0
d = 0



def readCSVFile(file):
    with open(file) as csvfile:
        readCSV = csv.reader(csvfile,delimiter=',')
        print(readCSV)
        csvList = []

        for row in readCSV:
            csvList.append(row)

    return csvList

def createIrisSampleList(list):
    finalList = []
    skipFirst = True;

    for x in list:
        if(skipFirst):
            skipFirst=False
            continue
        finalList.append([float(x[1]),float(x[2]),float(x[3]),float(x[4])])


    return finalList

def initialize(N,k,d):
    meanMatrix = []
    covarianceMatrix = []
    weightMatrix = []

    #Initialize Weight
    for i in range(0,k):
        weightMatrix.append(1/k)
    weightMatrix = np.asarray(weightMatrix)

    np.random.seed(6)


    #Initialize mean

    for i in range(0,k):
        mean=[]
        for j in range(0,d):
            randN = np.random.normal();
            mean.append(randN)
        mean = np.asarray(mean)
        meanMatrix.append(mean)
    meanMatrix = np.asarray(meanMatrix)

    #Initialize Covariance Matrix

    for i in range(0,k):

        """
        covarianceTemp = []
        for j in range(0,d):
            covarRow=[]
            for k in range(0,d):
                randN = np.random.normal(loc=0,scale=9);
                covarRow.append(randN)
            covarRow = np.asarray(covarRow)
            covarRow = np.abs(covarRow)
            covarianceTemp.append(covarRow)

        covarianceTemp = np.asarray(covarianceTemp)

        covarianceTemp = np.matmul(covarianceTemp,covarianceTemp.transpose())
        """


        covarianceTemp = skd.make_spd_matrix(n_dim=d)
        covarianceTemp = 40 * covarianceTemp

        covarianceMatrix.append(covarianceTemp)

    covarianceMatrix = np.asarray(covarianceMatrix)

    return meanMatrix,covarianceMatrix,weightMatrix


def multivariateGaussian(sample,mean,covariance,D):
    localSample = np.asarray([sample])
    localSample = localSample.transpose()
    localMean = np.asarray([mean])
    localMean = localMean.transpose()
    ##print(localSample)
    ##print(localMean)
    ##print(np.linalg.det(covariance))
    equation_part_one = 1/np.sqrt( (2 * np.pi)**D * np.linalg.det(covariance))
    equation_part_two = -0.5 * np.matmul((localSample-localMean).transpose(), np.matmul(np.linalg.inv(covariance) ,(localSample-localMean)))
    ##print(equation_part_two[0])
    ##print(covariance[0][0])
    equation_part_two = np.e**equation_part_two[0][0]
    final_equation = equation_part_one * equation_part_two
    ##print(equation_part_one)
    ##print(equation_part_two)

    return final_equation


def caculateloglikelihood(mean,covariance,weight,sample,D):
    logLikelihood = 0

    for j in range(0,len(sample)):
        tempSum = 0
        for i in range(0,len(mean)):
            tempSum += weight[i] * multivariateGaussian(sample[j],mean[i],covariance[i],D)
        logLikelihood += np.log(tempSum)

    return logLikelihood


def eStep(mean,covariance,weight,sample,gaussianNumber,sampleNumber,D):
    Pij = np.zeros(shape=(gaussianNumber,sampleNumber))

    for i in range(0,gaussianNumber):
        for j in range(0,sampleNumber):
            Pij[i][j] = weight[i] * multivariateGaussian(sample[j],mean[i],covariance[i],D) ##+ 0.00000000001

    for j in range(0,sampleNumber):
        normalizer = 0
        for i in range(0,gaussianNumber):
            normalizer+=Pij[i][j]

        for i in range(0,gaussianNumber):
            Pij[i][j] = Pij[i][j]/normalizer

    return Pij


def mstep(mean,covariance,weight,sample, Pij, gaussianNumber, sampleNumber, D):
    newMean = np.zeros(shape=(gaussianNumber, D))
    newCovariance = np.zeros(shape=(gaussianNumber, D, D))
    newWeight = np.zeros(shape=gaussianNumber)


    ##Finding the new mean
    for i in range(0,gaussianNumber):
        sumPij = 0
        sumPijXj = 0
        sumPijXminusM = 0
        for j in range(0,sampleNumber):
            sumPij += Pij[i][j]
            sumPijXj += Pij[i][j] * sample[j]

            columnSample = np.asarray([sample[j]])
            columnSample = columnSample.transpose()
            columnMean = np.asarray([mean[i]])
            columnMean = columnMean.transpose()

            sumPijXminusM += Pij[i][j] * np.matmul((columnSample-columnMean),np.transpose(columnSample-columnMean))

        newMean[i] = sumPijXj/sumPij
        ##print("Sum PijXminusM", sumPijXminusM)
        ##print("Sum Pij", sumPij)
        ##print("Ans",sumPijXminusM/sumPij)
        newCovariance[i] = sumPijXminusM/sumPij
        ##print("New covariance: ",newCovariance[i])
        newWeight[i] = sumPij/sampleNumber

    return newMean,newCovariance,newWeight


def printMatrices(mean,covariance,weight):
    print('Mean:')
    print(mean)
    print()
    print()

    print('Covariance:')
    print(covariance)
    print()
    print()

    print('Weight:')
    print(weight)
    print()
    print()


def plotEllipseForDataset(mean,covariance):

    for i in range(0,len(mean)):
        x = mean[i][0]
        y = mean[i][1]
        a = np.sqrt(covariance[i][0][0])
        b = np.sqrt(covariance[i][1][1])
        t = np.linspace(0, 2 * np.pi, 100)
        plt.plot(x + 2 * a * np.cos(t), y + 2 * b * np.sin(t),linestyle = '--', color='green')


def plotEllipseForEMAlgo(mean,covariance):

    for i in range(0,len(mean)):
        x = mean[i][0]
        y = mean[i][1]
        a = np.sqrt(covariance[i][0][0])
        b = np.sqrt(covariance[i][1][1])
        t = np.linspace(0, 2 * np.pi, 100)
        plt.plot(x + 2 * a * np.cos(t), y + 2 * b * np.sin(t),linestyle = ':', color='red')

def meanRMS(mean,pastMean):
    sum = 0
    for i in range(len(mean)):
        rm = (mean[i]-pastMean[i])**2
        rm = np.sum(rm)
        sum+=rm

    return sum




def createSyntheticDataset():
    mean = [ np.array([0,0]) , np.array([0,4]) , np.array([3,3]) ]
    mean = np.array(mean)

    covariance = [ np.array([[0.5,0.3],[0.3,0.5]]) , np.array([[1.1,0.5],[0.5,1.1]]) , np.array([[0.3,0.2],[0.2,0.3]]) ]
    covariance = np.array(covariance)

    np.random.seed(1305057)
    sampleList = []
    numberOfSamples = 300

    for i in range(0,numberOfSamples):
        for j in range(0,len(mean)):
            sample = np.random.multivariate_normal(mean[j],covariance[j])
            ##print(sample)
            sampleList.append(sample)

    sampleList = np.array(sampleList)

    return sampleList,mean,covariance






def plotPoints(sampleList,datasetMean,datasetCovariance,mean,covariance):
    x = []
    y = []

    for i in range(0,len(sampleList)):
        x.append(sampleList[i][0])
        y.append(sampleList[i][1])

    plt.scatter(x,y,linewidths=2)
    plotEllipseForDataset(datasetMean,datasetCovariance)
    plotEllipseForEMAlgo(mean,covariance)
    plt.xlabel("Feature 1")
    plt.ylabel("Feature 2")
    plt.show()








"""
##File Reading
csvFile = readCSVFile("Iris.csv")
sampleList = createIrisSampleList(csvFile)
sampleList = np.asarray(sampleList)

##print(sampleList)
"""




sampleList,datasetMean,datasetCovariance = createSyntheticDataset()



N = len(sampleList)
k = 3
d = 2













##Main algorithm
iteration = 1
prevLogLikelihood = 0
prevMean = 0
threshold = 1e-9

##Step 1: Initialize matrices
mean, covariance, weight = initialize(N, k, d)
Pij = np.zeros(shape=(k, N))
prevMean = mean

print("Initial")
printMatrices(mean,covariance,weight)

numberoftimes = 250
iterator = 0





while(True):

    print("Starting iteration: ", iteration)

    ##Step 2: E Step
    Pij = eStep(mean, covariance, weight, sampleList, k, N, d)
    ##print(Pij)


    ##Step 3: M Step
    mean, covariance, weight = mstep(mean, covariance, weight, sampleList, Pij, k, N, d)


    ##print("In the middle:")
    ##printMatrices(mean, covariance, weight)

    ##Step 4: LogLikeHood
    newLogLikelihood = caculateloglikelihood(mean, covariance, weight, sampleList, d)
    meanChange = meanRMS(mean,prevMean)

    print("Loglikelihood: ",newLogLikelihood)
    print("Change of mean: ",meanChange)


    if (np.abs(newLogLikelihood - prevLogLikelihood) < threshold or meanChange<threshold):
        break
    else:
        prevLogLikelihood = newLogLikelihood
        prevMean = mean

    print("Ending iteration: ", iteration)
    iteration+=1
    iterator+=1
    ##break;


print("Final")
printMatrices(mean,covariance,weight)
plotPoints(sampleList,datasetMean,datasetCovariance,mean,covariance)





