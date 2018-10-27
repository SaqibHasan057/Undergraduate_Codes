import numpy as np


n = 0
l = 0
w = []
sigmaSquare = 0
sigma = 0
train = 0
test = 0
N = 0


def readFile():
    configFile = open("config.txt")
    trainFile = open("train.txt")
    testFile = open("test.txt")

    global n
    global l
    global N
    global w
    global sigmaSquare
    global sigma
    global train
    global test

    lines = configFile.read().splitlines()
    formattedLines = []

    for x in lines:
        formattedLines.append(x.split(" "))

    n = int(formattedLines[0][0])
    N = 2 ** n
    l = int(formattedLines[0][1])

    for z in formattedLines[1]:
        w.append(float(z))
    w = np.array(w)
    sigmaSquare = float(formattedLines[2][0])
    sigma = np.sqrt(sigmaSquare)

    ##print(n,l,w,sigmaSquare)

    lines = trainFile.read().splitlines()
    train = str(lines[0])

    lines = testFile.read().splitlines()
    test = str(lines[0])

    ##print(train)
    ##print(test)

def printConfig():
    print("n,l:",n,l)
    print("w array:",w)
    print("Sigma square: ",sigmaSquare)
    print("Train:",train)
    print("Test:",test)
    print("\n")


def prior():
    priorArray = np.zeros(shape=(N))

    for i in range(0,len(train)-n+1):
        temp_str = train[i:i+n]
        index = int(temp_str,2)
        priorArray[index] += 1

    sum = np.sum(priorArray)
    ##print("Sum: ",sum)
    ##print("Before normalization: ",priorArray)
    priorArray = priorArray/sum
    ##print("After normalization: ",priorArray)

    return priorArray


def transition():
    transitionArray = np.zeros(shape=(N,N))

    for i in range(0,len(train)-n):
        given = int(train[i:i+n],2)
        followed = int(train[i+1:i+1+n],2)
        transitionArray[given][followed]+=1

    ##print("Before normalization: ")
    ##print(transitionArray)
    normalizeFactor = np.sum(transitionArray,axis=1)

    for i in range(0,len(normalizeFactor)):
        transitionArray[i]=transitionArray[i]/normalizeFactor[i]

    ##print("After normalization: ")
    ##print(transitionArray)
    return transitionArray

def observation():
    np.random.seed(3)
    valuesReceived = []
    for i in range(0,N):
        valuesReceived.append([])

    for i in range(0,len(train)-n+1):
        temp_str = train[i:i+n]
        temp_index = int(temp_str,2)

        x = 0
        for j in range(0,n):
            x+= int(temp_str[j])*w[j]

        x+= np.random.normal(loc=0,scale=sigma)

        valuesReceived[temp_index].append(x)

    observation = np.zeros(shape=(N,2))
    ##print("Values Received: ",valuesReceived)

    for i in range(0,len(valuesReceived)):
        observation[i][0] = np.mean(valuesReceived[i])
        observation[i][1] = np.std(valuesReceived[i])

    ##print(observation)

    return observation


def normalDensityFunction(x,mu,sigma):

    if(sigma==0):
        if(x==mu):
            return 1
        else:
            return 1e-30

    ##print("X,Mean,Sigma: ",x,mu,sigma)
    part1 = np.sqrt(2*np.pi)*sigma
    part1 = 1/part1

    part2 = -(x-mu)**2/(2*sigma**2)
    part2 = np.e**part2

    return part1*part2


def xKbits():
    xKString = []

    for i in range(0,len(test)-n+1):
        temp_str = test[i:i+n]
        temp_x = 0
        for j in range(0,n):
            temp_x+=int(temp_str[j])*w[j]

        temp_x += np.random.normal(loc=0,scale=sigma)
        xKString.append(temp_x)

    ##print(xKString)
    return xKString



def viterbi(prior,transition,observation,xKbits):

    trellisGraph = np.zeros(shape=(len(xKbits),N))
    linkGraph = np.zeros(shape=(len(xKbits),N))

   ## print("Initial trellis graph: ", trellisGraph)

    for i in range(0,N):
       ## print("Observations start: ",observation[i][0],observation[i][1])
        trellisGraph[0][i] = prior[i] * normalDensityFunction(xKbits[0],observation[i][0],observation[i][1])

   ## print("Trellis graph after first layer: ",trellisGraph)


    for i in range(1,len(xKbits)):
        for j in range(0,N):
            maxVal = -1e99
            maxValIndex = 0
            for x in range(0,N):
                if(transition[x][j]!=0):
                    val = trellisGraph[i-1][x]*transition[x][j] * normalDensityFunction(xKbits[i],observation[j][0],observation[j][1])

                    if(val>maxVal):
                        maxVal = val
                        maxValIndex = x

            trellisGraph[i][j] = maxVal
            linkGraph[i][j] = maxValIndex

    class_sequence = []

    maxProb = -1e99
    maxProbIndex = 0
    for i in range(0,N):
        if(trellisGraph[len(xKbits)-1][i]>maxProb):
            maxProb = trellisGraph[len(xKbits)-1][i]
            maxProbIndex = i

    class_sequence.append(maxProbIndex)
    print("Trellis Graph",trellisGraph)
    print("Link Graph",linkGraph)

    iterator = len(xKbits)-1
    holder = int(maxProbIndex)
    while iterator>0:
        class_sequence.append(linkGraph[iterator][holder])
        holder = int(linkGraph[iterator][holder])
        iterator-=1

    class_sequence = class_sequence[::-1]
    actual_sequence = []
    ##print("Class sequence: ",class_sequence)


    formatString = "{0:0"+str(n)+"b}"
    ##print("formatString: ",formatString)

    for i in range(0,len(class_sequence)):
        actual_sequence.append(formatString.format(int(class_sequence[i])))

    ##print("Actual sequence: ",actual_sequence)

    finalString = ""
    finalString+=actual_sequence[0]

    for i in range(1,len(actual_sequence)):
        finalString+=actual_sequence[i][n-1]

    print("Test string:",test)
    print("Final string:",finalString)
    return finalString


def printHMM(prior,transition,observation):
    print("Prior: ",prior)
    print("Transition: ",transition)
    print("Observation: ",observation)
    print("\n")


def accuracy(actual,calculated):
    count = 0
    for i in range(0,len(actual)):
        if(actual[i]==calculated[i]):
            count+=1

    accuracy = count/len(actual) * 100

    print("Accuracy: ",accuracy)

    return accuracy






readFile()
printConfig()
priorArr = prior()
transitionArr = transition()
observationArr = observation()
xK = xKbits()
##print("Xk: ",xK)
printHMM(priorArr,transitionArr,observationArr)
calculatedString = viterbi(priorArr,transitionArr,observationArr,xK)
acc = accuracy(test,calculatedString)




