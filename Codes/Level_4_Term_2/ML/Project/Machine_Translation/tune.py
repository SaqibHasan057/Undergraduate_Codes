nUnit = [64,128,256]
embedding_dimension = [20,30,50]
lr = [0.01,0.001,0.0001]
epoch = 10
batch_size = 32

bestValues = []
minimumLoss = 1e99

from train import *
import sys
from keras import backend as K
import tensorflow as tf

def writeHyperparameter(i,j,k):
    file = open("hyperparameter.txt","w")
    s = str(i)+" "+str(j)+" "+str(k)
    file.write(s)
    file.close()


tunerFile = open("tuning_results.txt","w")
for i in nUnit:
    for j in embedding_dimension:
        for k in lr:
            print(i,j,k)
            hist = tuningRun(i,j,k,epoch,batch_size,sys.argv[1],sys.argv[2])
            loss = hist.history['loss'][-1]
            acc = hist.history['acc'][-1]
            val_loss = hist.history['val_loss'][-1]
            val_acc = hist.history['val_acc'][-1]
            t = "Nunit: "+str(i)+" Embedding Dim: "+str(j)+" Learning Rate: "+str(k)+"\n"
            s = "loss: "+str(loss)+" acc: "+str(acc)+" val_loss: "+str(val_loss)+" val_acc: "+str(val_acc)+"\n"
            tunerFile.write(t)
            tunerFile.write(s)
            #print(loss,acc,val_loss,val_acc)
            if(val_loss<minimumLoss):
                bestValues=[i,j,k]
                minimumLoss=val_loss



tunerFile.close()



print("The best hyperparameter combination:")
print(bestValues)
writeHyperparameter(bestValues[0],bestValues[1],bestValues[2])