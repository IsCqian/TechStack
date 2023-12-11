import time
import svm
import os
import joblib
from pca_process import PCA


def svmtest(model_path):
    recogniton_time = 0.0
    path = '/home/qian/Desktop/hw/SVM'
    tbasePath = os.path.join(path, "data/Mnist-image/test/")
    tcName = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    tst = time.perf_counter()

    allErrCount = 0
    allErrorRate = 0.0
    allScore = 0.0
    #加载模型
    clf = joblib.load(model_path)
    for tcn in tcName:
        testPath = tbasePath + tcn
        # print("class " + tcn + " path is: {}.".format(testPath))
        tflist = svm.get_file_list(testPath)
        # tflist
        tdataMat, tdataLabel = svm.read_and_convert(tflist)


        #tdataMat_pca = PCA(tdataMat,50)


        print("test dataMat shape: {0}, test dataLabel len: {1} ".format(tdataMat.shape, len(tdataLabel)))

        # print("test dataLabel: {}".format(len(tdataLabel)))
        pre_st = time.perf_counter()

        preResult = clf.predict(tdataMat)
        pre_et = time.perf_counter()
        recogniton_time = recogniton_time+ pre_et-pre_st
        print("Recognition  " + tcn + " spent {:.4f}s.".format((pre_et - pre_st)))
        # print("predict result: {}".format(len(preResult)))
        errCount = len([x for x in preResult if x != tcn])
        print("errorCount: {}.".format(errCount))
        allErrCount += errCount
        score_st = time.perf_counter()

        score = clf.score(tdataMat, tdataLabel)
        score_et = time.perf_counter()

        print("computing score spent {:.6f}s.".format(score_et - score_st))
        allScore += score
        print("score: {:.6f}.".format(score))
        print("error rate is {:.6f}.".format((1 - score)))
        print("  ")

    tet =  time.perf_counter()

    print("Testing All class total spent {:.6f}s.".format(tet - tst))
    print("All error Count is: {}.".format(allErrCount))
    avgAccuracy = allScore / 10.0
    print("Average accuracy is: {:.6f}.".format(avgAccuracy))
    print("Average error rate is: {:.6f}.".format(1 - avgAccuracy))
    print("总用时：{:.5f}".format(recogniton_time))


if __name__ == '__main__':
    Accuracy = {}
    path = "/home/qian/Desktop/hw/SVM/"
    model_path=os.path.join(path,'model/poly_ovo.model')
    svmtest(model_path)


