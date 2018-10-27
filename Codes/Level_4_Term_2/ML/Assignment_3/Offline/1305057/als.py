import numpy as np
import pandas as pd
import pickle




##Old Dataset Processing
def createMatrix(train,test):
    training_data = pd.read_excel(train, header=None)
    trainMatrix = training_data._values

    validation_data = pd.read_excel(test, header=None)
    testMatrix = validation_data._values

    print("Shape of train: ",trainMatrix.shape)
    print("Shape of validation: ",testMatrix.shape)

    return testMatrix,testMatrix



##Dataset processing code
def createDataset(fileName):
    file = open(fileName)
    lines = file.readlines()
    dataset = []

    for strings in lines:
        temp = strings.split(",")
        temp[2] = temp[2].replace("\n",'')
        if(temp[2]!='rating'):
            temp[2] = float(temp[2])
        dataset.append(temp)

    return dataset



def processDataset(dataset,numberOfTraining,numberOfTestValidation):

    reviewerReviewedCount = {}
    itemsInDataset = {}
    datasetSelectedOnUser = {}

    for i in range(1,len(dataset)):
        if dataset[i][1] not in reviewerReviewedCount.keys():
            reviewerReviewedCount[dataset[i][1]]=1
            datasetSelectedOnUser[dataset[i][1]]=dataset[i]
        else:
            reviewerReviewedCount[dataset[i][1]]=reviewerReviewedCount[dataset[i][1]]+1

        if dataset[i][0] not in itemsInDataset:
            itemsInDataset[dataset[i][0]]=1
        else:
            itemsInDataset[dataset[i][0]] += 1


    reviewersTakenForTraining = {}
    itemsInTrainingData = {}
    datasetForTraining = []

    for i in range(1,len(dataset)):
        if dataset[i][1] not in reviewersTakenForTraining.keys():
            reviewersTakenForTraining[dataset[i][1]]=True
            if dataset[i][0] not in itemsInTrainingData.keys():
                itemsInTrainingData[dataset[i][0]]=True
            datasetForTraining.append(dataset[i])
        else:
            if dataset[i][0] not in itemsInTrainingData.keys():
                itemsInTrainingData[dataset[i][0]]=True
            datasetForTraining.append(dataset[i])

        if(len(datasetForTraining)>=numberOfTraining):
            break;

    reviewersTakenForTestValidation = {}
    itemsInTestValidationData = {}
    datasetForTestValidation = []

    for i in range(1,len(dataset)):
        if (dataset[i][0] in itemsInTrainingData.keys() and dataset[i][1] not in reviewersTakenForTraining.keys()):
            if reviewerReviewedCount[dataset[i][1]]>1:
                reviewersTakenForTestValidation[dataset[i][1]] = True
                itemsInTestValidationData[dataset[i][0]] = True
                datasetForTestValidation.append(dataset[i])

        if(len(datasetForTestValidation)>numberOfTestValidation):
            break


    print("Size of training: ",len(datasetForTraining))
    print("Size of testing: ",len(datasetForTestValidation))
    print("Number of products in training: ",len(itemsInTrainingData))
    print("Number of products in testing: ",len(itemsInTestValidationData))




    for i in itemsInTestValidationData.keys():
        if i not in itemsInTrainingData.keys():
            print("There are some unique products!!")

    for i in reviewersTakenForTraining.keys():
        if i in reviewersTakenForTestValidation.keys():
            print("There are some common user!!")


    for i in reviewersTakenForTestValidation.keys():
        if reviewerReviewedCount[i]<=1:
            print("Cannot exist in test validation!!")

    return datasetForTraining,datasetForTestValidation


