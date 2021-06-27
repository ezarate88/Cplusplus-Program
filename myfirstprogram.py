# This Python program has been written to work in conjuction with the C++ file for Corner Grocer. This program will
# open the file provided by Corner Grocer and organize the file to print out the number of sales of each item. 
# This file has also been programed to create a file with the proper counts to allow C++ to use that info and create
# a histogram from that file. 
# Author: Enrique Zarate
# Date: 6/20/2021


import re
import string


# Description: This function will create a list of unique items to eliminate duplicates and use that unique list to see how many 
# times that item is counted in the list of items that includes duplicates. 
# Example of what may be returned:
# Apples: 5
# Zucchini: 3
# Watermelon: 7
def finalSalesList():
    totalList = []
    uniqueList = set()
    with open("PurchaseList.txt") as purchaseList:
        totalList = purchaseList.read().splitlines()
    totalList.sort()
    for x in totalList:
        uniqueList.add(x)
    for x in uniqueList:
        print("{} {}".format(x, totalList.count(x)))


# Description: This function will search specifically for the string provided by the user. 
def searchSalesList(v):
    totalList = []
    with open("PurchaseList.txt") as purchaseList:
        totalList = purchaseList.read().splitlines()
    return totalList.count(v)

# This function is similar to the first in that it organizes the data like the first function but this function also 
# creates a file from that information in order to pass that back to C++ so that C++ can create the histogram from the 
# simplified data. 
def histogramCreator():
    totalList = []
    uniqueList = set()
    with open("PurchaseList.txt") as purchaseList:
        totalList = purchaseList.read().splitlines()
    totalList.sort()
    for x in totalList:
        uniqueList.add(x)
    newFile = open("frequency.dat", "w")
    for x in uniqueList:
        newFile.write("{} {}\n".format(x, totalList.count(x)))
    newFile.close()

    
