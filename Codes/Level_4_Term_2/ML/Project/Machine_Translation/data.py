import string
import re
from pickle import dump
from unicodedata import normalize
from numpy import array
import sys
import zipfile
import os


##open zip file

def unzip():
    import zipfile
    fileName = str(sys.argv[1])
    print(fileName)
    zip_ref = zipfile.ZipFile(fileName, 'r')
    zip_ref.extractall("")
    zip_ref.close()


# load doc into memory
def load_doc(filename):
    # open the file as read only
    file = open(filename, mode='rt', encoding='utf-8')
    # read all text
    text = file.read()
    # close the file
    file.close()
    return text


# split a loaded document into sentences
def to_pairs(doc):
    lines = doc.strip().split('\n')
    pairs = [line.split('\t') for line in lines]
    return pairs


def testBanglaNumber(word):
    l = ['১','২','৩','৪','৫','৬','৭','৮','৯','০']
    for i in l:
        if i in word:
            return True

    return False

# clean a list of lines
def clean_pairs(lines):
    cleaned = list()
    # prepare regex for char filtering
    re_print = re.compile('[^%s]' % re.escape(string.printable))
    # prepare translation table for removing punctuation
    table = str.maketrans('', '', string.punctuation+"।")
    for pair in lines:
        clean_pair = list()
        engLine = pair[0]
        bengLine = pair[1]

        ##Clean English
        # tokenize on white space
        engLine = engLine.split()
        # convert to lowercase
        engLine = [word.lower() for word in engLine]
        # remove punctuation from each token
        engLine = [word.translate(table) for word in engLine]
        # remove non-printable chars form each token
        engLine = [re_print.sub('', w) for w in engLine]
        # remove tokens with numbers in them
        engLine = [word for word in engLine if word.isalpha()]
        ##print("English line: ", engLine)
        # store as string
        clean_pair.append(' '.join(engLine))


        ##Clean Bangla
        ##print("first ", bengLine)
        # tokenize on white space
        bengLine = bengLine.split()
        ##print("second ", bengLine)
        # remove punctuation from each token
        bengLine = [word.translate(table) for word in bengLine]
        ##print("third ", bengLine)
        # remove tokens with numbers in them
        bengLine = [word for word in bengLine if not testBanglaNumber(word)]
        ##print("Bengali line: ", bengLine)
        # store as string
        clean_pair.append(' '.join(bengLine))

        cleaned.append(clean_pair)
    return array(cleaned)


# save a list of clean sentences to file
def save_clean_data(sentences, filename):
    dump(sentences, open(filename, 'wb'))
    print('Saved: %s' % filename)


# load dataset
unzip()
filename = 'ben.txt'
doc = load_doc(filename)
# split into english-german pairs
pairs = to_pairs(doc)
# print(pairs)
# clean sentences
clean_pairs = clean_pairs(pairs)
# print(clean_pairs)
# save clean pairs to file
save_clean_data(clean_pairs, 'Tmp/english-bangla.pkl')
# spot check
os.remove(filename)
os.remove("_about.txt")



from pickle import load
from pickle import dump
from numpy.random import rand
from numpy.random import shuffle

# load a clean dataset
def load_clean_sentences(filename):
	return load(open(filename, 'rb'))

# save a list of clean sentences to file
def save_clean_data(sentences, filename):
    dump(sentences, open(filename, 'wb'))
    print('Saved: %s' % filename)

def save_zip_data(sentences, filename,zipFileName):
    dump(sentences, open(filename, 'wb'))
    zipModule = zipfile.ZipFile(zipFileName, 'w')
    zipModule.write(filename, compress_type=zipfile.ZIP_DEFLATED)
    zipModule.close()
    os.remove(filename)
    print('Saved: %s' % filename)

# load dataset
raw_dataset = load_clean_sentences('Tmp/english-bangla.pkl')

# reduce dataset size
n_sentences = 4379
dataset = raw_dataset[:n_sentences, :]
# split into train/test
train,validation,test = dataset[:3520], dataset[3520:3960],dataset[3960:]
under10Minute,under90Minute = train[:100],train[:400]
a3SampleValidation = validation[:3]
# save
save_clean_data(dataset, 'Tmp/english-bangla-both.pkl')
save_zip_data(train, 'Data/Train/Best_hyperparameter_80_percent/data.pkl','Data/Train/Best_hyperparameter_80_percent/data.zip')
save_zip_data(validation, 'Data/Validation/Validation_10_percent/data.pkl','Data/Validation/Validation_10_percent/data.zip')
save_zip_data(test, 'Data/Test/Test_10_percent/data.pkl','Data/Test/Test_10_percent/data.zip')
save_zip_data(under10Minute, 'Data/Train/Under_10_min_training/data.pkl','Data/Train/Under_10_min_training/data.zip')
save_zip_data(under90Minute, 'Data/Train/Under_90_min_tuning/data.pkl','Data/Train/Under_90_min_tuning/data.zip')
save_zip_data(a3SampleValidation, 'Data/Validation/3_samples/data.pkl','Data/Validation/3_samples/data.zip')