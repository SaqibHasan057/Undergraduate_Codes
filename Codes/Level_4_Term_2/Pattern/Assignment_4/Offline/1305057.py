import numpy as np
import cv2
import time
import sys



def exhaustiveSearch(ref_image,test_image):
    ref_size = ref_image.shape
    test_size = test_image.shape

    M = ref_size[0]
    N = ref_size[1]

    m = test_size[0]-M+1
    n = test_size[1]-N+1

    ##print(M,N,m,n)

    D = np.zeros((m,n),dtype='int64')

    for a in range(0,m):
        for b in range(0,n):

            ##print(a,b,"out of",m,n)

            temp_D = 0

            for i in range(a,a+M):
                for j in range(b,b+N):
                    temp_D+= (float(test_image[i][j])-float(ref_image[i-a][j-b]))**2

            D[a][b]=temp_D

    ##for i in range(0,len(D)):
        ##for j in range(0,len(D[i])):
            ##print(i,",",j,":",D[i][j])
    index = [0,0]
    min = 1e99

    for i in range(0,m):
        for j in range(0,n):
            if(D[i][j]<min):
                index[0]=i
                index[1]=j
                min=D[i][j]


    """
    cv2.rectangle(test_image,(index[1],index[0]),(index[1]+N,index[0]+M),0,2)
    cv2.imshow("Final!!",test_image)
    cv2.waitKey(0)
    """
    return index

def logarithmicSearchManual(ref_image,test_image,x,y,rectangleSize):
    ref_size = ref_image.shape
    test_size = test_image.shape

    M = ref_size[0]
    N = ref_size[1]

    m = test_size[0] - M + 1
    n = test_size[1] - N + 1

    center = [int(x),int(y)]
    print("Initial center:",center)
    p = rectangleSize

    d = 1e99

    while(d>1):

        print("First",p, center)

        x = center[0]
        y = center[1]


        k = np.ceil(np.log2(p))

        d = 2**(k-1)

        pointsList = [[x,y],[x-d,y],[x-d,y+d],[x,y+d],[x+d,y+d],[x+d,y],[x+d,y-d],[x,y-d],[x-d,y-d]]

        minimum = 1e99
        index = center
        print("Second",pointsList,d,d)
        print()

        for z in range(0,len(pointsList)):
            points = pointsList[z]
            a = int(points[0])
            b = int(points[1])
            print(points)

            if(a>=m or b>=n):
                print("This one is skipped: ",points)
                continue

            temp_D = 0

            for i in range(a, a + M):
                for j in range(b, b + N):
                    temp_D += (float(test_image[i][j]) - float(ref_image[i - a][j - b])) ** 2

            print(temp_D)

            if(temp_D<minimum):
                minimum = temp_D
                index = pointsList[z]


        center = index
        p = p / 2

    ##print("Answer: ",center)
    center[0]=int(center[0])
    center[1]=int(center[1])

    """
    cv2.rectangle(test_image, (center[1], center[0]), (center[1] + N, center[0] + M), 0, 2)
    cv2.imshow("Final!!", test_image)
    cv2.waitKey(0)
    """

    return center



def padImage(image,padX,padY):
    size = image.shape
    copy = image
    ret = np.zeros(shape=(size[0]+padX,size[1]+padY))
    ##print(size)
    ##print(padX,padY)
    ##print(ret.shape)

    for i in range(0,size[0]):
        createdArray = np.zeros(padY)
        x = np.append(copy[i],createdArray)
        ##print(x.shape)
        ret[i] = x


    for i in range(size[0],size[0]+padX):
        createdArray = np.zeros(size[1]+padY)
        ret[i]=createdArray


    return ret


def logarithmicSearchAutomatic(ref_image,test_image):
    ref_size = ref_image.shape
    test_size = test_image.shape

    M = ref_size[0]
    N = ref_size[1]

    m = test_size[0] - M + 1
    n = test_size[1] - N + 1

    center = [int(test_size[0]/2), int(test_size[1]/2)]
    print("Initial center:", center)
    p = (test_size[0] - center[0])/2
    q = (test_size[1] - center[1])/2

    d = 1e99
    e = 1e99

    while (d > 1 or e > 1):
        print("First", p,q, center)

        x = center[0]
        y = center[1]

        k = np.round(np.log2(p))
        l =np.round(np.log2(q))

        d = 2 ** (k - 1)
        e = 2 ** (l-1)

        pointsList = [[x, y], [x - d, y], [x - d, y + e], [x, y + e], [x + d, y + e], [x + d, y], [x + d, y - e],
                      [x, y - e], [x - d, y - e]]

        minimum = 1e99
        index = center
        print("Second", pointsList, d, e)
        print()

        for z in range(0, len(pointsList)):
            points = pointsList[z]
            a = int(points[0])
            b = int(points[1])
            print(points)

            ##if (a >= m or b >= n):
                ##print("This one is skipped: ", points)
                ##continue

            temp_D = 0
            temp_test_image = padImage(test_image,M,N)

            for i in range(a, a + M):
                for j in range(b, b + N):
                    temp_D += (float(temp_test_image[i][j]) - float(ref_image[i - a][j - b])) ** 2

            print(temp_D)

            if (temp_D < minimum):
                minimum = temp_D
                index = pointsList[z]

        center = index
        if(d!=1):
            p = p / 2
        if(e!=1):
            q = q / 2

    ##print("Answer: ",center)
    center[0] = int(center[0])
    center[1] = int(center[1])

    """
    cv2.rectangle(test_image, (center[1], center[0]), (center[1] + N, center[0] + M), 0, 2)
    cv2.imshow("Final!!", test_image)
    cv2.waitKey(0)
    """

    return center


