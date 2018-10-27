import math
from matplotlib import pyplot as plt
import numpy as np
import csv
import re
import _pickle as cPickle
from random import *

fileName = 'bank-additional-full.csv'
dataset = None
attributesCountDictionary = None
attributesCountList = None
attributesType = None
attributesRow = None
attributesName = None

answerColumn = 20



class decisionStump:

    ##Constructor Function
    def __init__(self):
        self.dictAnswer = {}
        self.listAnswer = []
        self.attributeSelected = None
        self.entropyFull = None
        self.answerDict = None
        self.plurality = None

    ##This function counts the number of positive and negative value in the list
    def countPosNeg(self,list):
        countPos=0
        countNeg=0
        for i in list:
            if(i=='no'):
                countNeg+=1
            else:
                countPos+=1

        return countPos,countNeg

    #This function returns the probabilities based on a list of values
    def retProb(self,list):
        pos,neg = self.countPosNeg(list)
        posProb = pos/(pos+neg)
        negProb = neg/(pos+neg)
        return posProb,negProb

    #This function calculates the entropy based on the given probability
    def formulaOfEntropy(self,probability):
        if (probability<=0):
            return 0
        else:
            return -probability * math.log(probability,2)

    ##This calculates the total entropy of an attribute based on the list of values given
    def caculateEntropy(self,list):
        pos,neg = self.retProb(list)
        return self.formulaOfEntropy(pos) + self.formulaOfEntropy(neg)

    ##This calculates the total average entropy based on the attributes
    def entropy(self,possibleAttributes,attributesRow,answersRow):
        tempDict = {}
        for i in possibleAttributes:
            tempDict[i]=[]

        for i in range(0,len(attributesRow)):
            tempDict[attributesRow[i]].append(answersRow[i])

        entropy = 0
        total = len(attributesRow)

        for i in tempDict.keys():
            tempVal = self.caculateEntropy(tempDict[i])
            tempVal = len(tempDict[i])/total * tempVal
            entropy+=tempVal

        return entropy

    ##This calculates the total entropy of the attribute
    def fullEntropy(self,answersRow):
        self.entropyFull= self.caculateEntropy(answersRow)

    #This calculates the information gain of the attribute
    def informationGain(self,possibleAttributes,attributesRow,answersRow):
        entropyForAttribute = self.entropy(possibleAttributes,attributesRow,answersRow)
        return self.entropyFull - entropyForAttribute


    #This function returns the list of positive and negative of the list for the given attribute
    def getposNegListforAttribute(self,attribute,index,attributesList):
        posNegList = []

        for i in range (0,len(attributesList[index])):
            if(attributesList[index][i]==attribute):
                posNegList.append(attributesList[answerColumn][i])

        return posNegList

    #This creates the stump from the dataset
    def createStumpFromDataset(self,dataset):
        attribCountDictionary, attribCountList, attribType, attribRow, attribsName = numberofTypes(
            dataset)
        self.createStump(attribType,attribRow,attribsName)

    #This calculates the plurality
    def setPlurality(self,list):
        yes = 0
        no = 0

        for i in range(0,len(list)):
            if(list[i]=='yes'):
                yes+=1
            else:
                no+=1

        if(yes>no):
            self.plurality='yes'
        else:
            self.plurality='no'

    #This function creates the stump from the processed attribute transpose matrix
    def createStump(self,attributesType,attributesRow,attributesName):
        infoGain = []
        ##print(attributesRow[answerColumn])
        self.fullEntropy(attributesRow[answerColumn])
        self.setPlurality(attributesRow[answerColumn])

        for i in range(0,len(attributesRow)-1):
            infoGain.append(self.informationGain(attributesType[i],attributesRow[i],attributesRow[answerColumn]))

        index = 0
        max = float('-inf')

        for i in range(0,len(infoGain)):
            if(infoGain[i]>max):
                max = infoGain[i]
                index = i

        ##print(index)
        print(attributesName[index])

        tempDict = {}

        ##print("test ",attributesType[index])

        for x in attributesType[index]:
            ##print(x)
            posNegListforAttribute = self.getposNegListforAttribute(x,index,attributesRow)
            ##print(posNegListforAttribute)
            pos,neg = self.countPosNeg(posNegListforAttribute)
            ##print(pos," ",neg)
            if(pos>neg):
                tempDict[x]="yes"
            elif(pos<neg):
                tempDict[x]="no"
            else:
                tempDict[x]=self.plurality

        ##for i in tempDict.keys():
            ##print(i," : ",tempDict[i])

        self.answerDict = tempDict
        self.attributeSelected = index

    #This function tests the decision stump on a row of dataset
    def testOnStump(self,list):
        if list[self.attributeSelected] not in self.answerDict.keys():
            return self.plurality
        return self.answerDict[list[self.attributeSelected]]

    #This function tests on the whole dataset and returns the accuracy
    def testDataSetOnStump(self,dataset):
        correct = 0
        for i in range(1,len(dataset)):
            y_actual = dataset[i][answerColumn]
            y_predicted =self.testOnStump(dataset[i])

            if(y_actual==y_predicted):
                correct+=1

        return correct/len(dataset) * 100



















