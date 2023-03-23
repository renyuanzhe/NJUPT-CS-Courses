import numpy as np


def matrixT(A):
	B = [[0] * len(A)] * len(A[0])
	for i in range(len(A)):
		for j in range(len(A[0])):
			B[j][i] = A[i][j]
	return B


def mm(A, B):
    row_len = len(A)
    column_len = len(B[0])
    cross_len = len(B)
    res_mat = [[0] * column_len] * row_len
    for i in range(row_len):
        for j in range(column_len):
            for k in range(cross_len):
                temp = A[i][k] * B[k][j]
                res_mat[i][j] += temp

    print(res_mat)

def myExtGCD(a, b):
    """
    a: 模的取值
    b: 想求逆的值
    """
    if b == 0:
        return 1, 0, a
    else:
        x, y, q = myExtGCD(b, a % b)
        # q = gcd(a, b) = gcd(b, a%b)
        x, y = y, (x - (a // b) * y)
        return x, y, q

print(myExtGCD(26,7))
det=(int)(np.linalg.det([[1,2],[0,3]]))
print(det)
# 2-D array: 2 x 3
two_dim_matrix_one = np.array(
    [[10, 5, 12, 0, 0], [3, 14, 21, 0, 0], [8, 9, 11, 0, 0], [0, 0, 0, 11, 8], [0, 0, 0, 3, 7]])
a = (np.transpose(two_dim_matrix_one))

# 2-D array: 3 x 2
two_dim_matrix_two = np.array([[2, 24, 1, 4, 17]])
print(np.shape(two_dim_matrix_two))
print(np.shape(two_dim_matrix_one))
two_multi_res = mm([[2, 24, 1, 4, 17], [2, 24, 1, 4, 17]],
                   [[10, 5, 12, 0, 0], [3, 14, 21, 0, 0], [8, 9, 11, 0, 0], [0, 0, 0, 11, 8], [0, 0, 0, 3, 7]])

ccc = mm(two_dim_matrix_two, two_dim_matrix_one)
print('two_multi_res: %s' % (two_multi_res))
# print(np.dot(two_dim_matrix_two, two_dim_matrix_one))

# 1-D array
one_dim_vec_one = np.array([1, 2, 3])
one_dim_vec_two = np.array([4, 5, 6])
one_result_res = np.dot(one_dim_vec_one, one_dim_vec_two)
print('one_result_res: %s' % (one_result_res))
dd = [[1, 2, 3], [4, 5, 6]]
print(matrixT([[1, 2, 3], [4, 5, 6]]))
print(dd[0][1])
