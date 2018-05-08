#jonesjon 932709446
import math
import time
import numpy as np
import random as rand

#This is the number of terms that the polynomial will have, make sure this is of the form 2^k
SIZE = 8

MULTS = 0

def main():
    poly1 = [0] * SIZE #Initialize polynomials
    poly2 = [0] * SIZE

    generatePolynomials(SIZE, poly1, poly2)
    #print "First polynomial:"
    #printPoly(poly1)
    #print "Second polynomial:"
    #printPoly(poly2)

    print "Iterative multiplication:"
    t1 = time.time()
    r1 = iterMult(poly1, poly2)
    t2 = time.time()
    #printPoly(r1) #Prints out the polynomial
    print "\tIterative Mult took:",(t2-t1),"seconds.\n\tNumber of multiplications: ",MULTS

    globals()['MULTS'] = 0

    print "Divide and Conquer multiplication:"
    t1 = time.time()
    r2 = dnc(poly1, poly2, SIZE)
    t2 = time.time()
    #printPoly(r2) #Prints out the polynomial
    print "\tDivide and Conquer took:",(t2-t1),"seconds.\n\tNumber of multiplications: ",MULTS

    print "Fast Fourier Transform multiplication:"
    t1 = time.time()
    r3 = fourier(poly1, poly2)
    t2 = time.time()
    #printPoly(r3[:-1]) #Prints out the polynomial
    print "\tFourier took:",(t2-t1),"seconds."

def printPoly(a):
    for i in range(0, len(a) - 1):
        a[i]  = int(a[i])
    for i in range(0, len(a)):
        if i == 0:
            print a[i],
        elif i == 1:
            print str(a[i]) + "x",
        else:
            print str(a[i]) + "x^" + str(i),
        if i != (len(a) - 1):
            print " + ",
    print

#######################################################################################################################################################
#   Code derived from this java implementation of the divide and conquer algorithm
#   https://github.com/programmingNinja/Polynomial-multiplication-using-divide-and-conquer-and-its-analysis/blob/master/threeSubProblemQM.java
#######################################################################################################################################################
def dnc(a, b, n):
    #Base case
    if n == 1:
        globals()['MULTS'] += 1
        return a[0] * b[0]

    size = n // 2

    #Split polynomials into their low and their high terms
    aLo = a[:size]
    aHi = a[size:]
    bLo = b[:size]
    bHi = b[size:]

    addLoHiA = [0] * size
    addLoHiB = [0] * size

    for i in range(0, size):
        addLoHiA[i] = aLo[i] + aHi[i]
        addLoHiB[i] = bLo[i] + bHi[i]

    lowAB = dnc(aLo, bLo, size)
    middle = dnc(addLoHiA, addLoHiB, size)
    highAB = dnc(aHi, bHi, size)
    product = [0] * ((n + n) - 1)

    if n == 2:
        for i in range(0, n - 1):
            product[i] += lowAB
            product[i + size] += (middle - lowAB - highAB)
            product[i + (size + size)] += highAB
    else:
        for i in range(0, n - 1):
            product[i] += lowAB[i]
            product[i + size] += (middle[i] - lowAB[i] - highAB[i])
            product[i + (size + size)] += highAB[i]
    return product

###################################################################################
# Written with help from
###################################################################################
def iterMult(a, b):
    #Initialize the size of the resultant array
    result = [0] * (2*SIZE - 1)
    for i in range(0, SIZE):
        for j in range(0, SIZE):
            globals()['MULTS'] += 1
            result[i + j] += a[i] * b[j]
    return result

####################################################################################

#Returns a vector of coefficients
def fourier(a, b):
    #This function uses some python built in functions to get the job done thankfully in one line
    #Goes into the numpy library then its subset of fft functions and calls the rfft rounding fft's
    n = len(a) + len(b);
    solution = np.fft.irfft(np.fft.rfft(a, n) * np.fft.rfft(b, n))
    return solution

#Fills the two arrays passed in with coefficients
def generatePolynomials(n, a, b):
    j = n
    for i in range(0, n):
        a[i] = i + 1
        b[i] = j
        j -= 1


main()