##This function modifies the dataset into rows of each attribute and then returns a dictionary,list of attributes in row form, the number of types in each attribute and their names
def numberofTypes(dataset):
    typesDict = {}
    typeList = []
    types=[]
    listOfType = []
    attributesName = []


    for i in range(0,len(dataset[0])):
        countList = []
        attributesName.append(dataset[0][i])
        typesDict[dataset[0][i]] = 0
        typeList.append(0)
        listOfType.append([])
        for j in range(1,len(dataset)):
            listOfType[i].append(dataset[j][i])
            if dataset[j][i] not in countList:
                countList.append(dataset[j][i])
                typesDict[dataset[0][i]] = typesDict[dataset[0][i]] + 1
                typeList[i] = typeList[i] + 1
        list.sort(countList)
        types.append(countList)

    return typesDict,typeList,types,listOfType,attributesName

#This function counts the number of yes and no in the dataset
def countYesNo(dataset):
    yes = 0
    no = 0

    for i in range(1,len(dataset)):
        if(dataset[i][answerColumn]=='yes'):
            yes+=1
        else:
            no+=1

    return yes,no

#This function updates the dataset with equal number of yes and no
def updateDataset(dataset):
    list_of_rows_of_yes = []
    list_of_rows_of_no = []
    final_list = []


    for i in range(1,len(dataset)):
        if(dataset[i][answerColumn]=='yes'):
            list_of_rows_of_yes.append(dataset[i])
        else:
            list_of_rows_of_no.append(dataset[i])

    list_of_selected_no = []
    list_of_selected_no_indices = []

    k=0
    seed(1305057)
    while k < len(list_of_rows_of_yes):
        index = randint(0,len(list_of_rows_of_no)-1)

        if index not in list_of_selected_no_indices:
            list_of_selected_no.append(list_of_rows_of_no[index])
            list_of_selected_no_indices.append(index)
            k+=1
        else:
            continue

    for i in range(0,len(list_of_rows_of_yes)):
        final_list.append(list_of_rows_of_yes[i])

    for i in range(0,len(list_of_selected_no)):
        final_list.append(list_of_selected_no[i])

    shuffle(final_list)
    final_list.insert(0,dataset[0])

    return final_list


#This function turns the columns into rows of dictionary values in a dictionary
def createAttributeDict(dataset):
    dict = {}

    for i in range(0,len(dataset[0])):
        atrributeName = dataset[0][i]
        dict[atrributeName]=[]
        for j in range(1,len(dataset)):
            dict[atrributeName].append(dataset[j][i])

    return dict

#This function reads and converts the csv file into a list of list format
def readCSVFile(file):
    with open(file) as csvfile:
        readCSV = csv.reader(csvfile,delimiter=',')
        csvRet = []

        for row in readCSV:
            ##print(row)
            csvRow = row[0].split(';')
            ##print(csvRow)

            for i in range(0,len(csvRow)):
                csvRow[i] = re.sub('[\'\"]', '', csvRow[i])

            csvRet.append(csvRow)
        return csvRet


#This function converts a column, which is int or float, from string to int
def convertColumnToInt(column,dataset):
    for i in range(1,len(dataset)):
        dataset[i][column] = float(dataset[i][column])
        dataset[i][column] = int(dataset[i][column])


