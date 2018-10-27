from pickle import load
from numpy import array
from numpy import argmax
from keras.preprocessing.text import Tokenizer
from keras.preprocessing.sequence import pad_sequences
from keras.models import load_model
from nltk.translate.bleu_score import corpus_bleu
from Lib.attention import AttentionDecoder

import sys
import zipfile
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


# map an integer to a word
def word_for_id(integer, tokenizer):
    for word, index in tokenizer.word_index.items():
        if index == integer:
            return word
    return None


# generate target given source sequence
def predict_sequence(model, tokenizer, source):
    prediction = model.predict(source, verbose=0)[0]
    integers = [argmax(vector) for vector in prediction]
    target = list()
    for i in integers:
        word = word_for_id(i, tokenizer)
        if word is None:
            break
        target.append(word)
    return ' '.join(target)


# evaluate the skill of the model
def evaluate_model(model, tokenizer, sources, raw_dataset):
    actual, predicted = list(), list()
    for i, source in enumerate(sources):
        # translate encoded source text
        source = source.reshape((1, source.shape[0]))
        translation = predict_sequence(model, eng_tokenizer, source)
        raw_target, raw_src = raw_dataset[i]
        actual.append(raw_target.split())
        predicted.append(translation.split())
    # calculate BLEU score
    #print("I done!!")
    print('BLEU: %f' % corpus_bleu(actual, predicted, weights=(1.0, 0, 0, 0)))


# load datasets
dataset = load_clean_sentences('Tmp/english-bangla-both.pkl')
test,testFilePath = load_zip_sentences(str(sys.argv[1]))
# prepare english tokenizer
eng_tokenizer = create_tokenizer(dataset[:, 0])
eng_vocab_size = len(eng_tokenizer.word_index) + 1
eng_length = max_length(dataset[:, 0])
# prepare german tokenizer
ger_tokenizer = create_tokenizer(dataset[:, 1])
ger_vocab_size = len(ger_tokenizer.word_index) + 1
ger_length = max_length(dataset[:, 1])
# prepare data
testX = encode_sequences(ger_tokenizer, ger_length, test[:, 1])

# load model
model = load_model(str(sys.argv[2]), custom_objects={"AttentionDecoder": AttentionDecoder})
# test on some training sequences
print('test')
##print(test)
evaluate_model(model, eng_tokenizer, testX, test)
os.remove(testFilePath)