def squareSearch(ref_image,test_image,x,y,rectangleSize):
    ref_size = ref_image.shape
    test_size = test_image.shape

    M = ref_size[0]
    N = ref_size[1]

    m = test_size[0] - M + 1
    n = test_size[1] - N + 1

    ##print(M,N,m,n)

    center = [int(x), int(y)]
    ##print("Initial center:", center)
    p = rectangleSize



    x = center[0]
    y = center[1]

    d = 1

    pointsList = [[x, y], [x - d, y], [x - d, y + d], [x, y + d], [x + d, y + d], [x + d, y], [x + d, y - d],
                      [x, y - d], [x - d, y - d]]

    minimum = 1e99
    index = None
    for z in range(0, len(pointsList)):
        points = pointsList[z]
        a = int(points[0])
        b = int(points[1])
        ##print(points)

        if (a >= m or b >= n):
            ##print("This one is skipped: ",points)
            continue

        temp_D = 0

        for i in range(a, a + M):
            for j in range(b, b + N):
                temp_D += (float(test_image[i][j]) - float(ref_image[i - a][j - b])) ** 2

        ##print("This is the D value:",temp_D)

        if (temp_D < minimum):
            ##print("Comparing",temp_D,minimum)
            minimum = temp_D
            index = pointsList[z]


    center=index
    ##print("Answer: ", center)
    center[0] = int(center[0])
    center[1] = int(center[1])

    """
    cv2.rectangle(test_image, (center[1], center[0]), (center[1] + N, center[0] + M), 0, 2)
    cv2.imshow("Final!!", test_image)
    cv2.waitKey(0)
    """

    return center





def hierarchichalSearch(ref_image,test_image,x,y,p,numberOfLevels):
    ref_size = ref_image.shape
    test_size = test_image.shape

    M = ref_size[0]
    N = ref_size[1]

    m = test_size[0] - M + 1
    n = test_size[1] - N + 1

    levels = []

    levels.append([ref_image,test_image])



    #Creating the levels
    for i in range(1,numberOfLevels+1):
        prevLevelSet = levels[i-1]
        newRef = cv2.GaussianBlur(prevLevelSet[0], (5, 5), 0)
        newRef = cv2.resize(newRef, (0, 0), fx=0.5, fy=0.5)
        newTest = cv2.GaussianBlur(prevLevelSet[1], (5, 5), 0)
        newTest = cv2.resize(newTest, (0, 0), fx=0.5, fy=0.5)
        levels.append([newRef,newTest])

    sizeOfLevelsArray = len(levels)

    ##Outer most search:
    xy = exhaustiveSearch(levels[sizeOfLevelsArray-1][0],levels[sizeOfLevelsArray-1][1])
    ##print(xy)


    i = sizeOfLevelsArray-2

    while(i>=0):
        xy = squareSearch(levels[i][0],levels[i][1],2*xy[0],2*xy[1],1)
        ##print(xy,i)
        i-=1

    """
    cv2.rectangle(test_image, (xy[1], xy[0]), (xy[1] + N, xy[0] + M), 0, 2)
    cv2.imshow("Final!!", test_image)
    cv2.waitKey(0)
    """

    return xy





ref_image = None
test_image = None

## Read the images
ref_image = cv2.imread("ref.jpg")
ref_image = cv2.cvtColor(ref_image, cv2.COLOR_BGR2GRAY)
##ref_image = ref_image/255
ref_size = ref_image.shape
print("Reference size: ",ref_size)


test_image = cv2.imread("test.png")
test_image = cv2.cvtColor(test_image, cv2.COLOR_BGR2GRAY)
##test_image = test_image/255
test_size = test_image.shape
print("Image size: ",test_size)


start = time.time()
results = exhaustiveSearch(ref_image,test_image)
end = time.time()
timeTaken = end-start
print(results)
print("Time for the exhaustive algorithm: ",timeTaken)


"""
start = time.time()
results = logarithmicSearchAutomatic(ref_image,test_image)
end = time.time()
timeTaken = end-start
print(results)
print("Time for the 2D Logarithm algorithm: ",timeTaken)
"""


"""
start = time.time()
results = hierarchichalSearch(ref_image,test_image,test_size[0]/2,test_size[1]/2,32,2)
end = time.time()
timeTaken = end-start
print(results)
print("Time for the Hierarchichal algorithm: ",timeTaken)
"""


### 233.3670153617859 seconds
### 0.3874058723449707 seconds
### 0.12480020523071289 seconds


cv2.rectangle(test_image, (results[1], results[0]), (results[1] + ref_size[1], results[0] + ref_size[0]), 0, 2)
cv2.imshow("Final!!", test_image)
cv2.waitKey(0)