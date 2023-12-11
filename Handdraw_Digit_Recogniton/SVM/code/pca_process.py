import numpy as np

def PCA(X,k):
    # 输入参数：
    # X: 每一行对应一个样本的特征向量，每一列对应一个特征
    # k：选取的主成分数量

    # 输出参数：
    # W:降维矩阵

    n = X.shape[0]

    ######### 需要你完成: #########
    # 1. 计算数据的均值向量mu
    mu = np.mean(X,axis=0)
    X = X - mu

    # 2. 计算数据的协方差矩阵S
    S = np.cov(X.T)

    # 3. 对S进行特征值分解，求得其特征值L以及对应的特征向量U
    L,U = np.linalg.eig(S)
    L = np.real(L)

    # 4. 选取L中前k个最大的特征值所对应的特征向量构成降维矩阵W
    idx = np.argsort(L)[::-1]
    W = np.real(U[:, idx[:k]])
    ###############################

    Y = np.dot(X,W)

    return Y