def createMatrix(train_set,test_set):
    itemIdMap = {}
    trainUserMap = {}

    itemIndexing = 0
    userIndexing = 0
    allIdToItem = {}
    for i in range(0,len(train_set)):
        if train_set[i][0] not in itemIdMap:
            itemIdMap[train_set[i][0]]=itemIndexing
            allIdToItem[itemIndexing] = train_set[i][0]
            itemIndexing+=1
        if train_set[i][1] not in trainUserMap:
            trainUserMap[train_set[i][1]]=userIndexing
            userIndexing+=1

    train_matrix = np.zeros(shape=(len(trainUserMap), len(itemIdMap)))
    train_matrix.fill(-1)
    for i in range(0,len(train_set)):
        train_matrix[trainUserMap[train_set[i][1]]][itemIdMap[train_set[i][0]]] = train_set[i][2]
    print('Train matrix: ',train_matrix.shape)


    testValidationUserIndexing = 0
    testUserMap = {}
    testIdToUser = {}
    for i in range(0,len(test_set)):
        if test_set[i][1] not in testUserMap.keys():
            testUserMap[test_set[i][1]] = testValidationUserIndexing
            testIdToUser[testValidationUserIndexing] = test_set[i][1]
            testValidationUserIndexing+=1


    test_matrix = np.zeros(shape=(len(testUserMap), len(itemIdMap)))
    test_matrix.fill(-1)
    for i in range(0,len(test_set)):
        test_matrix[testUserMap[test_set[i][1]]][itemIdMap[test_set[i][0]]] = test_set[i][2]



    print("Test matrix: ",test_matrix.shape)
    return train_matrix,test_matrix,testIdToUser,allIdToItem



def parseAndCreateDataset(fileName):
    file = open(fileName)
    lines = file.readlines()
    dataset = []

    for strings in lines:
        temp = strings.split(",")
        temp[2] = temp[2].replace("\n", '')
        if (temp[2] != 'rating'):
            temp[2] = float(temp[2])
        dataset.append(temp)

    reviewerReviewedCount = {}
    newDataset = []

    for i in range(1, len(dataset)):
        if dataset[i][1] not in reviewerReviewedCount.keys():
            reviewerReviewedCount[dataset[i][1]] = 1
        else:
            reviewerReviewedCount[dataset[i][1]] = reviewerReviewedCount[dataset[i][1]] + 1

    for i in range(1, len(dataset)):
        if (reviewerReviewedCount[dataset[i][1]] > 10):
            newDataset.append(dataset[i])

    ##for i in range(1,100):
       ## print(newDataset[i][1],reviewerReviewedCount[newDataset[i][1]])



    return newDataset


def createTrainTestSplit(dataset,numberOfTraining,numberOfTestValidation):
    uniqueUsers = {}
    usersDataLines ={}
    uniqueItems = {}
    reviewerReviewedCount = {}

    for i in range(0, len(dataset)):
        if dataset[i][1] not in uniqueUsers.keys():
            uniqueUsers[dataset[i][1]] = 1
            usersDataLines[dataset[i][1]]=[]
            usersDataLines[dataset[i][1]].append(dataset[i])
        else:
            usersDataLines[dataset[i][1]].append(dataset[i])

        if dataset[i][0] not in uniqueItems.keys():
            uniqueItems[dataset[i][0]] = 1

    for i in range(0, len(dataset)):
        if dataset[i][1] not in reviewerReviewedCount.keys():
            reviewerReviewedCount[dataset[i][1]] = 1
        else:
            reviewerReviewedCount[dataset[i][1]] = reviewerReviewedCount[dataset[i][1]] + 1

    ##for i in usersDataLines.keys():
        ##print(len(usersDataLines[i]))

    for i in range(0,len(dataset)):
        if(reviewerReviewedCount[dataset[i][1]]<10):
            print("The number of items review is too low!!")

    print("Number of unique users: ", len(uniqueUsers))
    print("Number of unique items: ", len(uniqueItems))

    reviewersTakenForTraining = {}
    itemsInTrainingData = {}
    datasetForTraining = []
    loopCount = 0

    for i in usersDataLines.keys():
        temp_list = usersDataLines[i]
        reviewersTakenForTraining[i]=True
        for x in temp_list:
            ##print(x[0])
            datasetForTraining.append(x)
            if x[0] not in itemsInTrainingData:
                itemsInTrainingData[x[0]]=True
        loopCount+=1
        if(loopCount>=numberOfTraining):
            break

    print(len(reviewersTakenForTraining),len(itemsInTrainingData),len(datasetForTraining))

    reviewersTakenForTestValidation = {}
    itemsInTestValidationData = {}
    datasetForTestValidation = []
    loopCount = 0


    for i in usersDataLines.keys():
        if i in reviewersTakenForTraining.keys():
            continue
        temp_list = usersDataLines[i]
        reviewersTakenForTestValidation[i]=True
        for x in temp_list:
            ##print(x[0])
            if x[0] in itemsInTrainingData.keys():
                datasetForTestValidation.append(x)
                itemsInTestValidationData[x[0]]=True
        loopCount+=1
        if(loopCount>=numberOfTestValidation):
            break

    print(len(reviewersTakenForTestValidation),len(itemsInTestValidationData),len(datasetForTestValidation))

    print("Size of training: ", len(datasetForTraining))
    print("Size of testing: ", len(datasetForTestValidation))
    print("Number of products in training: ", len(itemsInTrainingData))
    print("Number of products in testing: ", len(itemsInTestValidationData))

    return datasetForTraining, datasetForTestValidation