#This function  is used to convert each of the columns with continuous values into a discrete set of values
def discretizeColumn(column,dataset,numberOfBins):
    min = float('inf')
    max = float('-inf')

    convertColumnToInt(column,dataset)

    for i in range(1,len(dataset)):
        if(dataset[i][column]>=max):
            max=dataset[i][column]
        if(dataset[i][column]<=min):
            min=dataset[i][column]

    diff = max-min
    binSize = diff/numberOfBins

    for i in range(1,len(dataset)):
        binNumber = (dataset[i][column]-min)/binSize
        binNumber = int(binNumber)
        dataset[i][column]=binNumber

#This function calls the discretizeColumn() function on each of the int/float columns in the dataset
def discretize(x,dataset,numberOfBins):
    for i in x:
        discretizeColumn(i,dataset,numberOfBins)




#This function is used to save dataset to a file
def saveInPickle(dataset,fileName):
    cPickle.dump(dataset, open(fileName, 'wb'))

#This function is used to retrieve dataset from a file
def loadFromPickle(file):
    return cPickle.load(open(file, 'rb'))

#This function calculates the cumulative weight needed for sampling
def calculateCumulativeWeights(weights):
    cumulative_weights = []
    cumulative_weights.append(-1)
    cumulative_weights.append(weights[1])

    for i in range(2,len(weights)):
        cumulative_weights.append(weights[i]+cumulative_weights[i-1])

    return cumulative_weights

#This function is used to calculate the index from the cumulative weight array
def getIndexFromCumulativeWeight(value,cumulative_weights):
    for i in range(1,len(cumulative_weights)):
        if(value<=cumulative_weights[i]):
            return i


#This function is used for sampling in the adaboost function
def sampledList(dataset,cumulative_weights,number_of_samples):
    list_of_samples = []
    list_of_sample_numbers = []

    list_of_samples.append(dataset[0])
    x=0

    seed(1305057)
    for i in range(0,number_of_samples):
        value = random()
        index = getIndexFromCumulativeWeight(value,cumulative_weights)
        list_of_samples.append(dataset[index])
        list_of_sample_numbers.append(index)

    return list_of_samples,list_of_sample_numbers

#This function is used for initializing the weight vector in adaboost
def initializeWeights(size):
    tempValue = 1/size
    weights=[]

    weights.append(-699)

    for i in range(0,size):
        weights.append(tempValue)

    return weights

#This function is used to normalize the weight vector in adaboost
def normalizeWeightList(weights):
    sum = 0;

    for i in range(1,len(weights)):
        sum+=weights[i]

    for i in range(1,len(weights)):
        weights[i]=weights[i]/sum

#This function is used to test the ensemble learning algorithm
def testAdaboost(hypotheses,hypotheses_weights,testRow):
    yes = 0
    no = 0

    for i in range(0,len(hypotheses)):
        tempVal = hypotheses[i].testOnStump(testRow)
        if(tempVal=='yes'):
            yes+=hypotheses_weights[i]
        else:
            no+=hypotheses_weights[i]

    if(yes>no):
        return 'yes'
    else:
        return 'no'

#This function is used to calculate the fscore
def calculatingFScore(hypotheses,hypotheses_weights,dataset):
    correct = 0
    truePositive = 0
    trueNegative = 0
    falsePositive = 0
    falseNegative = 0

    for i in range(1,len(dataset)):
        y_predicted = testAdaboost(hypotheses,hypotheses_weights,dataset[i])
        y_actual = dataset[i][answerColumn]

        if(y_actual == 'yes' and y_predicted == 'yes'):
            truePositive+=1
            correct+=1
        elif(y_actual == 'no' and y_predicted == 'yes'):
            falsePositive+=1
        elif(y_actual == 'no' and y_predicted == 'no'):
            trueNegative+=1
            correct+=1
        else:
            falseNegative+=1

    print("True Postive: ",truePositive," ","True Negative: ",trueNegative," ","False Positive: ",falsePositive," ","False Negative: ",falseNegative)
    precision=0
    recall=0
    if(truePositive==0 and falsePositive==0):
        precision=0
    else:
        precision = (truePositive)/(truePositive+falsePositive)

    if (truePositive == 0 and falseNegative == 0):
        recall=0
    else:
        recall = (truePositive)/(truePositive+falseNegative)
    print("Precision: ",precision," ","Recall: ",recall)

    f1_score = 0

    if(precision==0 or recall==0):
        f1_score=-699
    else:
        f1_score = 2/(1/precision+1/recall)
    acc = correct/(len(dataset)-1)

    return f1_score,acc






