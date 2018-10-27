from pickle import load
from numpy import array
from keras.preprocessing.text import Tokenizer
from keras.preprocessing.sequence import pad_sequences
from keras.utils import to_categorical
from keras.utils.vis_utils import plot_model
from keras.models import Sequential
from keras.layers import LSTM
from keras.layers import Dense
from keras.layers import Embedding
from keras.layers import RepeatVector
from keras.layers import TimeDistributed
from keras.callbacks import ModelCheckpoint
import keras
from gensim.models import Word2Vec
import numpy as np
from keras import backend as K
import tensorflow as tf


from Lib.attention import AttentionDecoder
import zipfile
import sys
import os




# load a clean dataset
def load_clean_sentences(filename):
    return load(open(filename, 'rb'))

def load_zip_sentences(fileName):
    fileIn = fileName
    zip_ref = zipfile.ZipFile(fileIn, 'r')
    extractTo = fileIn.replace("data.zip","")
    zip_ref.extractall("")
    returnFile = extractTo+"data.pkl"
    print(returnFile)
    return load(open(returnFile, 'rb')),returnFile


# fit a tokenizer
def create_tokenizer(lines):
    tokenizer = Tokenizer()
    tokenizer.fit_on_texts(lines)
    return tokenizer


# max sentence length
def max_length(lines):
    return max(len(line.split()) for line in lines)


# encode and pad sequences
def encode_sequences(tokenizer, length, lines):
    # integer encode sequences
    X = tokenizer.texts_to_sequences(lines)
    # pad sequences with 0 values
    X = pad_sequences(X, maxlen=length, padding='post')
    return X


# one hot encode target sequence
def encode_output(sequences, vocab_size):
    ylist = list()
    for sequence in sequences:
        encoded = to_categorical(sequence, num_classes=vocab_size)
        ylist.append(encoded)
    y = array(ylist)
    y = y.reshape(sequences.shape[0], sequences.shape[1], vocab_size)
    return y


# define NMT model
def define_model(src_vocab, tar_vocab, src_timesteps, tar_timesteps, n_units,layer):
    model = Sequential()
    model.add(layer)
    ##model.add(Embedding(src_vocab, n_units, input_length=src_timesteps, mask_zero=True))
    model.add(LSTM(n_units))
    model.add(RepeatVector(tar_timesteps))
    #model.add(LSTM(n_units, return_sequences=True))
    #model.add(TimeDistributed(Dense(tar_vocab, activation='softmax')))
    model.add(AttentionDecoder(n_units, tar_vocab))
    return model


def getEmbeddingLayerForWord2Vec(sentences,tokenizer,EMBEDDING_DIM,MAX_SEQUENCE_LENGTH):
    parsed_sentences = []
    for i in range(0,len(sentences)):
        line = sentences[i].split()
        parsed_sentences.append(line)
    ##print(parsed_sentences)
    word2VecModel = Word2Vec(parsed_sentences,size=EMBEDDING_DIM, min_count=1)
    ##print(list(word2VecModel.wv.index2word))
    ##print("Tokenizer:",tokenizer.word_index)
    ##print(tokenizer.word_index['ua'])

    embedding_matrix = np.zeros((len(tokenizer.word_index) + 1, EMBEDDING_DIM))

    for i in tokenizer.word_index.keys():
        index = i.upper()
        ##print(index)
        getArray = word2VecModel[index]
        embedding_matrix[tokenizer.word_index[i]] = getArray

    embedding_layer = Embedding(len(tokenizer.word_index) + 1,EMBEDDING_DIM,weights=[embedding_matrix],input_length=MAX_SEQUENCE_LENGTH,trainable=False)
    return embedding_layer

def tuningRun(i,j,k,ep,bs,trainFile,validateFile):
    # load datasets
    print("Calling tuning function:")
    dataset = load_clean_sentences('Tmp/english-bangla-both.pkl')
    train,trainFilePath = load_zip_sentences(trainFile)
    validate,validateFilePath = load_zip_sentences(validateFile)

    # prepare english tokenizer
    eng_tokenizer = create_tokenizer(dataset[:, 0])
    eng_vocab_size = len(eng_tokenizer.word_index) + 1
    eng_length = max_length(dataset[:, 0])
    print('English Vocabulary Size: %d' % eng_vocab_size)
    print('English Max Length: %d' % (eng_length))
    # prepare german tokenizer
    ger_tokenizer = create_tokenizer(dataset[:, 1])
    ger_vocab_size = len(ger_tokenizer.word_index) + 1
    ger_length = max_length(dataset[:, 1])
    print('Bangla Vocabulary Size: %d' % ger_vocab_size)
    print('Bangla Max Length: %d' % (ger_length))

    # prepare training data
    trainX = encode_sequences(ger_tokenizer, ger_length, train[:, 1])
    trainY = encode_sequences(eng_tokenizer, eng_length, train[:, 0])
    trainY = encode_output(trainY, eng_vocab_size)
    # prepare validation data
    validateX = encode_sequences(ger_tokenizer, ger_length, validate[:, 1])
    validateY = encode_sequences(eng_tokenizer, eng_length, validate[:, 0])
    validateY = encode_output(validateY, eng_vocab_size)
    print("Calling!!")
    unit = i
    EMBEDDING_DIM = j
    embeddingLayer = getEmbeddingLayerForWord2Vec(dataset[:, 1],ger_tokenizer,EMBEDDING_DIM,ger_length)

    # define model
    model = define_model(ger_vocab_size, eng_vocab_size, ger_length, eng_length, unit,embeddingLayer)
    opt = keras.optimizers.adam(lr=k)
    model.compile(optimizer='adam', loss='categorical_crossentropy',metrics=['acc'])
    # summarize defined model
    #print(model.summary())
    # fit model
    ##filename = 'model.h5'
    hist = model.fit(trainX, trainY, epochs=ep, batch_size=bs, validation_data=(validateX, validateY), verbose=1)
    ##model.save(filename)

    os.remove(trainFilePath)
    os.remove(validateFilePath)

    return hist

