import numpy as np

#################################################################
################### jonesjon 932709446 ##########################
#################################################################

#########################################################################################################################
## BEGIN CITATION ---
## This snippet of code was obtained from https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/N-Queens
## This is the code that generates all solutions to the n queens problem in tuple form
## I made some small edits in this code but commented it to show my understanding of the implementation
#########################################################################################################################

#Calls upon other functions that fill a 2d array of solutions to the n queens problem
def queensproblem(n):
    #Keep track of our solutions as we go
    solutions = [[]]
    #Check the first row of our nxn chessboard and generate all column placement solutions for it
    #This is why our tuple solutions get returned in order because we find all column placements for one row and return
    for row in range(n):
        #Add a queen to the board and check for solutions associated with that position
        solutions = add_one_queen(row, n, solutions)
    return solutions

#Using the solutions we've calculated previously we can check for additional solutions here and add that to our solution list
def add_one_queen(new_row, columns, prev_solutions):
    #One very long return statement that uses a set of for loops to iteratively check for solutions
    # If there is no conflict with the new column and the previous solution then add that column to the previous solution
    # Else check another solution and try some columns there
    return [solution + [new_column]
            for solution in prev_solutions
            for new_column in range(columns)
            if no_conflict(new_row, new_column, solution)]

#Now we cycle through all the rows on the board and check if our selected column has issues with any of the row positions
#Returns one big bool that evaluates to false if any of these fail
def no_conflict(new_row, new_column, solution):
    return all(solution[row]       != new_column           and
               solution[row] + row != new_column + new_row and
               solution[row] - row != new_column - new_row
               for row in range(new_row))

###########################################################################################################################
## END CITATION --
###########################################################################################################################

# Generates a set of visual representations of the queens solutions obtained from queensproblem
# 0's represent positions where no queen is present and a 1 indicates the presence of a queen
# Tuples are expanded into 2d arrays called a board here and returned as a set of 2d arrays called boards
def getBoards(n):
    allSolutions = queensproblem(n)
    boards = []
    #Fill the matrices with 2d forms of the solutions
    for aSolution in allSolutions:
        board = []
        #Start filling the rows
        for i in range(0, n):
            sub = [0] * n
            sub[aSolution[i]] = 1
            board.append(sub)
        boards.append(board)
    return boards

#Returns an array of the unique queens n solutions
#Removes repetitive solutions
def getUniqueQueens(n):
    boards = getBoards(n)
    numBoards = len(boards)

    #Check for the case of n=1,2,3
    if numBoards == 1:
        return boards
    elif numBoards == 0:
        print "There are no solutions"
        return []

    #Check each board and remove if we find an equality to a reflection or rotation
    i = 0
    while i < numBoards:
        if numBoards == 1:
            return boards
        board = boards[i]
        #Check check for 3 rotations
        for _ in range(0, 3):
            #Rotate
            board = np.rot90(board)
            #Check for similar
            k = 0
            while k < numBoards:
                #ignore if the current board
                if i == k:
                    k += 1
                    continue
                #Check for equality and remove if equal
                if np.array_equal(board, boards[k]):
                    del boards[k]
                    numBoards -= 1
                k += 1
        #get original again after a final rotation
        board = np.rot90(board)
        #reflect and run again
        board = np.fliplr(board)
        #Check first reflection then rotate
        k = 0
        while k < numBoards:
            #ignore if the current board
            if i == k:
                k += 1
                continue
            #Check for equality and remove if equal
            if np.array_equal(board, boards[k]):
                del boards[k]
                numBoards -= 1
            k += 1

        #Finally, rotate and check 3 times
        for _ in range(0, 3):
            #Rotate
            board = np.rot90(board)
            #Check for similar
            k = 0
            while k < numBoards:
                #ignore if the current board
                if i == k:
                    k += 1
                    continue
                #Check for equality and remove if equal
                if np.array_equal(board, boards[k]):
                    del boards[k]
                    numBoards -= 1
                k += 1
        i += 1
    #Return new boards matrix without the repetitive solutions
    return boards

#main function to print out the solutions
def main():
    n = input("Enter a number n for an n x n board with n queens: ");
    uniqueQueens = getUniqueQueens(n)

    #Print the solutions
    for board in uniqueQueens:
        print "--------------------------------------"
        for row in board:
            print row
    print "--------------------------------------"
    print "The number of unique solutions for a",n,"x",n,"board with",n,"queens is:",len(uniqueQueens)

main()
