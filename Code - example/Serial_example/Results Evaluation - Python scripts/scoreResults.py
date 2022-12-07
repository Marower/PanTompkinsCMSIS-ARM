import glob
import wfdb
import numpy

folder = 'mit-bih/'
resultDestination = 'results.csv'

f = open(resultDestination, 'w')
f.write('Recording, result file, Normal QRS count, Normal QRS detection, QRS count, TP, FN, FP\n')
f.close()

filecount = 0
annotationFiles = glob.glob(folder + '*.atr')
for annotationsFile in annotationFiles:
    filecount += 1
    print(str(filecount) + '/' + str(len(annotationFiles)))
    path = annotationsFile[0:annotationsFile.find('.atr')]
    fileName = path[path.rfind('\\') + 1:len(path)]
    annotations = wfdb.rdann(path, 'atr')
    for resultFile in glob.glob(path + '*.csv'):
        my_data = numpy.genfromtxt(resultFile, delimiter=',')[:, 1]
        QRS_indexes = numpy.nonzero(my_data)
        QRS = numpy.subtract(QRS_indexes, my_data[QRS_indexes].astype(int))[0, :]
        correctDetection = 0
        Normal_QRS_count = 0
        Normal_QRS_detection = 0
        falseDetection = 0
        missDetection = 0
        i = 0
        for a in annotations.sample:
            if annotations.symbol[i] == 'N':
                Normal_QRS_count += 1

                res = numpy.where((QRS >= (a - 20)) & (QRS <= (a + 20)))

                if any(res):
                    if len(res) == 1:
                        correctDetection += 1
                        QRS = numpy.delete(QRS, res[0])
                        if annotations.symbol[i] == 'N':
                            Normal_QRS_detection += 1
                    else:
                        missDetection += 1
                else:
                    missDetection += 1
            i += 1

        resultString = fileName + ', ' + resultFile + ', ' + str(Normal_QRS_count) + ', ' + str(Normal_QRS_detection)\
                       + ', ' + str(annotations.ann_len) + ', ' + str(correctDetection) + ', ' + str(missDetection) + \
                       ', ' + str(len(QRS)) + '\n'

        f = open(resultDestination, 'a')
        f.write(resultString)
        f.close()