##New Dataset processing
def createNewMatrix(train,test):
    training_data = pd.read_excel(train, header=None)
    trainMatrix = training_data._values

    validation_data = pd.read_excel(test, header=None)
    testMatrix = validation_data._values

    print("Shape of train: ",trainMatrix.shape)
    print("Shape of validation: ",testMatrix.shape)

    return trainMatrix,testMatrix

##ALS algo code
def getUnXm(U,input,N,m):
    Un = []
    Xm = []
    for i in range(0,N):
        if(input[i][m]==-1):
            continue
        else:
            ##print("For",m,"got",i)
            Un.append(U[i])
            Xm.append(input[i][m])
    Un = np.array(Un)
    Xm = np.array([Xm])
    Xm = np.transpose(Xm)

    return Un,Xm

def getVmXn(V,input,M,n):
    Vm = []
    Xn = []
    for i in range(0, M):
        if (input[n][i] == -1):
            continue
        else:
            Vm.append(V[:,i])
            Xn.append(input[n][i])
    Vm = np.array(Vm)
    Vm = np. transpose(Vm)
    Xn = np.array([Xn])
    return Vm,Xn


def RMSerror(old,new):

    errorSum = 0
    count = 0
    for i in range(0,len(old[0])):
        if (old[0][i]!=-1):
            errorSum+= (old[0][i]-new[0][i])**2
            count+=1

    return errorSum,count



def alsAlgorithm(N,M,k,lamdaU,lamdaV,input,iteration):
    np.random.seed(1305057)
    U = np.random.uniform(0,5,(N,k))
    Vt = np.random.uniform(0,5,(k,M))
    inputShape = input.shape

    prevLoss = 0
    differenceToEndLoss = 1e-2

   ## print("U",U)
    ##print("Vt",Vt)

    for iter in range(0,iteration):
        ##print("V calculation:")
        tempHold = 0
        tempFirst = True
        for m in range(0, M):
            Un, Xm = getUnXm(U, input, N, m)
            Ik = np.identity(k)
            UnT = np.transpose(Un)
            VmT = np.matmul(UnT, Un) + lamdaV * Ik
            VmT = np.linalg.inv(VmT)
            ##print("m:",m)
            ##print("UnT: ",UnT)
            ##print("Xm: ",Xm)
            VmT = np.matmul(VmT, np.matmul(UnT, Xm))
            ##print(m,":",VmT)
            if (tempFirst):
                tempHold = VmT
                tempFirst = False
            else:
                tempHold = np.concatenate((tempHold, VmT), axis=1)
            ##print()
        Vt = tempHold
        ##print("Updated Vt: ",Vt)

        ##print("U calculation:")
        tempHold = 0
        tempFirst = True
        for n in range(0, N):
            VmT, Xn = getVmXn(Vt, input, M, n)
            Ik = np.identity(k)
            Vm = np.transpose(VmT)
            Un = np.matmul(VmT, Vm) + lamdaU * Ik
            Un = np.linalg.inv(Un)
            Un = np.matmul(np.matmul(Xn, Vm), Un)
            ##print(n,":",Un)
            if (tempFirst):
                tempHold = Un
                tempFirst = False
            else:
                tempHold = np.concatenate((tempHold, Un), axis=0)
            ##print()
        U = tempHold
        ##print("Updated U: ", U)

        sumSquare = 0
        numbersCounted = 0
        for n in range(0, N):
            for m in range(0, M):
                if (input[n][m] == -1):
                    continue
                else:
                    val1 = np.array([U[n]])
                    val2 = np.transpose(np.array(Vt[:, m]))
                    tempVal = np.matmul(val1, val2)
                    ##print(tempVal)
                    sumSquare += (input[n][m] - tempVal[0]) ** 2
                    numbersCounted+=1

        regularization1 = 0
        for n in range(0, N):
            row = U[n]
            regularization1 += np.sum(row ** 2)

        regularization2 = 0
        for m in range(0, M):
            column = Vt[:, m]
            regularization2 += np.sum(column ** 2)

        loss = sumSquare + regularization1 + regularization2

        ##print("Loss after iteration ",iter+1,": ",loss)
        ##print("Sum Square: ",sumSquare)

        if(loss-prevLoss)<differenceToEndLoss:
            break

    totalError = sumSquare/numbersCounted
    totalError = np.sqrt(totalError)


    print("Training error: ",totalError)


    return U,Vt,totalError