def readHyperparameters(filename):
    f = open(filename,"r")
    h = f.read().splitlines()
    h = h[0]
    h = h.split()
    s=[]
    s.append(h[0])
    s.append(h[1])
    s.append(h[2])
    return s

def mainRun(ep,bs,trainFile,hyperparameterFile):
    # load datasets
    print("Main Training")
    dataset = load_clean_sentences('Tmp/english-bangla-both.pkl')
    train,trainFilePath = load_zip_sentences(trainFile)

    # prepare english tokenizer
    eng_tokenizer = create_tokenizer(dataset[:, 0])
    eng_vocab_size = len(eng_tokenizer.word_index) + 1
    eng_length = max_length(dataset[:, 0])
    print('English Vocabulary Size: %d' % eng_vocab_size)
    print('English Max Length: %d' % (eng_length))
    # prepare german tokenizer
    ger_tokenizer = create_tokenizer(dataset[:, 1])
    ger_vocab_size = len(ger_tokenizer.word_index) + 1
    ger_length = max_length(dataset[:, 1])
    print('Bangla Vocabulary Size: %d' % ger_vocab_size)
    print('Bangla Max Length: %d' % (ger_length))

    # prepare training data
    trainX = encode_sequences(ger_tokenizer, ger_length, train[:, 1])
    trainY = encode_sequences(eng_tokenizer, eng_length, train[:, 0])
    trainY = encode_output(trainY, eng_vocab_size)

    param = readHyperparameters(hyperparameterFile)

    unit = int(param[0])
    EMBEDDING_DIM = int(param[1])
    embeddingLayer = getEmbeddingLayerForWord2Vec(dataset[:, 1], ger_tokenizer, EMBEDDING_DIM, ger_length)

    # define model
    model = define_model(ger_vocab_size, eng_vocab_size, ger_length, eng_length, unit, embeddingLayer)
    opt = keras.optimizers.adam(lr=float(param[2]))
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['acc'])
    # summarize defined model
    print(model.summary())
    # fit model
    filename = 'model.h5'
    model.fit(trainX, trainY, epochs=ep, batch_size=bs, verbose=1)
    model.save(filename)

    os.remove(trainFilePath)





"""
# load datasets
dataset = load_clean_sentences('english-bangla-both.pkl')
train = load_clean_sentences('english-bangla-train.pkl')
validate = load_clean_sentences('english-bangla-validate.pkl')
test = load_clean_sentences('english-bangla-test.pkl')

# prepare english tokenizer
eng_tokenizer = create_tokenizer(dataset[:, 0])
eng_vocab_size = len(eng_tokenizer.word_index) + 1
eng_length = max_length(dataset[:, 0])
print('English Vocabulary Size: %d' % eng_vocab_size)
print('English Max Length: %d' % (eng_length))
# prepare german tokenizer
ger_tokenizer = create_tokenizer(dataset[:, 1])
ger_vocab_size = len(ger_tokenizer.word_index) + 1
ger_length = max_length(dataset[:, 1])
print('Bangla Vocabulary Size: %d' % ger_vocab_size)
print('Bangla Max Length: %d' % (ger_length))

# prepare training data
trainX = encode_sequences(ger_tokenizer, ger_length, train[:, 1])
trainY = encode_sequences(eng_tokenizer, eng_length, train[:, 0])
trainY = encode_output(trainY, eng_vocab_size)
#prepare validation data
validateX = encode_sequences(ger_tokenizer, ger_length, validate[:, 1])
validateY = encode_sequences(eng_tokenizer, eng_length, validate[:, 0])
validateY = encode_output(validateY, eng_vocab_size)
# prepare test data
testX = encode_sequences(ger_tokenizer, ger_length, test[:, 1])
testY = encode_sequences(eng_tokenizer, eng_length, test[:, 0])
testY = encode_output(testY, eng_vocab_size)
print("Calling!!")


unit = 128
EMBEDDING_DIM = 300
embeddingLayer = getEmbeddingLayerForWord2Vec(dataset[:, 1],ger_tokenizer,EMBEDDING_DIM,ger_length)

# define model
model = define_model(ger_vocab_size, eng_vocab_size, ger_length, eng_length, unit,embeddingLayer)
opt = keras.optimizers.adam(lr=0.001)
model.compile(optimizer='adam', loss='categorical_crossentropy',metrics=['acc'])
# summarize defined model
print(model.summary())
# fit model
filename = 'model.h5'
model.fit(trainX, trainY, epochs=15, batch_size=32, validation_data=(validateX, validateY), verbose=1)
model.save(filename)
"""


if __name__ == "__main__":
    epoch = 10
    batch_size = 32
    mainRun(epoch,batch_size,sys.argv[1],sys.argv[2])