#This is the main ensemble learning algorithm
def adaboost(dataset,numberOfHypotheses,numberOfSamples):
    weights=[]
    cumulative_weights=[]
    hypotheses = []
    hypotheses_weights = []

    weights = initializeWeights(len(dataset)-1)

    k=0

    while k<numberOfHypotheses:
        print("Hypothesis Number: ",k+1)
        cumulative_weights = calculateCumulativeWeights(weights)
        sampleList,sampleListIndices = sampledList(dataset,cumulative_weights,numberOfSamples)
        newDecisionStump = decisionStump()
        newDecisionStump.createStumpFromDataset(sampleList)
        ##print("Attribute: ",newDecisionStump.attributeSelected)

        hypotheses.append(newDecisionStump)
        error = 0

        for j in range(1,len(dataset)):
            tempVal = hypotheses[k].testOnStump(dataset[j])
            if(tempVal != dataset[j][answerColumn]):
                error = error + weights[j]

        print("Error from addition of weights: ",error)

        if(error>=0.5):
            hypotheses.pop()
            continue

        for j in range(1,len(dataset)):
            tempVal = hypotheses[k].testOnStump(dataset[j])
            if(tempVal == dataset[j][answerColumn]):
                weights[j] = weights[j] * error/(1-error)

        normalizeWeightList(weights)
        hypotheses_weights.append(math.log((1-error)/error,2))
        k+=1

    return hypotheses,hypotheses_weights

#This function is used to create a copy of the dataset
def createDatasetCopy(dataset):
    copyDataset=[]
    for i in range(0,len(dataset)):
        copyDataset.append(dataset[i])
    return copyDataset

#This function is used to join the data blocks in k-fold validation for training
def makeTrainSet(blocks,testBlockIndex,topRow):
    trainSet = []
    trainSet.append(topRow)

    for i in range(0,len(blocks)):
        if(i==testBlockIndex):
            continue
        else:
            for j in range(0,len(blocks[i])):
                trainSet.append(blocks[i][j])

    return trainSet


#This calls the ensemble learner for the k-folc cross validation
def k_fold_cross_validation(dataset,folds,adaboostK):
    copyDataset = createDatasetCopy(dataset)

    topRow = copyDataset[0]

    copyDataset.pop(0)

    sizeOfBlock = int(len(copyDataset)/folds)

    blocks = [copyDataset[x:x + sizeOfBlock] for x in range(0, len(copyDataset), sizeOfBlock)]

    print("Number of Blocks: ",len(blocks))
    print("Length of each block: ",len(blocks[0]))

    sumF1Score = 0
    sumAcc = 0
    count = 0



    for i in range(0,len(blocks)):
        testSet = []
        trainSet = []

        testSet.append(topRow)
        testSet = blocks[i]

        trainSet = makeTrainSet(blocks,i,topRow)
        print(len(trainSet))

        hypotheses,hypotheses_weights = adaboost(trainSet,adaboostK,len(trainSet)-1)
        f1Score,acc = calculatingFScore(hypotheses,hypotheses_weights,testSet)

        if(f1Score==-699):
            continue;
        sumF1Score+=f1Score
        sumAcc+=acc
        count+=1

    avgF1Score = sumF1Score/count
    avgAcc = sumAcc/count

    print("F1 Score: ",avgF1Score)
    print("Accuracy: ",avgAcc)






"""
dataset = readCSVFile("bank-additional-full.csv")
dataset = updateDataset(dataset)
##saveInPickle(dataset,"savedData.p")

"""





##Load dataset and convert the continuous data columns







dataset = loadFromPickle("savedData.p")
print(len(dataset))
print(dataset[0])

columnsToCover = [0,10,11,12,13,15,16,17,18,19]
discretize(columnsToCover,dataset,2)

k_fold = 5
k_in_adaboost = 10

k_fold_cross_validation(dataset,k_fold,k_in_adaboost)