def validate(k,lamdaU,test_matrix,U,Vt):
    totalError = 0
    totalCount = 0

    for i in range(0,len(test_matrix)):
        temp_row = np.array([test_matrix[i]])
        VmT, Xn = getVmXn(Vt, temp_row, Vt.shape[1], 0 )
        Ik = np.identity(k)
        Vm = np.transpose(VmT)
        Un = np.matmul(VmT, Vm) + lamdaU * Ik
        ##print(lamdaU)
        Un = np.linalg.inv(Un)
        Un = np.matmul(np.matmul(Xn, Vm), Un)
        ##print("Un ",Un)
        ##print(Un.shape)
        new_row = np.matmul(Un, Vt)
        ##print("New row",new_row)
        ##print(new_row.shape)
        error,numberCounted = RMSerror(temp_row,new_row)
        totalError+=error
        totalCount+=numberCounted
        ##print(totalError)

    totalError = totalError/totalCount
    totalError = np.sqrt(totalError)
    return totalError

def test(k,lamdaU,test_matrix,U,Vt):
    totalTestError = 0

    for i in range(0, len(test_matrix)):
        temp_row = np.array([test_matrix[i]])
        VmT, Xn = getVmXn(Vt, temp_row, Vt.shape[1], 0)
        Ik = np.identity(k)
        Vm = np.transpose(VmT)
        Un = np.matmul(VmT, Vm) + lamdaU * Ik

        Un = np.linalg.inv(Un)
        Un = np.matmul(np.matmul(Xn, Vm), Un)
        new_row = np.matmul(Un, Vt)

        error = RMSerror(temp_row, new_row)
        totalTestError += error


    return totalTestError



def recommendationSystem(save,inputLimit,validationLimit):
    inputSet, validationSet = createNewMatrix("ratings_train.xlsx", "ratings_validate.xlsx")
    if(inputLimit!=-1):
        inputSet = inputSet[:inputLimit]
    if(validationLimit!=-1):
        validationSet = validationSet[:validationLimit]
    inputShape = inputSet.shape

    print("Final datasets:")
    print("Input: ",inputSet.shape)
    print("Validation: ",validationSet.shape)

    N = inputShape[0]
    M = inputShape[1]
    k = 20
    lamda = 0.01
    lamdaU = lamda
    lamdaV = lamda
    numberOfIterations = 100

    U, Vt,trainError = alsAlgorithm(N, M, k, lamdaU, lamdaV, inputSet, numberOfIterations)
    validationError = validate(k, lamdaU, validationSet, U, Vt)

    ##print("Before")
    ##print(U,Vt)

    if save:
        filepath = "UV/"+str(k)+"_"+str(lamda)
        U.dump(filepath+"U")
        Vt.dump(filepath+"Vt")



    ##tempU = np.load(filepath+"U")
    ##tempV = np.load(filepath+"Vt")

    ##print("After")
    ##print(tempU,tempV)

    print("Training Error: ",trainError)
    print("Validation Error: ",validationError)


def runTest(k,lamda,testSet):
    filepath = "UV/" + str(k) + "_" + str(lamda)


    U = np.load(filepath+"U")
    Vt = np.load(filepath+"Vt")

    testError = validate(k, lamda, testSet, U, Vt)

    print("Test Error: ",testError)



recommendationSystem(False,500,100)
##train,test = createNewMatrix("ratings_train.xlsx", "ratings_validate.xlsx")
##runTest(40,0.01,test)











